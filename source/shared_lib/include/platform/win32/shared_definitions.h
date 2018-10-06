// ==============================================================
//	This file is part of Glest Shared Library (www.glest.org)
//
//	Copyright (C) 2001-2005 Martio Figueroa
//
//	You can redistribute this code and/or modify it under 
//	the terms of the GNU General Public License as published 
//	by the Free Software Foundation; either version 2 of the 
//	License, or (at your option) any later version
// ==============================================================

#ifndef _SHARED_PLATFORM_DEFINITIONS_H_
#define _SHARED_PLATFORM_DEFINITIONS_H_

#include <string>
#include "versions.h"
#include "leak_dumper.h"

namespace Shared {
	const std::string GameVersionString = GAME_VERSION;
	const std::string LastCompatibleVersionString = LAST_COMPATIBLE_VERSION;
	const std::string G3DViewerVersionString = G3D_VIEWER_VERSION;
	const std::string MapEditorVersionString = MAP_EDITOR_VERSION;
}//end namespace

#endif
