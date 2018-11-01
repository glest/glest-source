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

#ifndef _SHARED_GRAPHICS_CONTEXT_H_
#define _SHARED_GRAPHICS_CONTEXT_H_ 

#include "data_types.h"
#include "leak_dumper.h"

namespace Shared {
	namespace Graphics {

		using Platform::uint32;
		using Platform::int8;

		// =====================================================
		//	class Context
		// =====================================================

		class Context {
		protected:
			uint32 colorBits;
			uint32 depthBits;
			uint32 stencilBits;
			int8 hardware_acceleration;
			int8 fullscreen_anti_aliasing;
			float gammaValue;

		public:
			Context();
			virtual ~Context() {
			}

			uint32 getColorBits() const {
				return colorBits;
			}
			uint32 getDepthBits() const {
				return depthBits;
			}
			uint32 getStencilBits() const {
				return stencilBits;
			}
			int8 getHardware_acceleration() const {
				return hardware_acceleration;
			}
			int8 getFullscreen_anti_aliasing() const {
				return fullscreen_anti_aliasing;
			}
			float getGammaValue() const {
				return gammaValue;
			}

			void setColorBits(uint32 colorBits) {
				this->colorBits = colorBits;
			}
			void setDepthBits(uint32 depthBits) {
				this->depthBits = depthBits;
			}
			void setStencilBits(uint32 stencilBits) {
				this->stencilBits = stencilBits;
			}
			void setHardware_acceleration(int8 value) {
				hardware_acceleration = value;
			}
			void setFullscreen_anti_aliasing(int8 value) {
				fullscreen_anti_aliasing = value;
			}
			void setGammaValue(float value) {
				gammaValue = value;
			}

			virtual void init() = 0;
			virtual void end() = 0;
			virtual void reset() = 0;

			virtual void makeCurrent() = 0;
			virtual void swapBuffers() = 0;
		};

	}
}//end namespace

#endif
