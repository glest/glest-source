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

#ifndef _GLEST_GAME_BATTLEEND_H_
#   define _GLEST_GAME_BATTLEEND_H_

#   ifdef WIN32
#      include <winsock2.h>
#      include <winsock.h>
#   endif

#   include "program.h"
#   include "stats.h"
#   include "leak_dumper.h"

namespace Shared {
	namespace Graphics {
		class VideoPlayer;
	}
}

namespace ZetaGlest {
	namespace Game {

		class GameSettings;
		// =====================================================
		//      class BattleEnd
		//
		///     ProgramState representing the end of the game
		// =====================================================

		class BattleEnd :public ProgramState {
		private:
			Stats stats;

			GraphicButton buttonExit;
			int mouse2d;
			GraphicMessageBox mainMessageBox;
			Texture2D *renderToTexture;
			uint64 renderToTextureCount;
			ProgramState *originState;
			const char *containerName;

			::Shared::Graphics::VideoPlayer * menuBackgroundVideo;
			GameSettings *gameSettings;
			StrSound battleEndMusic;

			void showMessageBox(const string & text, const string & header,
				bool toggle);

		public:
			BattleEnd(Program * program, const Stats * stats,
				ProgramState * originState);
			~BattleEnd();

			virtual void update();
			virtual void render();
			virtual void keyDown(SDL_KeyboardEvent key);
			virtual void mouseDownLeft(int x, int y);
			virtual void mouseMove(int x, int y, const MouseState * ms);
			//virtual void tick();
			virtual void reloadUI();

		private:

			void initBackgroundVideo();
			std::pair < string, string > getBattleEndVideo(bool won);
			string getBattleEndMusic(bool won);
			void initBackgroundMusic();
		};

	}
}                              //end namespace

#endif
