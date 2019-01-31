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

#ifndef _SHARED_GRAPHICS_BUFFER_H_
#define _SHARED_GRAPHICS_BUFFER_H_

#include <string>
#include "leak_dumper.h"

using std::string;

namespace Shared {
	namespace Graphics {

		// =====================================================
		//	class VertexBuffer
		// =====================================================

		class VertexBuffer {
		private:
			static const int texCoordCount = 8;
			static const int attribCount = 8;

		private:
			void *positionPointer;
			void *normalPointer;

			void *texCoordPointers[texCoordCount];
			int texCoordCoordCounts[texCoordCount];

			void *attribPointers[attribCount];
			int attribCoordCounts[attribCount];
			string attribNames[attribCount];

		public:
			VertexBuffer();
			virtual ~VertexBuffer() {
			};

			virtual void init(int size) = 0;

			void setPositionPointer(void *pointer);
			void setNormalPointer(void *pointer);
			void setTexCoordPointer(void *pointer, int texCoordIndex, int coordCount);
			void setAttribPointer(void *pointer, int attribIndex, int coordCount, const string &name);
		};

		// =====================================================
		//	class IndexBuffer
		// =====================================================

		class IndexBuffer {
		private:
			void *indexPointer;

		public:
			IndexBuffer();
			virtual ~IndexBuffer() {
			}

			virtual void init(int size) = 0;

			void setIndexPointer(void *pointer);
		};

	}
} //end namespace

#endif
