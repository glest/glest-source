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

#ifndef _GAMEUTIL_H_
#define _GAMEUTIL_H_

#ifdef WIN32
#   include <winsock2.h>
#   include <winsock.h>
#endif

#include <string>
#include <vector>
#include "util.h"
#include "leak_dumper.h"

using std::string;

namespace Game {
	extern const char *mailString;

	void initSpecialStrings();
	string getCrashDumpFileName();
	string getPlatformTypeNameString();
	string getPlatformArchTypeNameString();
	string getPlatformNameString();
	string getCompilerNameString();
	string getAboutString1(int i);
	string getAboutString2(int i);
	string getTeammateName(int i);
	string getTeammateRole(int i);
	bool checkVersionCompatibility(string clientVersionString, string serverVersionString);
	string formatString(string str);

	string getGameReadWritePath(const string & lookupKey = "");
	string getGameCustomCoreDataPath(string originalBasePath,
		string uniqueFilePath);

	bool upgradeFilesInTemp();

} //end namespace

#endif
