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

#ifndef _SHARED_PLATFORM_FACTORYREPOSITORY_H_
#define _SHARED_PLATFORM_FACTORYREPOSITORY_H_

#include <string>
#include "graphics_factory.h"
#include "graphics_factory_gl.h"
#include "sound_factory.h"
#include "sound_factory_openal.h"
#include "sound_factory_none.h"
#include "leak_dumper.h"

using std::string;

using Shared::Graphics::GraphicsFactory;
using Shared::Graphics::Gl::GraphicsFactoryGl;
using Shared::Sound::SoundFactory;
using Shared::Sound::OpenAL::SoundFactoryOpenAL;
using Shared::Sound::SoundFactoryNone;

namespace Shared { namespace Platform {

// =====================================================
//	class FactoryRepository
// =====================================================

class FactoryRepository {
private:
	FactoryRepository(){};
	FactoryRepository(const FactoryRepository& );
	void operator=(const FactoryRepository& );

private:
	GraphicsFactoryGl graphicsFactoryGl;
	SoundFactoryOpenAL soundFactoryOpenAL;
	SoundFactoryNone soundFactoryNone;

public:
	static FactoryRepository &getInstance();

	GraphicsFactory *getGraphicsFactory(const string &name);
	SoundFactory *getSoundFactory(const string &name);
};

}} //end namespace

#endif
