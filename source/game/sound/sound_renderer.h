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

#ifndef _SOUNDRENDERER_H_
#define _SOUNDRENDERER_H_

#ifdef WIN32
#include <winsock2.h>
#include <winsock.h>
#endif

#include "sound.h"
#include "sound_player.h"
#include "window.h"
#include "vec.h"
#include "simple_threads.h"
#include "platform_common.h"
#include "leak_dumper.h"

namespace Game {
	using ::Shared::Sound::StrSound;
	using ::Shared::Sound::StaticSound;
	using ::Shared::Sound::SoundPlayer;
	using ::Shared::Graphics::Vec3f;
	using namespace ::Shared::PlatformCommon;

	// =====================================================
	// 	class SoundRenderer
	//
	///	Wrapper to acces the shared library sound engine
	// =====================================================

	class SoundRenderer : public SimpleTaskCallbackInterface {
	public:
		static const int ambientFade;
		static const float audibleDist;
	private:
		SoundPlayer * soundPlayer;

		//volume
		float fxVolume;
		float musicVolume;
		float ambientVolume;

		Mutex *mutex;
		bool runThreadSafe;

	private:
		SoundRenderer();

		void cleanup();

	public:
		//misc
		virtual ~SoundRenderer();
		static SoundRenderer &getInstance();
		bool init(Window *window);
		void update();
		virtual void simpleTask(BaseThread *callingThread, void *userdata) {
			update();
		}
		SoundPlayer *getSoundPlayer() const {
			return soundPlayer;
		}

		//music
		void playMusic(StrSound *strSound);
		void setMusicVolume(StrSound *strSound);
		void stopMusic(StrSound *strSound);

		//fx
		void playFx(StaticSound *staticSound, Vec3f soundPos, Vec3f camPos);
		void playFx(StaticSound *staticSound, bool force = false);

		//ambient
		void playAmbient(StrSound *strSound);
		void stopAmbient(StrSound *strSound);

		//misc
		void stopAllSounds(int64 fadeOff = 0);
		void loadConfig();

		bool wasInitOk() const;

		bool runningThreaded() const {
			return runThreadSafe;
		}

		bool isVolumeTurnedOff() const;
	};

} //end namespace

#endif
