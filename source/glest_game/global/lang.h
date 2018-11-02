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

#ifndef _GLEST_GAME_LANG_H_
#   define _GLEST_GAME_LANG_H_

#   ifdef WIN32
#      include <winsock2.h>
#      include <winsock.h>
#   endif

#   include "properties.h"
#   include "leak_dumper.h"

namespace ZetaGlest {
	namespace Game {

		using Shared::Util::Properties;

		// =====================================================
		//      class Lang
		//
		//      String table
		// =====================================================

		class Lang {
		private:

			bool is_utf8_language;
			string language;
			std::map < string, Properties > gameStringsAllLanguages;

			Properties scenarioStrings;

			Properties tilesetStrings;
			Properties tilesetStringsDefault;

			std::map < string, std::map < string,
				Properties > >techTreeStringsAllLanguages;
			string techNameLoaded;
			bool allowNativeLanguageTechtree;

		private:
			Lang();
			void loadGameStringProperties(string language, Properties & properties,
				bool fileMustExist,
				bool fallbackToDefault = false);
			bool fileMatchesISO630Code(string uselanguage,
				string testLanguageFile);
			string getNativeLanguageName(string uselanguage,
				string testLanguageFile);

			string parseResult(const string & key, const string & value);

		public:
			static Lang & getInstance();

			string getTechNameLoaded() const {
				return techNameLoaded;
			}
			bool getAllowNativeLanguageTechtree() const {
				return allowNativeLanguageTechtree;
			}
			void setAllowNativeLanguageTechtree(bool value) {
				allowNativeLanguageTechtree = value;
			}

			void loadGameStrings(string uselanguage, bool loadFonts =
				true, bool fallbackToDefault = false);
			void loadScenarioStrings(string scenarioDir, string scenarioName,
				bool isTutorial);
			bool loadTechTreeStrings(string techTree, bool forceLoad = false);
			void loadTilesetStrings(string tileset);

			string getString(const string & s, string uselanguage = "");
			bool hasString(const string & s, string uselanguage =
				"", bool fallbackToDefault = false);

			string getScenarioString(const string & s);
			bool hasScenarioString(const string & s);

			string getTechTreeString(const string & s, const char *defaultValue =
				NULL);
			string getTilesetString(const string & s, const char *defaultValue =
				NULL);

			string getLanguage() const {
				return language;
			}
			bool isLanguageLocal(string compareLanguage) const;
			//bool isUTF8Language() const;
			string getDefaultLanguage() const;

			map < string,
				string > getDiscoveredLanguageList(bool searchKeyIsLangName = false);
			pair < string,
				string > getNavtiveNameFromLanguageName(string langName);

			string getLanguageFile(string uselanguage);
		};

	}
}                              //end namespace

#endif
