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
}//end namespace

#endif
