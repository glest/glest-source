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

#include "randomgen.h"
#include <cassert>
#include "util.h"
#include <stdexcept>
#include "platform_util.h"
#include "math_util.h"
#include "leak_dumper.h"

using namespace std;
using namespace Shared::Graphics;

namespace Shared {
	namespace Util {

		// =====================================================
		//	class RandomGen
		// =====================================================

		const int RandomGen::m = 714025;
		const int RandomGen::a = 1366;
		const int RandomGen::b = 150889;

		RandomGen::RandomGen() {
			lastNumber = 0;
			disableLastCallerTracking = false;
		}

		void RandomGen::init(int seed) {
			lastNumber = seed % m;
		}

		int RandomGen::rand(string lastCaller) {
			if (lastCaller != "") {
				this->lastCaller.push_back(lastCaller);
			}
			this->lastNumber = (a*lastNumber + b) % m;
			return lastNumber;
		}

		std::string RandomGen::getLastCaller() const {
			std::string result = "";
			if (lastCaller.empty() == false) {
				for (unsigned int index = 0; index < lastCaller.size(); ++index) {
					result += lastCaller[index] + "|";
				}
			}
			return result;
		}

		void RandomGen::clearLastCaller() {
			if (lastCaller.empty() == false) {
				lastCaller.clear();
			}
		}
		void RandomGen::addLastCaller(std::string text) {
			if (disableLastCallerTracking == false) {
				lastCaller.push_back(text);
			}
		}

		int RandomGen::randRange(int min, int max, string lastCaller) {
			if (min > max) {
				char szBuf[8096] = "";
				snprintf(szBuf, 8096, "In [%s::%s Line: %d] min > max, min = %d, max = %d", __FILE__, __FUNCTION__, __LINE__, min, max);
				throw game_runtime_error(szBuf);
			}

			int diff = max - min;
			float numerator = static_cast<float>(diff + 1) * static_cast<float>(this->rand(lastCaller));
			int res = min + static_cast<int>(truncateDecimal<float>(numerator / static_cast<float>(m), 6));
			if (res < min || res > max) {
				char szBuf[8096] = "";
				snprintf(szBuf, 8096, "In [%s::%s Line: %d] res < min || res > max, min = %d, max = %d, res = %d", __FILE__, __FUNCTION__, __LINE__, min, max, res);
				throw game_runtime_error(szBuf);
			}
			return res;
		}

		float RandomGen::randRange(float min, float max, string lastCaller) {
			if (min > max) {
				char szBuf[8096] = "";
				snprintf(szBuf, 8096, "In [%s::%s Line: %d] min > max, min = %f, max = %f", __FILE__, __FUNCTION__, __LINE__, min, max);
				throw game_runtime_error(szBuf);
			}

			float rand01 = static_cast<float>(this->rand(lastCaller)) / (m - 1);
			float res = min + (max - min) * rand01;
			res = truncateDecimal<float>(res, 6);

			if (res < min || res > max) {
				char szBuf[8096] = "";
				snprintf(szBuf, 8096, "In [%s::%s Line: %d] res < min || res > max, min = %f, max = %f, res = %f", __FILE__, __FUNCTION__, __LINE__, min, max, res);
				throw game_runtime_error(szBuf);
			}
			return res;
		}

	}
} //end namespace
