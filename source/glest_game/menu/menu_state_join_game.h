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

#ifndef _MENUSTATEJOINGAME_H_
#define _MENUSTATEJOINGAME_H_

#ifdef WIN32
#   include <winsock2.h>
#   include <winsock.h>
#endif

#include "properties.h"
#include "main_menu.h"
#include "chat_manager.h"
#include <vector>
#include <string>
#include "leak_dumper.h"

using Shared::Util::Properties;

namespace Game {
	class NetworkMessageIntro;

	// ===============================
	//      class MenuStateJoinGame
	// ===============================

	class MenuStateJoinGame :
		public MenuState, public DiscoveredServersInterface {
	private:
		static const int
			newServerIndex;
		static const int
			newPrevServerIndex;
		static const int
			foundServersIndex;

	private:
		GraphicButton buttonReturn;
		GraphicButton buttonConnect;
		GraphicButton buttonAutoFindServers;
		GraphicButton buttonCreateGame;

		GraphicLabel labelServer;
		GraphicLabel labelServerType;
		GraphicLabel labelServerIp;
		GraphicLabel labelStatus;
		GraphicLabel labelInfo;
		GraphicListBox listBoxServerType;
		GraphicListBox listBoxServers;
		GraphicListBox listBoxFoundServers;
		GraphicLabel labelServerPort;
		GraphicLabel labelServerPortLabel;


		bool connected;
		int
			playerIndex;
		Properties servers;

		//Console console;
		ChatManager chatManager;

		bool abortAutoFind;
		bool autoConnectToServer;

	public:
		MenuStateJoinGame(Program * program, MainMenu * mainMenu,
			bool connect = false, Ip serverIp =
			Ip(), int portNumberOverride = -1);
		MenuStateJoinGame(Program * program, MainMenu * mainMenu,
			bool * autoFindHost);
		virtual ~MenuStateJoinGame();

		void
			mouseClick(int x, int y, MouseButton mouseButton);
		void
			mouseMove(int x, int y, const MouseState * mouseState);
		void
			render();
		void
			update();

		virtual
			bool
			textInput(std::string text);
		virtual void
			keyDown(SDL_KeyboardEvent key);
		virtual void
			keyPress(SDL_KeyboardEvent c);

		virtual
			bool
			isInSpecialKeyCaptureEvent() {
			return chatManager.getEditEnabled();
		}

		void
			reloadUI();

	private:

		void
			CommonInit(bool connect, Ip serverIp, int portNumberOverride);
		bool connectToServer();
		virtual void
			DiscoveredServers(std::vector < string > serverList);
	};
} //end namespace

#endif
