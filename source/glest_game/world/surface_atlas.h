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

#ifndef _GLEST_GAME_SURFACEATLAS_H_
#define _GLEST_GAME_SURFACEATLAS_H_

#ifdef WIN32
#include <winsock2.h>
#include <winsock.h>
#endif

#include <vector>
#include <set>
#include "texture.h"
#include "vec.h"
#include "leak_dumper.h"

using std::vector;
using std::set;
using Shared::Graphics::Pixmap2D;
using Shared::Graphics::Texture2D;
using Shared::Graphics::Vec2i;
using Shared::Graphics::Vec2f;

namespace ZetaGlest {
	namespace Game {

		// =====================================================
		//	class SurfaceInfo
		// =====================================================

		class SurfaceInfo {
		private:
			const Pixmap2D *center;
			const Pixmap2D *leftUp;
			const Pixmap2D *rightUp;
			const Pixmap2D *leftDown;
			const Pixmap2D *rightDown;
			Vec2f coord;
			const Texture2D *texture;

		public:
			explicit SurfaceInfo(const Pixmap2D *center);
			SurfaceInfo(const Pixmap2D *lu, const Pixmap2D *ru, const Pixmap2D *ld, const Pixmap2D *rd);
			bool operator==(const SurfaceInfo &si) const;

			inline const Pixmap2D *getCenter() const {
				return center;
			}
			inline const Pixmap2D *getLeftUp() const {
				return leftUp;
			}
			inline const Pixmap2D *getRightUp() const {
				return rightUp;
			}
			inline const Pixmap2D *getLeftDown() const {
				return leftDown;
			}
			inline const Pixmap2D *getRightDown() const {
				return rightDown;
			}
			inline const Vec2f &getCoord() const {
				return coord;
			}
			inline const Texture2D *getTexture() const {
				return texture;
			}

			inline void setCoord(const Vec2f &coord) {
				this->coord = coord;
			}
			inline void setTexture(const Texture2D *texture) {
				this->texture = texture;
			}
		};

		// =====================================================
		// 	class SurfaceAtlas
		//
		/// Holds all surface textures for a given Tileset
		// =====================================================

		class SurfaceAtlas {
		private:
			typedef vector<SurfaceInfo> SurfaceInfos;

		private:
			SurfaceInfos surfaceInfos;
			int surfaceSize;

		public:
			SurfaceAtlas();

			void addSurface(SurfaceInfo *si);
			float getCoordStep() const;

		private:
			void checkDimensions(const Pixmap2D *p);
		};

	}
}//end namespace

#endif
