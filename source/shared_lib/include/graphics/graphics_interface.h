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

#ifndef _SHARED_GRAPHICS_GRAPHICSINTERFACE_H_
#define _SHARED_GRAPHICS_GRAPHICSINTERFACE_H_

#include "map_preview.h"
#include "leak_dumper.h"

using namespace Shared::Map;

namespace Shared {
	namespace Graphics {

		class GraphicsFactory;
		class Context;
		class Texture2D;
		class Model;

		enum ResourceScope {
			rsGlobal,
			rsMenu,
			rsGame,

			rsCount
		};

		class RendererInterface {
		public:
			virtual Texture2D *newTexture2D(ResourceScope rs) = 0;
			virtual Model *newModel(ResourceScope rs, const string &path, bool deletePixMapAfterLoad = false, std::map<string, vector<pair<string, string> > > *loadedFileList = NULL, string *sourceLoader = NULL) = 0;

			virtual ~RendererInterface() {
			}
		};

		class RendererMapInterface {
		public:
			virtual void initMapSurface(int clientW, int clientH) = 0;
			virtual void renderMap(MapPreview *map, int x, int y, int clientW, int clientH, int cellSize, bool grid, bool heightMap, bool hideWater) = 0;

			virtual ~RendererMapInterface() {
			}
		};

		// =====================================================
		//	class GraphicsInterface
		//
		///	Interface for the graphic engine
		// =====================================================

		class GraphicsInterface {
		private:
			GraphicsFactory *graphicsFactory;
			Context *currentContext;

		private:
			friend class TextureManager;
			friend class FontManager;

		private:
			GraphicsInterface();
			GraphicsInterface(GraphicsInterface &);
			void operator=(GraphicsInterface &);

		public:
			static GraphicsInterface &getInstance();

			void setFactory(GraphicsFactory *graphicsFactory);
			void setCurrentContext(Context *context);

			Context *getCurrentContext() const {
				return currentContext;
			}
			GraphicsFactory *getFactory() const {
				return graphicsFactory;
			}
		};

	}
} //end namespace

#endif
