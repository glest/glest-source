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

#ifndef _SHARED_UTIL_PROPERTIES_H_
#define _SHARED_UTIL_PROPERTIES_H_

#include <string>
#include <map>
#include <vector>
#include "leak_dumper.h"
#include "platform_common.h"

using std::map;
using std::vector;
using std::string;
using std::pair;

namespace Shared {
	namespace Util {

		// =====================================================
		//	class Properties
		//
		///	ini-like file loader
		// =====================================================

		class Properties {
		private:
			static const int maxLine = 4096;

		public:
			typedef pair<string, string> PropertyPair;
			typedef map<string, string> PropertyMap;
			typedef vector<PropertyPair> PropertyVector;

		private:
			PropertyVector propertyVector;
			PropertyMap propertyMap;
			PropertyVector propertyVectorTmp;
			PropertyMap propertyMapTmp;

			string path;
			static string applicationPath;
			static string applicationDataPath;

			static string techtreePath;
			static string scenarioPath;
			static string tutorialPath;

		protected:
			void processTextLine(bool is_utf8_language, char *lineBuffer);

		public:
			static void setApplicationPath(string value) {
				Shared::PlatformCommon::replaceAll(value, "\\", "/");
				applicationPath = value;
			}
			static string getApplicationPath() {
				return applicationPath;
			}

			static void setApplicationDataPath(string value) {
				Shared::PlatformCommon::replaceAll(value, "\\", "/");
				applicationDataPath = value;
			}
			static string getApplicationDataPath() {
				return applicationDataPath;
			}

			static void setTechtreePath(string value) {
				Shared::PlatformCommon::replaceAll(value, "\\", "/");
				techtreePath = value;
			}
			static string getTechtreePath() {
				return techtreePath;
			}
			static void setScenarioPath(string value) {
				Shared::PlatformCommon::replaceAll(value, "\\", "/");
				scenarioPath = value;
			}
			static string getScenarioPath() {
				return scenarioPath;
			}
			static void setTutorialPath(string value) {
				Shared::PlatformCommon::replaceAll(value, "\\", "/");
				tutorialPath = value;
			}
			static string getTutorialPath() {
				return tutorialPath;
			}

			void clear();

			void loadFromText(const string &text);
			void load(const string &path, bool clearCurrentProperties = true);
			void save(const string &path);

			int getPropertyCount() const;
			string getKey(int i) const;
			string getString(int i) const;

			bool getBool(const string &key, const char *defaultValueIfNotFound = NULL) const;
			int getInt(const string &key, const char *defaultValueIfNotFound = NULL) const;
			int getInt(const string &key, int min, int max, const char *defaultValueIfNotFound = NULL) const;
			float getFloat(const string &key, const char *defaultValueIfNotFound = NULL) const;
			float getFloat(const string &key, float min, float max, const char *defaultValueIfNotFound = NULL) const;

			const string getString(const string &key, const char *defaultValueIfNotFound = "") const;

			int getInt(const char *key, const char *defaultValueIfNotFound = NULL) const;
			bool getBool(const char *key, const char *defaultValueIfNotFound = NULL) const;
			float getFloat(const char *key, const char *defaultValueIfNotFound = NULL) const;
			const string getString(const char *key, const char *defaultValueIfNotFound = NULL) const;
			const string getRandomKey(const bool realrandom) const;

			void setInt(const string &key, int value);
			void setBool(const string &key, bool value);
			void setFloat(const string &key, float value);
			void setString(const string &key, const string &value);

			bool hasString(const string &key) const;

			static bool applyTagsToValue(string &value, const std::map<string, string> *mapTagReplacementValues = NULL, bool skipUpdatePathClimbingParts = false);
			static std::map<string, string> getTagReplacementValues(std::map<string, string> *mapExtraTagReplacementValues = NULL);
			static bool isValuePathVariable(const string &value);
			static void updateValuePathVariable(string &value, bool skipUpdatePathClimbingParts = false);

			string getpath() const {
				return path;
			}

			string toString();
		};

	}
} //end namespace

#endif
