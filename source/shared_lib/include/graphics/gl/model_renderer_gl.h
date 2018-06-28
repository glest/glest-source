// ==============================================================
//	This file is part of Glest Shared Library (www.glest.org)
//
//	Copyright (C) 2001-2008 Martiño Figueroa
//
//	You can redistribute this code and/or modify it under 
//	the terms of the GNU General Public License as published 
//	by the Free Software Foundation; either version 2 of the 
//	License, or (at your option) any later version
// ==============================================================

#ifndef _SHARED_GRAPHICS_GL_MODELRENDERERGL_H_
#define _SHARED_GRAPHICS_GL_MODELRENDERERGL_H_

#include <array>
#include "model_renderer.h"
#include "model.h"
#include "opengl.h"
#include "leak_dumper.h"
#include "texture_gl.h"

using ::Shared::Graphics::Gl::Texture2DGl;

namespace Shared {
	namespace Graphics {
		namespace Gl {

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

			class MeshCallbackTeamColor : public MeshCallback {
			private:
				const Texture *teamTexture;

			public:
				MeshCallbackTeamColor() : MeshCallback() {
					teamTexture = NULL;
				}

				void setTeamTexture(const Texture *teamTexture) {
					this->teamTexture = teamTexture;
				}

				virtual void execute(const Mesh *mesh);

				static bool noTeamColors;
			};
		}
	}
}//end namespace

#endif
