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

#ifndef _SHARED_PLATFORMCOMMON_MINIFTPSERVERTHREAD_H_
#define _SHARED_PLATFORMCOMMON_MINIFTPSERVERTHREAD_H_

#ifdef WIN32
#include <winsock2.h>
#include <winsock.h>
#endif

#include "base_thread.h"
#include <vector>
#include <string>
#include "data_types.h"
#include "socket.h"

#include "leak_dumper.h"

using namespace std;

namespace Shared {
	namespace PlatformCommon {

		// =====================================================
		//	class FTPServerThread
		// =====================================================

		class FTPServerThread : public BaseThread {
		protected:
			std::pair<string, string> mapsPath;
			std::pair<string, string> tilesetsPath;
			std::pair<string, string> techtreesPath;
			string tempFilesPath;

			int portNumber;
			int maxPlayers;
			static FTPClientValidationInterface *ftpValidationIntf;

			bool internetEnabled;
			bool allowInternetTilesetFileTransfers;
			bool allowInternetTechtreeFileTransfers;

		public:

			FTPServerThread(std::pair<string, string> mapsPath,
				std::pair<string, string> tilesetsPath, std::pair<string, string> techtreesPath,
				bool internetEnabledFlag,
				bool allowInternetTilesetFileTransfers, bool allowInternetTechtreeFileTransfers,
				int portNumber, int maxPlayers, FTPClientValidationInterface *ftpValidationIntf,
				string tempFilesPath);
			~FTPServerThread();
			virtual void execute();
			virtual void signalQuit();
			virtual bool shutdownAndWait();

			void setInternetEnabled(bool value, bool forceChange = false);
			static void addClientToServerIPAddress(uint32 clientIp, uint32 ServerIp);
			static FTPClientValidationInterface * getFtpValidationIntf() {
				return ftpValidationIntf;
			}

		};

	}
} //end namespace

#endif
