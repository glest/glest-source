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

#ifndef _SHARED_GRAPHICS_GL_MODELRENDERERGL_H_
#define _SHARED_GRAPHICS_GL_MODELRENDERERGL_H_

#include "model_renderer.h"
#include "model.h"
#include "opengl.h"
#include "leak_dumper.h"
#include "texture_gl.h"

using ::Shared::Graphics::Gl::Texture2DGl;

namespace Shared {
	namespace Graphics {
		namespace Gl {
			class MeshCallback {
			private:
				const Texture *teamTexture;

			public:
				MeshCallback() {
					teamTexture = NULL;
				}

				void setTeamTexture(const Texture *teamTexture) {
					this->teamTexture = teamTexture;
				}

				void execute(const Mesh *mesh, float alpha);

				static bool noTeamColors;
			};

			// =====================================================
			//	class ModelRendererGl
			// =====================================================

			class ModelRendererGl : public ModelRenderer {
			private:
				bool rendering;
				bool duplicateTexCoords;
				int secondaryTexCoordUnit;
				GLuint lastTexture;

			public:
				ModelRendererGl();
				virtual void begin(bool renderNormals, bool renderTextures, bool renderColors, bool colorPickingMode, MeshCallback *meshCallback);
				virtual void end();
				virtual void render(Model *model, int renderMode = rmNormal, float alpha = 1.0f);
				virtual void renderNormalsOnly(Model *model);

				void setDuplicateTexCoords(bool duplicateTexCoords) {
					this->duplicateTexCoords = duplicateTexCoords;
				}
				void setSecondaryTexCoordUnit(int secondaryTexCoordUnit) {
					this->secondaryTexCoordUnit = secondaryTexCoordUnit;
				}

			private:

				void renderMesh(Mesh *mesh, int renderMode = rmNormal, float alpha = 1.0f);
				void renderMeshNormals(Mesh *mesh);
			};
		}
	}
} //end namespace

#endif
