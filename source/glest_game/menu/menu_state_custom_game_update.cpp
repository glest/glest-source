//
//      menu_state_custom_game_update.cpp: contains function definitions used
//      by menu_state_custom_game.cpp.
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

#include "menu_state_custom_game.h"
#include "sound_renderer.h"
#include "core_data.h"
#include "server_interface.h"
#include "network_manager.h"

namespace Glest
{
  namespace Game
  {
    const int MASTERSERVER_BROADCAST_PUBLISH_SECONDS = 6;
    const int BROADCAST_SETTINGS_SECONDS = 4;
    const int BROADCAST_MAP_DELAY_SECONDS = 5;

// These functions are prototyped in menu_state_custom_game.h

    void MenuStateCustomGame::update ()
    {
      Chrono chrono;
      if (SystemFlags::
          getSystemSettingType (SystemFlags::debugPerformance).enabled)
        chrono.start ();

// Test openal buffer underrun issue
//sleep(200);
// END

      MutexSafeWrapper
        safeMutex ((publishToMasterserverThread !=
                    NULL ?
                    publishToMasterserverThread->getMutexThreadObjectAccessor
                    () : NULL),
                   string (__FILE__) + "_" + intToStr (__LINE__));
      MutexSafeWrapper
        safeMutexCLI ((publishToClientsThread !=
                       NULL ?
                       publishToClientsThread->getMutexThreadObjectAccessor ()
                       : NULL),
                      string (__FILE__) + "_" + intToStr (__LINE__));

      try
      {
        if (serverInitError == true)
        {
          if (SystemFlags::
              getSystemSettingType (SystemFlags::debugSystem).enabled)
            SystemFlags::OutputDebug (SystemFlags::debugSystem,
                                      "In [%s::%s Line %d]\n",
                                      extractFileFromDirectoryPath (__FILE__).
                                      c_str (), __FUNCTION__, __LINE__);

          if (showGeneralError)
          {
            if (SystemFlags::getSystemSettingType (SystemFlags::debugSystem).
                enabled)
              SystemFlags::OutputDebug (SystemFlags::debugSystem,
                                        "In [%s::%s Line %d]\n",
                                        extractFileFromDirectoryPath
                                        (__FILE__).c_str (), __FUNCTION__,
                                        __LINE__);


            showGeneralError = false;
            mainMessageBoxState = 1;
            showMessageBox (generalErrorToShow, "Error", false);
          }

          if (SystemFlags::
              getSystemSettingType (SystemFlags::debugSystem).enabled)
            SystemFlags::OutputDebug (SystemFlags::debugSystem,
                                      "In [%s::%s Line %d]\n",
                                      extractFileFromDirectoryPath (__FILE__).
                                      c_str (), __FUNCTION__, __LINE__);

          if (this->headlessServerMode == false)
          {
            return;
          }
        }
        ServerInterface *serverInterface =
          NetworkManager::getInstance ().getServerInterface ();
        Lang & lang = Lang::getInstance ();

        if (serverInterface != NULL
            && serverInterface->getServerSocket () != NULL)
        {
          buttonClearBlockedPlayers.
            setEditable (serverInterface->getServerSocket
                         ()->hasBlockedIPAddresses ());
        }

        if (this->autoloadScenarioName != "")
        {
          listBoxScenario.setSelectedItem (formatString
                                           (this->autoloadScenarioName),
                                           false);
          lastSetChangedGameSettings = time (NULL);
          if (serverInterface != NULL)
          {
            lastGameSettingsreceivedCount =
              serverInterface->getGameSettingsUpdateCount ();
          }
          if (listBoxScenario.getSelectedItem () !=
              formatString (this->autoloadScenarioName))
          {
            mainMessageBoxState = 1;
            showMessageBox ("Could not find scenario name: " +
                            formatString (this->autoloadScenarioName),
                            "Scenario Missing", false);
            this->autoloadScenarioName = "";
          }
          else
          {
            loadScenarioInfo (Scenario::getScenarioPath (dirList,
                                                         scenarioFiles
                                                         [listBoxScenario.getSelectedItemIndex
                                                          ()]),
                              &scenarioInfo);
//labelInfo.setText(scenarioInfo.desc);

            SoundRenderer & soundRenderer = SoundRenderer::getInstance ();
            CoreData & coreData = CoreData::getInstance ();
            soundRenderer.playFx (coreData.getClickSoundC ());
//launchGame();
            PlayNow (true);
            return;
          }
        }

        if (needToLoadTextures)
        {
// this delay is done to make it possible to switch faster
          if (difftime ((long int) time (NULL), previewLoadDelayTimer) >= 2)
          {
//loadScenarioPreviewTexture();
            needToLoadTextures = false;
          }
        }

//bool haveAtLeastOneNetworkClientConnected = false;
        bool hasOneNetworkSlotOpen = false;
        int currentConnectionCount = 0;
        Config & config = Config::getInstance ();

        bool masterServerErr = showMasterserverError;

        if (SystemFlags::
            getSystemSettingType (SystemFlags::debugPerformance).enabled
            && chrono.getMillis () > 0)
          SystemFlags::OutputDebug (SystemFlags::debugPerformance,
                                    "In [%s::%s Line: %d] took msecs: %lld\n",
                                    extractFileFromDirectoryPath
                                    (__FILE__).c_str (), __FUNCTION__,
                                    __LINE__, chrono.getMillis ());
        if (SystemFlags::
            getSystemSettingType (SystemFlags::debugPerformance).enabled
            && chrono.getMillis () > 0)
          chrono.start ();

        if (masterServerErr)
        {
          if (SystemFlags::
              getSystemSettingType (SystemFlags::debugSystem).enabled)
            SystemFlags::OutputDebug (SystemFlags::debugSystem,
                                      "In [%s::%s Line %d]\n",
                                      extractFileFromDirectoryPath (__FILE__).
                                      c_str (), __FUNCTION__, __LINE__);

          if (EndsWith (masterServererErrorToShow, "wrong router setup") ==
              true)
          {
            masterServererErrorToShow = lang.getString ("WrongRouterSetup");
          }

          Lang & lang = Lang::getInstance ();
          string publishText = " (disabling publish)";
          if (lang.hasString ("PublishDisabled") == true)
          {
            publishText = lang.getString ("PublishDisabled");
          }

          masterServererErrorToShow += "\n\n" + publishText;
          showMasterserverError = false;
          mainMessageBoxState = 1;
          showMessageBox (masterServererErrorToShow,
                          lang.getString ("ErrorFromMasterserver"), false);

          if (this->headlessServerMode == false)
          {
            checkBoxPublishServer.setValue (false);
          }

          ServerInterface *serverInterface =
            NetworkManager::getInstance ().getServerInterface ();
          serverInterface->
            setPublishEnabled (checkBoxPublishServer.getValue () == true);
        }
        else if (showGeneralError)
        {
          if (SystemFlags::
              getSystemSettingType (SystemFlags::debugSystem).enabled)
            SystemFlags::OutputDebug (SystemFlags::debugSystem,
                                      "In [%s::%s Line %d]\n",
                                      extractFileFromDirectoryPath (__FILE__).
                                      c_str (), __FUNCTION__, __LINE__);

          showGeneralError = false;
          mainMessageBoxState = 1;
          showMessageBox (generalErrorToShow, "Error", false);
        }

        if (SystemFlags::
            getSystemSettingType (SystemFlags::debugPerformance).enabled
            && chrono.getMillis () > 0)
          SystemFlags::OutputDebug (SystemFlags::debugPerformance,
                                    "In [%s::%s Line: %d] took msecs: %lld\n",
                                    extractFileFromDirectoryPath
                                    (__FILE__).c_str (), __FUNCTION__,
                                    __LINE__, chrono.getMillis ());
        if (SystemFlags::
            getSystemSettingType (SystemFlags::debugPerformance).enabled
            && chrono.getMillis () > 0)
          chrono.start ();

        if (this->headlessServerMode == true && serverInterface == NULL)
        {
          throw megaglest_runtime_error ("serverInterface == NULL");
        }
        if (this->headlessServerMode == true
            && serverInterface->getGameSettingsUpdateCount () >
            lastMasterServerSettingsUpdateCount
            && serverInterface->getGameSettings () != NULL)
        {
          const GameSettings *settings = serverInterface->getGameSettings ();
//printf("\n\n\n\n=====#1 got settings [%d] [%d]:\n%s\n",lastMasterServerSettingsUpdateCount,serverInterface->getGameSettingsUpdateCount(),settings->toString().c_str());

          lastMasterServerSettingsUpdateCount =
            serverInterface->getGameSettingsUpdateCount ();
//printf("#2 custom menu got map [%s]\n",settings->getMap().c_str());

          setupUIFromGameSettings (*settings);
          printf ("received Settings map filter=%d\n",
                  settings->getMapFilter ());

          GameSettings gameSettings;
          loadGameSettings (&gameSettings);

//printf("\n\n\n\n=====#1.1 got settings [%d] [%d]:\n%s\n",lastMasterServerSettingsUpdateCount,serverInterface->getGameSettingsUpdateCount(),gameSettings.toString().c_str());

        }
        if (this->headlessServerMode == true
            && serverInterface->getMasterserverAdminRequestLaunch () == true)
        {
          serverInterface->setMasterserverAdminRequestLaunch (false);
          safeMutex.ReleaseLock ();
          safeMutexCLI.ReleaseLock ();

          PlayNow (false);
          return;
        }

// handle setting changes from clients
        SwitchSetupRequest **switchSetupRequests =
          serverInterface->getSwitchSetupRequests ();
//!!!
        switchSetupForSlots (switchSetupRequests, serverInterface, 0,
                             mapInfo.players, false);
        switchSetupForSlots (switchSetupRequests, serverInterface,
                             mapInfo.players, GameConstants::maxPlayers,
                             true);

        if (SystemFlags::
            getSystemSettingType (SystemFlags::debugPerformance).enabled
            && chrono.getMillis () > 0)
          SystemFlags::OutputDebug (SystemFlags::debugPerformance,
                                    "In [%s::%s Line: %d] took msecs: %lld\n",
                                    extractFileFromDirectoryPath
                                    (__FILE__).c_str (), __FUNCTION__,
                                    __LINE__, chrono.getMillis ());
        if (SystemFlags::
            getSystemSettingType (SystemFlags::debugPerformance).enabled
            && chrono.getMillis () > 0)
          chrono.start ();

        GameSettings gameSettings;
        loadGameSettings (&gameSettings);

        listBoxAISwitchTeamAcceptPercent.setEnabled
          (checkBoxEnableSwitchTeamMode.getValue ());

        int factionCount = 0;
        for (int i = 0; i < mapInfo.players; ++i)
        {
          if (hasNetworkGameSettings () == true)
          {
            if (listBoxControls[i].getSelectedItemIndex () != ctClosed)
            {
              int slotIndex = factionCount;
              if (listBoxControls[i].getSelectedItemIndex () == ctHuman)
              {
                switch (gameSettings.getNetworkPlayerStatuses (slotIndex))
                {
                case npst_BeRightBack:
                  labelPlayerStatus[i].setTexture (CoreData::getInstance
                                                   ().getStatusBRBTexture ());
                  break;
                case npst_Ready:
                  labelPlayerStatus[i].setTexture (CoreData::getInstance
                                                   ().getStatusReadyTexture
                                                   ());
                  break;
                case npst_PickSettings:
                  labelPlayerStatus[i].setTexture (CoreData::getInstance
                                                   ().getStatusNotReadyTexture
                                                   ());
                  break;
                case npst_Disconnected:
                  labelPlayerStatus[i].setTexture (NULL);
                  break;

                default:
                  labelPlayerStatus[i].setTexture (NULL);
                  break;
                }
              }
              else
              {
                labelPlayerStatus[i].setTexture (NULL);
              }

              factionCount++;
            }
            else
            {
              labelPlayerStatus[i].setTexture (NULL);
            }
          }

          if (listBoxControls[i].getSelectedItemIndex () == ctNetwork ||
              listBoxControls[i].getSelectedItemIndex () ==
              ctNetworkUnassigned)
          {
            hasOneNetworkSlotOpen = true;

            if (serverInterface->getSlot (i, true) != NULL &&
                serverInterface->getSlot (i, true)->isConnected ())
            {

              if (hasNetworkGameSettings () == true)
              {
                switch (serverInterface->
                        getSlot (i, true)->getNetworkPlayerStatus ())
                {
                case npst_BeRightBack:
                  labelPlayerStatus[i].setTexture (CoreData::getInstance
                                                   ().getStatusBRBTexture ());
                  break;
                case npst_Ready:
                  labelPlayerStatus[i].setTexture (CoreData::getInstance
                                                   ().getStatusReadyTexture
                                                   ());
                  break;
                case npst_PickSettings:
                default:
                  labelPlayerStatus[i].setTexture (CoreData::getInstance
                                                   ().getStatusNotReadyTexture
                                                   ());
                  break;
                }
              }

              serverInterface->getSlot (i,
                                        true)->setName (labelPlayerNames[i].
                                                        getText ());

//printf("FYI we have at least 1 client connected, slot = %d'\n",i);

//haveAtLeastOneNetworkClientConnected = true;
              if (serverInterface->getSlot (i, true) != NULL &&
                  serverInterface->getSlot (i,
                                            true)->getConnectHasHandshaked ())
              {
                currentConnectionCount++;
              }
              string label =
                (serverInterface->getSlot (i, true) !=
                 NULL ? serverInterface->getSlot (i,
                                                  true)->getVersionString () :
                 "");

              if (serverInterface->getSlot (i, true) != NULL &&
                  serverInterface->getSlot (i,
                                            true)->getAllowDownloadDataSynch
                  () == true
                  && serverInterface->getSlot (i,
                                               true)->getAllowGameDataSynchCheck
                  () == true)
              {
                if (serverInterface->getSlot (i,
                                              true)->getNetworkGameDataSynchCheckOk
                    () == false)
                {
                  label += " -waiting to synch:";
                  if (serverInterface->getSlot (i,
                                                true)->getNetworkGameDataSynchCheckOkMap
                      () == false)
                  {
                    label = label + " map";
                  }
                  if (serverInterface->getSlot (i,
                                                true)->getNetworkGameDataSynchCheckOkTile
                      () == false)
                  {
                    label = label + " tile";
                  }
                  if (serverInterface->getSlot (i,
                                                true)->getNetworkGameDataSynchCheckOkTech
                      () == false)
                  {
                    label = label + " techtree";
                  }
                }
                else
                {
                  label += " - data synch is ok";
                }
              }
              else
              {
                if (serverInterface->getSlot (i, true) != NULL &&
                    serverInterface->getSlot (i,
                                              true)->getAllowGameDataSynchCheck
                    () == true
                    && serverInterface->getSlot (i,
                                                 true)->getNetworkGameDataSynchCheckOk
                    () == false)
                {
                  label += " -synch mismatch:";

                  if (serverInterface->getSlot (i, true) != NULL
                      && serverInterface->getSlot (i,
                                                   true)->getNetworkGameDataSynchCheckOkMap
                      () == false)
                  {
                    label = label + " map";

                    if (serverInterface->getSlot (i,
                                                  true)->getReceivedDataSynchCheck
                        () == true
                        && lastMapDataSynchError !=
                        "map CRC mismatch, " + listBoxMap.getSelectedItem ())
                    {
                      lastMapDataSynchError =
                        "map CRC mismatch, " + listBoxMap.getSelectedItem ();
                      ServerInterface *serverInterface =
                        NetworkManager::getInstance ().getServerInterface ();
                      serverInterface->sendTextMessage (lastMapDataSynchError,
                                                        -1, true, "");
                    }
                  }

                  if (serverInterface->getSlot (i, true) != NULL &&
                      serverInterface->getSlot (i,
                                                true)->getNetworkGameDataSynchCheckOkTile
                      () == false)
                  {
                    label = label + " tile";

                    if (serverInterface->getSlot (i,
                                                  true)->getReceivedDataSynchCheck
                        () == true
                        && lastTileDataSynchError !=
                        "tile CRC mismatch, " +
                        listBoxTileset.getSelectedItem ())
                    {
                      lastTileDataSynchError =
                        "tile CRC mismatch, " +
                        listBoxTileset.getSelectedItem ();
                      ServerInterface *serverInterface =
                        NetworkManager::getInstance ().getServerInterface ();
                      serverInterface->sendTextMessage
                        (lastTileDataSynchError, -1, true, "");
                    }
                  }

                  if (serverInterface->getSlot (i, true) != NULL &&
                      serverInterface->getSlot (i,
                                                true)->getNetworkGameDataSynchCheckOkTech
                      () == false)
                  {
                    label = label + " techtree";

                    if (serverInterface->getSlot (i,
                                                  true)->getReceivedDataSynchCheck
                        () == true)
                    {
                      ServerInterface *serverInterface =
                        NetworkManager::getInstance ().getServerInterface ();
                      string report = serverInterface->getSlot (i,
                                                                true)->getNetworkGameDataSynchCheckTechMismatchReport
                        ();

                      if (lastTechtreeDataSynchError !=
                          "techtree CRC mismatch" + report)
                      {
                        lastTechtreeDataSynchError =
                          "techtree CRC mismatch" + report;

                        if (SystemFlags::getSystemSettingType
                            (SystemFlags::debugSystem).enabled)
                          SystemFlags::OutputDebug (SystemFlags::debugSystem,
                                                    "In [%s::%s Line: %d] report: %s\n",
                                                    extractFileFromDirectoryPath
                                                    (__FILE__).c_str (),
                                                    __FUNCTION__,
                                                    __LINE__,
                                                    report.c_str ());

                        serverInterface->sendTextMessage
                          ("techtree CRC mismatch", -1, true, "");
                        vector < string > reportLineTokens;
                        Tokenize (report, reportLineTokens, "\n");
                        for (int reportLine = 0;
                             reportLine <
                             (int) reportLineTokens.size (); ++reportLine)
                        {
                          serverInterface->sendTextMessage
                            (reportLineTokens[reportLine], -1, true, "");
                        }
                      }
                    }
                  }

                  if (serverInterface->getSlot (i, true) != NULL)
                  {
                    serverInterface->getSlot (i,
                                              true)->setReceivedDataSynchCheck
                      (false);
                  }
                }
              }

//float pingTime = serverInterface->getSlot(i)->getThreadedPingMS(serverInterface->getSlot(i)->getIpAddress().c_str());
              char szBuf[8096] = "";
              snprintf (szBuf, 8096, "%s", label.c_str ());

              labelNetStatus[i].setText (szBuf);
            }
            else
            {
              string port =
                "(" + intToStr (config.getInt ("PortServer")) + ")";
              labelNetStatus[i].setText ("--- " + port);
            }
          }
          else
          {
            labelNetStatus[i].setText ("");
          }
        }

        if (SystemFlags::
            getSystemSettingType (SystemFlags::debugPerformance).enabled
            && chrono.getMillis () > 0)
          SystemFlags::OutputDebug (SystemFlags::debugPerformance,
                                    "In [%s::%s Line: %d] took msecs: %lld\n",
                                    extractFileFromDirectoryPath
                                    (__FILE__).c_str (), __FUNCTION__,
                                    __LINE__, chrono.getMillis ());
        if (SystemFlags::
            getSystemSettingType (SystemFlags::debugPerformance).enabled
            && chrono.getMillis () > 0)
          chrono.start ();

        if (checkBoxScenario.getValue () == false)
        {
          // When scenario is checked the value for mapInfo.players is reset to
          // hardMaxPlayers. This resets it.
          mapInfo.players = checkBoxAllowObservers.getValue () == true ?
                                                        GameConstants::maxPlayers :
                                                        mapInfo.hardMaxPlayers;

          for (int i = 0; i < GameConstants::maxPlayers; ++i)
          {
            if (i >= mapInfo.hardMaxPlayers)
            {
              if (checkBoxAllowObservers.getValue() == false)
              {
                listBoxControls[i].setSelectedItemIndex (ctClosed);
                listBoxControls[i].setEditable (false);
                listBoxControls[i].setEnabled (false);
              }
              else
              {
                listBoxControls[i].setSelectedItemIndex (ctNetwork);
                listBoxControls[i].setEditable (false);
                listBoxFactions[i].setSelectedItem (GameConstants::OBSERVER_SLOTNAME);
                listBoxFactions[i].setEditable (false);
                listBoxTeams[i].setSelectedItem (intToStr (GameConstants::maxPlayers +
                                                fpt_Observer));
                listBoxTeams[i].setEditable (false);
              }

              listBoxRMultiplier[i].setEditable (false);
              listBoxRMultiplier[i].setEnabled (false);
              listBoxRMultiplier[i].setVisible (false);
            }
            else if (listBoxControls[i].getSelectedItemIndex () !=
                     ctNetworkUnassigned)
            {
              ConnectionSlot *slot = serverInterface->getSlot (i, true);
              if ((listBoxControls[i].getSelectedItemIndex () !=
                   ctNetwork)
                  || (listBoxControls[i].getSelectedItemIndex () ==
                      ctNetwork && (slot == NULL
                                    || slot->isConnected () == false)))
              {
                listBoxControls[i].setEditable (true);
                listBoxControls[i].setEnabled (true);
                listBoxFactions[i].setEditable (true);
                listBoxTeams[i].setEditable (true);

                if (listBoxControls[i].getSelectedItemIndex () == ctNetwork &&
                    listBoxFactions[i].getSelectedItem () == formatString (GameConstants::OBSERVER_SLOTNAME))
                {
                  listBoxFactions[i].setSelectedItemIndex (0);
                }
              }
              else
              {
                listBoxControls[i].setEditable (false);
                listBoxControls[i].setEnabled (false);
              }
            }
            else
            {
              listBoxControls[i].setEditable (false);
              listBoxControls[i].setEnabled (false);
            }
          }
        }
        else // if this is a scenario...
        {
          int i = mapInfo.players;
          do
          {
            listBoxControls[i].setSelectedItemIndex (ctClosed);
            listBoxControls[i].setEditable (false);
            listBoxControls[i].setEnabled (false);
          } while (++i < GameConstants::maxPlayers);
        }

        // updateNetworkSlots ();

        bool checkDataSynch =
          (serverInterface->getAllowGameDataSynchCheck () == true
           && needToSetChangedGameSettings == true
           &&
           ((difftime ((long int) time (NULL), lastSetChangedGameSettings) >=
             BROADCAST_SETTINGS_SECONDS)
            || (this->headlessServerMode == true)));

        if (SystemFlags::
            getSystemSettingType (SystemFlags::debugPerformance).enabled
            && chrono.getMillis () > 0)
          SystemFlags::OutputDebug (SystemFlags::debugPerformance,
                                    "In [%s::%s Line: %d] took msecs: %lld\n",
                                    extractFileFromDirectoryPath
                                    (__FILE__).c_str (), __FUNCTION__,
                                    __LINE__, chrono.getMillis ());
        if (SystemFlags::
            getSystemSettingType (SystemFlags::debugPerformance).enabled
            && chrono.getMillis () > 0)
          chrono.start ();

// Send the game settings to each client if we have at least one networked client
        if (checkDataSynch == true)
        {
          serverInterface->setGameSettings (&gameSettings, false);
          needToSetChangedGameSettings = false;
        }

        if (SystemFlags::
            getSystemSettingType (SystemFlags::debugPerformance).enabled
            && chrono.getMillis () > 0)
          SystemFlags::OutputDebug (SystemFlags::debugPerformance,
                                    "In [%s::%s Line: %d] took msecs: %lld\n",
                                    extractFileFromDirectoryPath
                                    (__FILE__).c_str (), __FUNCTION__,
                                    __LINE__, chrono.getMillis ());
        if (SystemFlags::
            getSystemSettingType (SystemFlags::debugPerformance).enabled
            && chrono.getMillis () > 0)
          chrono.start ();

        if (this->headlessServerMode == true || hasOneNetworkSlotOpen == true
            || checkBoxAllowInGameJoinPlayer.getValue () == true)
        {
          if (this->headlessServerMode == true &&
              GlobalStaticFlags::isFlagSet (gsft_lan_mode) == false)
          {
            checkBoxPublishServer.setValue (true);
          }
          listBoxFallbackCpuMultiplier.setEditable (true);
          checkBoxPublishServer.setEditable (true);

// Masterserver always needs one network slot
          if (this->headlessServerMode == true
              && hasOneNetworkSlotOpen == false)
          {
            bool anyoneConnected = false;
            for (int i = 0; i < mapInfo.players; ++i)
            {
              MutexSafeWrapper
                safeMutex ((publishToMasterserverThread !=
                            NULL ?
                            publishToMasterserverThread->getMutexThreadObjectAccessor
                            () : NULL),
                           string (__FILE__) + "_" + intToStr (__LINE__));

              ServerInterface *serverInterface =
                NetworkManager::getInstance ().getServerInterface ();
              ConnectionSlot *slot = serverInterface->getSlot (i, true);
              if (slot != NULL && slot->isConnected () == true)
              {
                anyoneConnected = true;
                break;
              }
            }

            for (int i = 0; i < mapInfo.players; ++i)
            {
              if (anyoneConnected == false
                  && listBoxControls[i].getSelectedItemIndex () != ctNetwork)
              {
                listBoxControls[i].setSelectedItemIndex (ctNetwork);
              }
            }

            updateNetworkSlots ();
          }
        }
        else
        {
          checkBoxPublishServer.setValue (false);
          checkBoxPublishServer.setEditable (false);
          listBoxFallbackCpuMultiplier.setEditable (false);
          listBoxFallbackCpuMultiplier.setSelectedItem ("1.0");

          ServerInterface *serverInterface =
            NetworkManager::getInstance ().getServerInterface ();
          serverInterface->
            setPublishEnabled (checkBoxPublishServer.getValue () == true);
        }

        bool republishToMaster =
          (difftime ((long int) time (NULL), lastMasterserverPublishing) >=
           MASTERSERVER_BROADCAST_PUBLISH_SECONDS);

        if (republishToMaster == true)
        {
          if (checkBoxPublishServer.getValue () == true)
          {
            needToRepublishToMasterserver = true;
            lastMasterserverPublishing = time (NULL);
          }
        }

        bool callPublishNow = (checkBoxPublishServer.getEditable () &&
                               checkBoxPublishServer.getValue () == true &&
                               needToRepublishToMasterserver == true);

        if (SystemFlags::
            getSystemSettingType (SystemFlags::debugPerformance).enabled
            && chrono.getMillis () > 0)
          SystemFlags::OutputDebug (SystemFlags::debugPerformance,
                                    "In [%s::%s Line: %d] took msecs: %lld\n",
                                    extractFileFromDirectoryPath
                                    (__FILE__).c_str (), __FUNCTION__,
                                    __LINE__, chrono.getMillis ());
        if (SystemFlags::
            getSystemSettingType (SystemFlags::debugPerformance).enabled
            && chrono.getMillis () > 0)
          chrono.start ();

        if (callPublishNow == true)
        {
// give it to me baby, aha aha ...
          publishToMasterserver ();
        }
        if (needToPublishDelayed)
        {
// this delay is done to make it possible to switch over maps which are not meant to be distributed
          if ((difftime ((long int) time (NULL), mapPublishingDelayTimer) >=
               BROADCAST_MAP_DELAY_SECONDS)
              || (this->headlessServerMode == true))
          {
// after 5 seconds we are allowed to publish again!
            needToSetChangedGameSettings = true;
            lastSetChangedGameSettings = time (NULL);
// set to normal....
            needToPublishDelayed = false;
          }
        }
        if (needToPublishDelayed == false || headlessServerMode == true)
        {
          bool broadCastSettings =
            (difftime ((long int) time (NULL), lastSetChangedGameSettings)
             >= BROADCAST_SETTINGS_SECONDS);

          if (headlessServerMode == true)
          {
// publish settings directly when we receive them
            ServerInterface *serverInterface =
              NetworkManager::getInstance ().getServerInterface ();
            if (lastGameSettingsreceivedCount <
                serverInterface->getGameSettingsUpdateCount ())
            {
              needToBroadcastServerSettings = true;
              lastSetChangedGameSettings = time (NULL);
              lastGameSettingsreceivedCount =
                serverInterface->getGameSettingsUpdateCount ();
            }
          }

          if (broadCastSettings == true)
          {
            needToBroadcastServerSettings = true;
            lastSetChangedGameSettings = time (NULL);
          }

          if (SystemFlags::getSystemSettingType
              (SystemFlags::debugPerformance).enabled
              && chrono.getMillis () > 0)
            SystemFlags::OutputDebug (SystemFlags::debugPerformance,
                                      "In [%s::%s Line: %d] took msecs: %lld\n",
                                      extractFileFromDirectoryPath
                                      (__FILE__).c_str (), __FUNCTION__,
                                      __LINE__, chrono.getMillis ());
          if (SystemFlags::getSystemSettingType
              (SystemFlags::debugPerformance).enabled
              && chrono.getMillis () > 0)
            chrono.start ();

//broadCastSettings = (difftime(time(NULL),lastSetChangedGameSettings) >= 2);
//if (broadCastSettings == true) {// reset timer here on bottom becasue used for different things
//      lastSetChangedGameSettings = time(NULL);
//}
        }

        if (this->headlessServerMode == true)
        {
          lastPlayerDisconnected ();
        }

//call the chat manager
        chatManager.updateNetwork ();

//console
        console.update ();

        if (SystemFlags::
            getSystemSettingType (SystemFlags::debugSystem).enabled)
          SystemFlags::OutputDebug (SystemFlags::debugSystem,
                                    "In [%s::%s Line %d]\n",
                                    extractFileFromDirectoryPath
                                    (__FILE__).c_str (), __FUNCTION__,
                                    __LINE__);

        if (SystemFlags::
            getSystemSettingType (SystemFlags::debugPerformance).enabled
            && chrono.getMillis () > 0)
          SystemFlags::OutputDebug (SystemFlags::debugPerformance,
                                    "In [%s::%s Line: %d] took msecs: %lld\n",
                                    extractFileFromDirectoryPath
                                    (__FILE__).c_str (), __FUNCTION__,
                                    __LINE__, chrono.getMillis ());
        if (SystemFlags::
            getSystemSettingType (SystemFlags::debugPerformance).enabled
            && chrono.getMillis () > 0)
          chrono.start ();

        if (currentConnectionCount > soundConnectionCount)
        {
          soundConnectionCount = currentConnectionCount;
          static PlaySoundClip snd;
          SoundRenderer::getInstance ().
            playFx (snd.getSound (snd.sfxAttention));
//switch on music again!!
          Config & config = Config::getInstance ();
          float configVolume = (config.getInt ("SoundVolumeMusic") / 100.f);
          CoreData::getInstance ().getMenuMusic ()->setVolume (configVolume);
        }
        soundConnectionCount = currentConnectionCount;

        if (SystemFlags::
            getSystemSettingType (SystemFlags::debugPerformance).enabled
            && chrono.getMillis () > 0)
          SystemFlags::OutputDebug (SystemFlags::debugPerformance,
                                    "In [%s::%s Line: %d] took msecs: %lld\n",
                                    extractFileFromDirectoryPath
                                    (__FILE__).c_str (), __FUNCTION__,
                                    __LINE__, chrono.getMillis ());
        if (SystemFlags::
            getSystemSettingType (SystemFlags::debugPerformance).enabled
            && chrono.getMillis () > 0)
          chrono.start ();

        if (enableFactionTexturePreview == true)
        {
          if (currentTechName_factionPreview != gameSettings.getTech () ||
              currentFactionName_factionPreview !=
              gameSettings.
              getFactionTypeName (gameSettings.getThisFactionIndex ()))
          {

            currentTechName_factionPreview = gameSettings.getTech ();
            currentFactionName_factionPreview =
              gameSettings.
              getFactionTypeName (gameSettings.getThisFactionIndex ());

            initFactionPreview (&gameSettings);
          }
        }

        if (SystemFlags::
            getSystemSettingType (SystemFlags::debugPerformance).enabled
            && chrono.getMillis () > 0)
          SystemFlags::OutputDebug (SystemFlags::debugPerformance,
                                    "In [%s::%s Line: %d] took msecs: %lld\n",
                                    extractFileFromDirectoryPath
                                    (__FILE__).c_str (), __FUNCTION__,
                                    __LINE__, chrono.getMillis ());
        if (SystemFlags::
            getSystemSettingType (SystemFlags::debugPerformance).enabled
            && chrono.getMillis () > 0)
          chrono.start ();

        if (autostart == true)
        {
          autostart = false;
          safeMutex.ReleaseLock ();
          safeMutexCLI.ReleaseLock ();
          if (autoStartSettings != NULL)
          {

            setupUIFromGameSettings (*autoStartSettings);
            ServerInterface *serverInterface =
              NetworkManager::getInstance ().getServerInterface ();
            serverInterface->setGameSettings (autoStartSettings, false);
          }
          else
          {
            RestoreLastGameSettings ();
          }
          PlayNow ((autoStartSettings == NULL));
          return;
        }
      }
      catch (megaglest_runtime_error & ex)
      {
//abort();
//printf("1111111bbbb ex.wantStackTrace() = %d\n",ex.wantStackTrace());
        char szBuf[8096] = "";
        snprintf (szBuf, 8096, "In [%s::%s %d]\nError detected:\n%s\n",
                  extractFileFromDirectoryPath (__FILE__).c_str (),
                  __FUNCTION__, __LINE__, ex.what ());
        SystemFlags::OutputDebug (SystemFlags::debugError, szBuf);
        if (SystemFlags::
            getSystemSettingType (SystemFlags::debugSystem).enabled)
          SystemFlags::OutputDebug (SystemFlags::debugSystem, "%s", szBuf);

//printf("2222222bbbb ex.wantStackTrace() = %d\n",ex.wantStackTrace());

        showGeneralError = true;
        generalErrorToShow = szBuf;
      }
      catch (const std::exception & ex)
      {
        char szBuf[8096] = "";
        snprintf (szBuf, 8096, "In [%s::%s %d]\nError detected:\n%s\n",
                  extractFileFromDirectoryPath (__FILE__).c_str (),
                  __FUNCTION__, __LINE__, ex.what ());
        SystemFlags::OutputDebug (SystemFlags::debugError, szBuf);
        if (SystemFlags::
            getSystemSettingType (SystemFlags::debugSystem).enabled)
          SystemFlags::OutputDebug (SystemFlags::debugSystem, "%s", szBuf);

        showGeneralError = true;
        generalErrorToShow = szBuf;
      }
    }

    void MenuStateCustomGame::updateControllers ()
    {
      try
      {
        bool humanPlayer = false;

        for (int i = 0; i < mapInfo.players; ++i)
        {
          if (listBoxControls[i].getSelectedItemIndex () == ctHuman)
          {
            humanPlayer = true;
          }
        }

        if (humanPlayer == false)
        {
          if (this->headlessServerMode == false)
          {
            bool foundNewSlotForHuman = false;
            for (int i = 0; i < mapInfo.players; ++i)
            {
              if (listBoxControls[i].getSelectedItemIndex () == ctClosed)
              {
                setSlotHuman (i);
                foundNewSlotForHuman = true;
                break;
              }
            }

            if (foundNewSlotForHuman == false)
            {
              for (int i = 0; i < mapInfo.players; ++i)
              {
                if (listBoxControls[i].getSelectedItemIndex () ==
                    ctClosed
                    || listBoxControls[i].getSelectedItemIndex () ==
                    ctCpuEasy
                    || listBoxControls[i].getSelectedItemIndex () ==
                    ctCpu
                    || listBoxControls[i].getSelectedItemIndex () ==
                    ctCpuUltra
                    || listBoxControls[i].getSelectedItemIndex () ==
                    ctCpuMega)
                {
                  setSlotHuman (i);

                  foundNewSlotForHuman = true;
                  break;
                }
              }
            }

            if (foundNewSlotForHuman == false)
            {
              ServerInterface *serverInterface =
                NetworkManager::getInstance ().getServerInterface ();
              ConnectionSlot *slot = serverInterface->getSlot (0, true);
              if (slot != NULL && slot->isConnected () == true)
              {
                serverInterface->removeSlot (0);
              }
              setSlotHuman (0);
            }
          }
        }

        for (int i = mapInfo.players; i < GameConstants::maxPlayers; ++i)
        {
          if (listBoxControls[i].getSelectedItemIndex () != ctNetwork &&
              listBoxControls[i].getSelectedItemIndex () !=
              ctNetworkUnassigned)
          {
//printf("Closed A [%d] [%s]\n",i,labelPlayerNames[i].getText().c_str());

            listBoxControls[i].setSelectedItemIndex (ctClosed);
          }
        }
      }
      catch (const std::exception & ex)
      {
        char szBuf[8096] = "";
        snprintf (szBuf, 8096, "In [%s::%s %d]\nError detected:\n%s\n",
                  extractFileFromDirectoryPath (__FILE__).c_str (),
                  __FUNCTION__, __LINE__, ex.what ());
        SystemFlags::OutputDebug (SystemFlags::debugError, szBuf);
        throw megaglest_runtime_error (szBuf);
      }
    }

    void MenuStateCustomGame::updateNetworkSlots ()
    {
      try
      {
        ServerInterface *serverInterface =
          NetworkManager::getInstance ().getServerInterface ();

        if (hasNetworkGameSettings () == true)
        {
          if (hasCheckedForUPNP == false)
          {

            if (checkBoxPublishServer.getValue () == true ||
                this->headlessServerMode == true)
            {

              hasCheckedForUPNP = true;
              serverInterface->getServerSocket ()->NETdiscoverUPnPDevices ();
            }
          }
        }
        else
        {
          hasCheckedForUPNP = false;
        }

        for (int i = 0; i < GameConstants::maxPlayers; ++i)
        {
          ConnectionSlot *slot = serverInterface->getSlot (i, true);
//printf("A i = %d control type = %d slot [%p]\n",i,listBoxControls[i].getSelectedItemIndex(),slot);

          if (slot == NULL &&
              listBoxControls[i].getSelectedItemIndex () == ctNetwork)
          {
            try
            {
              serverInterface->addSlot (i);
            }
            catch (const std::exception & ex)
            {
              char szBuf[8096] = "";
              snprintf (szBuf, 8096,
                        "In [%s::%s %d]\nError detected:\n%s\n",
                        extractFileFromDirectoryPath (__FILE__).c_str (),
                        __FUNCTION__, __LINE__, ex.what ());
              SystemFlags::OutputDebug (SystemFlags::debugError, szBuf);
              if (SystemFlags::getSystemSettingType
                  (SystemFlags::debugSystem).enabled)
                SystemFlags::OutputDebug (SystemFlags::debugSystem, "%s",
                                          szBuf);
              showGeneralError = true;
              if (serverInterface->isPortBound () == false)
              {
                generalErrorToShow =
                  Lang::getInstance ().getString ("ErrorBindingPort") +
                  " : " + intToStr (serverInterface->getBindPort ());
              }
              else
              {
                generalErrorToShow = ex.what ();
              }

// Revert network to CPU
              listBoxControls[i].setSelectedItemIndex (ctCpu);
            }
          }
          slot = serverInterface->getSlot (i, true);
          if (slot != NULL)
          {
            if ((listBoxControls[i].getSelectedItemIndex () != ctNetwork)
                || (listBoxControls[i].getSelectedItemIndex () ==
                    ctNetwork && slot->isConnected () == false
                    && i >= mapInfo.players))
            {
              if (slot->getCanAcceptConnections () == true)
              {
                slot->setCanAcceptConnections (false);
              }
              if (slot->isConnected () == true)
              {
                if (listBoxControls[i].getSelectedItemIndex () !=
                    ctNetworkUnassigned)
                {
                  listBoxControls[i].setSelectedItemIndex
                    (ctNetworkUnassigned);
                }
              }
              else
              {
                serverInterface->removeSlot (i);

                if (listBoxControls[i].getSelectedItemIndex () ==
                    ctNetworkUnassigned)
                {
                  listBoxControls[i].setSelectedItemIndex (ctClosed);
                }
              }
            }
            else if (slot->getCanAcceptConnections () == false)
            {
              slot->setCanAcceptConnections (true);
            }
          }
        }
      }
      catch (const std::exception & ex)
      {
        char szBuf[8096] = "";
        snprintf (szBuf, 8096, "In [%s::%s %d]\nError detected:\n%s\n",
                  extractFileFromDirectoryPath (__FILE__).c_str (),
                  __FUNCTION__, __LINE__, ex.what ());
        SystemFlags::OutputDebug (SystemFlags::debugError, szBuf);
        if (SystemFlags::
            getSystemSettingType (SystemFlags::debugSystem).enabled)
          SystemFlags::OutputDebug (SystemFlags::debugSystem, "%s", szBuf);
//throw megaglest_runtime_error(szBuf);
        showGeneralError = true;
        generalErrorToShow = szBuf;

      }
    }

    void MenuStateCustomGame::updateAllResourceMultiplier ()
    {
      for (int j = 0; j < GameConstants::maxPlayers; ++j)
      {
        updateResourceMultiplier (j);
      }
    }

    void MenuStateCustomGame::updateResourceMultiplier (const int index)
    {
//printf("Line: %d multiplier index: %d index: %d\n",__LINE__,listBoxRMultiplier[index].getSelectedItemIndex(),index);

      ControlType ct =
        static_cast < ControlType >
        (listBoxControls[index].getSelectedItemIndex ());
      if (ct == ctCpuEasy || ct == ctNetworkCpuEasy)
      {
        listBoxRMultiplier[index].setSelectedItem (floatToStr
                                                   (GameConstants::
                                                    easyMultiplier, 1));
        listBoxRMultiplier[index].setEnabled (checkBoxScenario.getValue () ==
                                              false);
      }
      else if (ct == ctCpu || ct == ctNetworkCpu)
      {
        listBoxRMultiplier[index].setSelectedItem (floatToStr
                                                   (GameConstants::
                                                    normalMultiplier, 1));
        listBoxRMultiplier[index].setEnabled (checkBoxScenario.getValue () ==
                                              false);
      }
      else if (ct == ctCpuUltra || ct == ctNetworkCpuUltra)
      {
        listBoxRMultiplier[index].setSelectedItem (floatToStr
                                                   (GameConstants::
                                                    ultraMultiplier, 1));
        listBoxRMultiplier[index].setEnabled (checkBoxScenario.getValue () ==
                                              false);
      }
      else if (ct == ctCpuMega || ct == ctNetworkCpuMega)
      {
        listBoxRMultiplier[index].setSelectedItem (floatToStr
                                                   (GameConstants::
                                                    megaMultiplier, 1));
        listBoxRMultiplier[index].setEnabled (checkBoxScenario.getValue () ==
                                              false);
      }
//if(ct == ctHuman || ct == ctNetwork || ct == ctClosed) {
      else
      {
        listBoxRMultiplier[index].setSelectedItem (floatToStr
                                                   (GameConstants::
                                                    normalMultiplier, 1));
        listBoxRMultiplier[index].setEnabled (false);
//!!!listBoxRMultiplier[index].setEnabled(checkBoxScenario.getValue() == false);
      }

      listBoxRMultiplier[index].
        setEditable (listBoxRMultiplier[index].getEnabled ());
      listBoxRMultiplier[index].setVisible (ct != ctHuman && ct != ctNetwork
                                            && ct != ctClosed);
//listBoxRMultiplier[index].setVisible(ct != ctClosed);

//printf("Line: %d multiplier index: %d index: %d\n",__LINE__,listBoxRMultiplier[index].getSelectedItemIndex(),index);
    }
  } // end namespace
}
