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

#include "cache_manager.h"

namespace Shared {
	namespace PlatformCommon {

		//Mutex CacheManager::mutexCache;
		Mutex CacheManager::mutexMap(CODE_AT_LINE);
		std::map<string, Mutex *> CacheManager::itemCacheMutexList;
		const char *CacheManager::getFolderTreeContentsCheckSumRecursivelyCacheLookupKey1 = "CRC_Cache_FileTree1";
		const char *CacheManager::getFolderTreeContentsCheckSumRecursivelyCacheLookupKey2 = "CRC_Cache_FileTree2";
		const char *CacheManager::getFolderTreeContentsCheckSumListRecursivelyCacheLookupKey1 = "CRC_Cache_FileTreeList1";
		const char *CacheManager::getFolderTreeContentsCheckSumListRecursivelyCacheLookupKey2 = "CRC_Cache_FileTreeList2";

	}
} //end namespace
