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

#ifndef Text_h
#define Text_h

#include <string>

using std::string;

enum FontTextHandlerType {
	ftht_2D,
	ftht_3D
};

/**
 * Base class upon which all text rendering calls are made.
 */
 //====================================================================
class Text {
protected:
	FontTextHandlerType type;
public:

	static std::string DEFAULT_FONT_PATH;
	static std::string DEFAULT_FONT_PATH_ABSOLUTE;

	Text(FontTextHandlerType type);
	virtual ~Text();

	virtual void init(string fontName, string fontFamilyName, int fontSize);
	virtual void SetFaceSize(int);
	virtual int GetFaceSize();

	virtual void Render(const char*, const int = -1);
	virtual float Advance(const char*, const int = -1);
	virtual float LineHeight(const char* = " ", const int = -1);

	virtual void Render(const wchar_t*, const int = -1);
	virtual float Advance(const wchar_t*, const int = -1);
	virtual float LineHeight(const wchar_t* = L" ", const int = -1);

};

#endif // Text_h
