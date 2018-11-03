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

#ifndef _SOUNDCONTAINER_H_
#define _SOUNDCONTAINER_H_

#ifdef WIN32
#include <winsock2.h>
#include <winsock.h>
#endif

#include <vector>
#include "sound.h"
#include "randomgen.h"
#include "leak_dumper.h"

using std::vector;
using Shared::Util::RandomGen;
using Shared::Sound::StaticSound;

namespace Game {
	// =====================================================
	// 	class SoundContainer
	//
	/// Holds a list of sounds that are usually played at random
	// =====================================================

	class SoundContainer {
	public:
		typedef vector<StaticSound*> Sounds;

	private:
		Sounds sounds;
		mutable RandomGen random;
		mutable int lastSound;

	public:
		SoundContainer();

		void resize(int size) {
			sounds.resize(size);
		}
		StaticSound *&operator[](int i) {
			return sounds[i];
		}

		const Sounds &getSounds() const {
			return sounds;
		}
		void clearSounds() {
			sounds.clear();
		}
		Sounds *getSoundsPtr() {
			return &sounds;
		}
		StaticSound *getRandSound() const;
	};

} //end namespace

#endif
