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

#include "surface_atlas.h"

#include <stdexcept>
#include <algorithm>

#include "renderer.h"
#include "util.h"
#include "math_util.h"
#include "leak_dumper.h"

using namespace std;
using namespace Shared::Util;
using namespace Shared::Graphics;

namespace Glest {
	namespace Game {

		// =====================================================
		//	class PixmapInfo
		// =====================================================

		SurfaceInfo::SurfaceInfo(const Pixmap2D *lu, const Pixmap2D *ru, const Pixmap2D *ld,
			const Pixmap2D *rd) {
			this->leftDown = ld;
			this->leftUp = lu;
			this->rightDown = rd;
			this->rightUp = ru;
			center = NULL;
			texture = NULL;

		}

		SurfaceInfo::SurfaceInfo(const Pixmap2D *center) {
			this->leftDown = NULL;
			this->leftUp = NULL;
			this->rightDown = NULL;
			this->rightUp = NULL;
			this->center = center;
			texture = NULL;
		}

		bool SurfaceInfo::operator==(const SurfaceInfo &si) const {
			return
				this->center == si.getCenter() &&
				this->leftDown == si.getLeftDown() &&
				this->leftUp == si.getLeftUp() &&
				this->rightDown == si.getRightDown() &&
				this->rightUp == si.getRightUp();
		}

		// ===============================
		// 	class SurfaceAtlas
		// ===============================

		SurfaceAtlas::SurfaceAtlas() {
			surfaceSize = -1;
		}

		void SurfaceAtlas::addSurface(SurfaceInfo *si) {
			if (si == NULL) {
				throw megaglest_runtime_error("Bad surface info (NULL)");
			}

			//check dimensions
			if (si->getCenter() != NULL) {
				checkDimensions(si->getCenter());
			} else {
				checkDimensions(si->getLeftUp());
				checkDimensions(si->getLeftDown());
				checkDimensions(si->getRightUp());
				checkDimensions(si->getRightDown());
			}

			//add info
			SurfaceInfos::iterator it = find(surfaceInfos.begin(), surfaceInfos.end(), *si);
			if (it == surfaceInfos.end()) {
				//add new texture
				Texture2D *t = Renderer::getInstance().newTexture2D(rsGame);
				if (t) {
					//if(t == NULL) {
					//	throw megaglest_runtime_error("Could not create new texture (NULL)");
					//}
					t->setWrapMode(Texture::wmClampToEdge);
					t->getPixmap()->init(surfaceSize, surfaceSize, 4);
				}

				si->setCoord(Vec2f(0.f, 0.f));
				si->setTexture(t);
				surfaceInfos.push_back(*si);

				//copy texture to pixmap
				if (si->getCenter() != NULL) {
					if (t) {
						t->getPixmap()->copy(si->getCenter());
					}
				} else {
					if (t) {
						t->getPixmap()->splat(si->getLeftUp(), si->getRightUp(), si->getLeftDown(), si->getRightDown());
					}
				}
			} else {
				si->setCoord(it->getCoord());
				si->setTexture(it->getTexture());
			}
		}

		float SurfaceAtlas::getCoordStep() const {
			return 1.f;
		}

		void SurfaceAtlas::checkDimensions(const Pixmap2D *p) {
			if (GlobalStaticFlags::getIsNonGraphicalModeEnabled() == true) {
				return;
			}

			if (p == NULL) {
				throw megaglest_runtime_error("Bad surface texture pixmap (NULL)");
			} else if (surfaceSize == -1) {
				surfaceSize = p->getW();
				//printf("Setting surfaceSize = %d for pixmap [%s]\n",surfaceSize,p->getPath().c_str());
			} else if (p->getW() != surfaceSize || p->getH() != surfaceSize) {
				char szBuf[8096] = "";
				snprintf(szBuf, 8096, "Bad surface texture dimensions, expected surfaceSize = %d, texture w = %d, h = %d", surfaceSize, p->getW(), p->getH());
				throw megaglest_runtime_error(szBuf);
			}
		}

	}
}//end namespace
