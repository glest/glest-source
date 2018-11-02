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

#ifndef _GLEST_GAME_OBJECT_H_
#   define _GLEST_GAME_OBJECT_H_

#   ifdef WIN32
#      include <winsock2.h>
#      include <winsock.h>
#   endif

#   include "model.h"
#   include "vec.h"
#   include "leak_dumper.h"
#   include "particle.h"
#   include "object_type.h"
#   include "tileset_model_type.h"

namespace ZetaGlest {
	namespace Game {

		class ObjectType;
		class ResourceType;
		class Resource;
		class TechTree;

		using Shared::Graphics::Model;
		using Shared::Graphics::Vec2i;
		using Shared::Graphics::Vec3f;
		using Shared::Graphics::UnitParticleSystem;

		// =====================================================
		//      class Object
		//
		///     A map object: tree, stone...
		// =====================================================

		class Object;

		class ObjectStateInterface {
		public:
			virtual void removingObjectEvent(Object * object) = 0;
			virtual ~ObjectStateInterface() {
			}
		};

		class Object :public BaseColorPickEntity, public ParticleOwner {
		private:
			typedef vector < UnitParticleSystem * >UnitParticleSystems;

		private:
			ObjectType * objectType;
			vector < UnitParticleSystem * >unitParticleSystems;
			Resource *resource;
			Vec3f pos;
			float rotation;
			int variation;
			int lastRenderFrame;
			Vec2i mapPos;
			bool visible;
			bool animated;
			float animProgress;
			float highlight;

			static ObjectStateInterface *stateCallback;

		public:
			Object(ObjectType * objectType, const Vec3f & pos,
				const Vec2i & mapPos);
			virtual ~Object();

			virtual void end();      //to kill particles
			virtual void logParticleInfo(string info) {
			};
			void initParticles();
			void initParticlesFromTypes(const ModelParticleSystemTypes *
				particleTypes);
			static void setStateCallback(ObjectStateInterface * value) {
				stateCallback = value;
			}

			const ObjectType *getType() const {
				return objectType;
			}
			Resource *getResource() const {
				return resource;
			}
			Vec3f getPos() const {
				return pos;
			}
			bool isVisible() const {
				return visible;
			}
			const Vec3f & getConstPos() const {
				return pos;
			}
			float getRotation() const {
				return rotation;
			}
			const Model *getModel() const;
			Model *getModelPtr() const;
			bool getWalkable() const;
			bool isAnimated() const {
				return animated;
			}

			float getHightlight() const {
				return highlight;
			}
			bool isHighlighted() const {
				return highlight > 0.f;
			}
			void resetHighlight();

			void setResource(const ResourceType * resourceType, const Vec2i & pos);
			void setHeight(float height);
			void setVisible(bool visible);

			int getLastRenderFrame() const {
				return lastRenderFrame;
			}
			void setLastRenderFrame(int value) {
				lastRenderFrame = value;
			}

			const Vec2i & getMapPos() const {
				return mapPos;
			}

			void updateHighlight();
			void update();
			float getAnimProgress() const {
				return animProgress;
			}

			virtual string getUniquePickName() const;
			void saveGame(XmlNode * rootNode);
			void loadGame(const XmlNode * rootNode, const TechTree * techTree);

			virtual void end(ParticleSystem * particleSystem);
		};

	}
}                              //end namespace

#endif
