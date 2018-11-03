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

#include "context_gl.h"

#include <cassert>
#include <stdexcept>

#include "opengl.h"
#include "util.h"
#include "leak_dumper.h"

using namespace std;
using namespace Shared::Util;

namespace Shared {
	namespace Graphics {
		namespace Gl {

			// =====================================================
			//	class ContextGl
			// =====================================================

			ContextGl::ContextGl() : Context() {

			}

			void ContextGl::init() {

				pcgl.init(colorBits, depthBits, stencilBits,
					(hardware_acceleration != 0), fullscreen_anti_aliasing,
					gammaValue);
			}

			ContextGl::~ContextGl() {
				end();
			}

			void ContextGl::end() {
				pcgl.end();
			}

			void ContextGl::makeCurrent() {
				pcgl.makeCurrent();
			}

			void ContextGl::swapBuffers() {
				pcgl.swapBuffers();
			}

		}
	}
} //end namespace
