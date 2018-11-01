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

#include "camera.h"

#include "leak_dumper.h"

namespace Shared {
	namespace Graphics {

		// =====================================================
		//	class Camera
		// =====================================================

		Camera::Camera() {
			position = Vec3f(0.0f);
		}

		void Camera::moveLocalX(float amount) {
			position = position + orientation.getLocalXAxis()*amount;
		}

		void Camera::moveLocalY(float amount) {
			position = position + orientation.getLocalYAxis()*amount;
		}

		void Camera::moveLocalZ(float amount) {
			position = position + orientation.getLocalZAxis()*amount;
		}

		void Camera::addYaw(float amount) {
			Quaternion q(EulerAngles(0, amount, 0));
			orientation *= q;
		}

		void Camera::addPitch(float amount) {
			Quaternion q(EulerAngles(amount, 0, 0));
			orientation *= q;
		}

		void Camera::addRoll(float amount) {
			Quaternion q(EulerAngles(0, 0, amount));
			orientation *= q;
		}

	}
}//end namespace
