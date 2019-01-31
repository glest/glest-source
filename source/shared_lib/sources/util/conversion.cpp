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

#include "conversion.h"

#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include "platform_common.h"
#include <sstream>
#include <iostream>
#include <locale>
#include "platform_util.h"
#include <limits>
#include "leak_dumper.h"

using namespace std;

namespace Shared {
	namespace Util {

		const int strSize = 256;

		bool strToBool(const string &s) {
			if (s == "0" || s == "false") {
				return false;
			}
			if (s == "1" || s == "true") {
				return true;
			}
			throw game_runtime_error("Error converting string to bool, expected 0 or 1, found: [" + s + "]");
		}

		int strToInt(const string &s) {
			char *endChar;
			setlocale(LC_NUMERIC, "C");
			int intValue = strtol(s.c_str(), &endChar, 10);

			if (*endChar != '\0') {
				throw game_runtime_error("Error converting from string to int, found: [" + s + "]");
			}

			return intValue;
		}

		uint32 strToUInt(const string &s) {
			char *endChar;
			setlocale(LC_NUMERIC, "C");
			uint32 intValue = strtoul(s.c_str(), &endChar, 10);

			if (*endChar != '\0') {
				throw game_runtime_error("Error converting from string to uint, found: [" + s + "]");
			}

			return intValue;
		}


		float strToFloat(const string &s) {
			char *endChar;

			setlocale(LC_NUMERIC, "C");
			float floatValue = static_cast<float>(strtod(s.c_str(), &endChar));

			if (*endChar != '\0') {
				throw game_runtime_error("Error converting from string to float, found: [" + s + "]");
			}

			return floatValue;
		}

		bool strToBool(const string &s, bool *b) {
			if (s == "0" || s == "false") {
				*b = false;
				return true;
			}
			if (s == "1" || s == "true") {
				*b = true;
				return true;
			}

			return false;
		}

		bool strToInt(const string &s, int *i) {
			char *endChar;

			setlocale(LC_NUMERIC, "C");
			*i = strtol(s.c_str(), &endChar, 10);

			if (*endChar != '\0') {
				return false;
			}
			return true;
		}

		bool strToUInt(const string &s, uint32 *i) {
			char *endChar;

			setlocale(LC_NUMERIC, "C");
			*i = strtoul(s.c_str(), &endChar, 10);

			if (*endChar != '\0') {
				return false;
			}
			return true;
		}

		bool strToFloat(const string &s, float *f) {
			char *endChar;
			setlocale(LC_NUMERIC, "C");
			*f = static_cast<float>(strtod(s.c_str(), &endChar));

			if (*endChar != '\0') {
				return false;
			}
			return true;
		}

		string boolToStr(bool b) {
			if (b) {
				return "1";
			} else {
				return "0";
			}
		}

		string intToStr(const int64 value) {
			char str[strSize] = "";
			//	static int MAX_INT_VALUE = std::numeric_limits<int>::max();
			//	if(value <= MAX_INT_VALUE) {
			//		snprintf(str, strSize-1, "%d", (int)value);
			//	}
			//	else {
			snprintf(str, strSize - 1, "%lld", (long long int)value);
			//	}
			return (str[0] != '\0' ? str : "");
		}

		string uIntToStr(const uint64 value) {
			char str[strSize] = "";
			//	static unsigned int MAX_UNSIGNED_INT_VALUE = std::numeric_limits<unsigned int>::max();
			//	if(value <= MAX_UNSIGNED_INT_VALUE) {
			//		snprintf(str, strSize-1, "%u", (int)value);
			//	}
			//	else {
			snprintf(str, strSize - 1, "%llu", (long long unsigned int)value);
			//	}
			return (str[0] != '\0' ? str : "");
		}

		string intToHex(int i) {
			char str[strSize] = "";
			snprintf(str, strSize - 1, "%x", i);
			return (str[0] != '\0' ? str : "");
		}

		string floatToStr(float f, int precision) {
			setlocale(LC_NUMERIC, "C");

			char str[strSize] = "";
			snprintf(str, strSize - 1, "%.*f", precision, f);
			return (str[0] != '\0' ? str : "");
		}

		string doubleToStr(double d, int precision) {
			setlocale(LC_NUMERIC, "C");

			char str[strSize] = "";
			snprintf(str, strSize - 1, "%.*f", precision, d);
			return (str[0] != '\0' ? str : "");
		}

		bool IsNumeric(const char *p, bool  allowNegative) {
			if (p == NULL) {
				return false;
			}
			if (strcmp(p, "-") == 0) {
				return false;
			}
			int index = 0;
			for (; *p; p++) {
				if (*p < '0' || *p > '9') {
					if (allowNegative == false || (*p != '-' && index == 0)) {
						return false;
					}
				}
				index++;
			}
			return true;
		}

		class Comma : public numpunct<char>// own facet class
		{
		protected:
			//char do_thousands_sep() const { return ','; }// use the comma
			//string do_grouping() const { return "\3"; }//group 3 digits
		};
		string formatNumber(uint64 f) {

			locale myloc(locale(),    // C++ default locale
				new Comma);// Own numeric facet

			ostringstream out;
			out.imbue(myloc);
			out << f;
			return out.str();
		}

		double getTimeDurationMinutes(int frames, int updateFps) {
			int framesleft = frames;
			double hours = (int) ((int) frames / (float) updateFps / 3600.0f);
			framesleft = (int) (framesleft - hours * 3600 * updateFps);
			double minutes = (int) ((int) framesleft / (float) updateFps / 60.0f);
			framesleft = (int) (framesleft - minutes * 60 * updateFps);
			double seconds = (int) ((int) framesleft / (float) updateFps);

			double result = (hours * 60.0) + minutes;
			if (seconds > 0) {
				result += seconds / 60.0;
			}
			return result;
		}

		string getTimeDurationString(int frames, int updateFps) {
			int framesleft = frames;
			int hours = (int) ((int) frames / (float) updateFps / 3600.0f);
			framesleft = framesleft - hours * 3600 * updateFps;
			int minutes = (int) ((int) framesleft / (float) updateFps / 60.0f);
			framesleft = framesleft - minutes * 60 * updateFps;
			int seconds = (int) ((int) framesleft / (float) updateFps);
			//framesleft=framesleft-seconds*GameConstants::updateFps;

			string hourstr = intToStr(hours);
			if (hours < 10) {
				hourstr = "0" + hourstr;
			}

			string minutestr = intToStr(minutes);
			if (minutes < 10) {
				minutestr = "0" + minutestr;
			}

			string secondstr = intToStr(seconds);
			if (seconds < 10) {
				secondstr = "0" + secondstr;
			}

			return hourstr + ":" + minutestr + ":" + secondstr;
		}

	}
} //end namespace
