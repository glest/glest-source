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

#ifndef TextFTGL_h
#define TextFTGL_h

#ifdef USE_FTGL

#include <FTGL/ftgl.h>

#include "font_text.h"

namespace Shared {
	namespace Graphics {
		namespace Gl {

			/**
			 * Use FTGL for rendering text in OpenGL
			 */
			 //====================================================================
			class TextFTGL : public Text {
			public:

				static string langHeightText;
				static int faceResolution;

				TextFTGL(FontTextHandlerType type);
				virtual ~TextFTGL();
				virtual void init(string fontName, string fontFamilyName, int fontSize);

				virtual void SetFaceSize(int);
				virtual int GetFaceSize();

				virtual void Render(const char*, const int = -1);
				virtual float Advance(const char*, const int = -1);
				virtual float LineHeight(const char*, const int = -1);

				virtual void Render(const wchar_t*, const int = -1);
				virtual float Advance(const wchar_t*, const int = -1);
				virtual float LineHeight(const wchar_t* = L" ", const int = -1);

			private:
				FTFont *ftFont;
				const char* fontFile;

				void cleanupFont();
			};

		}
	}
}//end namespace

#endif // USE_FTGL

#endif // TextFTGL_h
