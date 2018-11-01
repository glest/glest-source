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

#include "font_manager.h"

#include "graphics_interface.h"
#include "graphics_factory.h"
#include <stdexcept>
#include "util.h"
#include "platform_util.h"
#include "leak_dumper.h"

using namespace Shared::Platform;
using namespace Shared::Util;

namespace Shared {
	namespace Graphics {

		// =====================================================
		//	class FontManager
		// =====================================================
		FontManager::FontManager() {
			if (GlobalStaticFlags::getIsNonGraphicalModeEnabled() == true) {
				throw megaglest_runtime_error("Loading graphics in headless server mode not allowed!");
			}
			fonts.clear();
		}

		FontManager::~FontManager() {
			end();
		}

		Font2D *FontManager::newFont2D() {
			Font2D *font = GraphicsInterface::getInstance().getFactory()->newFont2D();
			fonts.push_back(font);
			return font;
		}

		Font3D *FontManager::newFont3D() {
			Font3D *font = GraphicsInterface::getInstance().getFactory()->newFont3D();
			fonts.push_back(font);
			return font;
		}

		void FontManager::endFont(Font *font, bool mustExistInList) {
			if (font != NULL) {
				bool found = false;
				for (unsigned int i = 0; i < fonts.size(); ++i) {
					if (fonts[i] != NULL && font == fonts[i]) {
						found = true;
						fonts.erase(fonts.begin() + i);
						break;
					}
				}
				if (found == false && mustExistInList == true) {
					throw std::runtime_error("found == false in endFont");
				}
				if (found == true) {
					font->end();
					delete font;
				}
			}
		}

		void FontManager::init() {
			for (size_t i = 0; i < fonts.size(); ++i) {
				if (fonts[i] != NULL) {
					fonts[i]->init();
				}
			}
		}

		void FontManager::end() {
			for (size_t i = 0; i < fonts.size(); ++i) {
				if (fonts[i] != NULL) {
					fonts[i]->end();
					delete fonts[i];
					fonts[i] = NULL;
				}
			}
			fonts.clear();
		}

	}
}//end namespace
