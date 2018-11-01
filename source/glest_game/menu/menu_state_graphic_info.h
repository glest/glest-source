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

#ifndef _GLEST_GAME_MENUSTATEGRAPHICINFO_H_
#   define _GLEST_GAME_MENUSTATEGRAPHICINFO_H_

#   include "main_menu.h"
#   include "leak_dumper.h"

using namespace
Shared::Graphics::Gl;

namespace
	Glest {
	namespace
		Game {

		// ===============================
		//      class MenuStateGraphicInfo  
		// ===============================

		class
			MenuStateGraphicInfo :
			public
			MenuState {
		private:
			GraphicButton
				buttonReturn;
			GraphicLabel
				labelInfo;
			GraphicLabel
				labelMoreInfo;

			GraphicLabel
				labelInternalInfo;

			//string glInfo;
			//string glMoreInfo;

		public:
			MenuStateGraphicInfo(Program * program, MainMenu * mainMenu);

			void
				mouseClick(int x, int y, MouseButton mouseButton);
			void
				mouseMove(int x, int y, const MouseState * mouseState);
			void
				render();
			virtual void
				keyDown(SDL_KeyboardEvent key);

			virtual void
				reloadUI();
		};

	}
}                              //end namespace

#endif
