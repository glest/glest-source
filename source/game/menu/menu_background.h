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

#ifndef _MENUBACKGROUND_H_
#define _MENUBACKGROUND_H_

#ifdef WIN32
#   include <winsock2.h>
#   include <winsock.h>
#endif

#include "particle.h"
#include "camera.h"
#include "vec.h"
#include "texture.h"
#include "model.h"
#include "randomgen.h"
#include "leak_dumper.h"

using Shared::Graphics::RainParticleSystem;
using Shared::Graphics::FireParticleSystem;
using Shared::Graphics::Camera;
using Shared::Graphics::Vec3f;
using Shared::Graphics::Vec2f;
using Shared::Graphics::Texture2D;
using Shared::Graphics::Model;
using Shared::Util::RandomGen;

namespace Game {
	// ===========================================================
	//      class MenuBackground  
	//
	///     Holds the data to display the 3D environment 
	/// in the MenuState
	// ===========================================================

	class
		MenuBackground {
	public:
		static const int
			meshSize = 32;
		static const int
			raindropCount = 1000;
		static const int
			characterCount = 5;

	private:
		Model *
			mainModel;

		//water
		bool
			water;
		float
			waterHeight;
		Texture2D *
			waterTexture;

		//fog
		bool
			fog;
		float
			fogDensity;

		//rain
		bool
			rain;
		Vec2f
			raindropPos[raindropCount];
		float
			raindropStates[raindropCount];

		//camera
		Camera
			camera;
		Camera
			lastCamera;
		const Camera *
			targetCamera;
		float
			t;

		//misc
		RandomGen
			random;
		Model *
			characterModels[characterCount];
		float
			anim;
		float
			fade;
		Vec3f
			aboutPosition;

		RainParticleSystem *
			rps;

	public:
		MenuBackground();
		~
			MenuBackground();

		bool
			getWater() const {
			return
				water;
		}
		float
			getWaterHeight() const {
			return
				waterHeight;
		}
		bool
			getFog() const {
			return
				fog;
		}
		float
			getFogDensity() const {
			return
				fogDensity;
		}
		bool
			getRain() const {
			return
				rain;
		}
		Texture2D *
			getWaterTexture() const {
			return
				waterTexture;
		}
		const Camera *
			getCamera() const {
			return &
				camera;
		}
		const Model *
			getCharacterModel(int i) const {
			return
				characterModels[i];
		}
		Model *
			getCharacterModelPtr(int i) const {
			return
				characterModels[i];
		}
		const Model *
			getMainModel() const {
			return
				mainModel;
		}
		Model *
			getMainModelPtr() const {
			return
				mainModel;
		}
		float
			getFade() const {
			return
				fade;
		}
		Vec2f
			getRaindropPos(int i) const {
			return
				raindropPos[i];
		}
		float
			getRaindropState(int i) const {
			return
				raindropStates[i];
		}
		float
			getAnim() const {
			return
				anim;
		}
		const
			Vec3f &
			getAboutPosition() const {
			return
				aboutPosition;
		}

		void
			setTargetCamera(const Camera * targetCamera);
		void
			update();

	private:
		Vec2f
			computeRaindropPos();
		void
			createRainParticleSystem();
		void
			cleanup();
	};

} //end namespace

#endif
