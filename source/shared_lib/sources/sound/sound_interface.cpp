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

#include "sound_interface.h"
#include "util.h"
#include "leak_dumper.h"

using namespace Shared::Util;

namespace Shared {
	namespace Sound {

		// =====================================================
		//	class SoundInterface
		// =====================================================

		SoundInterface &SoundInterface::getInstance() {
			static SoundInterface soundInterface;
			return soundInterface;
		}

		void SoundInterface::setFactory(SoundFactory *soundFactory) {
			this->soundFactory = soundFactory;
		}

		SoundPlayer *SoundInterface::newSoundPlayer() {

			if (SystemFlags::getSystemSettingType(SystemFlags::debugSound).enabled) SystemFlags::OutputDebug(SystemFlags::debugSystem, "In [%s::%s %d]\n", __FILE__, __FUNCTION__, __LINE__);

			return soundFactory->newSoundPlayer();
		}

	}
}//end namespace
