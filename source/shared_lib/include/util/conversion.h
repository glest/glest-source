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

#ifndef _SHARED_UTIL_CONVERSION_H_
#define _SHARED_UTIL_CONVERSION_H_

#include <string>
#include "data_types.h"
#include "leak_dumper.h"

using std::string;

using namespace Shared::Platform;

namespace Shared {
	namespace Util {

		bool strToBool(const string &s);
		int strToInt(const string &s);
		uint32 strToUInt(const string &s);
		float strToFloat(const string &s);

		bool strToBool(const string &s, bool *b);
		bool strToInt(const string &s, int *i);
		bool strToUInt(const string &s, uint32 *i);
		bool strToFloat(const string &s, float *f);

		string boolToStr(bool b);
		string uIntToStr(const uint64 value);
		string intToStr(const int64 value);
		string intToHex(int i);
		string floatToStr(float f, int precision = 2);
		string doubleToStr(double f, int precision = 2);

		bool IsNumeric(const char *p, bool  allowNegative = true);

		string formatNumber(uint64 f);

		double getTimeDurationMinutes(int frames, int updateFps);
		string getTimeDurationString(int frames, int updateFps);

	}
} //end namespace

#endif
