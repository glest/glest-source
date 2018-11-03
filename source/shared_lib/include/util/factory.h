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

#ifndef _SHARED_UTIL_FACTORY_
#define _SHARED_UTIL_FACTORY_

#include <map>
#include <string>
#include <stdexcept>
#include "platform_util.h"
#include "leak_dumper.h"

using std::map;
using std::string;
using std::pair;
using std::runtime_error;

namespace Shared {
	namespace Util {

		// =====================================================
		//	class SingleFactoryBase
		// =====================================================

		class SingleFactoryBase {
		public:
			virtual ~SingleFactoryBase() {
			}
			virtual void *newInstance() = 0;
		};

		// =====================================================
		//	class SingleFactory
		// =====================================================

		template<typename T>
		class SingleFactory : public SingleFactoryBase {
		public:
			virtual void *newInstance() {
				return new T();
			}
		};

		// =====================================================
		//	class MultiFactory
		// =====================================================

		template<typename T>
		class MultiFactory {
		private:
			typedef map<string, SingleFactoryBase*> Factories;
			typedef pair<string, SingleFactoryBase*> FactoryPair;

		private:
			Factories factories;

		public:
			virtual ~MultiFactory() {
				for (Factories::iterator it = factories.begin(); it != factories.end(); ++it) {
					delete it->second;
				}
				factories.clear();
			}

			template<typename R>
			void registerClass(string classId) {
				factories.insert(FactoryPair(classId, new SingleFactory<R>()));
			}

			T *newInstance(string classId) {
				Factories::iterator it = factories.find(classId);
				if (it == factories.end()) {
					throw game_runtime_error("Unknown class identifier: " + classId);
				}
				return static_cast<T*>(it->second->newInstance());
			}

			bool isClassId(string classId) {
				return factories.find(classId) != factories.end();
			}
		};

	}
} //end namespace

#endif
