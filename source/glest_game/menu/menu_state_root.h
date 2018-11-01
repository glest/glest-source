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

#ifndef _GLEST_GAME_MENUSTATEROOT_H_
#   define _GLEST_GAME_MENUSTATEROOT_H_

#   include "main_menu.h"
#   include "simple_threads.h"
#   include "miniftpclient.h"

#   include "leak_dumper.h"

namespace Glest {
	namespace Game {

		// ===============================
		//      class MenuStateRoot  
		// ===============================

		class GraphicMessageBox;
		class PopupMenu;

		class MenuStateRoot :public MenuState, public SimpleTaskCallbackInterface,
			public FTPClientCallbackInterface {
		private:
			GraphicButton buttonNewGame;
			GraphicButton buttonLoadGame;
			GraphicButton buttonMods;
			GraphicButton buttonOptions;
			GraphicButton buttonAbout;
			GraphicButton buttonExit;
			GraphicLabel labelVersion;
			GraphicLabel labelGreeting;

			GraphicMessageBox mainMessageBox;
			GraphicMessageBox errorMessageBox;
			GraphicMessageBox ftpMessageBox;

			PopupMenu popupMenu;

			static bool gameUpdateChecked;
			SimpleTaskThread *updatesHttpServerThread;
			FTPClientThread *ftpClientThread;
			std::map < string, pair < int, string > >fileFTPProgressList;
			string ftpFileName;
			string ftpFileURL;
			int lastDownloadProgress;

			virtual void simpleTask(BaseThread * callingThread, void *userdata);
			void startFTPClientIfRequired();
			virtual void FTPClient_CallbackEvent(string itemName,
				FTP_Client_CallbackType type,
				pair < FTP_Client_ResultType,
				string > result, void *userdata);

		public:
			MenuStateRoot(Program * program, MainMenu * mainMenu);
			virtual ~MenuStateRoot();

			void mouseClick(int x, int y, MouseButton mouseButton);
			void mouseMove(int x, int y, const MouseState * mouseState);
			void render();
			void update();
			virtual void keyDown(SDL_KeyboardEvent key);

			void showMessageBox(const string & text, const string & header,
				bool toggle);
			void showErrorMessageBox(const string & text, const string & header,
				bool toggle);
			void showFTPMessageBox(const string & text, const string & header,
				bool toggle, bool okOnly);

			virtual bool isMasterserverMode() const;
			virtual void reloadUI();
		};


	}
}                              //end namespace

#endif
