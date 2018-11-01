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

#ifndef _SHARED_GRAPHICS_SHADER_H_
#define _SHARED_GRAPHICS_SHADER_H_

#include "vec.h"
#include "matrix.h"
#include "texture.h"
#include "leak_dumper.h"

namespace Shared {
	namespace Graphics {

		// =====================================================
		//	class ShaderProgram
		// =====================================================

		class VertexShader;
		class FragmentShader;

		class ShaderProgram {
		public:
			virtual ~ShaderProgram() {
			}
			virtual void init() = 0;
			virtual void end() = 0;

			virtual void attach(VertexShader *vs, FragmentShader *fs) = 0;
			virtual bool link(string &messages) = 0;
			virtual void activate() = 0;
			virtual void deactivate() = 0;

			virtual void setUniform(const string &name, int value) = 0;
			virtual void setUniform(const string &name, float value) = 0;
			virtual void setUniform(const string &name, const Vec2f &value) = 0;
			virtual void setUniform(const string &name, const Vec3f &value) = 0;
			virtual void setUniform(const string &name, const Vec4f &value) = 0;
			virtual void setUniform(const string &name, const Matrix3f &value) = 0;
			virtual void setUniform(const string &name, const Matrix4f &value) = 0;
		};

		// =====================================================
		//	class Shader
		// =====================================================

		class Shader {
		public:
			virtual ~Shader() {
			}
			virtual void init() = 0;
			virtual void end() = 0;

			virtual void load(const string &path) = 0;
			virtual bool compile(string &messages) = 0;
		};

		class VertexShader : virtual public Shader {
		};

		class FragmentShader : virtual public Shader {
		};

		// =====================================================
		//	class ShaderSource
		// =====================================================

		class ShaderSource {
		private:
			string pathInfo;
			string code;

		public:
			const string &getPathInfo() const {
				return pathInfo;
			}
			const string &getCode() const {
				return code;
			}

			void load(const string &path);
		};

	}
}//end namespace

#endif
