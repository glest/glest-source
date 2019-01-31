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

#ifndef BYTE_ORDER_H
#define BYTE_ORDER_H

#include <algorithm>
#include "leak_dumper.h"

namespace Shared {
	namespace PlatformByteOrder {

		template<class T> T EndianReverse(T t) {
			//	unsigned char uc[sizeof t];
			//	memcpy(uc, &t, sizeof t);
			//
			//	for (unsigned char *b = uc, *e = uc + sizeof(T) - 1; b < e; ++b, --e) {
			//		std::swap(*b, *e);
			//	}
			//	memcpy(&t, uc, sizeof t);
			//	return t;

			char& raw = reinterpret_cast<char&>(t);
			std::reverse(&raw, &raw + sizeof(T));
			return t;
		}

		inline static bool isBigEndian() {
			short n = 0x1;
			return (*(char*) (&n) == 0x0);
		}


		template<class T> T toCommonEndian(T t) {
			static bool bigEndianSystem = isBigEndian();
			if (bigEndianSystem == true) {
				t = EndianReverse(t);
			}
			return t;
		}

		template<class T> T fromCommonEndian(T t) {
			static bool bigEndianSystem = isBigEndian();
			if (bigEndianSystem == true) {
				t = EndianReverse(t);
			}
			return t;
		}

		template<class T>
		void toEndianTypeArray(T *data, size_t size) {
			static bool bigEndianSystem = isBigEndian();
			if (bigEndianSystem == true) {
				for (size_t i = 0; i < size; ++i) {
					data[i] = toCommonEndian(data[i]);
				}
			}
		}

		template<class T>
		void fromEndianTypeArray(T *data, size_t size) {
			static bool bigEndianSystem = isBigEndian();
			if (bigEndianSystem == true) {
				for (size_t i = 0; i < size; ++i) {
					data[i] = fromCommonEndian(data[i]);
				}
			}
		}

	}
}

#endif
