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

#include "auto_test.h"

#include "program.h"
#include "main_menu.h"
#include "menu_state_new_game.h"
#include "menu_state_scenario.h"
#include "menu_state_custom_game.h"
#include "game.h"
#include "core_data.h"
#include "config.h"

#include "leak_dumper.h"


namespace Glest {
	namespace Game {

		// =====================================================
		//	class AutoTest
		// =====================================================

		const time_t AutoTest::invalidTime = -1;
		time_t AutoTest::gameTime = 60 * 20;
		bool AutoTest::wantExitGame = false;

		GameSettings AutoTest::gameSettings;
		string AutoTest::loadGameSettingsFile = "";

		// ===================== PUBLIC ========================

		AutoTest::AutoTest() {
			exitGame = false;
			gameStartTime = invalidTime;
			random.init(time(NULL));
		}

		AutoTest & AutoTest::getInstance() {
			static AutoTest autoTest;
			return autoTest;
		}

		void AutoTest::updateIntro(Program *program) {
			program->setState(new MainMenu(program));
		}

		void AutoTest::updateRoot(Program *program, MainMenu *mainMenu) {
			mainMenu->setState(new MenuStateNewGame(program, mainMenu));
		}

		void AutoTest::updateNewGame(Program *program, MainMenu *mainMenu) {
			if (loadGameSettingsFile != "") {
				gameStartTime = invalidTime;
				bool fileFound = CoreData::getInstance().loadGameSettingsFromFile(
					loadGameSettingsFile, &gameSettings);

				if (fileFound == false) {
					throw game_runtime_error("Specified game settings file [" + loadGameSettingsFile + "] was NOT found!");
				}
				//printf("Got settings:\n%s",gameSettings.toString().c_str());
				mainMenu->setState(new MenuStateCustomGame(program, mainMenu, false, pNewGame, true, &gameSettings));
			} else {
				mainMenu->setState(new MenuStateScenario(program, mainMenu, false,
					Config::getInstance().getPathListForType(ptScenarios)));
			}
		}

		void AutoTest::updateScenario(MenuStateScenario *menuStateScenario) {
			gameStartTime = invalidTime;

			int scenarioIndex = random.randRange(0, menuStateScenario->getScenarioCount() - 1);
			menuStateScenario->setScenario(scenarioIndex);

			menuStateScenario->launchGame();
		}

		bool AutoTest::updateGame(Game *game) {
			// record start time
			if (gameStartTime == invalidTime) {
				gameStartTime = time(NULL);
			}

			// quit if we've espend enough time in the game
			if (difftime(time(NULL), gameStartTime) > gameTime) {
				Program *program = game->getProgram();
				Stats endStats = game->quitGame();
				if (AutoTest::wantExitGame == true) {
					exitGame = true;
				}
				Game::exitGameState(program, endStats);
				return true;
			}

			return false;
		}

		void AutoTest::updateBattleEnd(Program *program) {
			program->setState(new MainMenu(program));
		}

	}
}//end namespace
