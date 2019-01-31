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

#include "resource.h"

#include "conversion.h"
#include "resource_type.h"
#include "checksum.h"
#include <stdexcept>
#include "util.h"
#include "tech_tree.h"
#include "leak_dumper.h"

using namespace Shared::Graphics;
using namespace Shared::Util;

namespace Game {
	// =====================================================
	//      class Resource
	// =====================================================

	Resource::Resource() {
		this->type = NULL;
		this->amount = 0;
		pos = Vec2i(0);
		balance = 0;

		addItemToVault(&this->amount, this->amount);
		addItemToVault(&this->balance, this->balance);
	}

	void Resource::init(const ResourceType * rt, int amount) {
		this->type = rt;
		this->amount = amount;
		pos = Vec2i(0);
		balance = 0;

		addItemToVault(&this->amount, this->amount);
		addItemToVault(&this->balance, this->balance);
	}

	void Resource::init(const ResourceType * rt, const Vec2i & pos) {
		this->type = rt;
		amount = rt->getDefResPerPatch();
		this->pos = pos;

		addItemToVault(&this->amount, this->amount);
		addItemToVault(&this->balance, this->balance);
	}

	string Resource::getDescription(bool translatedValue) const {
		string str;

		str += type->getName(translatedValue);
		str += "\n";
		str += intToStr(amount);
		str += "/";
		str += intToStr(type->getDefResPerPatch());

		return str;
	}

	int Resource::getAmount() const {
		checkItemInVault(&this->amount, this->amount);
		return amount;
	}

	int Resource::getBalance() const {
		checkItemInVault(&this->balance, this->balance);
		return balance;
	}

	void Resource::setAmount(int amount) {
		checkItemInVault(&this->amount, this->amount);
		this->amount = amount;
		addItemToVault(&this->amount, this->amount);
	}

	void Resource::setBalance(int balance) {
		checkItemInVault(&this->balance, this->balance);
		this->balance = balance;
		addItemToVault(&this->balance, this->balance);
	}

	bool Resource::decAmount(int i) {
		checkItemInVault(&this->amount, this->amount);
		amount -= i;
		addItemToVault(&this->amount, this->amount);

		if (amount > 0) {
			return false;
		}
		return true;
	}

	void Resource::saveGame(XmlNode * rootNode) const {
		std::map < string, string > mapTagReplacements;
		XmlNode *resourceNode = rootNode->addChild("Resource");

		//    int amount;
		resourceNode->addAttribute("amount", intToStr(amount),
			mapTagReplacements);
		//    const ResourceType *type;
		resourceNode->addAttribute("type", type->getName(),
			mapTagReplacements);
		//      Vec2i pos;
		resourceNode->addAttribute("pos", pos.getString(),
			mapTagReplacements);
		//      int balance;
		resourceNode->addAttribute("balance", intToStr(balance),
			mapTagReplacements);
	}

	void Resource::loadGame(const XmlNode * rootNode, int index,
		const TechTree * techTree) {
		vector < XmlNode * >resourceNodeList =
			rootNode->getChildList("Resource");

		if (index < (int) resourceNodeList.size()) {
			XmlNode *resourceNode = resourceNodeList[index];

			amount = resourceNode->getAttribute("amount")->getIntValue();
			type =
				techTree->getResourceType(resourceNode->getAttribute("type")->
					getValue());
			pos =
				Vec2i::strToVec2(resourceNode->getAttribute("pos")->getValue());
			balance = resourceNode->getAttribute("balance")->getIntValue();
		}
	}

	std::string Resource::toString()const {
		std::string result =
			"resource name = " + this->getDescription(false) + "\n";
		result += "amount = " + intToStr(this->amount) + "\n";
		result += "type = " + this->type->getName(false) + "\n";
		result +=
			"type resources per patch = " +
			intToStr(type->getDefResPerPatch()) + "\n";
		result += "pos = " + this->pos.getString() + "\n";
		result += "balance = " + intToStr(this->balance) + "\n";

		return result;
	}

	Checksum Resource::getCRC() {
		Checksum crcForResource;

		crcForResource.addInt(amount);
		crcForResource.addString(type->getName(false));
		crcForResource.addInt(pos.x);
		crcForResource.addInt(pos.y);
		crcForResource.addInt(balance);

		return crcForResource;
	}

} //end namespace
