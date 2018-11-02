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

#ifndef _GLEST_GAME_MENUSTATEOPTIONS_SOUND_H_
#   define _GLEST_GAME_MENUSTATEOPTIONS_SOUND_H_

#   include "main_menu.h"
#   include "leak_dumper.h"

namespace ZetaGlest {
	namespace Game {

		// ===============================
		//      class MenuStateOptionsSound
		// ===============================

		class MenuStateOptionsSound :public MenuState {
		private:

			GraphicButton buttonOk;
			GraphicButton buttonReturn;

			GraphicButton buttonKeyboardSetup;        // configure the keyboard
			GraphicButton buttonVideoSection;
			GraphicButton buttonAudioSection;
			GraphicButton buttonMiscSection;
			GraphicButton buttonNetworkSettings;

			GraphicLabel labelSoundFactory;
			GraphicListBox listBoxSoundFactory;

			GraphicLabel labelVolumeFx;
			GraphicListBox listBoxVolumeFx;

			GraphicLabel labelVolumeAmbient;
			GraphicListBox listBoxVolumeAmbient;

			GraphicLabel labelVolumeMusic;
			GraphicListBox listBoxVolumeMusic;

			GraphicMessageBox mainMessageBox;
			int mainMessageBoxState;

			ProgramState **parentUI;

		public:
			MenuStateOptionsSound(Program * program, MainMenu * mainMenu,
				ProgramState ** parentUI = NULL);

			void mouseClick(int x, int y, MouseButton mouseButton);
			void mouseMove(int x, int y, const MouseState * mouseState);
			void render();
			//virtual void keyDown(SDL_KeyboardEvent key);
			virtual void keyPress(SDL_KeyboardEvent c);
			//virtual bool isInSpecialKeyCaptureEvent();

			virtual void reloadUI();


		private:
			void saveConfig();
			void setActiveInputLable(GraphicLabel * newLable);
			//void showMessageBox(const string &text, const string &header, bool toggle);
		};

	}
}                              //end namespace

#endif
