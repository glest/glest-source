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

#ifndef _INCL_STEAMSHIM_CHILD_H_
#define _INCL_STEAMSHIM_CHILD_H_

#ifdef __cplusplus
extern "C" {
#endif

	typedef enum STEAMSHIM_EventType {
		SHIMEVENT_BYE,
		SHIMEVENT_STATSRECEIVED,
		SHIMEVENT_STATSSTORED,
		SHIMEVENT_SETACHIEVEMENT,
		SHIMEVENT_GETACHIEVEMENT,
		SHIMEVENT_RESETSTATS,
		SHIMEVENT_SETSTATI,
		SHIMEVENT_GETSTATI,
		SHIMEVENT_SETSTATF,
		SHIMEVENT_GETSTATF,
		SHIMEVENT_GETPERSONANAME,
		SHIMEVENT_GETCURRENTGAMELANGUAGE,
	} STEAMSHIM_EventType;

	/* not all of these fields make sense in a given event. */
	typedef struct STEAMSHIM_Event {
		STEAMSHIM_EventType type;
		int okay;
		int ivalue;
		float fvalue;
		unsigned long long epochsecs;
		char name[256];
	} STEAMSHIM_Event;

	int STEAMSHIM_init(void);  /* non-zero on success, zero on failure. */
	void STEAMSHIM_deinit(void);
	int STEAMSHIM_alive(void);
	const STEAMSHIM_Event *STEAMSHIM_pump(void);
	void STEAMSHIM_requestStats(void);
	void STEAMSHIM_storeStats(void);
	void STEAMSHIM_setAchievement(const char *name, const int enable);
	void STEAMSHIM_getAchievement(const char *name);
	void STEAMSHIM_resetStats(const int bAlsoAchievements);
	void STEAMSHIM_setStatI(const char *name, const int _val);
	void STEAMSHIM_getStatI(const char *name);
	void STEAMSHIM_setStatF(const char *name, const float val);
	void STEAMSHIM_getStatF(const char *name);
	void STEAMSHIM_getPersonaName();
	void STEAMSHIM_getCurrentGameLanguage();

#ifdef __cplusplus
}
#endif

#endif  /* include-once blocker */

/* end of steamshim_child.h ... */
