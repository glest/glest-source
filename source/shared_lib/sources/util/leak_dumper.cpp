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

#include "leak_dumper.h"

#ifdef SL_LEAK_DUMP
#include "platform_util.h"
#include <time.h>

bool AllocInfo::application_binary_initialized = false;
//static AllocRegistry memoryLeaks = AllocRegistry::getInstance();

// =====================================================
//	class AllocRegistry
// =====================================================

// ===================== PUBLIC ========================

AllocRegistry::~AllocRegistry() {
	dump("leak_dump.log");

	free(mutex);
	mutex = NULL;
}

void AllocRegistry::dump(const char *path) {

	int leakCount = 0;
	size_t leakBytes = 0;

	//time_t debugTime = time(NULL);
	//struct tm *loctime = localtime (&debugTime);
	struct tm loctime = threadsafe_localtime(systemtime_now());
	char szBuf2[100] = "";
	strftime(szBuf2, 100, "%Y-%m-%d %H:%M:%S", &loctime);

#ifdef WIN32
	FILE* f = _wfopen(utf8_decode(path).c_str(), L"wt");
#else
	FILE *f = fopen(path, "wt");
#endif

	if (f) {
		fprintf(f, "Memory leak dump at: %s\n\n", szBuf2);

		for (int index = 0; index < maxAllocs; ++index) {
			AllocInfo &info = allocs[index];
			if (info.freetouse == false && info.inuse == true) {

				if (info.line > 0) {
					leakBytes += info.bytes;

					//allocs[i].stack = AllocInfo::getStackTrace();
					fprintf(f, "Leak #%d.\tfile: %s, line: %d, ptr [%p], bytes: " SIZE_T_SPECIFIER ", array: %d, inuse: %d\n%s\n", ++leakCount, info.file, info.line, info.ptr, info.bytes, info.array, info.inuse, info.stack.c_str());
				}
			}
		}

		fprintf(f, "\nTotal leaks: %d, " SIZE_T_SPECIFIER " bytes\n", leakCount, leakBytes);
		fprintf(f, "Total allocations: %d, " SIZE_T_SPECIFIER " bytes\n", allocCount, allocBytes);
		fprintf(f, "Not monitored allocations: %d, " SIZE_T_SPECIFIER " bytes\n", nonMonitoredCount, nonMonitoredBytes);

		fclose(f);
	}

	printf("Memory leak dump summary at: %s\n", szBuf2);
	printf("Total leaks: %d, " SIZE_T_SPECIFIER " bytes\n", leakCount, leakBytes);
	printf("Total allocations: %d, " SIZE_T_SPECIFIER " bytes\n", allocCount, allocBytes);
	printf("Not monitored allocations: %d, " SIZE_T_SPECIFIER " bytes\n", nonMonitoredCount, nonMonitoredBytes);
}

#endif
