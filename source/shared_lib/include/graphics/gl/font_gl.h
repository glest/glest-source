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

#ifndef _SHARED_GRAPHICS_GL_FONTGL_H_
#define _SHARED_GRAPHICS_GL_FONTGL_H_

#include "font.h"
#include "opengl.h"
#include <string>
#include "leak_dumper.h"

using namespace std;

namespace Shared {
	namespace Graphics {
		namespace Gl {

			// =====================================================
			//	class FontGl
			// =====================================================

			class FontGl {
			protected:

				GLuint handle;
				static string default_fonttype;

			public:

				GLuint getHandle() const {
					return handle;
				}

				static string getDefault_fontType() {
					return default_fonttype;
				}
				static void setDefault_fontType(string value) {
					default_fonttype = value;
				}
			};

			// =====================================================
			//	class Font2DGl
			//
			///	OpenGL bitmap font
			// =====================================================

			class Font2DGl : public Font2D, public FontGl {
			public:

				virtual void init();
				virtual void end();
			};

			// =====================================================
			//	class Font3DGl
			//
			///	OpenGL outline font
			// =====================================================

			class Font3DGl : public Font3D, public FontGl {
			public:

				virtual void init();
				virtual void end();
			};

		}
	}
} //end namespace

#endif
