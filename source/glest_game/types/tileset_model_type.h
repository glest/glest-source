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

#ifndef _TILESET_MODEL_TYPE_H_
#define _TILESET_MODEL_TYPE_H_

#ifdef WIN32
#   include <winsock2.h>
#   include <winsock.h>
#endif

#include <vector>
#include "model.h"
#include "vec.h"
#include "leak_dumper.h"
#include "unit_particle_type.h"

using std::vector;

namespace Game {
	using Shared::Graphics::Model;
	using Shared::Graphics::Vec3f;

	// =====================================================
	//      class ObjectType  
	//
	///     Each of the possible objects of the map: trees, stones ...
	// =====================================================

	typedef vector < ObjectParticleSystemType * >ModelParticleSystemTypes;

	class TilesetModelType {
	private:
		Model * model;
		ModelParticleSystemTypes particleTypes;
		int height;
		bool rotationAllowed;
		bool randomPositionEnabled;
		bool smoothTwoFrameAnim;

		int animSpeed;

	public:
		TilesetModelType();
		~TilesetModelType();

		void addParticleSystem(ObjectParticleSystemType * particleSystem);
		inline bool hasParticles() const {
			return particleTypes.empty() == false;
		}
		inline ModelParticleSystemTypes *getParticleTypes() {
			return &particleTypes;
		}


		inline Model *getModel() const {
			return model;
		}
		inline void setModel(Model * model) {
			this->model = model;
		}

		inline int getHeight() const {
			return height;
		}
		inline void setHeight(int height) {
			this->height = height;
		}

		inline bool getRotationAllowed() const {
			return rotationAllowed;
		}
		inline void setRotationAllowed(bool rotationAllowed) {
			this->rotationAllowed = rotationAllowed;
		}

		inline bool getRandomPositionEnabled() const {
			return randomPositionEnabled;
		}
		inline void setRandomPositionEnabled(bool randomPositionEnabled) {
			this->randomPositionEnabled = randomPositionEnabled;
		}

		inline bool getSmoothTwoFrameAnim() const {
			return smoothTwoFrameAnim;
		}
		inline void setSmoothTwoFrameAnim(bool smoothTwoFrameAnim) {
			this->smoothTwoFrameAnim = smoothTwoFrameAnim;
		}

		inline int getAnimSpeed() const {
			return animSpeed;
		}
		inline void setAnimSpeed(int value) {
			animSpeed = value;
		}

		//      inline int getAnimSpeedVariation() const                        {return animVariation;}
		//      inline void setAnimSpeedVariation(int value) {animSpeed = valueVariation;}
	};

} //end namespace

#endif
