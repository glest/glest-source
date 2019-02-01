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

#include "selection.h"

#include <algorithm>

#include "unit_type.h"
#include "gui.h"
#include "config.h"
#include "world.h"
#include "leak_dumper.h"

using namespace std;

namespace Game {
	// =====================================================
	// 	class Selection
	// =====================================================

	void Selection::init(Gui *gui, int factionIndex, int teamIndex, bool allowSharedTeamUnits) {
		this->factionIndex = factionIndex;
		this->teamIndex = teamIndex;
		this->allowSharedTeamUnits = allowSharedTeamUnits;
		this->gui = gui;
		clear();
	}

	Selection::~Selection() {
		clear();
	}

	bool Selection::canSelectUnitFactionCheck(const Unit *unit) const {
		//check if enemy
		if (unit->getFactionIndex() != factionIndex) {
			if (this->allowSharedTeamUnits == false ||
				unit->getFaction()->getTeam() != teamIndex) {
				return false;
			}
		}

		return true;
	}

	bool Selection::isSelected(Unit* unit) const {
		if (unit == NULL)
			return false;
		//check if already selected
		for (int index = 0; index < (int) selectedUnits.size(); ++index) {
			if (selectedUnits[index] == unit) {
				return true;
			}
		}
	}

	bool Selection::select(Unit *unit, bool addToSelection, bool toggleSelection) {
		bool result = false;
		if (unit != NULL) {
			//check if already selected
			for (int index = 0; index < (int) selectedUnits.size(); ++index) {
				if (selectedUnits[index] == unit) {
					if (toggleSelection)
						unSelect(index);
					return true;
				}
			}

			//check if dead
			if (unit->isDead() == true) {
				return false;
			}

			//check if commandable
			if (unit->getType()->isCommandable() == false && isEmpty() == false) {
				return false;
			}

			//check if multisel
			if (unit->getType()->getMultiSelect() == false && isEmpty() == false) {
				return false;
			}

			//check if multitypesel
			if (selectedUnits.size() > 0) {
				bool isUnifromSelectOK = (selectedUnits.front()->getType() == unit->getType() && unit->isOperative() == selectedUnits.front()->isOperative());
				if (selectedUnits.front()->getType()->getUniformSelect() == true && !isUnifromSelectOK) {
					if (addToSelection)
						return false;
					else
						clear();
				}

				if (unit->getType()->getUniformSelect() == true
					&& !isUnifromSelectOK) {
					return false;
				}
			}

			//check if enemy
			if (canSelectUnitFactionCheck(unit) == false && isEmpty() == false) {
				return false;
			}

			//check existing enemy
			//if(selectedUnits.size() == 1 && selectedUnits.front()->getFactionIndex() != factionIndex) {
			if (selectedUnits.size() == 1 && canSelectUnitFactionCheck(selectedUnits.front()) == false) {
				clear();
			}

			//check existing multisel
			if (selectedUnits.size() == 1 &&
				selectedUnits.front()->getType()->getMultiSelect() == false) {
				clear();
			}

			if (SystemFlags::getSystemSettingType(SystemFlags::debugSystem).enabled) SystemFlags::OutputDebug(SystemFlags::debugSystem, "In [%s::%s Line: %d] unit selected [%s]\n", __FILE__, __FUNCTION__, __LINE__, unit->toString().c_str());

			unit->addObserver(this);

			int unitTypeId = unit->getType()->getId();
			bool inserted = false;
			for (int index = 0; index < (int) selectedUnits.size(); ++index) {

				int currentTypeId = selectedUnits[index]->getType()->getId();
				if (unitTypeId <= currentTypeId) {

					//place unit here
					selectedUnits.insert(selectedUnits.begin() + index, unit);
					inserted = true;
					break;
				}
			}
			if (inserted == false) {
				selectedUnits.push_back(unit);
			}
			result = true;
			gui->onSelectionChanged();
		}

		return result;
	}

	void Selection::select(const UnitContainer &units, bool addToSelection, bool toggleSelection) {

		//add units to gui
		for (UnitIterator it = units.begin(); it != units.end(); ++it) {
			select(*it, addToSelection, toggleSelection);
		}
	}

	void Selection::unSelect(const UnitContainer &units) {

		//add units to gui
		for (UnitIterator it = units.begin(); it != units.end(); ++it) {
			for (int i = 0; i < (int) selectedUnits.size(); ++i) {
				if (selectedUnits[i] == *it) {
					unSelect(i);
				}
			}
		}
	}

	void Selection::unSelect(int i) {
		selectedUnits.erase(selectedUnits.begin() + i);
		gui->onSelectionChanged();
	}

	void Selection::clear() {
		selectedUnits.clear();
	}

	bool Selection::isUniform() const {
		if (selectedUnits.empty() == true) {
			return true;
		}

		const UnitType *ut = selectedUnits.front()->getType();

		for (int i = 0; i < (int) selectedUnits.size(); ++i) {
			if (selectedUnits[i]->getType() != ut) {
				return false;
			}
		}
		return true;
	}

	bool Selection::isEnemy() const {
		return selectedUnits.size() == 1 &&
			//selectedUnits.front()->getFactionIndex() != factionIndex;
			canSelectUnitFactionCheck(selectedUnits.front()) == false;
	}

	bool Selection::isObserver() const {
		return selectedUnits.size() == 1 &&
			(teamIndex == (GameConstants::maxPlayers - 1 + fpt_Observer));
	}

	bool Selection::isCommandable() const {
		//printf("\n\n\n\n********* selection.isCommandable() ---> isEmpty() [%d] isEnemy() [%d] selectedUnits.size() [%d]\n\n",isEmpty(),isEnemy(),(int)selectedUnits.size());

		return
			isEmpty() == false &&
			isEnemy() == false &&
			(selectedUnits.size() == 1 && selectedUnits.front()->isAlive() == false) == false &&
			selectedUnits.front()->getType()->isCommandable();
	}

	bool Selection::isCancelable() const {
		return
			selectedUnits.size() > 1 ||
			(selectedUnits.size() == 1 && selectedUnits[0]->anyCommand(true));
	}

	bool Selection::isMeetable() const {
		return
			isUniform() &&
			isCommandable() &&
			selectedUnits.front()->getType()->getMeetingPoint();
	}

	Vec3f Selection::getRefPos() const {
		return getFrontUnit()->getCurrMidHeightVector();
	}

	bool Selection::hasUnit(const Unit* unit) const {
		return find(selectedUnits.begin(), selectedUnits.end(), unit) != selectedUnits.end();
	}

	bool Selection::assignGroup(int groupIndex, bool clearGroup, const UnitContainer *pUnits) {
		if (groupIndex < 0 || groupIndex >= maxGroups) {
			throw game_runtime_error("Invalid value for groupIndex = " + intToStr(groupIndex));
		}

		//clear group
		if (true == clearGroup) {
			groups[groupIndex].clear();
		}

		//assign new group
		const UnitContainer *addUnits = &selectedUnits;
		if (pUnits != NULL) {
			addUnits = pUnits;
		}

		for (unsigned int i = 0; i < addUnits->size(); ++i) {
			if (false == addUnitToGroup(groupIndex, (*addUnits)[i])) {
				// don't try to add more, group is maybe full
				return false;
			}
		}
		return true;
	}

	/**
		* returns false if unit cannot be added
		*/
	bool Selection::addUnitToGroup(int groupIndex, Unit *unit) {
		if (groupIndex < 0 || groupIndex >= maxGroups) {
			throw game_runtime_error("Invalid value for groupIndex = " + intToStr(groupIndex));
		}
		bool alreadyExists = false;
		for (int i = 0; i < (int) groups[groupIndex].size(); ++i) {
			if (groups[groupIndex][i] == unit) {
				alreadyExists = true;
				break;
			}
		}

		if (alreadyExists) {
			return true;
		}

		// check for non Multiselect units
		if ((int) groups[groupIndex].size() > 0) {
			if (!unit->getType()->getMultiSelect()) {
				//dont add single selection units to already filled group
				return false;
			}
			Unit* unitInGroup = groups[groupIndex][0];
			if (!unitInGroup->getType()->getMultiSelect()) {
				//dont add a unit to a group which has a single selection unit
				return false;
			}
		}

		// check for uniformselect units
		if ((int) groups[groupIndex].size() > 0) {
			Unit* unitInGroup = groups[groupIndex][0];
			if (unit->getType()->getUniformSelect() || unitInGroup->getType()->getUniformSelect()) {
				if (unit->isOperative() != unitInGroup->isOperative()) {
					//dont add units that are not in same operative state
					return false;
				}
				if (unitInGroup->getType() != unit->getType()) {
					//dont add another unit to a group of uniform selection units
					return false;
				}
			}
		}

		if (unit != NULL) {
			groups[groupIndex].push_back(unit);
			return true;
		} else {
			return false;
		}
	}

	void Selection::removeUnitFromGroup(int groupIndex, int unitId) {
		if (groupIndex < 0 || groupIndex >= maxGroups) {
			throw game_runtime_error("Invalid value for groupIndex = " + intToStr(groupIndex));
		}

		for (unsigned int i = 0; i < groups[groupIndex].size(); ++i) {
			Unit *unit = groups[groupIndex][i];
			if (unit != NULL && unit->getId() == unitId) {
				groups[groupIndex].erase(groups[groupIndex].begin() + i);
				break;
			}
		}
	}

	//vector<Unit*> Selection::getUnitsForGroup(int groupIndex) {
	//	if(groupIndex < 0 || groupIndex >= maxGroups) {
	//		throw game_runtime_error("Invalid value for groupIndex = " + intToStr(groupIndex));
	//	}
	//	return groups[groupIndex];
	//}

	void Selection::recallGroup(int groupIndex, bool clearSelection) {
		if (groupIndex < 0 || groupIndex >= maxGroups) {
			throw game_runtime_error("Invalid value for groupIndex = " + intToStr(groupIndex));
		}

		if (clearSelection == true) {
			clear();
		}
		for (int i = 0; i < (int) groups[groupIndex].size(); ++i) {
			select(groups[groupIndex][i], !clearSelection);
		}
	}

	void Selection::unitEvent(UnitObserver::Event event, const Unit *unit) {

		if (event == UnitObserver::eKill) {

			//remove from selection
			for (int index = 0; index < (int) selectedUnits.size(); ++index) {
				if (selectedUnits[index] == unit) {
					selectedUnits.erase(selectedUnits.begin() + index);
					break;
				}
			}

			//remove from groups
			for (int index = 0; index < maxGroups; ++index) {
				for (int index2 = 0; index2 < (int) groups[index].size(); ++index2) {
					if (groups[index][index2] == unit) {
						groups[index].erase(groups[index].begin() + index2);
						break;
					}
				}
			}

			//notify gui only if no more units to execute the command
			//of course the selection changed, but this doesn't matter in this case.
			if (selectedUnits.empty() == true) {
				gui->onSelectionChanged();
			}
		}
	}

	void Selection::saveGame(XmlNode *rootNode) const {

		std::map<string, string> mapTagReplacements;
		XmlNode *selectionNode = rootNode->addChild("Selection");

		selectionNode->addAttribute("factionIndex", intToStr(factionIndex), mapTagReplacements);
		selectionNode->addAttribute("teamIndex", intToStr(teamIndex), mapTagReplacements);
		selectionNode->addAttribute("allowSharedTeamUnits", intToStr(allowSharedTeamUnits), mapTagReplacements);

		for (unsigned int i = 0; i < selectedUnits.size(); i++) {
			Unit *unit = selectedUnits[i];

			XmlNode *selectedUnitsNode = selectionNode->addChild("selectedUnits");
			selectedUnitsNode->addAttribute("unitId", intToStr(unit->getId()), mapTagReplacements);
		}

		for (unsigned int x = 0; x < (unsigned int) maxGroups; ++x) {
			XmlNode *groupsNode = selectionNode->addChild("groups");
			for (unsigned int i = 0; i < (unsigned int) groups[x].size(); ++i) {
				Unit *unit = groups[x][i];

				XmlNode *selectedUnitsNode = groupsNode->addChild("selectedUnits");
				selectedUnitsNode->addAttribute("unitId", intToStr(unit->getId()), mapTagReplacements);
			}
		}
	}

	void Selection::loadGame(const XmlNode *rootNode, World *world) {

		const XmlNode *selectionNode = rootNode->getChild("Selection");

		factionIndex = selectionNode->getAttribute("factionIndex")->getIntValue();
		teamIndex = selectionNode->getAttribute("teamIndex")->getIntValue();
		if (selectionNode->hasAttribute("allowSharedTeamUnits") == true) {
			allowSharedTeamUnits = (selectionNode->getAttribute("allowSharedTeamUnits")->getIntValue() != 0);
		}

		vector<XmlNode *> selectedUnitsNodeList = selectionNode->getChildList("selectedUnits");
		for (unsigned int i = 0; i < selectedUnitsNodeList.size(); ++i) {
			XmlNode *selectedUnitsNode = selectedUnitsNodeList[i];

			int unitId = selectedUnitsNode->getAttribute("unitId")->getIntValue();
			Unit *unit = world->findUnitById(unitId);
			//assert(unit != NULL);
			//printf("#1 Unit [%s], group: %d\n",unit->getType()->getName().c_str(),i);
			selectedUnits.push_back(unit);
		}

		vector<XmlNode *> groupsNodeList = selectionNode->getChildList("groups");
		for (unsigned int i = 0; i < groupsNodeList.size(); ++i) {
			XmlNode *groupsNode = groupsNodeList[i];

			vector<XmlNode *> selectedGroupsUnitsNodeList = groupsNode->getChildList("selectedUnits");
			for (unsigned int j = 0; j < selectedGroupsUnitsNodeList.size(); ++j) {
				XmlNode *selectedGroupsUnitsNode = selectedGroupsUnitsNodeList[j];

				int unitId = selectedGroupsUnitsNode->getAttribute("unitId")->getIntValue();
				Unit *unit = world->findUnitById(unitId);
				//assert(unit != NULL);
				//printf("Unit #2 [%s], group: %d\n",unit->getType()->getName().c_str(),i);
				groups[i].push_back(unit);
			}
		}
	}

} //end namespace
