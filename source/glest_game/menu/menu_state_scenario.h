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

#ifndef _GLEST_GAME_MENUSTATESCENARIO_H_
#   define _GLEST_GAME_MENUSTATESCENARIO_H_

#   include "main_menu.h"
#   include "leak_dumper.h"

namespace Glest {
	namespace Game {

		// ===============================
		//      class MenuStateScenario
		// ===============================

		class MenuStateScenario :public MenuState {
		private:

			GraphicButton buttonReturn;
			GraphicButton buttonPlayNow;

			GraphicLabel labelInfo;
			GraphicLabel labelScenario;
			GraphicListBox listBoxScenario;
			GraphicLabel labelScenarioName;


			vector < string > scenarioFiles;

			ScenarioInfo scenarioInfo;
			vector < string > dirList;

			GraphicMessageBox mainMessageBox;
			int mainMessageBoxState;

			string autoloadScenarioName;

			time_t previewLoadDelayTimer;
			bool needToLoadTextures;

			bool enableScenarioTexturePreview;
			Texture2D *scenarioLogoTexture;

			bool isTutorialMode;

		public:
			MenuStateScenario(Program * program, MainMenu * mainMenu,
				bool isTutorialMode,
				const vector < string > &dirList,
				string autoloadScenarioName = "");
			virtual ~MenuStateScenario();

			void mouseClick(int x, int y, MouseButton mouseButton);
			void mouseMove(int x, int y, const MouseState * mouseState);
			void render();
			void update();

			void launchGame();
			void setScenario(int i);
			int getScenarioCount() const {
				return listBoxScenario.getItemCount();
			}

			virtual void keyDown(SDL_KeyboardEvent key);

			virtual void reloadUI();

		private:

			void loadScenarioInfo(string file, ScenarioInfo * scenarioInfo);
			void loadGameSettings(const ScenarioInfo * scenarioInfo,
				GameSettings * gameSettings);
			void loadScenarioPreviewTexture();
			Difficulty computeDifficulty(const ScenarioInfo * scenarioInfo);
			void showMessageBox(const string & text, const string & header,
				bool toggle);

			void cleanupPreviewTexture();
		};


	}
}                              //end namespace

#endif
