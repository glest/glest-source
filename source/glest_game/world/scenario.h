//
//      scenario.h:
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
//      along with this program.  If not, see <https://www.gnu.org/licenses/>

#ifndef _GLEST_GAME_SCENARIO_H_
#  define _GLEST_GAME_SCENARIO_H_

#  ifdef WIN32
#    include <winsock2.h>
#    include <winsock.h>
#  endif

#  include <string>
#  include <vector>
#  include "xml_parser.h"
#  include "checksum.h"
#  include "game_settings.h"

#  include "leak_dumper.h"

using std::string;
using std::vector;
using std::pair;

using Shared::Xml::XmlNode;
using namespace Shared::Util;

namespace Glest {
	namespace Game {

		enum Difficulty {
			dVeryEasy,
			dEasy,
			dMedium,
			dHard,
			dVeryHard,
			dInsane
		};

		class ScenarioInfo {

		public:
			ScenarioInfo() {
				difficulty = 0;
				for (unsigned int i = 0;
					i < (unsigned int) GameConstants::maxPlayers; ++i) {
					factionControls[i] = ctClosed;
					teams[i] = 0;
					factionTypeNames[i] = "";
					resourceMultipliers[i] = 0;
				} mapName = "";
				tilesetName = "";
				techTreeName = "";

				defaultUnits = false;
				defaultResources = false;
				defaultVictoryConditions = false;

				desc = "";

				fogOfWar = false;
				fogOfWar_exploredFlag = false;

				allowTeamUnitSharing = false;
				allowTeamResourceSharing = false;

				file = "";
				name = "";
				namei18n = "";
			} int difficulty;
			ControlType factionControls[GameConstants::maxPlayers];
			int teams[GameConstants::maxPlayers];
			string factionTypeNames[GameConstants::maxPlayers];
			float resourceMultipliers[GameConstants::maxPlayers];

			string mapName;
			string tilesetName;
			string techTreeName;

			bool defaultUnits;
			bool defaultResources;
			bool defaultVictoryConditions;

			string desc;

			bool fogOfWar;
			bool fogOfWar_exploredFlag;

			bool allowTeamUnitSharing;
			bool allowTeamResourceSharing;

			string file;
			string name;
			string namei18n;
		};

		// =====================================================
		//      class Script
		// =====================================================

		class Script {
		private:
			string name;
			string code;

		public:
			Script(const string & name, const string & code) {
				this->name = name;
				this->code = code;
			} const string & getName() const {
				return name;
			}
			const string & getCode() const {
				return code;
			}
		};

		// =====================================================
		//      class Scenario
		// =====================================================

		class Scenario {
		private:
			typedef pair < string, string > NameScriptPair;
			typedef vector < Script > Scripts;

			ScenarioInfo info;
			Scripts scripts;
			Checksum checksumValue;

		public:
			~Scenario();
			Checksum load(const string & path);
			Checksum *getChecksumValue() {
				return &checksumValue;
			}
			int getScriptCount() const {
				return (int) scripts.size();
			} const Script *getScript(int i) const {
				return &scripts[i];
			}
			ScenarioInfo getInfo() const {
				return info;
			}
			static bool isGameTutorial(string path);
			static string getScenarioPath(const vector < string > dir,
				const string & scenarioName,
				bool getMatchingRootScenarioPathOnly =
				false);
			static string getScenarioPath(const string & dir,
				const string & scenarioName);
			static int getScenarioPathIndex(const vector < string > dirList,
				const string & scenarioName);
			static string getScenarioDir(const vector < string > dir,
				const string & scenarioName);

			static bool loadScenarioInfo(string file,
				ScenarioInfo * scenarioInfo,
				bool isTutorial);
			static ControlType strToControllerType(const string & str);
			static string controllerTypeToStr(const ControlType & ct);

			static void loadGameSettings(const vector < string > &dirList,
				const ScenarioInfo * scenarioInfo,
				GameSettings * gameSettings,
				string scenarioDescription);

		private:
			string getFunctionName(const XmlNode * scriptNode);
		};

	}
}                              //end namespace

#endif
