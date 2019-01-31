// This file is part of Glest <https://github.com/Glest>
//
// Copyright (C) 2018  The Glest team
//
// Glest is a fork of MegaGlest <https://megaglest.org/>
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

#ifndef _SHARED_GRAPHICS_QUATERNION_H_
#define _SHARED_GRAPHICS_QUATERNION_H_ 

#include <string>

#include "vec.h"
#include "matrix.h"
#include "leak_dumper.h"

using namespace std;

namespace Shared {
	namespace Graphics {

		// =====================================================
		//	class AxisAngle
		// =====================================================

		class AxisAngle {
		public:
			Vec3f axis;
			float angle;

			AxisAngle() {
				angle = 0.0f;
			}
			AxisAngle(const Vec3f &axis, float angle);
		};

		// =====================================================
		//	class EulerAngles
		// =====================================================

		class EulerAngles {
		public:
			float x, y, z;

			EulerAngles() {
				x = 0.0f;
				y = 0.0f;
				z = 0.0f;
			}
			EulerAngles(float x, float y, float z);
		};

		// =====================================================
		//	class Quaternion
		// =====================================================

		class Quaternion {
		private:
			float w;
			Vec3f v;

		public:
			Quaternion();
			Quaternion(float w, const Vec3f &v);
			Quaternion(const EulerAngles &eulerAngles);
			//Quaternion(const AxisAngle &axisAngle);

			//initializers
			void setMultIdentity();
			void setAddIdentity();
			void setAxisAngle(const AxisAngle &axisAngle);
			void setEuler(const EulerAngles &eulerAngles);

			//unary operators
			//float length();
			Quaternion conjugate();
			//void normalize();

			//binary operators
			Quaternion operator + (const Quaternion &q) const;
			Quaternion operator * (const Quaternion &q) const;
			void operator += (const Quaternion &q);
			void operator *= (const Quaternion &q);

			//ternary operators
			Quaternion lerp(float t, const Quaternion &q) const;

			//conversions
			Matrix3f toMatrix3() const;
			Matrix4f toMatrix4() const;
			//AxisAngle toAxisAngle() const;

			//local axis
			Vec3f getLocalXAxis() const;
			Vec3f getLocalYAxis() const;
			Vec3f getLocalZAxis() const;
		};

	}
} //end namespace

#endif
