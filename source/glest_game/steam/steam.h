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

#ifndef STEAM_H
#define STEAM_H

#include <string>
#include <map>
#include "game_constants.h"

namespace ZetaGlest {
	namespace Game {

		struct SteamPrivate;

		enum SteamStatName {
			stat_online_wins,
			stat_online_loses,
			stat_online_kills,
			stat_online_kills_enemy,
			stat_online_deaths,
			stat_online_units,
			stat_online_resources_harvested,
			stat_online_quit_before_end,
			stat_online_minutes_played
		};

		enum SteamStatType {
			stat_int,
			stat_float,
			stat_avg
		};

		template <>
		inline EnumParser<SteamStatName>::EnumParser() {
			enumMap["stat_online_wins"] = stat_online_wins;
			enumMap["stat_online_loses"] = stat_online_loses;
			enumMap["stat_online_kills"] = stat_online_kills;
			enumMap["stat_online_kills_enemy"] = stat_online_kills_enemy;
			enumMap["stat_online_deaths"] = stat_online_deaths;
			enumMap["stat_online_units"] = stat_online_units;
			enumMap["stat_online_resources_harvested"] = stat_online_resources_harvested;
			enumMap["stat_online_quit_before_end"] = stat_online_quit_before_end;
			enumMap["stat_online_minutes_played"] = stat_online_minutes_played;
		}

		enum SteamAchievementName {
			ACH_WIN_ONE_GAME,
			ACH_WIN_ONE_GAME_ONLINE
		};

		template <>
		inline EnumParser<SteamAchievementName>::EnumParser() {
			enumMap["ACH_WIN_ONE_GAME"] = ACH_WIN_ONE_GAME;
			enumMap["ACH_WIN_ONE_GAME_ONLINE"] = ACH_WIN_ONE_GAME_ONLINE;
		}

		class Steam {
		public:
			void unlock(const char *name);
			void lock(const char *name);
			bool isUnlocked(const char *name);

			static SteamStatType getSteamStatNameType(string value);

			const std::string &userName() const;
			const std::string &lang() const;

			void resetStats(const int bAlsoAchievements) const;
			void storeStats() const;
			int getStatAsInt(const char *name) const;
			double getStatAsDouble(const char *name) const;
			void setStatAsInt(const char *name, int value);
			void setStatAsDouble(const char *name, double value);

			void requestRefreshStats();
			static void setDebugEnabled(bool value);

			Steam();
			~Steam();

		private:
			//friend struct SharedStatePrivate;

			SteamPrivate * p;
			static std::map<std::string, SteamStatType> SteamStatNameTypes;

			static std::map<std::string, SteamStatType> create_map() {
				std::map<std::string, SteamStatType> steamStatNameTypes;
				steamStatNameTypes["stat_online_wins"] = stat_int;
				steamStatNameTypes["stat_online_loses"] = stat_int;
				steamStatNameTypes["stat_online_kills"] = stat_int;
				steamStatNameTypes["stat_online_kills_enemy"] = stat_int;
				steamStatNameTypes["stat_online_deaths"] = stat_int;
				steamStatNameTypes["stat_online_units"] = stat_int;
				steamStatNameTypes["stat_online_resources_harvested"] = stat_int;
				steamStatNameTypes["stat_online_quit_before_end"] = stat_int;
				steamStatNameTypes["stat_online_minutes_played"] = stat_float;
				return steamStatNameTypes;
			}
		};

	}
}//end namespace

#endif // STEAM_H
