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

#ifndef _SHARED_GRAPHICS_TEXTUREMANAGER_H_
#define _SHARED_GRAPHICS_TEXTUREMANAGER_H_

#include <vector>
#include "texture.h"
#include "leak_dumper.h"

using std::vector;

namespace Shared {
	namespace Graphics {

		// =====================================================
		//	class TextureManager
		// =====================================================
		typedef vector<Texture*> TextureContainer;

		//manages textures, creation on request and deletion on destruction
		class TextureManager {

		protected:
			TextureContainer textures;

			Texture::Filter textureFilter;
			int maxAnisotropy;

		public:
			TextureManager();
			~TextureManager();
			void init(bool forceInit = false);
			void end();

			void setFilter(Texture::Filter textureFilter);
			void setMaxAnisotropy(int maxAnisotropy);
			void initTexture(Texture *texture);
			void endTexture(Texture *texture, bool mustExistInList = false);
			void endLastTexture(bool mustExistInList = false);
			void reinitTextures();

			Texture::Filter getTextureFilter() const {
				return textureFilter;
			}
			int getMaxAnisotropy() const {
				return maxAnisotropy;
			}

			Texture *getTexture(const string &path);
			Texture1D *newTexture1D();
			Texture2D *newTexture2D();
			Texture3D *newTexture3D();
			TextureCube *newTextureCube();

			const TextureContainer &getTextures() const {
				return textures;
			}
		};


	}
}//end namespace

#endif
