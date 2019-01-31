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

#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#ifdef WIN32
#   include <winsock2.h>
#   include <winsock.h>
#endif

#include <string>
#include "vec.h"
#include "platform_common.h"
#include "xml_parser.h"
#include "leak_dumper.h"

using std::string;
using std::map;
using Shared::Xml::XmlNode;

namespace Game {
	using Shared::Graphics::Vec2i;
	using Shared::PlatformCommon::ValueCheckerVault;

	class ResourceType;
	class TechTree;
	// =====================================================
	//      class Resource  
	//
	/// Amount of a given ResourceType
	// =====================================================

	class Resource :public ValueCheckerVault {
	private:
		int amount;
		const ResourceType *type;
		Vec2i pos;
		int balance;

	public:
		Resource();
		void init(const ResourceType * rt, int amount);
		void init(const ResourceType * rt, const Vec2i & pos);

		const ResourceType *getType() const {
			return type;
		}
		Vec2i getPos() const {
			return pos;
		}

		int getAmount() const;
		int getBalance() const;
		string getDescription(bool translatedValue) const;

		void setAmount(int amount);
		void setBalance(int balance);

		bool decAmount(int i);

		void saveGame(XmlNode * rootNode) const;
		void loadGame(const XmlNode * rootNode, int index,
			const TechTree * techTree);

		std::string toString() const;
		Checksum getCRC();
	};

} //end namespace

#endif
