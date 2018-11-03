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

#ifndef _SHARED_GRAPHICS_GL_SHADERGL_H_
#define _SHARED_GRAPHICS_GL_SHADERGL_H_

#include <map>
#include <vector>
#include "shader.h"
#include "opengl.h"
#include "leak_dumper.h"

using std::vector;
using std::string;
using std::pair;

namespace Shared {
	namespace Graphics {
		namespace Gl {

			// =====================================================
			//	class ShaderProgramGl
			// =====================================================

			class ShaderProgramGl : public ShaderProgram {
			private:
				typedef pair<string, int> AttributePair;
				typedef vector<AttributePair> Attributes;

			private:
				Attributes attributes;
				GLhandleARB handle;
				VertexShader *vertexShader;
				FragmentShader *fragmentShader;
				bool inited;

			public:
				ShaderProgramGl();

				GLhandleARB getHandle() const {
					return handle;
				}

				virtual void init();
				virtual void end();

				virtual void attach(VertexShader *vertexShader, FragmentShader *fragmentShader);
				virtual bool link(string &messages);
				virtual void activate();
				virtual void deactivate();

				virtual void setUniform(const string &name, int value);
				virtual void setUniform(const string &name, float value);
				virtual void setUniform(const string &name, const Vec2f &value);
				virtual void setUniform(const string &name, const Vec3f &value);
				virtual void setUniform(const string &name, const Vec4f &value);
				virtual void setUniform(const string &name, const Matrix3f &value);
				virtual void setUniform(const string &name, const Matrix4f &value);

				void bindAttribute(const string &name, int index);

			private:
				GLint getLocation(const string &name);
			};

			// =====================================================
			//	class ShaderGl
			// =====================================================

			class ShaderGl : virtual public Shader {
			protected:
				GLhandleARB handle;
				ShaderSource source;
				bool inited;

			public:
				ShaderGl();

				const ShaderSource *getSource() const {
					return &source;
				}
				GLhandleARB getHandle() const {
					return handle;
				}

				virtual void load(const string &path);
				virtual bool compile(string &messages);
				virtual void end();
			};

			// =====================================================
			//	class VertexShaderGl
			// =====================================================

			class VertexShaderGl : public VertexShader, public ShaderGl {
			public:
				virtual void init();
			};

			// =====================================================
			//	class FragmentShaderGl
			// =====================================================

			class FragmentShaderGl : public FragmentShader, public ShaderGl {
			public:
				virtual void init();
			};

		}
	}
} //end namespace

#endif
