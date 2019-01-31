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

#include "buffer.h"

#include "leak_dumper.h"

namespace Shared {
	namespace Graphics {

		// =====================================================
		//	class VertexBuffer
		// =====================================================

		VertexBuffer::VertexBuffer() {
			positionPointer = NULL;
			normalPointer = NULL;
			for (int i = 0; i < texCoordCount; ++i) {
				texCoordPointers[i] = NULL;
				texCoordCoordCounts[i] = -1;
			}
			for (int i = 0; i < attribCount; ++i) {
				attribPointers[i] = NULL;
				attribCoordCounts[i] = -1;
			}
		}

		void VertexBuffer::setPositionPointer(void *pointer) {
			positionPointer = pointer;
		}

		void VertexBuffer::setNormalPointer(void *pointer) {
			normalPointer = pointer;
		}

		void VertexBuffer::setTexCoordPointer(void *pointer, int texCoordIndex, int coordCount) {
			texCoordPointers[texCoordIndex] = pointer;
			texCoordCoordCounts[texCoordIndex] = coordCount;
		}

		void VertexBuffer::setAttribPointer(void *pointer, int attribIndex, int coordCount, const string &name) {
			attribPointers[attribIndex] = pointer;
			attribCoordCounts[attribIndex] = coordCount;
			attribNames[attribIndex] = name;
		}

		// =====================================================
		//	class IndexBuffer
		// =====================================================

		IndexBuffer::IndexBuffer() {
			indexPointer = NULL;
		}

		void IndexBuffer::setIndexPointer(void *pointer) {
			indexPointer = pointer;
		}

	}
} //end namespace
