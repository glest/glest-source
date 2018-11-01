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

#ifndef _SHARED_UTIL_CHECKSUM_H_
#define _SHARED_UTIL_CHECKSUM_H_

#include <string>
#include <map>
#include "data_types.h"
#include "thread.h"
#include "leak_dumper.h"

using std::string;
using namespace Shared::Platform;

namespace Shared {
	namespace Util {

		// =====================================================
		//	class Checksum
		// =====================================================

		class Checksum {
		private:
			uint32	sum;
			int32	r;
			int32	c1;
			int32	c2;
			std::map<string, uint32> fileList;

			static Mutex fileListCacheSynchAccessor;
			static std::map<string, uint32> fileListCache;

			void addSum(uint32 value);
			bool addFileToSum(const string &path);

		public:
			Checksum();

			uint32 getSum();
			uint32 getFinalFileListSum();
			uint32 getFileCount();

			//uint32 addByte(int8 value);
			uint32 addByte(const char value);
			uint32 addBytes(const void *_data, size_t _size);
			void addString(const string &value);
			uint32 addInt(const int32 &value);
			uint32 addUInt(const uint32 &value);
			uint32 addInt64(const int64 &value);
			void addFile(const string &path);

			static void removeFileFromCache(const string file);
			static void clearFileCache();
		};

	}
}//end namespace

#endif
