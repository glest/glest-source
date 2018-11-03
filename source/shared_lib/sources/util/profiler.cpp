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

#include "profiler.h"

#ifdef SL_PROFILE

#include <stdexcept>
#include "leak_dumper.h"

using namespace std;

namespace Shared {
	namespace Util {

		// =====================================================
		//	class Section
		// =====================================================

		Section::Section(const string &name) {
			this->name = name;
			milisElapsed = 0;
			parent = NULL;
		}

		Section *Section::getChild(const string &name) {
			SectionContainer::iterator it;
			for (it = children.begin(); it != children.end(); ++it) {
				if ((*it)->getName() == name) {
					return *it;
				}
			}

			return NULL;
		}

		void Section::print(FILE *outStream, int tabLevel) {

			float percent = (parent == NULL || parent->milisElapsed == 0) ? 100.0f : 100.0f*milisElapsed / parent->milisElapsed;
			//string pname= parent==NULL? "": parent->getName();

			for (int i = 0; i < tabLevel; ++i)
				fprintf(outStream, "\t");

			fprintf(outStream, "%s: ", name.c_str());
			fprintf(outStream, "%d ms, ", milisElapsed);
			fprintf(outStream, "%.1f%s\n", percent, "%");

			SectionContainer::iterator it;
			for (it = children.begin(); it != children.end(); ++it) {
				(*it)->print(outStream, tabLevel + 1);
			}
		}

		// =====================================================
		//	class Profiler
		// =====================================================

		Profiler::Profiler() {
			rootSection = new Section("Root");
			currSection = rootSection;
			rootSection->start();
		}

		Profiler::~Profiler() {
			rootSection->stop();

			string profileLog = "profiler.log";
			if (getGameReadWritePath(GameConstants::path_logs_CacheLookupKey) != "") {
				profileLog = getGameReadWritePath(GameConstants::path_logs_CacheLookupKey) + profileLog;
			} else {
				string userData = config.getString("UserData_Root", "");
				if (userData != "") {
					endPathWithSlash(userData);
				}
				profileLog = userData + profileLog;
			}
#ifdef WIN32
			FILE* f = = _wfopen(utf8_decode(profileLog).c_str(), L"w");
#else
			FILE *f = fopen(profileLog.c_str(), "w");
#endif
			if (f == NULL)
				throw game_runtime_error("Can not open file: " + profileLog);

			fprintf(f, "Profiler Results\n\n");

			rootSection->print(f);

			fclose(f);
		}

		Profiler &Profiler::getInstance() {
			static Profiler profiler;
			return profiler;
		}

		void Profiler::sectionBegin(const string &name) {
			Section *childSection = currSection->getChild(name);
			if (childSection == NULL) {
				childSection = new Section(name);
				currSection->addChild(childSection);
				childSection->setParent(currSection);
			}
			currSection = childSection;
			childSection->start();
		}

		void Profiler::sectionEnd(const string &name) {
			if (name == currSection->getName()) {
				currSection->stop();
				currSection = currSection->getParent();
			} else {
				throw game_runtime_error("Profile: Leaving section is not current section: " + name);
			}
		}

	}
} //end namespace

#endif
