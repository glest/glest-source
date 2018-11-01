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

#ifndef _SHARED_GRAPHICS_GL_CONTEXTGL_H_
#define _SHARED_GRAPHICS_GL_CONTEXTGL_H_ 

#include "context.h"
#include "gl_wrap.h"
#include "leak_dumper.h"

namespace Shared {
	namespace Graphics {
		namespace Gl {

			using Platform::PlatformContextGl;

			// =====================================================
			//	class ContextGl
			// =====================================================

			class ContextGl : public Context {
			protected:
				PlatformContextGl pcgl;

			public:
				ContextGl();
				virtual ~ContextGl();

				virtual void init();
				virtual void end();
				virtual void reset() {
				};

				virtual void makeCurrent();
				virtual void swapBuffers();

				const PlatformContextGl *getPlatformContextGl() const {
					return &pcgl;
				}
				PlatformContextGl *getPlatformContextGlPtr() {
					return &pcgl;
				}
			};

		}
	}
}//end namespace

#endif
