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

#ifndef _SHARED_CONST_H_
#define _SHARED_CONST_H_

#include <string>
#include "../../versions.h"
#include "leak_dumper.h"

namespace Shared {
	const std::string GameVersionString = GAME_VERSION;
	const std::string GameBuildDateString = GAME_BUILD_DATE;
	const std::string G3DViewerVersionString = G3D_VIEWER_VERSION;
	const std::string MapEditorVersionString = MAP_EDITOR_VERSION;
} //end namespace

#endif
