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

#ifndef _SHARED_UTIL_RANDOM_H_
#define _SHARED_UTIL_RANDOM_H_

#include <string>
#include <vector>
#include "leak_dumper.h"

namespace Shared {
	namespace Util {

		// =====================================================
		//	class RandomGen
		// =====================================================

		class RandomGen {
		private:
			static const int m;
			static const int a;
			static const int b;

		private:
			int lastNumber;
			std::vector<std::string> lastCaller;
			bool disableLastCallerTracking;

			int rand(std::string lastCaller);

		public:
			RandomGen();
			void init(int seed);

			int randRange(int min, int max, std::string lastCaller = "");
			float randRange(float min, float max, std::string lastCaller = "");

			int getLastNumber() const {
				return lastNumber;
			}
			void setLastNumber(int value) {
				lastNumber = value;
			}

			std::string getLastCaller() const;
			void clearLastCaller();
			void addLastCaller(std::string text);
			void setDisableLastCallerTracking(bool value) {
				disableLastCallerTracking = value;
			}
		};

	}
} //end namespace

#endif
