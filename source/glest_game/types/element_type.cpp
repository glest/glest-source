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

#include "element_type.h"

#include <cassert>

#include "resource_type.h"
#include "upgrade_type.h"
#include "unit_type.h"
#include "resource.h"
#include "tech_tree.h"
#include "logger.h"
#include "lang.h"
#include "renderer.h"
#include "leak_dumper.h"

using namespace Shared::Util;

namespace Glest {
	namespace Game {

		// =====================================================
		//      class DisplayableType
		// =====================================================

		DisplayableType::DisplayableType() {
			image = NULL;
		}

		string DisplayableType::getName(bool translatedValue) const {
			if (translatedValue == false)
				return name;

			Lang & lang = Lang::getInstance();
			return lang.getTechTreeString("CommandName_" + name, name.c_str());
		}

		//void DisplayableType::saveGame(XmlNode *rootNode) const {
		//      std::map<string,string> mapTagReplacements;
		//      XmlNode *displayableTypeNode = rootNode->addChild("DisplayableType");
		//
		//      displayableTypeNode->addAttribute("name",name, mapTagReplacements);
		//}

		// =====================================================
		//      class RequirableType
		// =====================================================

		string RequirableType::getReqDesc(bool translatedValue) const {
			return getReqDesc(false, translatedValue);
		}

		const Resource *RequirableType::getCost(const ResourceType * rt) const {
			for (int i = 0; i < (int) costs.size(); ++i) {
				if (costs[i].getType() == rt) {
					return &costs[i];
				}
			}
			return NULL;
		}


		string RequirableType::getResourceReqDesc(bool lineBreaks,
			bool translatedValue) const {
			string str = "";
			for (int i = 0; i < getCostCount(); ++i) {
				if (getCost(i)->getAmount() != 0) {
					str += getCost(i)->getType()->getName(translatedValue);
					str += ": " + intToStr(getCost(i)->getAmount());
					if (lineBreaks == true) {
						str += "\n";
					} else {
						str += " ";
					}
				}
			}

			return str;
		}

		string RequirableType::getUnitAndUpgradeReqDesc(bool lineBreaks,
			bool translatedValue)
			const {
			string str = "";
			for (int i = 0; i < getUnitReqCount(); ++i) {
				str += getUnitReq(i)->getName(translatedValue);
				if (lineBreaks == true) {
					str += "\n";
				} else {
					str += " ";
				}
			}

			for (int i = 0; i < getUpgradeReqCount(); ++i) {
				str += getUpgradeReq(i)->getName(translatedValue);
				if (lineBreaks == true) {
					str += "\n";
				} else {
					str += " ";
				}
			}

			return str;
		}

		string RequirableType::getReqDesc(bool ignoreResourceRequirements, bool translatedValue) const {
			string str =
				getName(translatedValue) + " " +
				Lang::getInstance().getString("Reqs",
				(translatedValue ==
					true ? "" : "english")) + ":\n";
			if (ignoreResourceRequirements == false) {
				str += getResourceReqDesc(true, translatedValue);
			}

			str += getUnitAndUpgradeReqDesc(true, translatedValue);
			return str;
		}

		//void RequirableType::saveGame(XmlNode *rootNode) const {
		//      DisplayableType::saveGame(rootNode);
		//
		//      std::map<string,string> mapTagReplacements;
		//      XmlNode *requirableTypeNode = rootNode->addChild("RequirableType");
		//
		////    UnitReqs unitReqs;                      //needed units
		//      for(unsigned int i = 0; i < unitReqs.size(); ++i) {
		//              const UnitType *ut = unitReqs[i];
		//
		//              XmlNode *unitReqsNode = requirableTypeNode->addChild("unitReqs");
		//              unitReqsNode->addAttribute("name",ut->getName(), mapTagReplacements);
		//      }
		////    UpgradeReqs upgradeReqs;        //needed upgrades
		//      for(unsigned int i = 0; i < upgradeReqs.size(); ++i) {
		//              const UpgradeType* ut = upgradeReqs[i];
		//
		//              ut->saveGame(requirableTypeNode);
		//      }
		//
		//}

		// =====================================================
		//      class ProducibleType
		// =====================================================

		ProducibleType::ProducibleType() {
			cancelImage = NULL;
			productionTime = 0;
		}

		ProducibleType::~ProducibleType() {
		}

		//void ProducibleType::saveGame(XmlNode *rootNode) const {
		//      RequirableType::saveGame(rootNode);
		//
		//      std::map<string,string> mapTagReplacements;
		//      XmlNode *producibleTypeNode = rootNode->addChild("ProducibleType");
		//
		////    Costs costs;
		//      for(unsigned int i = 0; i < costs.size(); ++i) {
		//              const Resource &res = costs[i];
		//              res.saveGame(producibleTypeNode);
		//      }
		////    Texture2D *cancelImage;
		////    int productionTime;
		//      producibleTypeNode->addAttribute("productionTime",intToStr(productionTime), mapTagReplacements);
		//}

		//void ProducibleType::loadGame(const XmlNode *rootNode) {
		//      const XmlNode *producibleTypeNode = rootNode->getChild("ProducibleType");
		//
		//      //int newUnitId = producibleTypeNode->getAttribute("id")->getIntValue();
		//}

	}
}                               //end namespace
