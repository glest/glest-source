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

#ifndef _SHARED_SOUND_SOUNDPLAYEROPENAL_H_
#define _SHARED_SOUND_SOUNDPLAYEROPENAL_H_

#include "sound_player.h"
#include "platform_util.h"
#include "platform_common.h"
#include <SDL.h>
#ifdef __APPLE__
#include <OpenAL/alc.h>
#include <OpenAL/al.h>
#else
#include <AL/alc.h>
#include <AL/al.h>
#endif
#include <vector>
#include "leak_dumper.h"

using std::vector;
using namespace Shared::PlatformCommon;

namespace Shared {
	namespace Sound {
		namespace OpenAL{
			class SoundSource {
			public:
				SoundSource();
				virtual ~SoundSource();

				bool playing();
				void stop();
				void unQueueBuffers();

			protected:
				friend class SoundPlayerOpenAL;
				ALenum getFormat(Sound* sound);

				ALuint source;
			};

			class StaticSoundSource : public SoundSource {
			public:
				StaticSoundSource();
				virtual ~StaticSoundSource();

				void play(StaticSound* sound);

			protected:
				friend class SoundPlayerOpenAL;
				bool bufferAllocated;
				ALuint buffer;
			};

			class StreamSoundSource : public SoundSource {
			public:
				StreamSoundSource();
				virtual ~StreamSoundSource();

				void play(StrSound* sound, int64 fade);
				void update();
				void stop();
				void stop(int64 fade);

			protected:
				friend class SoundPlayerOpenAL;
				static const size_t STREAMBUFFERSIZE = 4096 * 500;
				static const size_t STREAMFRAGMENTS = 10;
				static const size_t STREAMFRAGMENTSIZE
					= STREAMBUFFERSIZE / STREAMFRAGMENTS;

				bool fillBufferAndQueue(ALuint buffer);

				StrSound* sound;
				ALuint buffers[STREAMFRAGMENTS];
				ALenum format;

				enum FadeState { NoFading, FadingOn, FadingOff };
				FadeState fadeState;
				Chrono chrono; // delay-fade chrono
				int64 fade;
			};

			// ==============================================================
			//	class SoundPlayerSDL
			//
			///	SoundPlayer implementation using SDL_mixer
			// ==============================================================

			class SoundPlayerOpenAL : public SoundPlayer {
			public:
				SoundPlayerOpenAL();
				virtual ~SoundPlayerOpenAL();
				virtual bool init(const SoundPlayerParams *params);
				virtual void end();
				virtual void play(StaticSound *staticSound, bool force=false);
				virtual void play(StrSound *strSound, int64 fadeOn=0);
				virtual void stop(StrSound *strSound, int64 fadeOff=0);
				virtual void stopAllSounds(int64 fadeOff=0);
				virtual void updateStreams();	//updates str buffers if needed

			private:
				friend class SoundSource;
				friend class StaticSoundSource;
				friend class StreamSoundSource;

				void printOpenALInfo();

				StaticSoundSource* findStaticSoundSource();
				StreamSoundSource* findStreamSoundSource();
				void checkAlcError(string message);
				static void checkAlError(string message);

				ALCdevice* device;
				ALCcontext* context;

				typedef std::vector<StaticSoundSource*> StaticSoundSources;
				StaticSoundSources staticSources;
				typedef std::vector<StreamSoundSource*> StreamSoundSources;
				StreamSoundSources streamSources;

				SoundPlayerParams params;
			};
		}
	}
} //end namespace

#endif
