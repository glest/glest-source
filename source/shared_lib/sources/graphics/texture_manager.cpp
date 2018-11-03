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

#include "texture_manager.h"

#include <cstdlib>
#include <stdexcept>

#include "graphics_interface.h"
#include "graphics_factory.h"

#include "util.h"
#include "platform_util.h"
#include "leak_dumper.h"

using namespace Shared::Util;
using namespace Shared::Platform;

namespace Shared {
	namespace Graphics {

		// =====================================================
		//	class TextureManager
		// =====================================================

		TextureManager::TextureManager() {
			if (GlobalStaticFlags::getIsNonGraphicalModeEnabled() == true) {
				throw game_runtime_error("Loading graphics in headless server mode not allowed!");
			}


			textureFilter = Texture::fBilinear;
			maxAnisotropy = 1;
		}

		TextureManager::~TextureManager() {
			end();
		}

		void TextureManager::initTexture(Texture *texture) {
			if (texture != NULL) {
				texture->init(textureFilter, maxAnisotropy);
			}
		}

		void TextureManager::endTexture(Texture *texture, bool mustExistInList) {
			if (texture != NULL) {
				bool found = false;
				for (unsigned int idx = 0; idx < textures.size(); idx++) {
					Texture *curTexture = textures[idx];
					if (curTexture == texture) {
						found = true;
						textures.erase(textures.begin() + idx);
						break;
					}
				}
				if (found == false && mustExistInList == true) {
					throw std::runtime_error("found == false in endTexture");
				}
				texture->end();
				delete texture;
			}
		}

		void TextureManager::endLastTexture(bool mustExistInList) {
			bool found = false;
			if (textures.size() > 0) {
				found = true;
				int index = (int) textures.size() - 1;
				Texture *curTexture = textures[index];
				textures.erase(textures.begin() + index);

				curTexture->end();
				delete curTexture;
			}
			if (found == false && mustExistInList == true) {
				throw std::runtime_error("found == false in endLastTexture");
			}
		}

		void TextureManager::init(bool forceInit) {
			for (unsigned int i = 0; i < textures.size(); ++i) {
				Texture *texture = textures[i];
				if (texture == NULL) {
					throw std::runtime_error("texture == NULL during init");
				}
				if (forceInit == true) {
					texture->reseInitState();
				}
				if (forceInit == true) {
					texture->end(false);
				}
				texture->init(textureFilter, maxAnisotropy);
			}
		}

		void TextureManager::end() {
			for (unsigned int i = 0; i < textures.size(); ++i) {
				if (textures[i] != NULL) {
					textures[i]->end();
					delete textures[i];
				}
			}
			textures.clear();
		}

		void TextureManager::setFilter(Texture::Filter textureFilter) {
			this->textureFilter = textureFilter;
		}

		void TextureManager::setMaxAnisotropy(int maxAnisotropy) {
			this->maxAnisotropy = maxAnisotropy;
		}

		Texture *TextureManager::getTexture(const string &path) {
			for (unsigned int i = 0; i < textures.size(); ++i) {
				if (textures[i]->getPath() == path) {
					return textures[i];
				}
			}
			return NULL;
		}

		Texture1D *TextureManager::newTexture1D() {
			Texture1D *texture1D = GraphicsInterface::getInstance().getFactory()->newTexture1D();
			textures.push_back(texture1D);

			return texture1D;
		}

		Texture2D *TextureManager::newTexture2D() {
			Texture2D *texture2D = GraphicsInterface::getInstance().getFactory()->newTexture2D();
			textures.push_back(texture2D);

			return texture2D;
		}

		Texture3D *TextureManager::newTexture3D() {
			Texture3D *texture3D = GraphicsInterface::getInstance().getFactory()->newTexture3D();
			textures.push_back(texture3D);

			return texture3D;
		}


		TextureCube *TextureManager::newTextureCube() {
			TextureCube *textureCube = GraphicsInterface::getInstance().getFactory()->newTextureCube();
			textures.push_back(textureCube);

			return textureCube;
		}

	}
} //end namespace
