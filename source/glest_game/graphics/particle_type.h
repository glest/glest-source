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

#ifndef _PARTICLETYPE_H_
#define _PARTICLETYPE_H_

#ifdef WIN32
#include <winsock2.h>
#include <winsock.h>
#endif

#include <string>
#include <list>
#include "particle.h"
#include "factory.h"
#include "texture.h"
#include "vec.h"
#include "xml_parser.h"
#include "graphics_interface.h"
#include "leak_dumper.h"

using std::string;
using namespace Shared::Graphics;

namespace Game {
	using Shared::Graphics::ParticleSystem;
	using Shared::Graphics::UnitParticleSystem;
	using Shared::Graphics::AttackParticleSystem;
	using Shared::Graphics::ProjectileParticleSystem;
	using Shared::Graphics::SplashParticleSystem;
	using Shared::Graphics::Texture2D;
	using Shared::Graphics::Vec3f;
	using Shared::Graphics::Vec4f;
	using Shared::Graphics::Model;
	using Shared::Util::MultiFactory;
	using Shared::Xml::XmlNode;

	class UnitParticleSystemType;

	// ===========================================================
	//	class ParticleSystemType 
	//
	///	A type of particle system
	// ===========================================================

	class ParticleSystemType : public ParticleSystemTypeInterface {
	protected:
		string type;
		Texture2D *texture;
		Model *model;
		float modelCycle;
		string primitive;
		Vec3f offset;
		Vec4f color;
		Vec4f colorNoEnergy;
		float size;
		float sizeNoEnergy;
		float speed;
		float speedUpRelative;
		float speedUpConstant;
		float gravity;
		float emissionRate;
		int energyMax;
		int energyVar;
		string mode;
		bool teamcolorNoEnergy;
		bool teamcolorEnergy;
		int alternations;
		int particleSystemStartDelay;
		typedef std::list<UnitParticleSystemType*> Children;
		Children children;

		bool minmaxEnabled;
		int minHp;
		int maxHp;
		bool minmaxIsPercent;

		void copyAll(const ParticleSystemType &src);
	public:

		ParticleSystemType();
		virtual ~ParticleSystemType();

		ParticleSystemType & operator=(const ParticleSystemType &src);
		ParticleSystemType(const ParticleSystemType &src);

		void load(const XmlNode *particleSystemNode, const string &dir,
			RendererInterface *renderer, std::map<string, vector<pair<string, string> > > &loadedFileList,
			string parentLoader, string techtreePath);
		void setValues(AttackParticleSystem *ats);
		bool hasTexture() const {
			return(texture != NULL);
		}
		bool hasModel() const {
			return(model != NULL);
		}

		bool getMinmaxEnabled() const {
			return minmaxEnabled;
		}
		int getMinHp() const {
			return minHp;
		}
		int getMaxHp() const {
			return maxHp;
		}
		bool getMinmaxIsPercent() const {
			return minmaxIsPercent;
		}

		void setMinmaxEnabled(bool value) {
			minmaxEnabled = value;
		}
		void setMinHp(int value) {
			minHp = value;
		}
		void setMaxHp(int value) {
			maxHp = value;
		}
		void setMinmaxIsPercent(bool value) {
			minmaxIsPercent = value;
		}

		string getType() const {
			return type;
		};

		virtual void saveGame(XmlNode *rootNode);
		virtual void loadGame(const XmlNode *rootNode);

	protected:

	};

	// ===========================================================
	//	class ParticleSystemTypeProjectile
	// ===========================================================

	class ParticleSystemTypeProjectile : public ParticleSystemType {
	private:
		string trajectory;
		float trajectorySpeed;
		float trajectoryScale;
		float trajectoryFrequency;

	public:
		ParticleSystemTypeProjectile();
		void load(const XmlNode *particleFileNode, const string &dir, const string &path,
			RendererInterface *renderer, std::map<string, vector<pair<string, string> > > &loadedFileList,
			string parentLoader, string techtreePath);
		ProjectileParticleSystem *create(ParticleOwner *owner);

		virtual void saveGame(XmlNode *rootNode);
	};

	// ===========================================================
	//	class ParticleSystemTypeSplash
	// ===========================================================

	class ParticleSystemTypeSplash : public ParticleSystemType {
	public:

		ParticleSystemTypeSplash();
		void load(const XmlNode *particleFileNode, const string &dir, const string &path,
			RendererInterface *renderer, std::map<string, vector<pair<string, string> > > &loadedFileList,
			string parentLoader, string techtreePath);
		SplashParticleSystem *create(ParticleOwner *owner);

		virtual void saveGame(XmlNode *rootNode);

	private:
		float emissionRateFade;
		float verticalSpreadA;
		float verticalSpreadB;
		float horizontalSpreadA;
		float horizontalSpreadB;
	};

} //end namespace

#endif
