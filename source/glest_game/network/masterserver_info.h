// This file is part of ZetaGlest <https://github.com/ZetaGlest>
//
// Copyright (C) 2018  The ZetaGlest team
//
// ZetaGlest is a fork of MegaGlest <https://megaglest.org>
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

#ifndef _GLEST_GAME_MASTERSERVERINFO_H_
#define _GLEST_GAME_MASTERSERVERINFO_H_

#include <string>
#include "game_constants.h"
#include "leak_dumper.h"

using std::string;

namespace ZetaGlest {
	namespace Game {

		// ===========================================================
		//	class ParticleSystemType 
		//
		///	A type of particle system
		// ===========================================================

		class MasterServerInfo {
		protected:
			//general info:
			string glestVersion;
			string platform;
			string binaryCompileDate;

			//game info:
			string serverTitle;
			string ipAddress;

			//game setup info:
			string tech;
			string map;
			string tileset;
			int activeSlots;
			int networkSlots;
			int connectedClients;
			int externalconnectport;
			string country;
			int status;

		public:
			const string &getGlestVersion() const {
				return glestVersion;
			}
			const string &getPlatform() const {
				return platform;
			}
			const string &getBinaryCompileDate() const {
				return binaryCompileDate;
			}

			const string &getServerTitle() const {
				return serverTitle;
			}
			const string &getIpAddress() const {
				return ipAddress;
			}

			const string &getTech() const {
				return tech;
			}
			const string &getMap() const {
				return map;
			}
			const string &getTileset() const {
				return tileset;
			}
			const int getActiveSlots() const {
				return activeSlots;
			}
			const int getNetworkSlots() const {
				return networkSlots;
			}
			const int getConnectedClients() const {
				return connectedClients;
			}
			const int getExternalConnectPort() const {
				return externalconnectport;
			}
			const string &getCountry() const {
				return country;
			}
			const int getStatus() const {
				return status;
			}


			//general info:
			void setGlestVersion(string value) {
				glestVersion = value;
			}
			void setPlatform(string value) {
				platform = value;
			}
			void setBinaryCompileDate(string value) {
				binaryCompileDate = value;
			}

			//game info:
			void setServerTitle(string value) {
				serverTitle = value;
			}
			void setIpAddress(string value) {
				ipAddress = value;
			}

			//game setup info:
			void setTech(string value) {
				tech = value;
			}
			void setMap(string value) {
				map = value;
			}
			void setTileset(string value) {
				tileset = value;
			}

			void setActiveSlots(int value) {
				activeSlots = value;
			}
			void setNetworkSlots(int value) {
				networkSlots = value;
			}
			void setConnectedClients(int value) {
				connectedClients = value;
			}
			void setExternalConnectPort(int value) {
				externalconnectport = value;
			}
			void setCountry(string value) {
				country = value;
			}
			void setStatus(int value) {
				status = value;
			}
		};

	}
}//end namespace

#endif
