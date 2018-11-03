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

#include "shader_manager.h"
#include <stdexcept>
#include "graphics_interface.h"
#include "graphics_factory.h"
#include "util.h"
#include "platform_util.h"
#include "leak_dumper.h"

using namespace Shared::Util;

namespace Shared {
	namespace Graphics {

		// =====================================================
		//	class ShaderManager
		// =====================================================

		ShaderManager::ShaderManager() {
			if (GlobalStaticFlags::getIsNonGraphicalModeEnabled() == true) {
				throw game_runtime_error("Loading graphics in headless server mode not allowed!");
			}

		}

		ShaderManager::~ShaderManager() {
		}

		void ShaderManager::init() {
			for (unsigned int i = 0; i < shaders.size(); ++i) {
				shaders[i]->init();
				if (!shaders[i]->compile(logString)) {
					throw game_runtime_error("Can't compile shader\n");
				}
			}
			for (unsigned int i = 0; i < shaderPrograms.size(); ++i) {
				shaderPrograms[i]->init();
				if (!shaderPrograms[i]->link(logString)) {
					throw game_runtime_error("Can't link shader\n");
				}
			}
		}

		void ShaderManager::end() {
			for (unsigned int i = 0; i < shaderPrograms.size(); ++i) {
				shaderPrograms[i]->end();
				delete shaderPrograms[i];
			}
			shaderPrograms.clear();
			for (unsigned int i = 0; i < shaders.size(); ++i) {
				shaders[i]->end();
				delete shaders[i];
			}
			shaders.clear();
		}

		ShaderProgram *ShaderManager::newShaderProgram() {
			ShaderProgram *sp = GraphicsInterface::getInstance().getFactory()->newShaderProgram();
			shaderPrograms.push_back(sp);
			return sp;
		}

		VertexShader *ShaderManager::newVertexShader() {
			VertexShader *vs = GraphicsInterface::getInstance().getFactory()->newVertexShader();
			shaders.push_back(vs);
			return vs;
		}

		FragmentShader *ShaderManager::newFragmentShader() {
			FragmentShader *fs = GraphicsInterface::getInstance().getFactory()->newFragmentShader();
			shaders.push_back(fs);
			return fs;
		}

	}
} //end namespace
