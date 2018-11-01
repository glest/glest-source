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

#ifndef _GLEST_GAME_UNITPARTICLETYPE_H_
#define _GLEST_GAME_UNITPARTICLETYPE_H_

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
#include "particle_type.h"

using std::string;
using namespace Shared::Graphics;

namespace Glest {
	namespace Game {

		using Shared::Graphics::ParticleManager;
		using Shared::Graphics::ParticleSystem;
		using Shared::Graphics::UnitParticleSystem;
		using Shared::Graphics::Texture2D;
		using Shared::Graphics::Vec3f;
		using Shared::Graphics::Vec4f;
		using Shared::Util::MultiFactory;
		using Shared::Xml::XmlNode;

		// ===========================================================
		//	class ParticleSystemType 
		//
		///	A type of particle system
		// ===========================================================

		class UnitParticleSystemType : public ParticleSystemType {
		protected:
			UnitParticleSystem::Shape shape;
			float angle;
			float radius;
			float minRadius;
			float emissionRateFade;
			Vec3f direction;
			bool relative;
			string meshName;
			bool relativeDirection;
			bool fixed;
			int staticParticleCount;
			bool isVisibleAtNight;
			bool isVisibleAtDay;
			bool isDaylightAffected;
			bool radiusBasedStartenergy;
			int delay;
			int lifetime;
			float startTime;
			float endTime;


		public:
			UnitParticleSystemType();
			virtual ~UnitParticleSystemType() {
			};

			void load(const XmlNode *particleSystemNode, const string &dir,
				RendererInterface *newTexture, std::map<string, vector<pair<string, string> > > &loadedFileList,
				string parentLoader, string techtreePath);
			void load(const XmlNode *particleFileNode, const string &dir, const string &path, RendererInterface *newTexture,
				std::map<string, vector<pair<string, string> > > &loadedFileList, string parentLoader,
				string techtreePath);

			void setStartTime(float startTime) {
				this->startTime = startTime;
			}
			float getStartTime() const {
				return this->startTime;
			}
			void setEndTime(float endTime) {
				this->endTime = endTime;
			}
			float getEndTime() const {
				return this->endTime;
			}

			const void setValues(UnitParticleSystem *uts);
			bool hasTexture() const {
				return(texture != NULL);
			}
			virtual void saveGame(XmlNode *rootNode);
			virtual void loadGame(const XmlNode *rootNode);
		};

		class ObjectParticleSystemType : public UnitParticleSystemType {
		public:
			ObjectParticleSystemType();
			virtual ~ObjectParticleSystemType();
		};

	}
}//end namespace

#endif
