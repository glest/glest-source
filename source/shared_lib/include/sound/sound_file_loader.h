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

#ifndef _SHARED_SOUND_SOUNDFILELOADER_H_
#define _SHARED_SOUND_SOUNDFILELOADER_H_

#include <string>
#include <fstream>
#include "data_types.h"
#include "factory.h"
#include "leak_dumper.h"

struct OggVorbis_File;

using std::string;
using std::ifstream;

namespace Shared {
	namespace Sound {

		using Platform::uint32;
		using Platform::int8;
		using Util::MultiFactory;

		class SoundInfo;

		// =====================================================
		//	class SoundFileLoader  
		//
		///	Interface that all SoundFileLoaders will implement
		// =====================================================

		class SoundFileLoader {
		public:
			virtual ~SoundFileLoader() {
			}

			virtual void open(const string &path, SoundInfo *soundInfo) = 0;
			virtual uint32 read(int8 *samples, uint32 size) = 0;
			virtual void close() = 0;
			virtual void restart() = 0;
			virtual string getFileName() = 0;
		};

		// =====================================================
		//	class WavSoundFileLoader  
		//
		///	Wave file loader
		// =====================================================

		class WavSoundFileLoader : public SoundFileLoader {
		private:
			static const int maxDataRetryCount = 10;
			string fileName;
		private:
			uint32 dataOffset;
			uint32 dataSize;
			uint32 bytesPerSecond;
			ifstream f;

		public:
			virtual void open(const string &path, SoundInfo *soundInfo);
			virtual uint32 read(int8 *samples, uint32 size);
			virtual void close();
			virtual void restart();
			virtual string getFileName() {
				return fileName;
			}
		};

		// =====================================================
		//	class OggSoundFileLoader 
		//
		///	OGG sound file loader, uses ogg-vorbis library
		// =====================================================

		class OggSoundFileLoader : public SoundFileLoader {
		private:
			OggVorbis_File *vf;
			FILE *f;
			string fileName;

		public:
			OggSoundFileLoader();
			virtual void open(const string &path, SoundInfo *soundInfo);
			virtual uint32 read(int8 *samples, uint32 size);
			virtual void close();
			virtual void restart();
			virtual string getFileName() {
				return fileName;
			}
		};

		// =====================================================
		//	class SoundFileLoaderFactory
		// =====================================================

		class SoundFileLoaderFactory : public MultiFactory<SoundFileLoader> {
		private:
			SoundFileLoaderFactory();
		public:
			static SoundFileLoaderFactory * getInstance();
		};

	}
} //end namespace

#endif
