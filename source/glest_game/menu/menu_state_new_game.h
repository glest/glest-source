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

#ifndef _GLEST_GAME_MENUSTATENEWGAME_H_
#   define _GLEST_GAME_MENUSTATENEWGAME_H_

#   include "main_menu.h"
#   include "leak_dumper.h"

namespace ZetaGlest {
	namespace Game {

		// ===============================
		//      class MenuStateNewGame  
		// ===============================

		class MenuStateNewGame :public MenuState {
		private:
			GraphicButton buttonCustomGame;
			GraphicButton buttonScenario;
			GraphicButton buttonJoinGame;
			GraphicButton buttonMasterserverGame;
			GraphicButton buttonTutorial;
			GraphicButton buttonReturn;

		public:
			MenuStateNewGame(Program * program, MainMenu * mainMenu);

			void mouseClick(int x, int y, MouseButton mouseButton);
			void mouseMove(int x, int y, const MouseState * mouseState);
			void update();
			void render();
			virtual void keyDown(SDL_KeyboardEvent key);

			void reloadUI();
		};


	}
}                              //end namespace

#endif
