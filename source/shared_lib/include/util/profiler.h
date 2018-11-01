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

#ifndef _SHARED_UTIL_PROFILER_H_
#define _SHARED_UTIL_PROFILER_H_

//#define SL_PROFILE
//SL_PROFILE controls if profile is enabled or not

#include "platform_util.h"
#include "platform_common.h"
#include <list>
#include <string>
#include "leak_dumper.h"

using std::list;
using std::string;

using Shared::PlatformCommon::Chrono;

namespace Shared {
	namespace Util {

#ifdef SL_PROFILE

		// =====================================================
		//	class Section
		// =====================================================

		class Section {
		public:
			typedef list<Section*> SectionContainer;
		private:
			string name;
			Chrono chrono;
			int64 milisElapsed;
			Section *parent;
			SectionContainer children;

		public:
			Section(const string &name);

			Section *getParent() {
				return parent;
			}
			const string &getName() const {
				return name;
			}

			void setParent(Section *parent) {
				this->parent = parent;
			}

			void start() {
				chrono.start();
			}
			void stop() {
				milisElapsed += chrono.getMillis();
			}

			void addChild(Section *child) {
				children.push_back(child);
			}
			Section *getChild(const string &name);

			void print(FILE *outSream, int tabLevel = 0);
		};

		// =====================================================
		//	class Profiler
		// =====================================================

		class Profiler {
		private:
			Section * rootSection;
			Section *currSection;
		private:
			Profiler();
		public:
			~Profiler();
			static Profiler &getInstance();
			void sectionBegin(const string &name);
			void sectionEnd(const string &name);
		};

#endif //SL_PROFILE

		// =====================================================
		//	class funtions
		// =====================================================

		inline void profileBegin(const string &sectionName) {
#ifdef SL_PROFILE
			Profiler::getInstance().sectionBegin(sectionName);
#endif
		}

		inline void profileEnd(const string &sectionName) {
#ifdef SL_PROFILE
			Profiler::getInstance().sectionEnd(sectionName);
#endif
		}

	}
}//end namespace

#endif 
