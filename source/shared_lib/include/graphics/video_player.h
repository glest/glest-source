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

#ifndef VIDEO_PLAYER_H_
#define VIDEO_PLAYER_H_

#include <string>

struct SDL_Window;
class ctx;

using namespace std;

namespace Shared {
	namespace Graphics {

		class VideoLoadingCallbackInterface {
		public:
			virtual ~VideoLoadingCallbackInterface() {
			}
			/** a value from 1 to 100 representing % done */
			virtual void renderVideoLoading(int progressPercent) = 0;
		};

		class VideoPlayer {
		protected:

			string filename;
			string filenameFallback;
			SDL_Window *window;
			int x;
			int y;
			int width;
			int height;
			int colorBits;

			bool successLoadingLib;
			string pluginsPath;
			bool verboseEnabled;

			bool stop;
			bool finished;
			bool loop;

			VideoLoadingCallbackInterface *loadingCB;
			ctx *ctxPtr;

			static bool disabled;
			void init();

			void cleanupPlayer();
			bool initPlayer(string mediaURL);

		public:
			VideoPlayer(VideoLoadingCallbackInterface *loadingCB,
				string filename,
				string filenameFallback,
				SDL_Window *window, int x, int y,
				int width, int height, int colorBits,
				bool loop, string pluginsPath, bool verboseEnabled = false);
			virtual ~VideoPlayer();

			static void setDisabled(bool value) {
				disabled = value;
			}
			static bool getDisabled() {
				return disabled;
			}

			void PlayVideo();
			void StopVideo() {
				stop = true;
			}

			bool initPlayer();
			void closePlayer();

			bool playFrame(bool swapBuffers = true);
			bool isPlaying() const;

			static bool hasBackEndVideoPlayer();

			void RestartVideo();
		};

	}
}

#endif /* VIDEO_PLAYER_H_ */
