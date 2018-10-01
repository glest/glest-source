//
//      menu_state_about.h:
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
//      along with this program.  If not, see <https://www.gnu.org/licenses/>```

#ifndef _GLEST_GAME_MENUSTATEABOUT_H_
#   define _GLEST_GAME_MENUSTATEABOUT_H_

#   ifdef WIN32
#      include <winsock2.h>
#      include <winsock.h>
#   endif

#   include "main_menu.h"
#   include "leak_dumper.h"

namespace Glest {
	namespace Game {

		// ===============================
		//      class MenuStateAbout  
		// ===============================

		class MenuStateAbout :public MenuState {
		public:
			static const int aboutStringCount1 = 4;
			static const int aboutStringCount2 = 3;
			static const int teammateCount = 9;
			static const int teammateTopLineCount = 5;

		private:
			GraphicButton buttonReturn;
			GraphicLabel labelAdditionalCredits;
			GraphicLabel labelAbout1[aboutStringCount1];
			GraphicLabel labelAbout2[aboutStringCount2];
			GraphicLabel labelTeammateName[teammateCount];
			GraphicLabel labelTeammateRole[teammateCount];

			bool adjustModelText;
			string loadAdditionalCredits();

			bool enableCustomModCredits;
			Texture2D *customModTexture;
			int customModTextureX;
			int customModTextureY;
			int customModTextureW;
			int customModTextureH;
			float customModTextureAlpha;

			GraphicLabel labelCustomModCredits;

		public:
			MenuStateAbout(Program * program, MainMenu * mainMenu);
			virtual ~MenuStateAbout();

			void mouseClick(int x, int y, MouseButton mouseButton);
			void mouseMove(int x, int y, const MouseState * mouseState);
			void render();
			virtual void keyDown(SDL_KeyboardEvent key);

			virtual void reloadUI();
		};

	}
}                              //end namespace

#endif
