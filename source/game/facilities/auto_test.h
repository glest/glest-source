// This file is part of Glest <https://github.com/Glest>
//
// Copyright (C) 2018  The Glest team
//
// Glest is a fork of MegaGlest <https://megaglest.org/>
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

#ifndef _SHARED_UTIL_AUTO_TEST_H_
#define _SHARED_UTIL_AUTO_TEST_H_

#ifdef WIN32
#include <winsock2.h>
#include <winsock.h>
#endif

#include <ctime>
#include "randomgen.h"
#include <string>
#include "game_settings.h"
#include "leak_dumper.h"

using namespace std;
using Shared::Util::RandomGen;

namespace Game {
	class Program;
	class MainMenu;
	class MenuStateScenario;
	class Game;

	// =====================================================
	//	class AutoTest  
	//
	/// Interface to write log files
	// =====================================================

	class AutoTest {
	private:
		int gameStartTime;
		RandomGen random;
		bool exitGame;
		static bool wantExitGame;

		static GameSettings gameSettings;
		static string loadGameSettingsFile;

		static const time_t invalidTime;
		static time_t gameTime;

	public:
		static AutoTest & getInstance();
		AutoTest();

		static void setMaxGameTime(time_t value) {
			gameTime = value;
		}
		static void setWantExitGameWhenDone(bool value) {
			wantExitGame = value;
		}
		static string getLoadGameSettingsFile() {
			return loadGameSettingsFile;
		}
		static void setLoadGameSettingsFile(const string &filename) {
			loadGameSettingsFile = filename;
		}

		bool mustExitGame() const {
			return exitGame;
		}

		void updateIntro(Program *program);
		void updateRoot(Program *program, MainMenu *mainMenu);
		void updateNewGame(Program *program, MainMenu *mainMenu);
		void updateScenario(MenuStateScenario *menuStateScenario);
		bool updateGame(Game *game);
		void updateBattleEnd(Program *program);
	};

} //end namespace

#endif
