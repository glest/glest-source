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

#include "shader.h"

#include <stdexcept>
#include <fstream>
#include "platform_util.h"
#include "leak_dumper.h"

using namespace std;

namespace Shared {
	namespace Graphics {

		// =====================================================
		//	class ShaderSource
		// =====================================================

		void ShaderSource::load(const string &path) {
			pathInfo += path + " ";

			//open file
			ifstream ifs(path.c_str());
			if (ifs.fail()) {
				throw game_runtime_error("Can't open shader file: " + path);
			}

			//read source
			while (true) {
				fstream::int_type c = ifs.get();
				if (ifs.eof() || ifs.fail() || ifs.bad()) {
					break;
				}
				code += c;
			}
		}

	}
}//end namespace
