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

#ifndef _SHARED_GRAPHICS_CAMERA_H_
#define _SHARED_GRAPHICS_CAMERA_H_

#include "vec.h"
#include "quaternion.h"
#include "leak_dumper.h"

namespace Shared {
	namespace Graphics {

		// =====================================================
		//	class Camera
		// =====================================================

		class Camera {
		private:
			Quaternion orientation;
			Vec3f position;
		public:
			Camera();

			Vec3f getPosition() const {
				return position;
			}
			Quaternion getOrientation() const {
				return orientation;
			}

			const Vec3f & getConstPosition() const {
				return position;
			}
			const Quaternion & getConstOrientation() const {
				return orientation;
			}

			void setPosition(const Vec3f &position) {
				this->position = position;
			}
			void setOrientation(const Quaternion &orientation) {
				this->orientation = orientation;
			}

			void moveLocalX(float amount);
			void moveLocalY(float amount);
			void moveLocalZ(float amount);

			void addYaw(float amount);
			void addPitch(float amount);
			void addRoll(float amount);
		};

	}
} //end namespace

#endif
