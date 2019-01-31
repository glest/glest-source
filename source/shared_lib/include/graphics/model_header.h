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

#ifndef _SHARED_GRAPHICTYPES_MODELHEADER_H_
#define _SHARED_GRAPHICTYPES_MODELHEADER_H_

#include "data_types.h"
#include "leak_dumper.h"

using Shared::Platform::uint8;
using Shared::Platform::uint16;
using Shared::Platform::uint32;
using Shared::Platform::float32;

namespace Shared {
	namespace Graphics {
#pragma pack(push, 1) 

		struct FileHeader {
			uint8 id[3];
			uint8 version;
		};

		//version 4

		struct ModelHeader {
			uint16 meshCount;
			uint8 type;
		};

		enum ModelType {
			mtMorphMesh
		};

		enum MeshPropertyFlag : uint32 {
			mpfNone = 0,
			mpfCustomColor = 1,
			mpfTwoSided = 2,
			mpfNoSelect = 4,
			mpfGlow = 8
		};
		inline MeshPropertyFlag operator~ (MeshPropertyFlag a) {
			return (MeshPropertyFlag) ~(uint32) a;
		}
		inline MeshPropertyFlag operator| (MeshPropertyFlag a, MeshPropertyFlag b) {
			return (MeshPropertyFlag) ((uint32) a | (uint32) b);
		}
		inline MeshPropertyFlag operator& (MeshPropertyFlag a, MeshPropertyFlag b) {
			return (MeshPropertyFlag) ((uint32) a & (uint32) b);
		}
		inline MeshPropertyFlag operator^ (MeshPropertyFlag a, MeshPropertyFlag b) {
			return (MeshPropertyFlag) ((uint32) a ^ (uint32) b);
		}
		inline MeshPropertyFlag& operator|= (MeshPropertyFlag& a, MeshPropertyFlag b) {
			return (MeshPropertyFlag&) ((uint32&) a |= (uint32) b);
		}
		inline MeshPropertyFlag& operator&= (MeshPropertyFlag& a, MeshPropertyFlag b) {
			return (MeshPropertyFlag&) ((uint32&) a &= (uint32) b);
		}
		inline MeshPropertyFlag& operator^= (MeshPropertyFlag& a, MeshPropertyFlag b) {
			return (MeshPropertyFlag&) ((uint32&) a ^= (uint32) b);
		}

		static const int MESH_TEXTURE_COUNT = 3;

		enum MeshTexture : uint32 {
			mtNone = 0,
			mtDiffuse = 1,
			mtSpecular = 2,
			mtNormal = 4
		};
		inline MeshTexture operator~ (MeshTexture a) {
			return (MeshTexture) ~(uint32) a;
		}
		inline MeshTexture operator| (MeshTexture a, MeshTexture b) {
			return (MeshTexture) ((uint32) a | (uint32) b);
		}
		inline MeshTexture operator& (MeshTexture a, MeshTexture b) {
			return (MeshTexture) ((uint32) a & (uint32) b);
		}
		inline MeshTexture operator^ (MeshTexture a, MeshTexture b) {
			return (MeshTexture) ((uint32) a ^ (uint32) b);
		}
		inline MeshTexture& operator|= (MeshTexture& a, MeshTexture b) {
			return (MeshTexture&) ((uint32&) a |= (uint32) b);
		}
		inline MeshTexture& operator&= (MeshTexture& a, MeshTexture b) {
			return (MeshTexture&) ((uint32&) a &= (uint32) b);
		}
		inline MeshTexture& operator^= (MeshTexture& a, MeshTexture b) {
			return (MeshTexture&) ((uint32&) a ^= (uint32) b);
		}

		const int meshTextureChannelCount[] = { 4, 1, 3 };

		const uint32 meshNameSize = 64;
		const uint32 mapPathSize = 64;

		struct MeshHeader {
			uint8 name[meshNameSize];
			uint32 frameCount;
			uint32 vertexCount;
			uint32 indexCount;
			float32 diffuseColor[3];
			float32 specularColor[3];
			float32 specularPower;
			float32 opacity;
			MeshPropertyFlag properties;
			MeshTexture textures;
		};

#pragma pack(pop) 

		//version 3

		//front faces are clockwise faces
		struct ModelHeaderV3 {
			uint32 meshCount;
		};

		enum MeshPropertyV3 : uint32 {
			mp3None = 0,
			mp3NoTexture = 1,
			mp3TwoSided = 2,
			mp3CustomColor = 4
		};
		inline MeshPropertyV3 operator~ (MeshPropertyV3 a) {
			return (MeshPropertyV3) ~(uint32) a;
		}
		inline MeshPropertyV3 operator| (MeshPropertyV3 a, MeshPropertyV3 b) {
			return (MeshPropertyV3) ((uint32) a | (uint32) b);
		}
		inline MeshPropertyV3 operator& (MeshPropertyV3 a, MeshPropertyV3 b) {
			return (MeshPropertyV3) ((uint32) a & (uint32) b);
		}
		inline MeshPropertyV3 operator^ (MeshPropertyV3 a, MeshPropertyV3 b) {
			return (MeshPropertyV3) ((uint32) a ^ (uint32) b);
		}
		inline MeshPropertyV3& operator|= (MeshPropertyV3& a, MeshPropertyV3 b) {
			return (MeshPropertyV3&) ((uint32&) a |= (uint32) b);
		}
		inline MeshPropertyV3& operator&= (MeshPropertyV3& a, MeshPropertyV3 b) {
			return (MeshPropertyV3&) ((uint32&) a &= (uint32) b);
		}
		inline MeshPropertyV3& operator^= (MeshPropertyV3& a, MeshPropertyV3 b) {
			return (MeshPropertyV3&) ((uint32&) a ^= (uint32) b);
		}

		struct MeshHeaderV3 {
			uint32 vertexFrameCount;
			uint32 normalFrameCount;
			uint32 texCoordFrameCount;
			uint32 colorFrameCount;
			uint32 pointCount;
			uint32 indexCount;
			MeshPropertyV3 properties;
			uint8 texName[64];
		};

		//version 2

		struct MeshHeaderV2 {
			uint32 vertexFrameCount;
			uint32 normalFrameCount;
			uint32 texCoordFrameCount;
			uint32 colorFrameCount;
			uint32 pointCount;
			uint32 indexCount;
			uint8 hasTexture;
			uint8 primitive;
			uint8 cullFace;
			uint8 texName[64];
		};

	}
} //end namespace

#endif
