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

#ifndef _SHARED_PLATFORM_GLWRAP_H_
#define _SHARED_PLATFORM_GLWRAP_H_

#ifdef WIN32

#include <windows.h>

#include <GL/glew.h>

#define GLEST_GLPROC(X, Y) inline X( static a= wglGetProcAddress(a); return a;)

#else

#include <GL/glew.h>
#define GL_GLEXT_PROTOTYPES

#endif

#include <string>
#include "font.h"
#include "data_types.h"
#include <SDL.h>
#include "leak_dumper.h"

using std::string;

using Shared::Graphics::FontMetrics;

namespace Shared {
	namespace Platform {

		// =====================================================
		//	class PlatformContextGl
		// =====================================================

		class PlatformContextGl {
		protected:
			SDL_Surface *icon;
			SDL_Window *window;
			SDL_GLContext glcontext;

		public:
			// Example values:
			// DEFAULT_CHARSET (English) = 1
			// GB2312_CHARSET (Chinese)  = 134
#ifdef WIN32
			static DWORD charSet;
#else
			static int charSet;
#endif

		public:
			PlatformContextGl();
			virtual ~PlatformContextGl();

			virtual void init(int colorBits, int depthBits, int stencilBits,
				bool hardware_acceleration, int8 fullscreen_anti_aliasing,
				float gammaValue);
			virtual void end();

			virtual void makeCurrent();
			virtual void swapBuffers();

			SDL_Window * getScreenWindow() {
				return window;
			}
			SDL_Surface * getScreenSurface();

			DeviceContextHandle getHandle() const {
				return 0;
			}
		};

		// =====================================================
		//	Global Fcs
		// =====================================================

#if defined(__APPLE__)
		void createGlFontBitmaps(uint32 &base, const string &type, int size, int width, int charCount, FontMetrics &metrics);
		void createGlFontOutlines(uint32 &base, const string &type, int width, float depth, int charCount, FontMetrics &metrics);
#else
		void createGlFontBitmaps(uint32 &base, const string &type, int size, int width, int charCount, FontMetrics &metrics);
		void createGlFontOutlines(uint32 &base, const string &type, int width, float depth, int charCount, FontMetrics &metrics);
#endif

		const char *getPlatformExtensions(const PlatformContextGl *pcgl);
		void* getGlProcAddress(const char *procName);

	}
}//end namespace

#endif
