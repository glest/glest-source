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

#ifndef _COMMANDER_H_
#define _COMMANDER_H_

#ifdef WIN32
#   include <winsock2.h>
#   include <winsock.h>
#endif

#include <vector>
#include "vec.h"
#include "selection.h"
#include "command_type.h"
#include "platform_util.h"
#include "base_thread.h"
#include "leak_dumper.h"

using std::vector;

namespace Game {
	using Shared::Graphics::Vec2i;
	using Shared::PlatformCommon::Chrono;

	class
		World;
	class
		Unit;
	class
		Command;
	class
		CommandType;
	class
		NetworkCommand;
	class
		Game;
	class
		SwitchTeamVote;

	// =====================================================
	//      class Commander
	//
	///     Gives commands to the units
	// =====================================================
	class
		Commander {
	private:
		typedef
			vector <
			std::pair <
			CommandResult,
			string > >
			CommandResultContainer;

	private:
		World *
			world;
		Chrono
			perfTimer;

		std::vector <
			std::pair < int,
			NetworkCommand > >
			replayCommandList;

		bool
			pauseNetworkCommands;

	public:
		Commander();
		virtual ~
			Commander();

		bool
			getPauseNetworkCommands() const {
			return
				this->
				pauseNetworkCommands;
		}
		void
			setPauseNetworkCommands(bool pause) {
			this->pauseNetworkCommands = pause;
		}

		void
			signalNetworkUpdate(Game * game);
		void
			init(World * world);
		void
			updateNetwork(Game * game);

		void
			addToReplayCommandList(NetworkCommand & command, int worldFrameCount);
		bool
			getReplayCommandListForFrame(int worldFrameCount);
		bool
			hasReplayCommandListForFrame() const;
		int
			getReplayCommandListForFrameCount() const;

		std::pair <
			CommandResult,
			string >
			tryGiveCommand(const Selection * selection,
				const CommandType * commandType, const Vec2i & pos,
				const UnitType * unitType, CardinalDir facing,
				bool tryQueue, Unit * targetUnit = NULL) const;

		std::pair <
			CommandResult,
			string >
			tryGiveCommand(const Unit * unit, const CommandType * commandType,
				const Vec2i & pos, const UnitType * unitType,
				CardinalDir facing, bool tryQueue =
				false, Unit * targetUnit =
				NULL, int unitGroupCommandId = -1) const;
		std::pair <
			CommandResult,
			string >
			tryGiveCommand(const Selection * selection, CommandClass commandClass,
				const Vec2i & pos = Vec2i(0), const Unit * targetUnit =
				NULL, bool tryQueue = false) const;
		std::pair <
			CommandResult,
			string >
			tryGiveCommand(const Selection * selection,
				const CommandType * commandType, const Vec2i & pos =
				Vec2i(0), const Unit * targetUnit =
				NULL, bool tryQueue = false) const;
		std::pair <
			CommandResult,
			string >
			tryGiveCommand(const Selection * selection, const Vec2i & pos,
				const Unit * targetUnit = NULL, bool tryQueue =
				false, int unitCommandGroupId = -1, bool isMove = false) const;
		CommandResult
			tryCancelCommand(const Selection * selection) const;
		void
			trySetMeetingPoint(const Unit * unit, const Vec2i & pos) const;
		void
			trySwitchTeam(const Faction * faction, int teamIndex) const;
		void
			trySwitchTeamVote(const Faction * faction,
				SwitchTeamVote * vote) const;
		void
			tryDisconnectNetworkPlayer(const Faction * faction,
				int playerIndex) const;

		void
			tryPauseGame(bool joinNetworkGame, bool clearCaches) const;
		void
			tryResumeGame(bool joinNetworkGame, bool clearCaches) const;

		void
			tryNetworkPlayerDisconnected(int factionIndex) const;

		Command *
			buildCommand(const NetworkCommand& networkCommand) const;

	private:
		std::pair <
			CommandResult,
			string >
			pushNetworkCommand(const NetworkCommand& networkCommand, bool insertAtStart = false) const;
		std::pair <
			CommandResult,
			string >
			computeResult(const CommandResultContainer & results) const;
		std::pair<CommandResult, string>
			giveNetworkCommand(NetworkCommand& networkCommand) const;
		bool
			canSubmitCommandType(const Unit * unit,
				const CommandType * commandType) const;
	};

} //end namespace

#endif
