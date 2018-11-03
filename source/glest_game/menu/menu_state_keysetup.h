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

#ifndef _MENUSTATEKEYSETUP_H_
#define _MENUSTATEKEYSETUP_H_

#include "main_menu.h"
#include "server_line.h"
#include "leak_dumper.h"

namespace Game {
	// ===============================
	//      class
	// ===============================
	typedef vector < GraphicButton * >UserButtons;
	typedef vector < GraphicLabel * >GraphicLabels;

	class MenuStateKeysetup :public MenuState {

	private:

		GraphicButton buttonOk;
		GraphicButton buttonDefaults;
		GraphicButton buttonReturn;

		GraphicButton buttonKeyboardSetup;        // configure the keyboard
		GraphicButton buttonVideoSection;
		GraphicButton buttonAudioSection;
		GraphicButton buttonMiscSection;
		GraphicButton buttonNetworkSettings;

		GraphicLabel labelTitle;

		GraphicScrollBar keyScrollBar;
		UserButtons keyButtons;
		GraphicLabels labels;
		int keyButtonsToRender;
		int keyButtonsYBase;
		int keyButtonsXBase;
		int keyButtonsLineHeight;
		int keyButtonsHeight;
		int keyButtonsWidth;

		GraphicMessageBox mainMessageBox;
		int mainMessageBoxState;
		vector < pair < string, string > >mergedProperties;
		vector < pair < string, string > >masterProperties;
		vector < pair < string, string > >userProperties;

		int hotkeyIndex;
		//char hotkeyChar;
		SDL_Keycode hotkeyChar;

		GraphicLabel labelTestTitle;
		GraphicLabel labelTestValue;

		ProgramState **parentUI;

	public:
		MenuStateKeysetup(Program * program, MainMenu * mainMenu,
			ProgramState ** parentUI = NULL);
		virtual ~MenuStateKeysetup();

		void mouseClick(int x, int y, MouseButton mouseButton);
		void mouseUp(int x, int y, const MouseButton mouseButton);
		void mouseMove(int x, int y, const MouseState * mouseState);
		void update();
		void render();

		virtual void keyDown(SDL_KeyboardEvent key);
		virtual void keyPress(SDL_KeyboardEvent c);
		virtual void keyUp(SDL_KeyboardEvent key);

		virtual bool isInSpecialKeyCaptureEvent() {
			return true;
		}

		//static void setDisplayMessageFunction(DisplayMessageFunction pDisplayMessage) { pCB_DisplayMessage = pDisplayMessage; }

		void reloadUI();

	private:
		void showMessageBox(const string & text, const string & header,
			bool toggle);
		void clearUserButtons();
		void cleanup();
	};
} //end namespace

#endif
