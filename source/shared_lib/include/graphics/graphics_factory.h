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

#ifndef _SHARED_GRAPHICS_GRAPHICSFACTORY_H_
#define _SHARED_GRAPHICS_GRAPHICSFACTORY_H_

#include <cstdlib>
#include <string>
#include <map>
#include <vector>
using std::string;

#include "leak_dumper.h"

namespace Shared {
	namespace Graphics {

		class Context;

		class TextureManager;
		class Texture1D;
		class Texture2D;
		class Texture3D;
		class TextureCube;

		class ModelManager;
		class ModelRenderer;
		class Model;

		class FontManager;
		class TextRenderer2D;
		class TextRenderer3D;
		class Font2D;
		class Font3D;

		class ParticleManager;
		class ParticleRenderer;

		class ShaderManager;
		class ShaderProgram;
		class VertexShader;
		class FragmentShader;

		// =====================================================
		//	class GraphicsFactory
		// =====================================================

		class GraphicsFactory {
		public:
			virtual ~GraphicsFactory() {
			}

			//context
			virtual Context *newContext() {
				return NULL;
			}

			//textures
			virtual TextureManager *newTextureManager() {
				return NULL;
			}
			virtual Texture1D *newTexture1D() {
				return NULL;
			}
			virtual Texture2D *newTexture2D() {
				return NULL;
			}
			virtual Texture3D *newTexture3D() {
				return NULL;
			}
			virtual TextureCube *newTextureCube() {
				return NULL;
			}

			//models
			virtual ModelManager *newModelManager() {
				return NULL;
			}
			virtual ModelRenderer *newModelRenderer() {
				return NULL;
			}
			virtual Model *newModel(const string &path, TextureManager* textureManager, bool deletePixMapAfterLoad, std::map<string, std::vector<std::pair<string, string> > > *loadedFileList, string *sourceLoader) {
				return NULL;
			}

			//text
			virtual FontManager *newFontManager() {
				return NULL;
			}
			virtual TextRenderer2D *newTextRenderer2D() {
				return NULL;
			}
			virtual TextRenderer3D *newTextRenderer3D() {
				return NULL;
			}
			virtual Font2D *newFont2D() {
				return NULL;
			}
			virtual Font3D *newFont3D() {
				return NULL;
			}

			//particles
			virtual ParticleManager *newParticleManager() {
				return NULL;
			}
			virtual ParticleRenderer *newParticleRenderer() {
				return NULL;
			}

			//shaders
			virtual ShaderManager *newShaderManager() {
				return NULL;
			}
			virtual ShaderProgram *newShaderProgram() {
				return NULL;
			}
			virtual VertexShader *newVertexShader() {
				return NULL;
			}
			virtual FragmentShader *newFragmentShader() {
				return NULL;
			}
		};

	}
}//end namespace

#endif
