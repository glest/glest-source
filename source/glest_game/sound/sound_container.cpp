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

#include "sound_container.h"

#include "util.h"
#include "leak_dumper.h"

using namespace Shared::Util;

namespace Glest {
	namespace Game {

		// =====================================================
		// 	class SoundContainer
		// =====================================================

		SoundContainer::SoundContainer() {
			lastSound = -1;
		}

		StaticSound *SoundContainer::getRandSound() const {
			switch (sounds.size()) {
				case 0:
					return NULL;
				case 1:
					return sounds[0];
				default:
					int soundIndex = random.randRange(0, (int) sounds.size() - 1);
					if (soundIndex == lastSound) {
						soundIndex = (lastSound + 1) % sounds.size();
					}
					lastSound = soundIndex;
					return sounds[soundIndex];
			}
		}

	}
}//end namespace
