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

#ifndef _SHARED_GRAPHICS_GL_GRAPHICSFACTORYBASICGL_H_
#define _SHARED_GRAPHICS_GL_GRAPHICSFACTORYBASICGL_H_

#include "graphics_factory.h"
#include "text_renderer_gl.h"
#include "model_renderer_gl.h"
#include "context_gl.h"
#include "model_gl.h"
#include "texture_gl.h"
#include "font_gl.h"
#include "leak_dumper.h"

namespace Shared {
	namespace Graphics {
		namespace Gl {

			// =====================================================
			//	class GraphicsFactoryBasicGl
			// =====================================================

			class GraphicsFactoryBasicGl : public GraphicsFactory {
			public:
				virtual TextRenderer2D *newTextRenderer2D() {
					return new TextRenderer2DGl();
				}
				virtual TextRenderer3D *newTextRenderer3D() {
					return new TextRenderer3DGl();
				}
				virtual ModelRenderer *newModelRenderer() {
					return new ModelRendererGl();
				}
				virtual Context *newContext() {
					return new ContextGl();
				}
				virtual Model *newModel(const string &path, TextureManager* textureManager, bool deletePixMapAfterLoad, std::map<string, vector<pair<string, string> > > *loadedFileList, string *sourceLoader) {
					return new ModelGl(path, textureManager, deletePixMapAfterLoad, loadedFileList, sourceLoader);
				}
				virtual Texture2D *newTexture2D() {
					return new Texture2DGl();
				}
				virtual Font2D *newFont2D() {
					return new Font2DGl();
				}
				virtual Font3D *newFont3D() {
					return new Font3DGl();
				}
			};

		}
	}
} //end namespace

#endif
