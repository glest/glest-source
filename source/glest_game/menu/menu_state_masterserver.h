//
//      menu_state_masterserver.h: game setup menu as it appears to
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

#ifndef _GLEST_GAME_MENUSTATEMASTERSERVER_H_
#   define _GLEST_GAME_MENUSTATEMASTERSERVER_H_

#   include "main_menu.h"
#   include "server_line.h"
#   include "masterserver_info.h"
#   include "simple_threads.h"
#   include "network_interface.h"
#   include "ircclient.h"
#   include "chat_manager.h"
#   include "leak_dumper.h"

namespace Glest
{
  namespace Game
  {

// ===============================
//      class MenuStateMasterserver
// ===============================
    typedef vector < ServerLine * >ServerLines;
    typedef vector < GraphicButton * >UserButtons;
    typedef vector < MasterServerInfo * >MasterServerInfos;

    class MenuStateMasterserver:public MenuState,
      public SimpleTaskCallbackInterface, public IRCCallbackInterface
    {

    private:

      GraphicButton buttonRefresh;
      GraphicButton buttonReturn;
      GraphicButton buttonCreateGame;
      GraphicLabel labelAutoRefresh;
      GraphicListBox listBoxAutoRefresh;
      GraphicLabel labelTitle;

      GraphicLabel announcementLabel;
      GraphicLabel versionInfoLabel;

      GraphicLine lines[3];

      GraphicLabel glestVersionLabel;
      GraphicLabel platformLabel;
      //GraphicLabel binaryCompileDateLabel;

      //game info:
      GraphicLabel serverTitleLabel;
      GraphicLabel countryLabel;
      GraphicLabel statusLabel;

      GraphicLabel ipAddressLabel;

      //game setup info:
      GraphicLabel techLabel;
      GraphicLabel mapLabel;
      GraphicLabel tilesetLabel;
      GraphicLabel activeSlotsLabel;

      GraphicLabel externalConnectPort;

      GraphicLabel selectButton;

      GraphicMessageBox mainMessageBox;
      int mainMessageBoxState;

      GraphicLabel ircOnlinePeopleLabel;
      GraphicLabel ircOnlinePeopleStatusLabel;

      bool announcementLoaded;
      bool needUpdateFromServer;
      int autoRefreshTime;
      time_t lastRefreshTimer;
      SimpleTaskThread *updateFromMasterserverThread;
      bool playServerFoundSound;
      ServerLines serverLines;
      string serverInfoString;
      int serverLinesToRender;
      int serverLinesYBase;
      int serverLinesLineHeight;
      GraphicScrollBar userScrollBar;
      GraphicScrollBar serverScrollBar;
      UserButtons userButtons;
      UserButtons userButtonsToRemove;
      int userButtonsToRender;
      int userButtonsYBase;
      int userButtonsXBase;
      int userButtonsLineHeight;
      int userButtonsHeight;
      int userButtonsWidth;
      string currentIrcNick;


      //Console console;

      static DisplayMessageFunction pCB_DisplayMessage;
        std::string threadedErrorMsg;

        std::vector < string > ircArgs;
      Mutex *mutexIRCClient;
      IRCThread *ircClient;
        std::vector < string > oldNickList;

      Console consoleIRC;
      ChatManager chatManager;

      bool masterserverParseErrorShown;

    public:
        MenuStateMasterserver (Program * program, MainMenu * mainMenu);
       ~MenuStateMasterserver ();

      void mouseClick (int x, int y, MouseButton mouseButton);
      void mouseUp (int x, int y, const MouseButton mouseButton);
      void mouseMove (int x, int y, const MouseState * mouseState);
      void update ();
      void render ();

      virtual bool textInput (std::string text);
      virtual void keyDown (SDL_KeyboardEvent key);

      virtual void simpleTask (BaseThread * callingThread, void *userdata);
      virtual bool isInSpecialKeyCaptureEvent ()
      {
        return chatManager.getEditEnabled ();
      }

      static void setDisplayMessageFunction (DisplayMessageFunction
                                             pDisplayMessage)
      {
        pCB_DisplayMessage = pDisplayMessage;
      }

      virtual void reloadUI ();

    private:
      void showMessageBox (const string & text, const string & header,
                           bool toggle);
      bool connectToServer (string ipString, int port);
      //void setConsolePos(int yPos);
      void setButtonLinePosition (int pos);
      void clearServerLines ();
      void clearUserButtons ();
      void rebuildServerLines (const string & serverInfo);
      void cleanup ();
      virtual void IRC_CallbackEvent (IRCEventType evt, const char *origin,
                                      const char **params,
                                      unsigned int count);

    };


}}                              //end namespace

#endif
