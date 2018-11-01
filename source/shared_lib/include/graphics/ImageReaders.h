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

#ifndef IMAGE_READERS_H
#define IMAGE_READERS_H

#include "FileReader.h"
#include "BMPReader.h"
#include "JPGReader.h"
#include "PNGReader.h"
#include "TGAReader.h"
#include "leak_dumper.h"

//Initialize some objects
namespace Shared {
	namespace Graphics {

		// =====================================================
		//	namespace ImageRegisterer
		// =====================================================

		namespace ImageRegisterer {

			//This function registers all image-readers, but only once (any further call is unnecessary)
			bool registerImageReaders();

			//Since you can't call void methods here, I have used a method doing nothing except initializing the image Readers
#ifdef WIN32
			static bool readersRegistered = registerImageReaders(); //should always return true, this should guarantee that the readers are registered <--> ImageReaders is included anywhere
#else
			static bool readersRegistered __attribute__((unused)) = registerImageReaders(); //should always return true, this should guarantee that the readers are registered <--> ImageReaders is included anywhere
#endif
		}

	}
} //end namespace

#endif
