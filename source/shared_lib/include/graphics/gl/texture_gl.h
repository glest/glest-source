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

#ifndef _SHARED_GRAPHICS_GL_TEXTUREGL_H_
#define _SHARED_GRAPHICS_GL_TEXTUREGL_H_

#include "texture.h"
#include "opengl.h"
#include "leak_dumper.h"

namespace Shared {
	namespace Graphics {
		namespace Gl {

			// =====================================================
			//	class TextureGl
			// =====================================================

			class TextureGl {
			protected:
				GLuint handle;
				GLuint renderBufferId;
				GLuint frameBufferId;

				static bool enableATIHacks;

				void initRenderBuffer();
				void initFrameBuffer();
				void attachRenderBuffer();

			public:
				TextureGl();
				virtual ~TextureGl();

				static void setEnableATIHacks(bool value) {
					enableATIHacks = value;
				}
				static bool getEnableATIHacks() {
					return enableATIHacks;
				}

				GLuint getHandle() const {
					return handle;
				}
				GLuint getRenderBufferHandle() const {
					return renderBufferId;
				}
				GLuint getFrameBufferHandle() const {
					return frameBufferId;
				}

				bool supports_FBO_RBO();
				void setup_FBO_RBO();
				void attachFrameBufferToTexture();
				void dettachFrameBufferFromTexture();
				void dettachRenderBufferFromTexture();
				bool checkFrameBufferStatus();
				void teardown_FBO_RBO();

				virtual int getTextureWidth() const = 0;
				virtual int getTextureHeight() const = 0;

				void OutputTextureDebugInfo(Texture::Format format, int components, const string path, std::size_t rawSize, GLenum texType);
			};

			// =====================================================
			//	class Texture1DGl
			// =====================================================

			class Texture1DGl : public Texture1D, public TextureGl {
			public:
				Texture1DGl();
				virtual ~Texture1DGl();

				virtual void init(Filter filter, int maxAnisotropy = 1);
				virtual void end(bool deletePixelBuffer = true);

				virtual int getTextureWidth() const {
					return Texture1D::getTextureWidth();
				}
				virtual int getTextureHeight() const {
					return Texture1D::getTextureHeight();
				}
			};

			// =====================================================
			//	class Texture2DGl
			// =====================================================

			class Texture2DGl : public Texture2D, public TextureGl {
			public:
				Texture2DGl();
				virtual ~Texture2DGl();

				virtual void init(Filter filter, int maxAnisotropy = 1);
				virtual void end(bool deletePixelBuffer = true);

				virtual int getTextureWidth() const {
					return Texture2D::getTextureWidth();
				}
				virtual int getTextureHeight() const {
					return Texture2D::getTextureHeight();
				}
			};

			// =====================================================
			//	class Texture3DGl
			// =====================================================

			class Texture3DGl : public Texture3D, public TextureGl {
			public:

				Texture3DGl();
				virtual ~Texture3DGl();

				virtual void init(Filter filter, int maxAnisotropy = 1);
				virtual void end(bool deletePixelBuffer = true);

				virtual int getTextureWidth() const {
					return Texture3D::getTextureWidth();
				}
				virtual int getTextureHeight() const {
					return Texture3D::getTextureHeight();
				}
			};

			// =====================================================
			//	class TextureCubeGl
			// =====================================================

			class TextureCubeGl : public TextureCube, public TextureGl {
			public:

				TextureCubeGl();
				virtual ~TextureCubeGl();

				virtual void init(Filter filter, int maxAnisotropy = 1);
				virtual void end(bool deletePixelBuffer = true);

				virtual int getTextureWidth() const {
					return TextureCube::getTextureWidth();
				}
				virtual int getTextureHeight() const {
					return TextureCube::getTextureHeight();
				}

			};

		}
	}
}//end namespace

#endif
