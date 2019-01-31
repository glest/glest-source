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

#ifndef _SHARED_GRAPHICS_MODELRENDERER_H_
#define _SHARED_GRAPHICS_MODELRENDERER_H_

#include "model.h"
#include "leak_dumper.h"

namespace Shared {
	namespace Graphics {
		namespace Gl {
			class MeshCallback;
		}

		enum RenderMode {
			rmNormal,
			rmSelection,
			renderModeCount
		};

		class Texture;

		// =====================================================
		//	class ModelRenderer
		// =====================================================

		class ModelRenderer {
		protected:
			bool renderNormals;
			bool renderTextures;
			bool renderColors;
			bool colorPickingMode;
			Gl::MeshCallback *meshCallback;

		public:
			ModelRenderer() {
				renderNormals = false;
				renderTextures = false;
				renderColors = true;
				colorPickingMode = false;

				meshCallback = NULL;
			}

			virtual ~ModelRenderer() {
			};

			virtual void begin(bool renderNormals, bool renderTextures, bool renderColors, bool colorPickingMode, Gl::MeshCallback *meshCallback = NULL) = 0;
			virtual void end() = 0;
			virtual void render(Model *model, int renderMode = rmNormal, float alpha = 1.0f) = 0;
			virtual void renderNormalsOnly(Model *model) = 0;
		};
	}
} //end namespace

#endif
