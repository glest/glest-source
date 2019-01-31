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

#ifndef _SHARED_PLATFORMCOMMON_BASETHREAD_H_
#define _SHARED_PLATFORMCOMMON_BASETHREAD_H_

#include "leak_dumper.h"
#include "thread.h"
#include <string>
#include <map>

using namespace Shared::Platform;
using namespace std;

namespace Shared {
	namespace PlatformCommon {

		// =====================================================
		//	class BaseThread
		// =====================================================

		class BaseThread : public Thread {
		protected:
			Mutex *mutexRunning;
			Mutex *mutexQuit;
			Mutex *mutexBeginExecution;
			Mutex *mutexDeleteSelfOnExecutionDone;

			Mutex *mutexThreadObjectAccessor;

			bool threadOwnerValid;
			Mutex *mutexThreadOwnerValid;

			Mutex *mutexExecutingTask;
			bool executingTask;

			void *ptr;
			static Mutex mutexMasterThreadList;
			static std::map<void *, int> masterThreadList;

			bool quit;
			bool running;
			string uniqueID;
			bool hasBeginExecution;
			bool deleteSelfOnExecutionDone;

			Mutex *mutexStarted;
			bool started;

			virtual void setQuitStatus(bool value);
			void deleteSelfIfRequired();

			void *genericData;


		public:
			BaseThread();
			virtual ~BaseThread();
			virtual void execute() = 0;

			virtual void signalQuit();
			virtual bool getQuitStatus();
			virtual bool getRunningStatus();

			virtual bool getStarted();
			virtual void setStarted(bool value);

			virtual bool getHasBeginExecution();
			virtual void setHasBeginExecution(bool value);

			static bool shutdownAndWait(BaseThread *ppThread);
			virtual bool shutdownAndWait();
			virtual bool canShutdown(bool deleteSelfIfShutdownDelayed = false);

			virtual bool getDeleteSelfOnExecutionDone();
			virtual void setDeleteSelfOnExecutionDone(bool value);

			void setUniqueID(string value) {
				uniqueID = value;
			}
			string getUniqueID() {
				return uniqueID;
			}

			virtual void setRunningStatus(bool value);

			void setExecutingTask(bool value);
			bool getExecutingTask();


			void setThreadOwnerValid(bool value);
			bool getThreadOwnerValid();
			Mutex * getMutexThreadOwnerValid();

			Mutex * getMutexThreadObjectAccessor();

			template <typename T>
			T * getGenericData() {
				return genericData;
			}
			template <typename T>
			void setGenericData(T *value) {
				genericData = value;
			}

			static bool isThreadDeleted(void *ptr);
		};

		class RunningStatusSafeWrapper {
		protected:
			BaseThread *thread;
		public:

			RunningStatusSafeWrapper(BaseThread *thread) {
				this->thread = thread;
				Enable();
			}
			~RunningStatusSafeWrapper() {
				Disable();
			}

			void Enable() {
				if (this->thread != NULL) {
					this->thread->setRunningStatus(true);
				}
			}
			void Disable() {
				if (this->thread != NULL) {
					this->thread->setRunningStatus(false);
				}
			}
		};

		class ExecutingTaskSafeWrapper {
		protected:
			BaseThread *thread;
		public:

			ExecutingTaskSafeWrapper(BaseThread *thread) {
				this->thread = thread;
				Enable();
			}
			~ExecutingTaskSafeWrapper() {
				Disable();
			}

			void Enable() {
				if (this->thread != NULL) {
					this->thread->setExecutingTask(true);
				}
			}
			void Disable() {
				if (this->thread != NULL) {
					this->thread->setExecutingTask(false);
				}
			}
		};


	}
} //end namespace

#endif
