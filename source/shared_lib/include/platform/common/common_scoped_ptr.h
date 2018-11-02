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

#ifndef _COMMON_SCOPED_PTR_H_
#define _COMMON_SCOPED_PTR_H_

#include <memory>

// =====================================================
//	Hack for compilers that dont support cxx11's unique_ptr which replaces auto_ptr
// =====================================================
//using namespace std;

// C++11
#if defined(HAVE_CXX11) || (__cplusplus >= 201103L) || (_MSC_VER >= 1900)

#if defined(WIN32)
#define auto_ptr unique_ptr
#else
#define auto_ptr std::unique_ptr
#endif

#endif

#endif
