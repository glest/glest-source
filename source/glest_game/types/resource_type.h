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

#ifndef _RESOURCETYPE_H_
#define _RESOURCETYPE_H_

#ifdef WIN32
#   include <winsock2.h>
#   include <winsock.h>
#endif

#include "element_type.h"
#include "model.h"
#include "checksum.h"
#include "leak_dumper.h"
#include "unit_particle_type.h"
#include "object_type.h"

namespace Game {
	using Shared::Graphics::Model;
	using Shared::Util::Checksum;

	enum ResourceClass {
		rcTech,
		rcTileset,
		rcStatic,
		rcConsumable
	};

	// =====================================================
	//      class ResourceType
	//
	///     A type of resource that can be harvested or not
	// =====================================================


	class ResourceType :public DisplayableType {
	private:
		ResourceClass resourceClass;
		int tilesetObject;        //used only if class==rcTileset
		int resourceNumber;       //used only if class==rcTech, resource number in the map
		int interval;             //used only if class==rcConsumable
		int defResPerPatch;       //used only if class==rcTileset || class==rcTech
		bool recoup_cost;
		bool displayInHud;

		Model *model;
		ObjectParticleSystemTypes particleTypes;
		bool cleanupMemory;

	public:
		ResourceType();
		~ResourceType();
		void load(const string & dir, Checksum * checksum,
			Checksum * techtreeChecksum, std::map < string,
			vector < pair < string, string > > >&loadedFileList,
			string techtreePath);

		virtual string getName(bool translatedValue = false) const;
		//get
		int getClass() const {
			return resourceClass;
		}
		int getTilesetObject() const {
			return tilesetObject;
		}
		int getResourceNumber() const {
			return resourceNumber;
		}
		int getInterval() const {
			return interval;
		}
		int getDefResPerPatch() const {
			return defResPerPatch;
		}
		Model *getModel() const {
			return model;
		}
		bool getRecoup_cost() const {
			return recoup_cost;
		}
		bool getDisplayInHud() const {
			return displayInHud;
		}

		bool hasParticles() const {
			return !particleTypes.empty();
		}
		const ObjectParticleSystemTypes *getObjectParticleSystemTypes() const {
			return &particleTypes;
		}

		void setCleanupMemory(bool value) {
			cleanupMemory = value;
		}

		static ResourceClass strToRc(const string & s);
		void deletePixels();

		void saveGame(XmlNode * rootNode);
	};

} //end namespace

#endif
