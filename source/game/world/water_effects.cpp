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

#include "water_effects.h"

#include "config.h"
#include "map.h"
#include "leak_dumper.h"

namespace Game {
	// =====================================================
	//	class WaterSplash
	// =====================================================

	WaterSplash::WaterSplash(const Vec2f &pos, int size) {
		this->pos = pos;
		this->size = 1 + (size - 1) / 2;
		anim = 0.f;
		enabled = true;

	}

	void WaterSplash::update(float amount) {
		if (enabled) {
			anim += amount / size;
			if (anim > 1.f) {
				enabled = false;
			}
		}
	}

	// ===============================
	// 	class WaterEffects  
	// ===============================

	WaterEffects::WaterEffects() {
		anim = 0;
	}

	void WaterEffects::update(float speed) {
		anim += 0.5f / GameConstants::updateFps;
		if (anim > 1.f) {
			anim = 0;
		}
		for (int i = 0; i < (int) waterSplashes.size(); ++i) {
			waterSplashes[i].update(speed / GameConstants::updateFps);
		}
	}

	void WaterEffects::addWaterSplash(const Vec2f &pos, int size) {
		for (int i = 0; i < (int) waterSplashes.size(); ++i) {
			if (!waterSplashes[i].getEnabled()) {
				waterSplashes[i] = WaterSplash(pos, size);
				return;
			}
		}
		waterSplashes.push_back(WaterSplash(pos, size));
	}

} //end namespace
