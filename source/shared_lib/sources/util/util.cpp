// This file is part of Glest <https://github.com/Glest>
//
// Copyright (C) 2018  The Glest team
//
// Glest is a fork of MegaGlest <https://megaglest.org/>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>

#include "util.h"

#include <ctime>
#include <cassert>
#include <stdexcept>
#include <cstring>
#include <cstdio>
#include <stdarg.h>
#include <time.h>
#include <fcntl.h> // for open()

#ifdef WIN32
#include <io.h> // for open()
#else
#include <unistd.h>
#include <limits.h>
#endif

#include <sys/stat.h> // for open()
#include "platform_util.h"
#include "platform_common.h"
#include "conversion.h"
#include "simple_threads.h"
#include "platform_util.h"
#ifndef WIN32
#include <errno.h>
#endif

#include "leak_dumper.h"

using namespace std;
using namespace Shared::Platform;
using namespace Shared::PlatformCommon;
using namespace Shared::Util;

namespace Shared {
	namespace Util {

		bool GlobalStaticFlags::isNonGraphicalMode = false;
		uint64 GlobalStaticFlags::flags = gsft_none;

		// Init statics
		std::map<SystemFlags::DebugType, SystemFlags::SystemFlagsType> *SystemFlags::debugLogFileList = NULL;
		int SystemFlags::lockFile = -1;
		int SystemFlags::lockFileCountIndex = -1;
		string SystemFlags::lockfilename = "";
		bool SystemFlags::haveSpecialOutputCommandLineOption = false;
		CURL *SystemFlags::curl_handle = NULL;
		bool SystemFlags::curl_global_init_called = false;
		int SystemFlags::DEFAULT_HTTP_TIMEOUT = 10;
		bool SystemFlags::VERBOSE_MODE_ENABLED = false;
		bool SystemFlags::ENABLE_THREADED_LOGGING = false;
		static LogFileThread *threadLogger = NULL;
		bool SystemFlags::SHUTDOWN_PROGRAM_MODE = false;
		//

		static void *myrealloc(void *ptr, size_t size) {
			/* There might be a realloc() out there that doesn't like reallocing
			   NULL pointers, so we take care of it here */
			if (ptr)
				return realloc(ptr, size);
			else
				return malloc(size);
		}

		bool SystemFlags::getThreadedLoggerRunning() {
			return (threadLogger != NULL && threadLogger->getRunningStatus() == true);
		}

		std::size_t SystemFlags::getLogEntryBufferCount() {
			std::size_t ret = 0;
			if (threadLogger != NULL && threadLogger->getRunningStatus() == true) {
				ret = threadLogger->getLogEntryBufferCount();
			}
			return ret;
		}

		size_t SystemFlags::httpWriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data) {
			size_t realsize = size * nmemb;
			struct httpMemoryStruct *mem = (struct httpMemoryStruct *)data;

			mem->memory = (char *) myrealloc(mem->memory, mem->size + realsize + 1);
			if (mem->memory) {
				memcpy(&(mem->memory[mem->size]), ptr, realsize);
				mem->size += realsize;
				mem->memory[mem->size] = 0;
			}
			return realsize;
		}

		std::string SystemFlags::escapeURL(std::string URL, CURL *handle) {
			string result = URL;

			if (handle == NULL) {
				handle = SystemFlags::curl_handle;
			}
			char *escaped = curl_easy_escape(handle, URL.c_str(), 0);
			if (escaped != NULL) {
				result = escaped;
				curl_free(escaped);
			}
			return result;
		}

		std::string SystemFlags::getHTTP(std::string URL, CURL *handle, int timeOut, CURLcode *savedResult) {
			if (handle == NULL) {
				handle = SystemFlags::curl_handle;
			}

			if (SystemFlags::getSystemSettingType(SystemFlags::debugSystem).enabled) SystemFlags::OutputDebug(SystemFlags::debugSystem, "In [%s::%s Line %d]\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);
			curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
			curl_easy_setopt(handle, CURLOPT_URL, URL.c_str());

			/* send all data to this function  */
			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, SystemFlags::httpWriteMemoryCallback);

			struct SystemFlags::httpMemoryStruct chunk;
			chunk.memory = NULL; /* we expect realloc(NULL, size) to work */
			chunk.size = 0;    /* no data at this point */

			/* we pass our 'chunk' struct to the callback function */
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *) &chunk);

			/* some servers don't like requests that are made without a user-agent
			   field, so we provide one */
			curl_easy_setopt(handle, CURLOPT_USERAGENT, "glest-agent/1.0");

			/* follow HTTP redirects (status 3xx), 20 at most */
			curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1);
			curl_easy_setopt(handle, CURLOPT_MAXREDIRS, 20);

			if (SystemFlags::getSystemSettingType(SystemFlags::debugSystem).enabled) SystemFlags::OutputDebug(SystemFlags::debugSystem, "In [%s::%s Line %d] handle = %p\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__, handle);

			if (getSystemSettingType(SystemFlags::debugNetwork).enabled == true) {
				curl_easy_setopt(handle, CURLOPT_VERBOSE, 1);
			}

			if (SystemFlags::getSystemSettingType(SystemFlags::debugSystem).enabled) SystemFlags::OutputDebug(SystemFlags::debugSystem, "In [%s::%s Line %d]\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);

			char errbuf[CURL_ERROR_SIZE] = "";
			curl_easy_setopt(handle, CURLOPT_ERRORBUFFER, errbuf);

			// max X seconds to connect to the URL
			if (timeOut < 0) {
				timeOut = SystemFlags::DEFAULT_HTTP_TIMEOUT;
			}
			curl_easy_setopt(handle, CURLOPT_CONNECTTIMEOUT, timeOut);

			/* get contents from the URL */
			CURLcode result = curl_easy_perform(handle);

			if (SystemFlags::VERBOSE_MODE_ENABLED) printf("CURL result = %d\n", result);
			if (SystemFlags::VERBOSE_MODE_ENABLED) printf("CURL errbuf [%s]\n", errbuf);
			if (SystemFlags::getSystemSettingType(SystemFlags::debugSystem).enabled) SystemFlags::OutputDebug(SystemFlags::debugSystem, "In [%s::%s Line %d] return code [%d] [%s]\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__, result, errbuf);

			std::string serverResponse = (chunk.memory != NULL ? chunk.memory : "");
			if (chunk.memory) {
				free(chunk.memory);
			}

			if (savedResult != NULL) {
				*savedResult = result;
			}
			if (result != CURLE_OK) {
				serverResponse = errbuf;
			}


			if (SystemFlags::getSystemSettingType(SystemFlags::debugSystem).enabled) SystemFlags::OutputDebug(SystemFlags::debugSystem, "In [%s::%s Line %d] serverResponse [%s]\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__, serverResponse.c_str());

			return serverResponse;
		}

		CURL *SystemFlags::initHTTP() {
			if (SystemFlags::curl_global_init_called == false) {
				SystemFlags::curl_global_init_called = true;
				//printf("HTTP init\n");
				if (SystemFlags::getSystemSettingType(SystemFlags::debugSystem).enabled) SystemFlags::OutputDebug(SystemFlags::debugSystem, "In [%s::%s Line %d] calling curl_global_init\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);
				if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line %d] calling curl_global_init\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);
				CURLcode result = curl_global_init(CURL_GLOBAL_ALL);
				if (SystemFlags::getSystemSettingType(SystemFlags::debugSystem).enabled) SystemFlags::OutputDebug(SystemFlags::debugSystem, "In [%s::%s Line %d] curl_global_init called and returned: result %d [%s]\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__, result, curl_easy_strerror(result));
				if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line %d] curl_global_init called and returned: result %d [%s]\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__, result, curl_easy_strerror(result));
				//printf("In [%s::%s Line %d] curl_global_init called and returned: result %d [%s]\n",extractFileFromDirectoryPath(__FILE__).c_str(),__FUNCTION__,__LINE__,result,curl_easy_strerror(result));
			}
			if (SystemFlags::getSystemSettingType(SystemFlags::debugSystem).enabled) SystemFlags::OutputDebug(SystemFlags::debugSystem, "In [%s::%s Line %d] calling curl_easy_init\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);
			if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line %d] calling curl_easy_init\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);
			CURL *handle = curl_easy_init();
			if (handle == NULL) {
				if (SystemFlags::getSystemSettingType(SystemFlags::debugSystem).enabled) SystemFlags::OutputDebug(SystemFlags::debugSystem, "In [%s::%s Line %d] ERROR handle = NULL\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);
				if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line %d] ERROR handle = NULL\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);
			}
			if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line %d] handle = %p\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__, handle);
			curl_easy_setopt(handle, CURLOPT_NOSIGNAL, 1);
			curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1);
			curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
			if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line %d] handle = %p\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__, handle);
			return handle;
		}

		void SystemFlags::globalCleanupHTTP() {

			if (curl_handle != NULL) {
				if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line: %d]\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);
				SystemFlags::cleanupHTTP(&curl_handle, true);
				curl_handle = NULL;
			}

			if (SystemFlags::curl_global_init_called == true) {
				SystemFlags::curl_global_init_called = false;
				//printf("HTTP cleanup\n");
				curl_global_cleanup();
				//printf("In [%s::%s Line %d] curl_global_cleanup called\n",extractFileFromDirectoryPath(__FILE__).c_str(),__FUNCTION__,__LINE__);
			}
		}

		SystemFlags::SystemFlagsType * SystemFlags::setupRequiredMembers() {
			if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line: %d]\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);

			if (threadLogger == NULL && SystemFlags::SHUTDOWN_PROGRAM_MODE == true) {
				//throw game_runtime_error("threadLogger == NULL && SystemFlags::SHUTDOWN_PROGRAM_MODE == true");
				if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line: %d] ERROR threadLogger == NULL && SystemFlags::SHUTDOWN_PROGRAM_MODE == true\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);
				//static SystemFlagsType *result = new SystemFlagsType();
				static SystemFlags::SystemFlagsType result;
				result.enabled = SystemFlags::VERBOSE_MODE_ENABLED;
				return &result;
			} else {
				SystemFlags::init(false);
				return NULL;
			}
		}

		void SystemFlags::init(bool haveSpecialOutputCommandLineOption) {
			SystemFlags::haveSpecialOutputCommandLineOption = haveSpecialOutputCommandLineOption;
			if (SystemFlags::debugLogFileList == NULL) {
				if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line: %d]\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);

				if (threadLogger == NULL && SystemFlags::SHUTDOWN_PROGRAM_MODE == true) {
					//throw game_runtime_error("threadLogger == NULL && SystemFlags::SHUTDOWN_PROGRAM_MODE == true");
					if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line: %d] ERROR threadLogger == NULL && SystemFlags::SHUTDOWN_PROGRAM_MODE == true\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);
					return;
				}

				SystemFlags::debugLogFileList = new std::map<SystemFlags::DebugType, SystemFlags::SystemFlagsType>();

				(*SystemFlags::debugLogFileList)[SystemFlags::debugSystem] = SystemFlags::SystemFlagsType(SystemFlags::debugSystem);
				(*SystemFlags::debugLogFileList)[SystemFlags::debugNetwork] = SystemFlags::SystemFlagsType(SystemFlags::debugNetwork);
				(*SystemFlags::debugLogFileList)[SystemFlags::debugPerformance] = SystemFlags::SystemFlagsType(SystemFlags::debugPerformance);
				(*SystemFlags::debugLogFileList)[SystemFlags::debugWorldSynch] = SystemFlags::SystemFlagsType(SystemFlags::debugWorldSynch);
				(*SystemFlags::debugLogFileList)[SystemFlags::debugUnitCommands] = SystemFlags::SystemFlagsType(SystemFlags::debugUnitCommands);
				(*SystemFlags::debugLogFileList)[SystemFlags::debugPathFinder] = SystemFlags::SystemFlagsType(SystemFlags::debugPathFinder);
				(*SystemFlags::debugLogFileList)[SystemFlags::debugLUA] = SystemFlags::SystemFlagsType(SystemFlags::debugLUA);
				(*SystemFlags::debugLogFileList)[SystemFlags::debugSound] = SystemFlags::SystemFlagsType(SystemFlags::debugSound);
				(*SystemFlags::debugLogFileList)[SystemFlags::debugError] = SystemFlags::SystemFlagsType(SystemFlags::debugError);
			}

			if (threadLogger == NULL && SystemFlags::SHUTDOWN_PROGRAM_MODE == false) {
				if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line: %d]\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);
				threadLogger = new LogFileThread();
				threadLogger->start();
				sleep(1);
			}

			if (SystemFlags::getSystemSettingType(SystemFlags::debugSystem).enabled) SystemFlags::OutputDebug(SystemFlags::debugSystem, "In [%s::%s Line %d]\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);

			if (curl_handle == NULL) {
				if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line: %d]\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);
				if (SystemFlags::getSystemSettingType(SystemFlags::debugSystem).enabled) SystemFlags::OutputDebug(SystemFlags::debugSystem, "In [%s::%s Line %d]\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);

				curl_handle = SystemFlags::initHTTP();

				if (SystemFlags::getSystemSettingType(SystemFlags::debugSystem).enabled) SystemFlags::OutputDebug(SystemFlags::debugSystem, "In [%s::%s Line %d] curl_handle = %p\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__, curl_handle);
			}
		}

		inline bool acquire_file_lock(int hnd) {
#ifndef WIN32
			struct ::flock lock;
			// Initialize the flock structure.
			memset(&lock, 0, sizeof(lock));
			lock.l_type = F_WRLCK;
			lock.l_whence = SEEK_SET;
			lock.l_start = 0;
			lock.l_len = 0;
			lock.l_pid = 0;
			return -1 != ::fcntl(hnd, F_SETLK, &lock);
#else
			HANDLE hFile = (HANDLE) _get_osfhandle(hnd);
			return TRUE == ::LockFile(hFile, 0, 0, 0, -0x10000);
#endif
		}

		SystemFlags::SystemFlags() {

		}

		void SystemFlags::cleanupHTTP(CURL **handle, bool globalCleanup) {
			if (handle != NULL && *handle != NULL) {
				curl_easy_cleanup(*handle);
				*handle = NULL;

				if (globalCleanup == true) {
					SystemFlags::globalCleanupHTTP();
				}
			}
		}

		SystemFlags::~SystemFlags() {
			SystemFlags::Close();

			if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line: %d]\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);

			SystemFlags::globalCleanupHTTP();

			if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line: %d]\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);
		}

		void SystemFlags::Close() {
			if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line: %d]\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);

			if (threadLogger != NULL) {
				SystemFlags::ENABLE_THREADED_LOGGING = false;
				//SystemFlags::SHUTDOWN_PROGRAM_MODE=true;
				time_t elapsed = time(NULL);
				threadLogger->signalQuit();
				if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line: %d]\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);
				//threadLogger->shutdownAndWait();
				for (; threadLogger->canShutdown(false) == false &&
					difftime(time(NULL), elapsed) <= 15;) {
					//sleep(150);
				}
				if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line: %d]\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);
				//		if(threadLogger->canShutdown(false)) {
				//			Sleep(0);
				//		}
				if (threadLogger->shutdownAndWait() == true) {
					if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line: %d]\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);
					delete threadLogger;
					if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line: %d]\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);
				}
				threadLogger = NULL;
				//delete threadLogger;
				//threadLogger = NULL;
				if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line: %d]\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);
			}

			if (SystemFlags::debugLogFileList != NULL) {
				if (SystemFlags::haveSpecialOutputCommandLineOption == false) {
					if (SystemFlags::VERBOSE_MODE_ENABLED) printf("START Closing logfiles\n");
				}

				for (std::map<SystemFlags::DebugType, SystemFlags::SystemFlagsType>::iterator iterMap = SystemFlags::debugLogFileList->begin();
					iterMap != SystemFlags::debugLogFileList->end(); ++iterMap) {
					SystemFlags::SystemFlagsType &currentDebugLog = iterMap->second;
					currentDebugLog.Close();
				}

				delete SystemFlags::debugLogFileList;
				SystemFlags::debugLogFileList = NULL;
			}
			if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line: %d]\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);

			if (SystemFlags::lockFile != -1) {
#ifndef WIN32
				close(SystemFlags::lockFile);
#else
				_close(SystemFlags::lockFile);
#endif
				SystemFlags::lockFile = -1;
				SystemFlags::lockFileCountIndex = -1;

				if (SystemFlags::lockfilename != "") {
					int remove_result = remove(SystemFlags::lockfilename.c_str());

					if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line: %d] remove_result = %d for file [%s]\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__, remove_result, SystemFlags::lockfilename.c_str());

					SystemFlags::lockfilename = "";
				}
			}

			if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line: %d]\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);

			if (SystemFlags::debugLogFileList != NULL) {
				if (SystemFlags::haveSpecialOutputCommandLineOption == false) {
					if (SystemFlags::VERBOSE_MODE_ENABLED) printf("END Closing logfiles\n");
				}
			}

			if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line: %d]\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);
		}

		void SystemFlags::handleDebug(DebugType type, const char *fmt, ...) {
			if (SystemFlags::debugLogFileList == NULL) {
				if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line: %d]\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);

				if (threadLogger == NULL && SystemFlags::SHUTDOWN_PROGRAM_MODE == true) {
					//throw game_runtime_error("threadLogger == NULL && SystemFlags::SHUTDOWN_PROGRAM_MODE == true");
					if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line: %d] ERROR threadLogger == NULL && SystemFlags::SHUTDOWN_PROGRAM_MODE == true\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);
					//return;
				}

				SystemFlags::init(false);
			}
			//SystemFlags::SystemFlagsType &currentDebugLog = (*SystemFlags::debugLogFileList)[type];
			SystemFlags::SystemFlagsType &currentDebugLog = getSystemSettingType(type);
			if (currentDebugLog.enabled == false) {
				return;
			}

			va_list argList;
			va_start(argList, fmt);

			const int max_debug_buffer_size = 8096;
			char szBuf[max_debug_buffer_size] = "";
			vsnprintf(szBuf, max_debug_buffer_size - 1, fmt, argList);
			va_end(argList);

			if (currentDebugLog.debugLogFileName != "" &&
				SystemFlags::ENABLE_THREADED_LOGGING &&
				threadLogger != NULL &&
				threadLogger->getRunningStatus() == true) {
				threadLogger->addLogEntry(type, szBuf);
			} else {
				// Get the current time.
				time_t curtime = time(NULL);
				logDebugEntry(type, (szBuf[0] != '\0' ? szBuf : ""), curtime);
			}
		}


		void SystemFlags::logDebugEntry(DebugType type, string debugEntry, time_t debugTime) {
			if (SystemFlags::debugLogFileList == NULL) {
				if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line: %d]\n", extractFileFromDirectoryPath(__FILE__).c_str(), __FUNCTION__, __LINE__);
				SystemFlags::init(false);
			}
			//SystemFlags::SystemFlagsType &currentDebugLog = (*SystemFlags::debugLogFileList)[type];
			SystemFlags::SystemFlagsType &currentDebugLog = getSystemSettingType(type);
			if (currentDebugLog.enabled == false) {
				return;
			}

			char szBuf2[100] = "";
			//if (type != debugPathFinder && type != debugError && type != debugWorldSynch) {
			if (type != debugPathFinder && type != debugWorldSynch) {
				// Get the current time.
			//    time_t curtime = time (NULL);
				// Convert it to local time representation.
				//struct tm *loctime = localtime (&debugTime);
				std::tm loctime = threadsafe_localtime(debugTime);
				strftime(szBuf2, 100, "%Y-%m-%d %H:%M:%S", &loctime);
			}
			/*
				va_list argList;
				va_start(argList, fmt);

				const int max_debug_buffer_size = 8096;
				char szBuf[max_debug_buffer_size]="";
				vsnprintf(szBuf,max_debug_buffer_size-1,fmt, argList);
			*/
			// Either output to a logfile or
			if (currentDebugLog.debugLogFileName != "") {
				if (currentDebugLog.fileStream == NULL ||
					currentDebugLog.fileStream->is_open() == false) {

					// If the file is already open (shared) by another debug type
					// do not over-write the file but share the stream pointer
					if (SystemFlags::debugLogFileList != NULL) {
						for (std::map<SystemFlags::DebugType, SystemFlags::SystemFlagsType>::iterator iterMap = SystemFlags::debugLogFileList->begin();
							iterMap != SystemFlags::debugLogFileList->end(); ++iterMap) {
							SystemFlags::SystemFlagsType &currentDebugLog2 = iterMap->second;

							if (iterMap->first != type &&
								currentDebugLog.debugLogFileName == currentDebugLog2.debugLogFileName &&
								currentDebugLog2.fileStream != NULL) {
								currentDebugLog.fileStream = currentDebugLog2.fileStream;
								currentDebugLog.fileStreamOwner = false;
								currentDebugLog.mutex = currentDebugLog2.mutex;
								break;
							}
						}
					}

					string debugLog = currentDebugLog.debugLogFileName;

					if (SystemFlags::lockFile == -1) {
						const string lock_file_name = "debug.lck";
						string lockfile = extractDirectoryPathFromFile(debugLog);
						lockfile += lock_file_name;
						SystemFlags::lockfilename = lockfile;

#ifndef WIN32
						//SystemFlags::lockFile = open(lockfile.c_str(), O_WRONLY | O_CREAT | O_EXCL, S_IRUSR|S_IWUSR);
						SystemFlags::lockFile = open(lockfile.c_str(), O_WRONLY | O_CREAT, S_IREAD | S_IWRITE);
#else
						SystemFlags::lockFile = _open(lockfile.c_str(), O_WRONLY | O_CREAT, S_IREAD | S_IWRITE);
#endif
						if (SystemFlags::lockFile < 0 || acquire_file_lock(SystemFlags::lockFile) == false) {
							string newlockfile = lockfile;
							int idx = 1;
							for (idx = 1; idx <= 100; ++idx) {
								newlockfile = lockfile + intToStr(idx);

								if (SystemFlags::lockFile != -1) {
#ifndef WIN32
									close(SystemFlags::lockFile);
#else
									_close(SystemFlags::lockFile);
#endif
									SystemFlags::lockFile = -1;
									SystemFlags::lockFileCountIndex = -1;
								}
								//SystemFlags::lockFile = open(newlockfile.c_str(), O_WRONLY | O_CREAT | O_EXCL, S_IRUSR|S_IWUSR);
#ifndef WIN32
								SystemFlags::lockFile = open(newlockfile.c_str(), O_WRONLY | O_CREAT, S_IREAD | S_IWRITE);
#else
								SystemFlags::lockFile = _open(newlockfile.c_str(), O_WRONLY | O_CREAT, S_IREAD | S_IWRITE);

#endif
								if (SystemFlags::lockFile >= 0 && acquire_file_lock(SystemFlags::lockFile) == true) {
									break;
								}
							}

							SystemFlags::lockFileCountIndex = idx;
							SystemFlags::lockfilename = newlockfile;
							debugLog += intToStr(idx);

							if (SystemFlags::haveSpecialOutputCommandLineOption == false) {
								if (SystemFlags::VERBOSE_MODE_ENABLED) printf("Opening additional logfile [%s]\n", debugLog.c_str());
							}
						}
					} else if (SystemFlags::lockFileCountIndex > 0) {
						debugLog += intToStr(SystemFlags::lockFileCountIndex);

						if (SystemFlags::haveSpecialOutputCommandLineOption == false) {
							if (SystemFlags::VERBOSE_MODE_ENABLED) printf("Opening additional logfile [%s]\n", debugLog.c_str());
						}
					}

					if (currentDebugLog.fileStream == NULL) {
#if defined(WIN32) && !defined(__MINGW32__)
						currentDebugLog.fileStream = new std::ofstream(_wfopen(utf8_decode(debugLog).c_str(), L"w"));
#else
						currentDebugLog.fileStream = new std::ofstream();
						currentDebugLog.fileStream->open(debugLog.c_str(), ios_base::out | ios_base::trunc);
#endif
						currentDebugLog.fileStreamOwner = true;
						currentDebugLog.mutex = new Mutex(CODE_AT_LINE);
					}

					if (SystemFlags::haveSpecialOutputCommandLineOption == false) {
						if (SystemFlags::VERBOSE_MODE_ENABLED) printf("Opening logfile [%s] type = %d, currentDebugLog.fileStreamOwner = %d, file stream open = %d\n", debugLog.c_str(), type, currentDebugLog.fileStreamOwner, currentDebugLog.fileStream->is_open());
					}

					if (currentDebugLog.fileStream->is_open() == true) {
						MutexSafeWrapper safeMutex(currentDebugLog.mutex, string(extractFileFromDirectoryPath(__FILE__).c_str()) + "_" + intToStr(__LINE__));

						(*currentDebugLog.fileStream) << "Starting Glest logging for type: " << type << "\n";
						(*currentDebugLog.fileStream).flush();

						safeMutex.ReleaseLock();
					}
				}

				assert(currentDebugLog.fileStream != NULL);

				if (currentDebugLog.fileStream->is_open() == true) {
					static string mutexCodeLocation = string(extractFileFromDirectoryPath(__FILE__).c_str()) + "_" + intToStr(__LINE__);
					MutexSafeWrapper safeMutex(currentDebugLog.mutex, mutexCodeLocation);

					// All items in the if clause we don't want timestamps
					if (type != debugPathFinder && type != debugError && type != debugWorldSynch) {
						(*currentDebugLog.fileStream) << "[" << szBuf2 << "] " << debugEntry.c_str();
					} else if (type == debugError) {
						(*currentDebugLog.fileStream) << "[" << szBuf2 << "] *ERROR* " << debugEntry.c_str();
					} else {
						(*currentDebugLog.fileStream) << debugEntry.c_str();
					}
					(*currentDebugLog.fileStream).flush();

					safeMutex.ReleaseLock();
				}
			}

			// output to console
			if (currentDebugLog.debugLogFileName == "" ||
				(currentDebugLog.debugLogFileName != "" &&
				(currentDebugLog.fileStream == NULL ||
					currentDebugLog.fileStream->is_open() == false))) {

				if (type != debugPathFinder && type != debugError) {
					printf("[%s] %s", szBuf2, debugEntry.c_str());
				} else if (type == debugError) {
					printf("*ERROR* [%s] %s", szBuf2, debugEntry.c_str());
				} else {
					printf("%s", debugEntry.c_str());
				}
			}
		}


		string lastDir(const string &s) {
			size_t i = s.find_last_of('/');
			size_t j = s.find_last_of('\\');
			size_t pos;

			if (i == string::npos) {
				pos = j;
			} else if (j == string::npos) {
				pos = i;
			} else {
				pos = i < j ? j : i;
			}

			if (pos == string::npos) {
				throw game_runtime_error(string(extractFileFromDirectoryPath(__FILE__).c_str()) + " line: " + intToStr(__LINE__) + " pos == string::npos for [" + s + "]");
			}

			if (pos + 1 == s.length() && s.length() > 0 &&
				(s[pos] == '/' || s[pos] == '\\')) {
				string retry = s.substr(0, pos);
				return lastDir(retry);
			}
			string result = (s.empty() == false ? s.substr(pos + 1, s.length()) : "");
			replaceAll(result, "/", "");
			replaceAll(result, "\\", "");

			//printf("=-=-=-=- LASTDIR in [%s] out [%s]\n",s.c_str(),result.c_str());

			return result;
		}

		string lastFile(const string &s) {
			return lastDir(s);
		}

		string cutLastFile(const string &s) {
			size_t i = s.find_last_of('/');
			size_t j = s.find_last_of('\\');
			size_t pos;

			if (i == string::npos) {
				pos = j;
			} else if (j == string::npos) {
				pos = i;
			} else {
				pos = i < j ? j : i;
			}

			if (pos != string::npos) {
				//throw game_runtime_error(string(extractFileFromDirectoryPath(__FILE__).c_str()) + " line: " + intToStr(__LINE__) + " pos == string::npos for [" + s + "]");
			//}

				return (s.substr(0, pos));
			}
			return s;
		}

		string cutLastExt(const string &s) {
			size_t i = s.find_last_of('.');
			if (i != string::npos) {
				//throw game_runtime_error(string(extractFileFromDirectoryPath(__FILE__).c_str()) + " line: " + intToStr(__LINE__) + " i==string::npos for [" + s + "]");
		   //}

				return (s.substr(0, i));
			}
			return s;
		}

		string ext(const string &s) {
			size_t i;

			i = s.find_last_of('.') + 1;

			if (i != string::npos) {
				//throw game_runtime_error(string(extractFileFromDirectoryPath(__FILE__).c_str()) + " line: " + intToStr(__LINE__) + " i==string::npos for [" + s + "]");
		   //}
				return (s.substr(i, s.size() - i));
			}
			return "";
		}

		string replaceBy(const string &s, char c1, char c2) {
			string rs = s;

			for (size_t i = 0; i < s.size(); ++i) {
				if (rs[i] == c1) {
					rs[i] = c2;
				}
			}

			return rs;
		}

		vector<string> split(string s, string d) {
			vector<string> results;

			if (s.empty() == false) {
				size_t lastOffset = 0;

				while (true) {
					size_t offset = s.find_first_of(d, lastOffset);
					results.push_back(s.substr(lastOffset, offset - lastOffset));
					if (offset == string::npos)
						break;
					else
						lastOffset = offset + d.size(); //skip the delimiter
				}
			}
			return results;
		}

		string toLower(const string &s) {
			string rs = s;

			for (size_t i = 0; i < s.size(); ++i) {
				rs[i] = tolower(s[i]);
			}

			return rs;
		}

		bool compareNonCaseSensitive(const string &a, const string &b) {
			return (toLower(a) < toLower(b));
		}

		//void copyStringToBuffer(char *buffer, int bufferSize, const string& s){
		//	strncpy(buffer, s.c_str(), bufferSize-1);
		//	buffer[bufferSize-1]= '\0';
		//}

		// ==================== numeric fcs ====================

		//float saturate(float value) {
		//	if (value < 0.f){
		//        return 0.f;
		//	}
		//	if (value > 1.f){
		//        return 1.f;
		//	}
		//    return value;
		//}

		int clamp(int value, int min, int max) {
			if (value < min) {
				return min;
			}
			if (value > max) {
				return max;
			}
			return value;
		}

		int64 clamp(int64 value, int64 min, int64 max) {
			if (value < min) {
				return min;
			}
			if (value > max) {
				return max;
			}
			return value;
		}

		float clamp(float value, float min, float max) {
			if (value < min) {
				return min;
			}
			if (value > max) {
				return max;
			}
			return value;
		}

		//int round(float f){
		//     return (int) f;
		//}

		string trimAllExceptNumbersAndPeriods(string str) {
			char current;
			size_t startIndex, endIndex;
			for (startIndex = 0; startIndex < str.length(); startIndex++) {
				current = str[startIndex];
				if ((current >= '0' && current <= '9') || current == '.')
					break;
			}
			for (endIndex = str.length() - 1; endIndex > startIndex; endIndex--) {
				current = str[endIndex];
				if ((current >= '0' && current <= '9') || current == '.')
					break;
			}
			return str.substr(startIndex, (endIndex - startIndex) + 1);
		}

		// ==================== misc ====================
		int compareMajorMinorVersion(const string &versionA, const string &versionB) {
			if (versionA == versionB)
				return 0;
			string verA = trimAllExceptNumbersAndPeriods(versionA);
			string verB = trimAllExceptNumbersAndPeriods(versionB);
			int majorA = getMajor(verA);
			int minorA = getMinor(verA);
			int majorB = getMajor(verB);
			int minorB = getMinor(verB);

			//printf("majorA:%d  minorA:%d majorB:%d minorB:%d\n",majorA,minorA,majorB,minorB);
			if (majorA < majorB) {
				return -1;
			} else if (majorA == majorB) {
				if (minorA < minorB) {
					return -1;
				} else if (minorA == minorB) {
					return 0;
				} else {
					return 1;
				}
			} else {
				return 1;
			}
		}

		int getMajor(string version) {
			vector<string> parts;

			if (version.empty() == false) {
				parts = split(version.substr(1), ".");
			}

			if (parts.size() > 1 && parts[0] != "" && IsNumeric(parts[0].c_str(), false)) {
				return strToInt(parts[0]);
			} else {
				return 0;
			}
		}

		int getMinor(string version) {
			vector<string> parts;

			if (version.empty() == false) {
				parts = split(version.substr(1), ".");
			}
			if (parts.size() > 1 && parts[1] != "") {
				string resultStr = "";
				for (int i = 0; i < (int) parts[1].length(); ++i) {
					// just add leading numbers
					if (IsNumeric((resultStr + parts[1][i]).c_str(), false)) {
						resultStr += parts[1][i];
					} else {
						break;
					}
				}
				if (resultStr == "") {
					return 0;
				} else {
					return strToInt(resultStr);
				}
			} else {
				return 0;
			}
		}

#ifdef __unix__
        std::string getExecPath() {
            char buff[PATH_MAX];
#ifdef __linux__
            ssize_t len = ::readlink("/proc/self/exe", buff, sizeof(buff)-1);
#else
            // e.g. for FreeBSD with procfs installed.
            ssize_t len = ::readlink("/proc/curproc/file", buff, sizeof(buff)-1);
#endif // __linux__
            if (len != -1) {
                  buff[len] = '\0';
                  return std::string(buff);
            }
            /* handle error condition */
            return std::string("");
        }
#endif // __linux__
        void eraseSubStr(std::string & mainStr, const std::string & toErase)
        {
            // Search for the substring in string
            size_t pos = mainStr.find(toErase);

            if (pos != std::string::npos)
            {
                // If found then erase it from string
                mainStr.erase(pos, toErase.length());
            }
        }


#if defined(DATADIR) && defined(BINDIR) && defined(__unix__)
        string getDatPath() {
            string curPath = getExecPath();
            const string subBinPath = endPathWithSlash(formatPath(TOSTRING(BINDIR))) + "glest";
            eraseSubStr(curPath, subBinPath);
            string datPath = curPath + endPathWithSlash(TOSTRING(DATADIR));
            return datPath;
        }
#endif
	}
} //end namespace
