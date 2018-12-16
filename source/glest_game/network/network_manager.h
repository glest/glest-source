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

#ifndef _NETWORKMANAGER_H_
#define _NETWORKMANAGER_H_

#include <cassert>
#include "socket.h"
#include "checksum.h"
#include "server_interface.h"
#include "client_interface.h"
#include "leak_dumper.h"

using Shared::Util::Checksum;

namespace Game {
	// =====================================================
	//	class NetworkManager
	// =====================================================

	class NetworkManager {
	private:
		GameNetworkInterface * gameNetworkInterface;
		NetworkRole networkRole;

	public:
		static NetworkManager &getInstance();

		NetworkManager();
		virtual ~NetworkManager();

		void init(NetworkRole networkRole, bool publishEnabled = false);
		void end();
		void update();

		bool isNetworkGame();
		bool isNetworkGameWithConnectedClients();

		GameNetworkInterface* getGameNetworkInterface(bool throwErrorOnNull = true);
		ServerInterface* getServerInterface(bool throwErrorOnNull = true);
		ClientInterface* getClientInterface(bool throwErrorOnNull = true);
		NetworkRole getNetworkRole() const {
			return networkRole;
		}

		void setNetworkRole(NetworkRole role) {
			networkRole = role;
		}

		void initServerInterfaces(ClientLagCallbackInterface *intf);
	};

} //end namespace

#endif
