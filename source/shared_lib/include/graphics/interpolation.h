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

#ifndef _SHARED_GRAPHICS_INTERPOLATION_H_
#define _SHARED_GRAPHICS_INTERPOLATION_H_

#include "vec.h"
#include "model.h"
#include <map>
#include "leak_dumper.h"

namespace Shared {
	namespace Graphics {

		// =====================================================
		//	class InterpolationData
		// =====================================================

		class InterpolationData {
		private:
			const Mesh *mesh;

			Vec3f *vertices;
			Vec3f *normals;

			int raw_frame_ofs;

			static bool enableInterpolation;

			void update(const Vec3f* src, Vec3f* &dest, float t, bool cycle);

		public:
			InterpolationData(const Mesh *mesh);
			~InterpolationData();

			static void setEnableInterpolation(bool enabled) {
				enableInterpolation = enabled;
			}

			const Vec3f *getVertices() const {
				return !vertices || !enableInterpolation ? mesh->getVertices() + raw_frame_ofs : vertices;
			}
			const Vec3f *getNormals() const {
				return !normals || !enableInterpolation ? mesh->getNormals() + raw_frame_ofs : normals;
			}

			void update(float t, bool cycle);
			void updateVertices(float t, bool cycle);
			void updateNormals(float t, bool cycle);
		};

	}
} //end namespace

#endif
