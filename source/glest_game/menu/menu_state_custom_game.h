//
//      menu_state_custom_game.h: game setup menu as it appears to
//      to the host
//
//      This file is part of ZetaGlest <https://github.com/ZetaGlest>
//
//      Copyright (C) 2018  The ZetaGlest team
//
//      ZetaGlest is a fork of MegaGlest <https://megaglest.org>
//
//      This program is free software: you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation, either version 3 of the License, or
//      (at your option) any later version.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program.  If not, see <https://www.gnu.org/licenses/>

#ifndef _GLEST_GAME_MENUSTATECUSTOMGAME_H_
#   define _GLEST_GAME_MENUSTATECUSTOMGAME_H_

#   include "main_menu.h"
#   include "chat_manager.h"
#   include "simple_threads.h"
#   include "map_preview.h"
#   include "common_scoped_ptr.h"
#   include "leak_dumper.h"

using namespace
Shared::Map;

namespace Shared {
	namespace Graphics {
		class VideoPlayer;
	}
}

namespace Glest {
	namespace Game {

		class SwitchSetupRequest;
		class ServerInterface;
		class TechTree;
		class MenuStateCustomGame;

		enum ParentMenuState {
			pNewGame,
			pMasterServer,
			pLanGame
		};
		// =====================================================
		//      class GraphicListBoxFactions
        // =====================================================

		class GraphicListBoxFactions : public GraphicListBox {
		private:
			MenuStateCustomGame * menu;
			int index;
		public:
			GraphicListBoxFactions(const std::string &containerName = "", const std::string &objName = "");
			void addInformation(MenuStateCustomGame* m, int i);
			bool mouseClick(int x, int y, string advanceToItemStartingWith);
		};
		// ===============================
		//      class MenuStateCustomGame
		// ===============================

		class MenuStateCustomGame :
			public MenuState, public SimpleTaskCallbackInterface {
			friend class GraphicListBoxFactions;
		private:
			GraphicButton buttonReturn;
			GraphicButton buttonPlayNow;
			GraphicButton buttonRestoreLastSettings;
			GraphicLabel labelControl;
			GraphicLabel labelRMultiplier;
			GraphicLabel labelFaction;
			GraphicLabel labelTeam;
			GraphicLabel labelMap;
			GraphicLabel labelFogOfWar;
			GraphicLabel labelTechTree;
			GraphicLabel labelTileset;
			GraphicLabel labelMapInfo;
			GraphicLabel labelLocalGameVersion;
			GraphicLabel labelLocalIP;
			GraphicLabel labelGameName;

			GraphicListBox listBoxMap;
			GraphicListBox listBoxFogOfWar;
			GraphicListBox listBoxTechTree;
			GraphicListBox listBoxTileset;

			vector < string > mapFiles;
			vector < string > playerSortedMaps[GameConstants::maxPlayers + 1];
			vector <
				string > formattedPlayerSortedMaps[GameConstants::maxPlayers + 1];
			vector < string > techTreeFiles;
			vector < string > tilesetFiles;
			vector < string > factionFiles;
			GraphicLabel labelPlayers[GameConstants::maxPlayers];
			GraphicLabel labelPlayerNames[GameConstants::maxPlayers];
			GraphicListBox listBoxControls[GameConstants::maxPlayers];
			GraphicButton buttonBlockPlayers[GameConstants::maxPlayers];
			GraphicListBox listBoxRMultiplier[GameConstants::maxPlayers];
			GraphicListBoxFactions listBoxFactions[GameConstants::maxPlayers];
			GraphicListBox listBoxTeams[GameConstants::maxPlayers];
			GraphicLabel labelNetStatus[GameConstants::maxPlayers];
			MapInfo mapInfo;

			GraphicButton buttonClearBlockedPlayers;

			GraphicLabel labelPublishServer;
			GraphicCheckBox checkBoxPublishServer;

			GraphicMessageBox mainMessageBox;
			int
				mainMessageBoxState;

			GraphicLabel labelNetworkPauseGameForLaggedClients;
			GraphicCheckBox checkBoxNetworkPauseGameForLaggedClients;

			GraphicLabel labelMapFilter;
			GraphicListBox listBoxMapFilter;

			GraphicLabel labelAdvanced;
			GraphicCheckBox checkBoxAdvanced;

			GraphicLabel labelAllowObservers;
			GraphicCheckBox checkBoxAllowObservers;

			GraphicLabel *
				activeInputLabel;

			GraphicLabel labelPlayerStatus[GameConstants::maxPlayers];
			GraphicListBox listBoxPlayerStatus;

			GraphicLabel labelEnableSwitchTeamMode;
			GraphicCheckBox checkBoxEnableSwitchTeamMode;

			GraphicLabel labelAISwitchTeamAcceptPercent;
			GraphicListBox listBoxAISwitchTeamAcceptPercent;
			GraphicLabel labelFallbackCpuMultiplier;
			GraphicListBox listBoxFallbackCpuMultiplier;

			GraphicLabel labelAllowInGameJoinPlayer;
			GraphicCheckBox checkBoxAllowInGameJoinPlayer;

			GraphicLabel labelAllowTeamUnitSharing;
			GraphicCheckBox checkBoxAllowTeamUnitSharing;

			GraphicLabel labelAllowTeamResourceSharing;
			GraphicCheckBox checkBoxAllowTeamResourceSharing;


			GraphicLabel labelAllowNativeLanguageTechtree;
			GraphicCheckBox checkBoxAllowNativeLanguageTechtree;

			GraphicCheckBox checkBoxScenario;
			GraphicLabel labelScenario;
			GraphicListBox listBoxScenario;

			vector < string > scenarioFiles;
			ScenarioInfo scenarioInfo;
			vector < string > dirList;
			string autoloadScenarioName;
			time_t previewLoadDelayTimer;
			bool needToLoadTextures;
			bool enableScenarioTexturePreview;
			Texture2D *
				scenarioLogoTexture;

			bool needToSetChangedGameSettings;
			time_t lastSetChangedGameSettings;
			time_t lastMasterserverPublishing;
			time_t lastNetworkPing;
			time_t mapPublishingDelayTimer;
			bool needToPublishDelayed;

			bool headlessHasConnectedPlayer;

			bool needToRepublishToMasterserver;
			bool needToBroadcastServerSettings;
			std::map < string, string > publishToServerInfo;
			SimpleTaskThread *
				publishToMasterserverThread;
			SimpleTaskThread *
				publishToClientsThread;

			ParentMenuState parentMenuState;
			int
				soundConnectionCount;

			time_t tMasterserverErrorElapsed;
			bool showMasterserverError;
			string masterServererErrorToShow;

			bool showGeneralError;
			string generalErrorToShow;
			bool serverInitError;

			//Console console;
			ChatManager chatManager;
			bool showFullConsole;

			string lastMapDataSynchError;
			string lastTileDataSynchError;
			string lastTechtreeDataSynchError;

			string defaultPlayerName;
			int8 switchSetupRequestFlagType;

			bool enableFactionTexturePreview;
			bool enableMapPreview;

			string currentTechName_factionPreview;
			string currentFactionName_factionPreview;
			string currentFactionLogo;
			Texture2D *
				factionTexture;
			::Shared::Graphics::VideoPlayer * factionVideo;
			bool factionVideoSwitchedOffVolume;

			MapPreview mapPreview;
			Texture2D *
				mapPreviewTexture;
			bool zoomedMap;
			int
				render_mapPreviewTexture_X;
			int
				render_mapPreviewTexture_Y;
			int
				render_mapPreviewTexture_W;
			int
				render_mapPreviewTexture_H;

			bool autostart;
			GameSettings *
				autoStartSettings;

			std::map < int, int >
				lastSelectedTeamIndex;
			float
				rMultiplierOffset;
			bool hasCheckedForUPNP;

			string lastCheckedCRCTilesetName;
			string lastCheckedCRCTechtreeName;
			string lastCheckedCRCMapName;

			string last_Forced_CheckedCRCTilesetName;
			string last_Forced_CheckedCRCTechtreeName;
			string last_Forced_CheckedCRCMapName;

			uint32 lastCheckedCRCTilesetValue;
			uint32 lastCheckedCRCTechtreeValue;
			uint32 lastCheckedCRCMapValue;
			vector < pair < string, uint32 > >factionCRCList;

			bool forceWaitForShutdown;
			bool headlessServerMode;
			bool masterserverModeMinimalResources;
			int
				lastMasterServerSettingsUpdateCount;

			auto_ptr < TechTree > techTree;

			string gameUUID;

			int
				lastGameSettingsreceivedCount;

		public:
			MenuStateCustomGame(Program * program, MainMenu * mainMenu,
				bool openNetworkSlots =
				false, ParentMenuState parentMenuState =
				pNewGame, bool autostart =
				false, GameSettings * settings =
				NULL, bool masterserverMode =
				false, string autoloadScenarioName = "");
			virtual ~MenuStateCustomGame();

			void
				mouseClick(int x, int y, MouseButton mouseButton);
			void
				mouseMove(int x, int y, const MouseState * mouseState);
			void
				render();
			void
				update();

			virtual bool textInput(std::string text);
			virtual void
				keyDown(SDL_KeyboardEvent key);
			virtual void
				keyPress(SDL_KeyboardEvent c);
			virtual void
				keyUp(SDL_KeyboardEvent key);


			virtual void
				simpleTask(BaseThread * callingThread, void *userdata);
			virtual void
				setupTask(BaseThread * callingThread, void *userdata);
			virtual void
				shutdownTask(BaseThread * callingThread, void *userdata);
			static void
				setupTaskStatic(BaseThread * callingThread);
			static void
				shutdownTaskStatic(BaseThread * callingThread);

			virtual bool isInSpecialKeyCaptureEvent();
			virtual bool isMasterserverMode()const;

			virtual bool isVideoPlaying();
		private:

			void
				lastPlayerDisconnected();
			bool hasNetworkGameSettings();
			void
				loadGameSettings(GameSettings * gameSettings,
					bool forceCloseUnusedSlots = false);
			void
				loadMapInfo(string file, MapInfo * mapInfo, bool loadMapPreview);
			void
				cleanupMapPreviewTexture();

			void
				updateControllers();
			void
				closeUnusedSlots();
			void
				updateNetworkSlots();
			void
				publishToMasterserver();
			void
				returnToParentMenu();
			void
				showMessageBox(const string & text, const string & header,
					bool toggle);

			void
				saveGameSettingsToFile(std::string fileName);
			void
				switchToNextMapGroup(const int direction);
			void
				updateAllResourceMultiplier();
			void
				updateResourceMultiplier(const int index);
			string getCurrentMapFile();
			void
				setActiveInputLabel(GraphicLabel * newLable);
			string getHumanPlayerName(int index = -1);

			void
				loadFactionTexture(string filepath);

			GameSettings loadGameSettingsFromFile(std::string fileName);
			void
				loadGameSettings(const std::string & fileName);
			void
				RestoreLastGameSettings();
			void
				PlayNow(bool saveGame);

			void
				SetActivePlayerNameEditor();
			void
				cleanup();

			int32 getNetworkPlayerStatus();
			void
				setupUIFromGameSettings(const GameSettings & gameSettings);

			void
				switchSetupForSlots(SwitchSetupRequest ** switchSetupRequests,
					ServerInterface * &serverInterface, int startIndex,
					int endIndex, bool onlyNetworkUnassigned);

			string createGameName(string controllingPlayer = "");
			void
				reloadUI();
			void
				loadScenarioInfo(string file, ScenarioInfo * scenarioInfo);
			void
				processScenario();
			void
				SetupUIForScenarios();
			int
				setupMapList(string scenario);
			int
				setupTechList(string scenario, bool forceLoad = false);
			void
				reloadFactions(bool keepExistingSelectedItem, string scenario);
			void
				setupTilesetList(string scenario);
			void
				setSlotHuman(int i);

			void
				initFactionPreview(const GameSettings * gameSettings);

			bool
				checkNetworkPlayerDataSynch(bool checkMapCRC, bool checkTileSetCRC,
					bool checkTechTreeCRC);

			void
				cleanupThread(SimpleTaskThread ** thread);
			void
				simpleTaskForMasterServer(BaseThread * callingThread);
			void
				simpleTaskForClients(BaseThread * callingThread);
			void
				KeepCurrentHumanPlayerSlots(GameSettings & gameSettings);
		};

	}
}                              //end namespace

#endif
