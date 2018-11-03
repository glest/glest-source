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

#ifndef _SHARED_PLATFORM_WINDOWGL_H_
#define _SHARED_PLATFORM_WINDOWGL_H_

#include "context_gl.h"
#include "window.h"
#include "leak_dumper.h"

using Shared::Graphics::Gl::ContextGl;

namespace Shared {
	namespace Platform {

		// =====================================================
		//	class WindowGl
		// =====================================================

		class WindowGl : public Window {
		private:
			ContextGl context;

			static void setGamma(SDL_Window *window, float gammaValue);
		public:
			WindowGl();
			WindowGl(SDL_Window *sdlWindow);
			virtual ~WindowGl();

			void initGl(int colorBits, int depthBits, int stencilBits,
				bool hardware_acceleration, int8 fullscreen_anti_aliasing,
				float gammaValue);
			void makeCurrentGl();
			void swapBuffersGl();
			void setGamma(float gammaValue);

			SDL_Window * getScreenWindow();
			SDL_Surface * getScreenSurface();
			virtual int getScreenWidth();
			virtual int getScreenHeight();
			virtual int getDesiredScreenWidth() {
				return getScreenWidth();
			}
			virtual int getDesiredScreenHeight() {
				return getScreenHeight();
			}

			virtual bool ChangeVideoMode(bool preserveContext, int resWidth, int resHeight,
				bool fullscreenWindow, int colorBits, int depthBits, int stencilBits,
				bool hardware_acceleration, int8 fullscreen_anti_aliasing,
				float gammaValue);

		protected:
			virtual void eventToggleFullScreen(bool isFullscreen);
		};

	}
} //end namespace

#endif
