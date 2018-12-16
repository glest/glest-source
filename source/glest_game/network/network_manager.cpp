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

#include "network_manager.h"
#include "util.h"
#include "leak_dumper.h"

using namespace Shared::Util;

namespace Game {
	// =====================================================
	//	class NetworkManager
	// =====================================================

	NetworkManager &NetworkManager::getInstance() {
		static NetworkManager networkManager;
		return networkManager;
	}

	NetworkManager::NetworkManager() {
		if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line: %d]\n", __FILE__, __FUNCTION__, __LINE__);

		gameNetworkInterface = NULL;
		networkRole = nrIdle;

		if (SystemFlags::getSystemSettingType(SystemFlags::debugNetwork).enabled) SystemFlags::OutputDebug(SystemFlags::debugNetwork, "In [%s::%s Line: %d] this->networkRole = %d gameNetworkInterface [%p]\n", __FILE__, __FUNCTION__, __LINE__, this->networkRole, gameNetworkInterface);
	}

	NetworkManager::~NetworkManager() {
		end();
	}

	void NetworkManager::init(NetworkRole networkRole, bool publishEnabled) {
		if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line: %d]\n", __FILE__, __FUNCTION__, __LINE__);
		if (SystemFlags::getSystemSettingType(SystemFlags::debugNetwork).enabled) SystemFlags::OutputDebug(SystemFlags::debugNetwork, "In [%s::%s Line: %d] this->networkRole = %d, networkRole = %d, gameNetworkInterface [%p]\n", __FILE__, __FUNCTION__, __LINE__, this->networkRole, networkRole, gameNetworkInterface);

		//assert(gameNetworkInterface==NULL);
		NetworkMessage::resetNetworkPacketStats();
		this->networkRole = networkRole;

		if (networkRole == nrServer) {
			if (SystemFlags::getSystemSettingType(SystemFlags::debugNetwork).enabled) SystemFlags::OutputDebug(SystemFlags::debugNetwork, "In [%s::%s Line: %d] this->networkRole = %d, networkRole = %d, gameNetworkInterface [%p]\n", __FILE__, __FUNCTION__, __LINE__, this->networkRole, networkRole, gameNetworkInterface);
			gameNetworkInterface = new ServerInterface(publishEnabled, NULL);
		} else {
			if (SystemFlags::getSystemSettingType(SystemFlags::debugNetwork).enabled) SystemFlags::OutputDebug(SystemFlags::debugNetwork, "In [%s::%s Line: %d] this->networkRole = %d, networkRole = %d, gameNetworkInterface [%p]\n", __FILE__, __FUNCTION__, __LINE__, this->networkRole, networkRole, gameNetworkInterface);
			gameNetworkInterface = new ClientInterface();
		}

		//printf("==========] CREATING gameNetworkInterface [%p]\n",gameNetworkInterface);

		if (SystemFlags::getSystemSettingType(SystemFlags::debugNetwork).enabled) SystemFlags::OutputDebug(SystemFlags::debugNetwork, "In [%s::%s Line: %d] this->networkRole = %d gameNetworkInterface [%p]\n", __FILE__, __FUNCTION__, __LINE__, this->networkRole, gameNetworkInterface);
	}

	void NetworkManager::initServerInterfaces(ClientLagCallbackInterface *intf) {
		ServerInterface *server = getServerInterface();
		server->setClientLagCallbackInterface(intf);
	}

	void NetworkManager::end() {
		if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line: %d]\n", __FILE__, __FUNCTION__, __LINE__);
		if (SystemFlags::getSystemSettingType(SystemFlags::debugNetwork).enabled) SystemFlags::OutputDebug(SystemFlags::debugNetwork, "In [%s::%s Line: %d] this->networkRole = %d gameNetworkInterface [%p]\n", __FILE__, __FUNCTION__, __LINE__, this->networkRole, gameNetworkInterface);
		//printf("In [%s::%s] Line: %d gameNetworkInterface = %p\n",__FILE__,__FUNCTION__,__LINE__,gameNetworkInterface);
		//printf("==========] DELETING gameNetworkInterface [%p]\n",gameNetworkInterface);

		delete gameNetworkInterface;
		gameNetworkInterface = NULL;
		networkRole = nrIdle;

		if (SystemFlags::VERBOSE_MODE_ENABLED) printf("In [%s::%s Line: %d]\n", __FILE__, __FUNCTION__, __LINE__);
		if (SystemFlags::getSystemSettingType(SystemFlags::debugNetwork).enabled) SystemFlags::OutputDebug(SystemFlags::debugNetwork, "In [%s::%s Line: %d] this->networkRole = %d gameNetworkInterface [%p]\n", __FILE__, __FUNCTION__, __LINE__, this->networkRole, gameNetworkInterface);
	}

	void NetworkManager::update() {
		if (gameNetworkInterface != NULL) {
			gameNetworkInterface->update();
		}
	}

	bool NetworkManager::isNetworkGame() {
		return networkRole == nrClient || (networkRole == nrServer && getServerInterface() != NULL && getServerInterface()->getSlotCount() > 0);
	}

	bool NetworkManager::isNetworkGameWithConnectedClients() {
		return networkRole == nrClient || (networkRole == nrServer && getServerInterface() != NULL && getServerInterface()->getConnectedSlotCount(true) > 0);
	}

	GameNetworkInterface* NetworkManager::getGameNetworkInterface(bool throwErrorOnNull) {
		if (throwErrorOnNull) {
			//assert(gameNetworkInterface!=NULL);

			if (gameNetworkInterface == NULL) {
				throw game_runtime_error("gameNetworkInterface==NULL");
			}
		}
		return gameNetworkInterface;
	}

	ServerInterface* NetworkManager::getServerInterface(bool throwErrorOnNull) {
		if (throwErrorOnNull) {
			//assert(gameNetworkInterface!=NULL);
			if (gameNetworkInterface == NULL) {
				throw game_runtime_error("gameNetworkInterface==NULL");
			}

			assert(networkRole == nrServer);
			if (networkRole != nrServer) {
				throw game_runtime_error("networkRole!=nrServer");
			}
		}
		return dynamic_cast<ServerInterface*>(gameNetworkInterface);
	}

	ClientInterface* NetworkManager::getClientInterface(bool throwErrorOnNull) {
		//if(SystemFlags::getSystemSettingType(SystemFlags::debugNetwork).enabled) SystemFlags::OutputDebug(SystemFlags::debugNetwork,"In [%s::%s Line: %d] this->networkRole = %d gameNetworkInterface [%p]\n",__FILE__,__FUNCTION__,__LINE__,this->networkRole,gameNetworkInterface);

		if (throwErrorOnNull) {
			//assert(gameNetworkInterface!=NULL);
			if (gameNetworkInterface == NULL) {
				throw game_runtime_error("gameNetworkInterface==NULL");
			}

			assert(networkRole == nrClient);
			if (networkRole != nrClient) {
				throw game_runtime_error("networkRole!=nrClient");
			}
		}
		return dynamic_cast<ClientInterface*>(gameNetworkInterface);
	}

} //end namespace
