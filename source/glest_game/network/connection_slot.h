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

#ifndef _CONNECTIONSLOT_H_
#define _CONNECTIONSLOT_H_

#include "socket.h"
#include "network_interface.h"
#include "base_thread.h"
#include <time.h>
#include <vector>

#include "leak_dumper.h"

using Shared::Platform::ServerSocket;
using Shared::Platform::Socket;
using std::vector;

namespace Game {
	class ServerInterface;
	class ConnectionSlot;

	// =====================================================
	//	class ConnectionSlotThread
	// =====================================================

	enum ConnectionSlotEventType {
		eNone,
		eReceiveSocketData,
		eSendSocketData
	};

	class ConnectionSlotEvent {
	public:

		ConnectionSlotEvent() {
			eventType = eNone;
			triggerId = -1;
			connectionSlot = NULL;
			networkMessage = NULL;
			socketTriggered = false;
			eventCompleted = false;
			eventId = -1;
		}

		int64 triggerId;
		ConnectionSlot* connectionSlot;
		ConnectionSlotEventType eventType;
		NetworkMessage *networkMessage;
		bool socketTriggered;
		bool eventCompleted;
		int64 eventId;
	};

	//
	// This interface describes the methods a callback object must implement
	//
	class ConnectionSlotCallbackInterface {
	public:
		virtual bool isClientConnected(int index) = 0;
		virtual bool getAllowInGameConnections() const = 0;
		virtual ConnectionSlot *getSlot(int index, bool lockMutex) = 0;
		virtual Mutex *getSlotMutex(int index) = 0;

		virtual void slotUpdateTask(ConnectionSlotEvent *event) = 0;
		virtual ~ConnectionSlotCallbackInterface() {
		}
	};

	class ConnectionSlotThread : public BaseThread, public SlaveThreadControllerInterface {
	protected:

		ConnectionSlotCallbackInterface * slotInterface;
		Semaphore semTaskSignalled;
		Mutex *triggerIdMutex;
		vector<ConnectionSlotEvent> eventList;
		int slotIndex;
		MasterSlaveThreadController *masterController;

		Mutex *triggerGameStarted;
		bool gameStarted;

		virtual void setQuitStatus(bool value);
		virtual void setTaskCompleted(int eventId);

		void slotUpdateTask(ConnectionSlotEvent *event);

	public:
		explicit ConnectionSlotThread(int slotIndex);
		ConnectionSlotThread(ConnectionSlotCallbackInterface *slotInterface, int slotIndex);
		virtual ~ConnectionSlotThread();

		bool getGameStarted();
		void setGameStarted(bool value);

		virtual void setMasterController(MasterSlaveThreadController *master) {
			masterController = master;
		}
		virtual void signalSlave(void *userdata);

		virtual void execute();
		void signalUpdate(ConnectionSlotEvent *event);
		bool isSignalCompleted(ConnectionSlotEvent *event);

		int getSlotIndex() const {
			return slotIndex;
		}
		void setSlotIndex(int index) {
			this->slotIndex = index;
		}

		void purgeCompletedEvents();
		//void purgeAllEvents();
		void setAllEventsCompleted();

		virtual bool canShutdown(bool deleteSelfIfShutdownDelayed = false);
	};

	// =====================================================
	//	class ConnectionSlot
	// =====================================================

	class ConnectionSlot : public NetworkInterface {
	private:
		ServerInterface * serverInterface;

		Mutex *mutexSocket;
		Socket* socket;
		int playerIndex;
		string name;
		bool ready;
		vector<std::pair<string, uint32> > vctFileList;
		bool receivedNetworkGameStatus;
		time_t connectedTime;
		bool gotIntro;

		Mutex *mutexCloseConnection;

		Mutex *mutexPendingNetworkCommandList;
		vector<NetworkCommand> vctPendingNetworkCommandList;
		ConnectionSlotThread* slotThreadWorker;
		int currentFrameCount;
		int currentLagCount;
		int graceLagCtr;
		time_t lastReceiveCommandListTime;
		bool gotLagCountWarning;
		string versionString;
		int sessionKey;
		uint32 connectedRemoteIPAddress;
		NetworkPlayerStatusType playerStatus;
		string playerLanguage;
		string playerUUID;
		string platform;

		bool skipLagCheck;
		bool joinGameInProgress;
		bool canAcceptConnections;
		bool startInGameConnectionLaunch;
		bool pauseForInGameConnection;
		bool unPauseForInGameConnection;
		bool sentSavedGameInfo;

		int autoPauseGameCountForLag;

	public:
		ConnectionSlot(ServerInterface* serverInterface, int playerIndex);
		~ConnectionSlot();

		int getAutoPauseGameCountForLag();
		void incrementAutoPauseGameCountForLag();

		bool getGameStarted();
		void setGameStarted(bool value);

		bool getStartInGameConnectionLaunch() const {
			return startInGameConnectionLaunch;
		}
		void setStartInGameConnectionLaunch(bool value) {
			startInGameConnectionLaunch = value;
		}

		bool getPauseForInGameConnection() const {
			return pauseForInGameConnection;
		}
		void setPauseForInGameConnection(bool value) {
			pauseForInGameConnection = value;
		}

		bool getUnPauseForInGameConnection() const {
			return unPauseForInGameConnection;
		}
		void setUnPauseForInGameConnection(bool value) {
			unPauseForInGameConnection = value;
		}

		bool getSkipLagCheck() const {
			return skipLagCheck;
		}
		bool getJoinGameInProgress() const {
			return joinGameInProgress;
		}

		int getGraceLagCtr() {
			return graceLagCtr++;
		}
		void resetGraceLagCtr() {
			graceLagCtr = 0;
		}

		bool getSentSavedGameInfo() const {
			return sentSavedGameInfo;
		}
		void setSentSavedGameInfo(bool value) {
			sentSavedGameInfo = value;
		}

		ConnectionSlotThread *getWorkerThread() {
			return slotThreadWorker;
		}

		void update(bool checkForNewClients, int lockedSlotIndex);
		void setPlayerIndex(int value);
		int getPlayerIndex() const {
			return playerIndex;
		}

		uint32 getConnectedRemoteIPAddress() const {
			return connectedRemoteIPAddress;
		}

		void setReady();
		const string &getName() const {
			return name;
		}
		const string &getUUID() const {
			return playerUUID;
		}
		const string &getPlatform() const {
			return platform;
		}
		void setName(string value) {
			name = value;
		}
		bool isReady() const {
			return ready;
		}

		virtual std::string getIpAddress(bool mutexLock = true);

		virtual Socket* getSocket(bool mutexLock = true);
		pair<bool, Socket*> getSocketInfo();

		virtual void close();
		//virtual bool getFogOfWar();

		bool getReceivedNetworkGameStatus() const {
			return receivedNetworkGameStatus;
		}
		void setReceivedNetworkGameStatus(bool value) {
			receivedNetworkGameStatus = value;
		}

		bool hasValidSocketId();
		virtual bool getConnectHasHandshaked() const {
			return gotIntro;
		}
		std::vector<std::string> getThreadErrorList() const {
			return threadErrorList;
		}
		void clearThreadErrorList() {
			threadErrorList.clear();
		}

		vector<NetworkCommand> getPendingNetworkCommandList(bool clearList = false);
		//void clearPendingNetworkCommandList();

		void signalUpdate(ConnectionSlotEvent *event);
		bool updateCompleted(ConnectionSlotEvent *event);

		virtual void sendMessage(NetworkMessage* networkMessage);
		int getCurrentFrameCount() const {
			return currentFrameCount;
		}

		int getCurrentLagCount() const {
			return currentLagCount;
		}
		void setCurrentLagCount(int value) {
			currentLagCount = value;
		}

		time_t getLastReceiveCommandListTime() const {
			return lastReceiveCommandListTime;
		}

		bool getLagCountWarning() const {
			return gotLagCountWarning;
		}
		void setLagCountWarning(bool value) {
			gotLagCountWarning = value;
		}

		const string &getVersionString() const {
			return versionString;
		}

		void validateConnection();
		virtual string getHumanPlayerName(int index = -1);
		virtual int getHumanPlayerIndex() const {
			return playerIndex;
		}

		NetworkPlayerStatusType getNetworkPlayerStatus() const {
			return playerStatus;
		}

		string getNetworkPlayerLanguage() const {
			return playerLanguage;
		}

		time_t getConnectedTime() const {
			return connectedTime;
		}
		int getSessionKey() const {
			return sessionKey;
		}

		void updateSlot(ConnectionSlotEvent *event);
		virtual bool isConnected();

		PLATFORM_SOCKET getSocketId();

		void setCanAcceptConnections(bool value) {
			canAcceptConnections = value;
		}
		bool getCanAcceptConnections() const {
			return canAcceptConnections;
		}

		virtual void saveGame(XmlNode *rootNode) {
		};

		//void resetJoinGameInProgressFlags();
		void setJoinGameInProgressFlags();

	protected:

		Mutex * getServerSynchAccessor();
		std::vector<std::string> threadErrorList;
		Mutex *socketSynchAccessor;

		void setSocket(Socket *newSocket);
		void deleteSocket();
		virtual void update() {
		}

		bool hasDataToRead();
	};

} //end namespace

#endif
