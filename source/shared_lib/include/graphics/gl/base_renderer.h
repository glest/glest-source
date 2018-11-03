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

#ifndef _BASE_RENDERER_H_
#define _BASE_RENDERER_H_

#include "graphics_interface.h"
#include "leak_dumper.h"

namespace Shared {
	namespace Graphics {

		// ===============================================
		//	class BaseRenderer
		// ===============================================

		class BaseRenderer : public RendererMapInterface {
		public:
			BaseRenderer() {
			}
			virtual ~BaseRenderer() {
			}

			virtual void initMapSurface(int clientW, int clientH);
			virtual void renderMap(MapPreview *map, int x, int y, int clientW, int clientH, int cellSize, bool grid = false, bool heightMap = false, bool hideWater = false);
		};

	}
} //end namespace

#endif
