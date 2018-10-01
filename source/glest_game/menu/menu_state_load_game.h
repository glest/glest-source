//
//      menu_state_load_game.h:
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

#ifndef _GLEST_GAME_MENUSTATELOADGAME_H_
#   define _GLEST_GAME_MENUSTATELOADGAME_H_

#   include "main_menu.h"
#   include "leak_dumper.h"

namespace Glest {
	namespace Game {

		// ===============================
		//      class MenuStateLoadGame
		// ===============================
		//typedef vector<GraphicButton*> SaveSlotButtons;
		class MenuStateLoadGame :public MenuState {
		private:
			GraphicButton loadButton;
			GraphicButton deleteButton;
			GraphicButton abortButton;
			vector < GraphicButton * >slots;
			vector < GraphicComponent * >slotsGB;
			vector < string > filenames;
			GraphicScrollBar slotsScrollBar;
			GraphicButton *selectedButton;

			GraphicButton *buttonToDelete;

			Texture2D *previewTexture;

			GraphicLabel headerLabel;
			GraphicLabel noSavedGamesLabel;
			GraphicLabel savedGamesLabel;
			GraphicLabel infoHeaderLabel;
			GraphicLabel infoTextLabel;
			GraphicLabel versionWarningLabel;

			GraphicLine lines[2];

			GraphicMessageBox mainMessageBox;

			string saveGameDir;
			int slotLinesYBase;
			int slotsLineHeight;

		public:
			MenuStateLoadGame(Program * program, MainMenu * mainMenu);
			~MenuStateLoadGame();

			void mouseClick(int x, int y, MouseButton mouseButton);
			void mouseUp(int x, int y, const MouseButton mouseButton);
			void mouseMove(int x, int y, const MouseState * mouseState);
			void update();
			void render();
			virtual void keyDown(SDL_KeyboardEvent key);

			void reloadUI();

		private:

			void clearSlots();
			void listFiles();

			void showMessageBox(const string & text, const string & header,
				bool toggle);

			void cleanupTexture(Texture2D ** texture);
		};


	}
}                              //end namespace

#endif
