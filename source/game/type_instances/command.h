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

#ifndef _COMMAND_H_
#define _COMMAND_H_

#ifdef WIN32
#   include <winsock2.h>
#   include <winsock.h>
#endif

#include <cstdlib>
#include "unit.h"
#include "vec.h"
#include "game_constants.h"
#include "leak_dumper.h"

namespace Game {
	using Shared::Graphics::Vec2i;

	class CommandType;

	enum CommandStateType {
		cst_None,
		cst_linkedUnit,
		cst_EmergencyReturnResource
	};

	// =====================================================
	//      class Command
	//
	///     A unit command
	// =====================================================

	class Command {
	private:
		const CommandType *commandType;
		Vec2i originalPos;
		Vec2i pos;
		UnitReference unitRef;    //target unit, used to move and attack optionally
		CardinalDir facing;       // facing, for build command
		const UnitType *unitType; //used for build

		CommandStateType stateType;
		int stateValue;

		int unitCommandGroupId;

		Command();
	public:
		//constructor
		Command(const CommandType * ct, const Vec2i & pos = Vec2i(0));
		Command(const CommandType * ct, Unit * unit);
		Command(const CommandType * ct, const Vec2i & pos,
			const UnitType * unitType, CardinalDir facing);

		virtual ~Command() {
		}
		//get
		inline const CommandType *getCommandType() const {
			return commandType;
		}
		inline Vec2i getPos() const {
			return pos;
		}
		inline Vec2i getOriginalPos() const {
			return originalPos;
		}
		inline Unit *getUnit() const {
			return unitRef.getUnit();
		}
		inline const UnitType *getUnitType() const {
			return unitType;
		}
		inline CardinalDir getFacing() const {
			return facing;
		}

		//Priority: commands of higher priority will cancel commands of lower priority
		virtual int getPriority();

		//set 
		void setCommandType(const CommandType * commandType);
		void setPos(const Vec2i & pos);
		//void setOriginalPos(const Vec2i &pos);
		void setPosToOriginalPos();

		void setUnit(Unit * unit);

		inline void setStateType(CommandStateType value) {
			stateType = value;
		}
		inline CommandStateType getStateType() const {
			return stateType;
		}

		inline void setStateValue(int value) {
			stateValue = value;
		}
		inline int getStateValue() const {
			return stateValue;
		}

		inline void setUnitCommandGroupId(int value) {
			unitCommandGroupId = value;
		}
		inline int getUnitCommandGroupId() const {
			return unitCommandGroupId;
		}

		std::string toString(bool translatedValue) const;

		void saveGame(XmlNode * rootNode, Faction * faction);
		static Command *loadGame(const XmlNode * rootNode, const UnitType * ut,
			World * world);

		Checksum getCRC();
	};

} //end namespace

#endif
