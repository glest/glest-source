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

#ifndef _SHARED_GRAPHICS_GL_PARTICLERENDERERGL_H_
#define _SHARED_GRAPHICS_GL_PARTICLERENDERERGL_H_

#include "particle_renderer.h"
#include "leak_dumper.h"

namespace Shared {
	namespace Graphics {
		namespace Gl {

			// =====================================================
			//	class ParticleRendererGl
			// =====================================================

			class ParticleRendererGl : public ParticleRenderer {
			public:
				static const int bufferSize = 1024;

			private:
				bool rendering;
				Vec3f vertexBuffer[bufferSize];
				Vec2f texCoordBuffer[bufferSize];
				Vec4f colorBuffer[bufferSize];

			public:
				//particles
				ParticleRendererGl();
				virtual void renderManager(ParticleManager *pm, ModelRenderer *mr);
				virtual void renderSystem(ParticleSystem *ps);
				virtual void renderSystemLine(ParticleSystem *ps);
				virtual void renderSystemLineAlpha(ParticleSystem *ps);
				virtual void renderModel(GameParticleSystem *ps, ModelRenderer *mr);

			protected:
				void renderBufferQuads(int quadCount);
				void renderBufferLines(int lineCount);
				void setBlendMode(ParticleSystem::BlendMode blendMode);
			};

		}
	}
} //end namespace

#endif
