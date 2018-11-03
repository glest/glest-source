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

#ifndef _SHARED_GRAPHICS_GL_OPENGL_H_
#define _SHARED_GRAPHICS_GL_OPENGL_H_

#include <GL/glew.h>
#include <cassert>
#include <stdexcept>
#include <string>
#include "conversion.h"
#include "gl_wrap.h"
#include "platform_util.h"
#include "leak_dumper.h"

using std::runtime_error;
using std::string;

namespace Shared {
	namespace Graphics {
		namespace Gl {

			using Util::intToStr;

			// =====================================================
			//	Globals
			// =====================================================

			bool getVBOSupported();
			void setVBOSupported(bool value);

			//void overrideGlExtensionSupport(const char *extensionName,bool value);
			bool isGlExtensionSupported(const char *extensionName);
			//bool isGlVersionSupported(int major, int minor, int release);
			const char *getGlVersion();
			const char *getGlRenderer();
			const char *getGlVendor();
			const char *getGlExtensions();
			const char *getGlPlatformExtensions();
			int getGlMaxLights();
			int getGlMaxTextureSize();
			int getGlMaxTextureUnits();
			int getGlModelviewMatrixStackDepth();
			int getGlProjectionMatrixStackDepth();
			//void checkGlExtension(const char *extensionName);

			void inline _assertGl(const char *file, int line, GLenum *forceErrorNumber = NULL) {
				GLenum error = (forceErrorNumber != NULL ? *forceErrorNumber : glGetError());
				if (error != GL_NO_ERROR) {
#ifdef _DEBUG
					if (error == GL_INVALID_ENUM) {
						return;
					}
#endif

					//if(error != GL_INVALID_ENUM) {
					const char *errorString = reinterpret_cast<const char*>(gluErrorString(error));
					char szBuf[8096] = "";
					snprintf(szBuf, 8096, "OpenGL error #%d [0x%X] : [%s] at file: [%s], line: %d", error, error, errorString, file, line);
					//throw game_runtime_error("OpenGL error #" + intToStr(error) + " : " + string(errorString) + " at file: " + string(file) + ", line " + intToStr(line));
					throw game_runtime_error(szBuf);
					//}
				}

			}

#ifdef NDEBUG

#define assertGl() ((void) 0);
#define assertGlWithErrorNumber(forceErrorNumber) ((void) 0);

#else

#define assertGl() _assertGl(__FILE__, __LINE__);
#define assertGlWithErrorNumber(forceErrorNumber) _assertGl(__FILE__, __LINE__, &forceErrorNumber);

#endif

		}
	}
} //end namespace

#endif
