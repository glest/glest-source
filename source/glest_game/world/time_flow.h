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

#ifndef _GLEST_GAME_TIMEFLOW_H_
#define _GLEST_GAME_TIMEFLOW_H_

#ifdef WIN32
#include <winsock2.h>
#include <winsock.h>
#endif

#include "tileset.h"
#include "sound.h"
#include "leak_dumper.h"

namespace Glest {
	namespace Game {

		using Shared::Sound::StrSound;
		using Shared::Sound::StrSound;
		using Shared::Sound::StaticSound;


		// =====================================================
		// 	class TimeFlow  
		//
		/// Raises time related events (day/night cycle) 
		// =====================================================

		class TimeFlow {
		public:
			static const float dusk;
			static const float dawn;

		private:
			bool firstTime;
			Tileset *tileset;
			float time;
			float lastTime;
			float timeInc;

		public:
			TimeFlow();
			void init(Tileset *tileset);

			inline float getTime() const {
				return time;
			}
			inline bool isDay() const {
				return time > dawn && time < dusk;
			}
			inline bool isNight() const {
				return !isDay();
			}
			inline bool isTotalNight() const {
				return time<dawn + 1.f || time>dusk - 1.f;
			}
			inline float getTimeInc() const {
				return timeInc;
			}

			Vec3f computeLightColor() const;
			void update();

			void saveGame(XmlNode *rootNode);
			void loadGame(const XmlNode *rootNode);

		private:
			//bool isAproxTime(float time) const;
		};

	}
} //end namespace

#endif
