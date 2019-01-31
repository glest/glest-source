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

#ifndef _SHARED_GRAPHICS_TEXTRENDERER_H_
#define _SHARED_GRAPHICS_TEXTRENDERER_H_

#include <string>
#include "vec.h"
#include "font.h"
#include "leak_dumper.h"

using std::string;

namespace Shared {
	namespace Graphics {

		// =====================================================
		//	class TextRenderer2D
		// =====================================================

		class TextRenderer {
		public:
			virtual void render(const string &text, float x, float y, bool centered = false, Vec4f *color = NULL) = 0;
			virtual void end() = 0;

			virtual ~TextRenderer() {
			}
		};

		class TextRenderer2D : public TextRenderer {
		public:
			virtual ~TextRenderer2D() {
			};

			virtual void begin(Font2D *font) = 0;
			//virtual void render(const string &text, int x, int y, bool centered= false,Vec3f *color=NULL)= 0;
			//virtual void end()= 0;
		};

		// =====================================================
		//	class TextRenderer3D
		// =====================================================

		class TextRenderer3D : public TextRenderer {
		public:
			virtual ~TextRenderer3D() {
			};

			virtual void begin(Font3D *font) = 0;
			//virtual void render(const string &text, float x, float y, bool centered= false,Vec3f *color=NULL)= 0;
			//virtual void end()= 0;
		};

	}
} //end namespace

#endif
