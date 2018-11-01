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

#ifndef _SHARED_GRAPHICS_FONTMANAGER_H_
#define _SHARED_GRAPHICS_FONTMANAGER_H_

#include "font.h"
#include <vector>
#include "leak_dumper.h"

using namespace std;

namespace Shared {
	namespace Graphics {

		// =====================================================
		//	class FontManager
		//
		///	Creates, Intializes, Finalizes, and Deletes fonts
		// =====================================================

		class FontManager {
		protected:
			typedef vector<Font*> FontContainer;

		protected:
			FontContainer fonts;

		public:
			FontManager();
			virtual ~FontManager();

			Font2D *newFont2D();
			Font3D *newFont3D();

			void endFont(Font *font, bool mustExistInList = false);

			void init();
			void end();
		};

	}
}//end namespace

#endif
