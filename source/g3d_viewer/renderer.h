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

#ifndef _SHADER_G3DVIEWER_RENDERER_H_
#define _SHADER_G3DVIEWER_RENDERER_H_

#ifdef WIN32
#include <winsock2.h>
#include <winsock.h>
#endif

#include "model_renderer.h"
#include "model_renderer_gl.h"
#include "texture_manager.h"
#include "model.h"
#include "texture.h"

#include "particle_renderer.h"
#include "model_manager.h"
#include "graphics_interface.h"

//#include "model_manager.h"
//#include "graphics_factory_gl.h"

using Shared::Graphics::ModelRenderer;
using Shared::Graphics::TextureManager;
using Shared::Graphics::ModelManager;
using Shared::Graphics::Model;
using Shared::Graphics::Texture2D;
using Shared::Graphics::ParticleRenderer;
using Shared::Graphics::ParticleManager;
using Shared::Graphics::ParticleSystem;
using Shared::Graphics::Gl::MeshCallback;
//#include "model_renderer.h"

using Shared::Graphics::Mesh;
using Shared::Graphics::Texture;

using namespace Shared::Graphics;

namespace Shared {
	namespace G3dViewer {
		// ===============================
		// 	class Renderer
		// ===============================

		class Renderer : public RendererInterface {
		public:
			static int windowX;
			static int windowY;
			static int windowW;
			static int windowH;

		public:
			enum PlayerColor {
				pcRed,
				pcBlue,
				pcGreen,
				pcYellow,
				pcWhite,
				pcCyan,
				pcOrange,
				pcMagenta,
			};

		private:
			bool wireframe;
			bool normals;
			bool grid;

			int width;
			int height;

			ModelRenderer *modelRenderer;
			TextureManager *textureManager;
			ParticleRenderer *particleRenderer;

			ParticleManager *particleManager;
			ModelManager *modelManager;

			Texture2D *customTextureRed;
			Texture2D *customTextureBlue;
			Texture2D *customTextureGreen;
			Texture2D *customTextureYellow;
			Texture2D *customTextureWhite;
			Texture2D *customTextureCyan;
			Texture2D *customTextureOrange;
			Texture2D *customTextureMagenta;
			MeshCallback meshCallback;

			float red;
			float green;
			float blue;
			float alpha;

			Renderer();
			void checkGlCaps();
			void checkExtension(const string &extension, const string &msg);

		public:
			virtual ~Renderer();
			static Renderer *getInstance();

			void init();
			void reset(int w, int h, PlayerColor playerColor);
			void transform(float rotX, float rotY, float zoom);
			void renderGrid();

			bool getNormals() const {
				return normals;
			}
			bool getWireframe() const {
				return wireframe;
			}
			bool getGrid() const {
				return grid;
			}

			void toggleNormals();
			void toggleWireframe();
			void toggleGrid();

			void renderTheModel(Model *model, float f);

			void manageParticleSystem(ParticleSystem *particleSystem);
			void updateParticleManager();
			void renderParticleManager();
			Texture2D *getPlayerColorTexture(PlayerColor playerColor);

			Texture2D * getNewTexture2D();

			Model *newModel(ResourceScope rs, const string &path, bool deletePixMapAfterLoad = false, std::map<string, vector<pair<string, string> > > *loadedFileList = NULL, string *sourceLoader = NULL);
			void endModel(ResourceScope rs, Model *model);
			Texture2D *newTexture2D(ResourceScope rs) {
				return getNewTexture2D();
			}

			void initTextureManager();
			void initModelManager();

			void end();

			void setBackgroundColor(float red, float green, float blue);
			void setAlphaColor(float alpha);
			void saveScreen(const string &path, std::pair<int, int> *overrideSize);
			bool hasActiveParticleSystem(ParticleSystem::ParticleSystemType typeName) const;
		};

	}
}//end namespace

#endif
