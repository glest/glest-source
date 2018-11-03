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

#ifndef _METRICS_H_
#define _METRICS_H_

#ifdef WIN32
#   include <winsock2.h>
#   include <winsock.h>
#endif

#include "config.h"
#include "leak_dumper.h"

namespace Game {
	// =====================================================
	//      class Metrics
	// =====================================================

	class Metrics {
	private:
		int virtualW;
		int virtualH;
		int screenW;
		int screenH;
		int minimapX;
		int minimapY;
		int minimapW;
		int minimapH;
		int displayX;
		int displayY;
		int displayH;
		int displayW;

	private:
		Metrics();
		static Metrics *getInstancePtr();
		void reloadData(int resWidth = -1, int resHeight = -1);

	public:
		static const Metrics & getInstance();

		int getVirtualW() const {
			return virtualW;
		}
		int getVirtualH() const {
			return virtualH;
		}
		int getScreenW() const {
			return screenW;
		}
		int getScreenH() const {
			return screenH;
		}
		int getMinimapX() const {
			return minimapX;
		}
		int getMinimapY() const {
			return minimapY;
		}
		int getMinimapW() const {
			return minimapW;
		}
		int getMinimapH() const {
			return minimapH;
		}
		int getDisplayX() const {
			return displayX;
		}
		int getDisplayY() const {
			return displayY;
		}
		int getDisplayH() const {
			return displayH;
		}
		int getDisplayW() const {
			return displayW;
		}
		float getAspectRatio() const;

		int toVirtualX(int w) const;
		int toVirtualY(int h) const;

		bool isInDisplay(int x, int y) const;
		bool isInMinimap(int x, int y) const;

		static void reload(int resWidth = -1, int resHeight = -1);
	};

} //end namespace

#endif
