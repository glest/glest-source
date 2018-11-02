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

#ifndef _GLEST_GAME_WATER_EFFECTS_H_
#define _GLEST_GAME_WATER_EFFECTS_H_

#ifdef WIN32
#include <winsock2.h>
#include <winsock.h>
#endif

#include <vector>
#include "vec.h"
#include "leak_dumper.h"

using std::vector;

using Shared::Graphics::Vec2f;

namespace ZetaGlest {
	namespace Game {

		class Map;

		// =====================================================
		//	class WaterSplash
		// =====================================================

		class WaterSplash {
		private:
			Vec2f pos;
			int size;
			float anim;
			bool enabled;

		public:
			WaterSplash(const Vec2f &pos, int size);

			void update(float amount);

			const Vec2f &getPos() const {
				return pos;
			}
			const int &getSize() const {
				return size;
			}
			float getAnim() const {
				return anim;
			}
			bool getEnabled() const {
				return enabled;
			}
		};

		// ===============================
		// 	class WaterEffects  
		//
		/// List of water splashes
		// ===============================

		class WaterEffects {
		public:
			typedef vector<WaterSplash> WaterSplashes;

		private:
			WaterSplashes waterSplashes;
			float anim;

		public:
			WaterEffects();

			void update(float speed);

			float getAmin() const {
				return anim;
			}

			void addWaterSplash(const Vec2f &pos, int size);
			int getWaterSplashCount() const {
				return (int) waterSplashes.size();
			}
			const WaterSplash *getWaterSplash(int i) const {
				return &waterSplashes[i];
			}
		};

	}
}//end namespace

#endif
