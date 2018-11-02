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

#include "sound.h"

#include <fstream>
#include <stdexcept>
#include "util.h"
#include "leak_dumper.h"

using namespace Shared::Util;
namespace Shared {
	namespace Sound {

		//bool Sound::masterserverMode = false;

		// =====================================================
		//	class SoundInfo
		// =====================================================

		SoundInfo::SoundInfo() {
			channels = 0;
			samplesPerSecond = 0;
			bitsPerSample = 0;
			size = 0;
			bitRate = 0;
		}

		// =====================================================
		//	class Sound
		// =====================================================

		Sound::Sound() {
			volume = 0.0f;
			fileName = "";
			soundFileLoader = 0;
		}

		// =====================================================
		//	class StaticSound
		// =====================================================

		StaticSound::StaticSound() {
			samples = NULL;
			soundFileLoader = NULL;
			fileName = "";
		}

		StaticSound::~StaticSound() {
			close();
		}

		void StaticSound::close() {
			if (samples != NULL) {
				delete[] samples;
				samples = NULL;
			}

			if (soundFileLoader != NULL) {
				soundFileLoader->close();
				delete soundFileLoader;
				soundFileLoader = NULL;
			}
		}

		void StaticSound::load(const string &path) {
			close();

			fileName = path;

			if (GlobalStaticFlags::getIsNonGraphicalModeEnabled() == true) {
				return;
			}
			string ext = (path.empty() == false ? path.substr(path.find_last_of('.') + 1) : "");
			soundFileLoader = SoundFileLoaderFactory::getInstance()->newInstance(ext);

			if (soundFileLoader == NULL) {
				throw game_runtime_error("soundFileLoader == NULL");
			}
			soundFileLoader->open(path, &info);
			samples = new int8[info.getSize()];
			soundFileLoader->read(samples, info.getSize());
			soundFileLoader->close();

			delete soundFileLoader;
			soundFileLoader = NULL;
		}

		// =====================================================
		//	class StrSound
		// =====================================================

		StrSound::StrSound() {
			soundFileLoader = NULL;
			next = NULL;
			fileName = "";
		}

		StrSound::~StrSound() {
			close();
		}

		void StrSound::open(const string &path) {
			close();

			fileName = path;

			if (GlobalStaticFlags::getIsNonGraphicalModeEnabled() == true) {
				return;
			}

			string ext = (path.empty() == false ? path.substr(path.find_last_of('.') + 1) : "");

			soundFileLoader = SoundFileLoaderFactory::getInstance()->newInstance(ext);
			soundFileLoader->open(path, &info);
		}

		uint32 StrSound::read(int8 *samples, uint32 size) {
			if (GlobalStaticFlags::getIsNonGraphicalModeEnabled() == true) {
				return 0;
			}

			return soundFileLoader->read(samples, size);
		}

		void StrSound::close() {
			if (soundFileLoader != NULL) {
				soundFileLoader->close();
				delete soundFileLoader;
				soundFileLoader = NULL;
			}
		}

		void StrSound::restart() {
			if (GlobalStaticFlags::getIsNonGraphicalModeEnabled() == true) {
				return;
			}

			soundFileLoader->restart();
		}

	}
}//end namespace
