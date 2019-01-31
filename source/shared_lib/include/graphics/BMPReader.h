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

#ifndef BMPREADER_H
#define BMPREADER_H

// =====================================
//      class BMPReader
// =====================================

#include "FileReader.h"
#include "pixmap.h"
#include "leak_dumper.h"

namespace Shared {
	namespace Graphics {

		class BMPReader : FileReader<Pixmap2D> {
		public:
			BMPReader();

			Pixmap2D* read(ifstream& in, const string& path, Pixmap2D* ret) const;
		};


	}
} //end namespace

#endif
