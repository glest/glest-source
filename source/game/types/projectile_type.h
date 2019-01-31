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

#ifndef _PROJECTILETYPE_H_
#define _PROJECTILETYPE_H_

#ifdef WIN32
#   include <winsock2.h>
#   include <winsock.h>
#endif

#include "sound.h"
#include "vec.h"
//#include "xml_parser.h"
#include "util.h"
//#include "element_type.h"
#include "factory.h"
#include "sound_container.h"
#include "particle_type.h"
#include "leak_dumper.h"

using std::vector;
using std::string;

namespace Game {
	// =====================================================
	//      class ProjectileType
	// =====================================================

	class ProjectileType {
	protected:
		ParticleSystemTypeProjectile * projectileParticleSystemType;
		SoundContainer hitSounds;
		float attackStartTime;

		string spawnUnit;
		int spawnUnitcount;
		bool spawnUnitAtTarget;

		bool shake;
		int shakeIntensity;
		int shakeDuration;

		bool shakeVisible;
		bool shakeInCameraView;
		bool shakeCameraDistanceAffected;
		int damagePercentage;

	public:
		ProjectileType();
		virtual ~ProjectileType();


		void load(const XmlNode * projectileNode, const string & dir,
			const string & techtreepath, std::map < string,
			vector < pair < string, string > > >&loadedFileList,
			string parentLoader);

		//get/set
		inline StaticSound *getHitSound() const {
			return hitSounds.getRandSound();
		}
		ParticleSystemTypeProjectile *getProjectileParticleSystemType() const {
			return projectileParticleSystemType;
		}
		float getAttackStartTime() const {
			return attackStartTime;
		}
		void setAttackStartTime(float value) {
			attackStartTime = value;
		}

		string getSpawnUnit() const {
			return spawnUnit;
		}
		int getSpawnUnitcount() const {
			return spawnUnitcount;
		}
		bool getSpawnUnitAtTarget() const {
			return spawnUnitAtTarget;
		}

		bool isShake() const {
			return shake;
		}
		bool isShakeCameraDistanceAffected() const {
			return shakeCameraDistanceAffected;
		}
		int getShakeDuration() const {
			return shakeDuration;
		}
		bool isShakeInCameraView() const {
			return shakeInCameraView;
		}
		int getShakeIntensity() const {
			return shakeIntensity;
		}
		bool isShakeVisible() const {
			return shakeVisible;
		}
		int getDamagePercentage() const {
			return damagePercentage;
		}
		void setDamagePercentage(int value) {
			damagePercentage = value;
		}

		void setProjectileParticleSystemType(ParticleSystemTypeProjectile *
			pointer) {
			projectileParticleSystemType = pointer;
		}
		ParticleSystemTypeProjectile *getProjectileParticleSystemType() {
			return projectileParticleSystemType;
		}
	};

} //end namespace

#endif
