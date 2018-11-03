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

#include "model_renderer_gl.h"

#include "opengl.h"
#include "gl_wrap.h"
#include "texture_gl.h"
#include "interpolation.h"
#include "leak_dumper.h"

#ifndef FLT_EPSILON
#define FLT_EPSILON 1.192092896e-07F
#endif

using namespace Shared::Platform;

namespace Shared {
	namespace Graphics {
		namespace Gl {
			bool MeshCallback::noTeamColors = false;

			void MeshCallback::execute(const Mesh *mesh, float alpha) {
				alpha *= mesh->getOpacity();
				uint8 factionOpacity = mesh->getFactionColorOpacity(); //team color
				float color[4];
				color[0] = 1.0f; // Red
				color[1] = 1.0f; // Green
				color[2] = 1.0f; // Blue
				if (!mesh->getCustomTexture() || factionOpacity == 0 || teamTexture == NULL || MeshCallback::noTeamColors) {
					glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
					glActiveTexture(GL_TEXTURE1);
					if (alpha < 1.f - FLT_EPSILON) {
						glEnable(GL_TEXTURE_2D);
						glMultiTexCoord2f(GL_TEXTURE1, 0.f, 0.f);
						glBindTexture(GL_TEXTURE_2D, teamTexture == NULL ? 0 : static_cast<const Texture2DGl*>(teamTexture)->getHandle());
						color[3] = alpha;
						glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, color);

						glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
						glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_REPLACE);
						glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_PREVIOUS);
						glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);

						glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_ALPHA, GL_MODULATE);
						glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA, GL_PREVIOUS);
						glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_ALPHA, GL_SRC_ALPHA);
						glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_ALPHA, GL_CONSTANT);
						glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_ALPHA, GL_SRC_ALPHA);
					} else
						glDisable(GL_TEXTURE_2D);
					glActiveTexture(GL_TEXTURE2);
					glDisable(GL_TEXTURE_2D);
					glActiveTexture(GL_TEXTURE0);
				} else {
					//texture 0
					glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);

					//set color to interpolation
					glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_INTERPOLATE);
					glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_TEXTURE);
					glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);
					glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB, GL_TEXTURE1);
					glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB, GL_SRC_COLOR);
					glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE2_RGB, GL_TEXTURE);
					glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND2_RGB, GL_SRC_ALPHA);

					glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_ALPHA, GL_REPLACE);
					glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA, GL_TEXTURE);
					glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_ALPHA, GL_SRC_ALPHA);

					//texture 1
					glActiveTexture(GL_TEXTURE1);
					glEnable(GL_TEXTURE_2D);
					glMultiTexCoord2f(GL_TEXTURE1, 0.f, 0.f);
					GLuint handle = static_cast<const Texture2DGl*>(teamTexture)->getHandle();
					glBindTexture(GL_TEXTURE_2D, handle);
					color[3] = factionOpacity * 0.00392156862f; // Alpha
					glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, color);

					glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);

					glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);

					glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_PRIMARY_COLOR);
					glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);

					glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB, GL_PREVIOUS);
					glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB, GL_SRC_COLOR);

					glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_ALPHA, GL_INTERPOLATE);
					glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA, GL_TEXTURE);
					glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_ALPHA, GL_SRC_ALPHA);
					glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_ALPHA, GL_PREVIOUS);
					glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_ALPHA, GL_SRC_ALPHA);
					glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE2_ALPHA, GL_CONSTANT);
					glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND2_ALPHA, GL_SRC_ALPHA);
					
					glActiveTexture(GL_TEXTURE2);
					if (alpha < 1.f - FLT_EPSILON) {
						glEnable(GL_TEXTURE_2D);
						glMultiTexCoord2f(GL_TEXTURE1, 0.f, 0.f);
						glBindTexture(GL_TEXTURE_2D, handle);
						color[3] = alpha;
						glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, color);

						glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
						glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_REPLACE);
						glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_PREVIOUS);
						glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);

						glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_ALPHA, GL_MODULATE);
						glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA, GL_PREVIOUS);
						glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_ALPHA, GL_SRC_ALPHA);
						glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_ALPHA, GL_CONSTANT);
						glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_ALPHA, GL_SRC_ALPHA);
					} else
						glDisable(GL_TEXTURE_2D);

					glActiveTexture(GL_TEXTURE0);
				}
			}

			// =====================================================
			//	class MyClass
			// =====================================================

			// ===================== PUBLIC ========================

			ModelRendererGl::ModelRendererGl() {
				rendering = false;
				duplicateTexCoords = false;
				secondaryTexCoordUnit = 1;
				lastTexture = 0;
			}

			void ModelRendererGl::begin(bool renderNormals, bool renderTextures, bool renderColors,
				bool colorPickingMode, MeshCallback *meshCallback) {
				//assertions
				assert(rendering == false);
				assertGl();

				this->renderTextures = renderTextures;
				this->renderNormals = renderNormals;
				this->renderColors = renderColors;
				this->colorPickingMode = colorPickingMode;
				this->meshCallback = meshCallback;

				rendering = true;
				lastTexture = 0;
				glBindTexture(GL_TEXTURE_2D, 0);

				//push attribs
				glPushAttrib(GL_ENABLE_BIT | GL_LIGHTING_BIT | GL_POLYGON_BIT | GL_CURRENT_BIT | GL_TEXTURE_BIT);
				glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);

				//init opengl
				if (this->colorPickingMode == false) {
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				}
				glBindTexture(GL_TEXTURE_2D, 0);
				glFrontFace(GL_CCW);

				if (this->colorPickingMode == false) {
					glEnable(GL_NORMALIZE);
					glEnable(GL_BLEND);

					glEnable(GL_POLYGON_OFFSET_FILL);
					glPolygonOffset(0.005f, 0.0f);
				}

				glEnableClientState(GL_VERTEX_ARRAY);

				if (renderNormals) {
					glEnableClientState(GL_NORMAL_ARRAY);
				}

				if (renderTextures) {
					glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				}

				/*
					glHint( GL_LINE_SMOOTH_HINT, GL_FASTEST );
					glHint( GL_FRAGMENT_SHADER_DERIVATIVE_HINT, GL_FASTEST );
					glHint( GL_GENERATE_MIPMAP_HINT, GL_FASTEST );
					glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST );
					glHint( GL_POINT_SMOOTH_HINT, GL_FASTEST );
					glHint( GL_POLYGON_SMOOTH_HINT, GL_FASTEST );
					glHint( GL_TEXTURE_COMPRESSION_HINT, GL_FASTEST );
				*/

				if (this->colorPickingMode == true) {
					BaseColorPickEntity::beginPicking();
				}

				//assertions
				assertGl();
			}

			void ModelRendererGl::end() {
				//assertions
				assert(rendering);
				assertGl();

				//set render state
				rendering = false;

				if (this->colorPickingMode == false) {
					glPolygonOffset(0.0f, 0.0f);
					glDisable(GL_POLYGON_OFFSET_FILL);
				}

				//pop
				glPopAttrib();
				glPopClientAttrib();

				if (colorPickingMode == true) {
					BaseColorPickEntity::endPicking();
				}

				//assertions
				assertGl();
			}

			void ModelRendererGl::render(Model *model, int renderMode, float alpha) {
				//assertions
				assert(rendering);
				assertGl();

				//if(model->getIsStaticModel()) printf("In [%s::%s Line: %d] filename [%s] is static about to render...\n",__FILE__,__FUNCTION__,__LINE__,model->getFileName().c_str());

				//render every mesh
				//if(model->getIsStaticModel() == true) {
				for (uint32 i = 0; i < model->getMeshCount(); ++i) {
					renderMesh(model->getMeshPtr(i), renderMode, alpha);
				}
				//}
				//assertions
				assertGl();
			}

			void ModelRendererGl::renderNormalsOnly(Model *model) {
				//assertions
				assert(rendering);
				assertGl();

				//render every mesh
				//if(model->getIsStaticModel() == true) {
				for (uint32 i = 0; i < model->getMeshCount(); ++i) {
					renderMeshNormals(model->getMeshPtr(i));
				}
				//}

				//assertions
				assertGl();
			}

			// ===================== PRIVATE =======================

			void ModelRendererGl::renderMesh(Mesh *mesh, int renderMode, float alpha) {

				if (renderMode == rmSelection && mesh->getNoSelect() == true) {// don't render this and do nothing
					return;
				}
				//assertions
				assertGl();

				//glPolygonOffset(0.05f, 0.0f);
				//set cull face
				if (mesh->getTwoSided()) {
					glDisable(GL_CULL_FACE);
				} else {
					glEnable(GL_CULL_FACE);
				}
				glEnable(GL_BLEND);
				
				//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Vec4f(1.0f, 1.0f, 1.0f, alpha).ptr());
				if (renderMode == rmNormal && mesh->getGlow() == true) {
					// glow on
					glBlendFunc(GL_ONE, GL_ONE);
				} else
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				if (this->colorPickingMode == false) {
					//set color
					if (renderColors) {
						Vec4f color(mesh->getDiffuseColor(), 1.f);
						glColor4fv(color.ptr());
					}
					
					//texture state
					const Texture2DGl *texture = static_cast<const Texture2DGl*>(mesh->getTexture(0));
					if (texture != NULL && renderTextures) {
						if (lastTexture != texture->getHandle()) {
							//assert(glIsTexture(texture->getHandle()));
							//throw game_runtime_error("glIsTexture(texture->getHandle()) == false for texture: " + texture->getPath());
							if (glIsTexture(texture->getHandle()) == GL_TRUE) {
								glBindTexture(GL_TEXTURE_2D, texture->getHandle());
								lastTexture = texture->getHandle();
							} else {
								glBindTexture(GL_TEXTURE_2D, 0);
								lastTexture = 0;
							}
						}
					} else {
						glBindTexture(GL_TEXTURE_2D, 0);
						lastTexture = 0;
					}

					if (meshCallback != NULL) {
						meshCallback->execute(mesh, alpha);
					}
				}

				//misc vars
				uint32 vertexCount = mesh->getVertexCount();
				uint32 indexCount = mesh->getIndexCount();

				//assertions
				assertGl();

				if (getVBOSupported() == true && mesh->getFrameCount() == 1) {
					if (mesh->hasBuiltVBOEntities() == false) {
						mesh->BuildVBOs();
					}
					//printf("Rendering Mesh with VBO's\n");

					//vertices
					glBindBufferARB(GL_ARRAY_BUFFER_ARB, mesh->getVBOVertices());
					glVertexPointer(3, GL_FLOAT, 0, (char *) NULL);		// Set The Vertex Pointer To The Vertex Buffer
					//glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );

					//normals
					if (renderNormals) {
						glBindBufferARB(GL_ARRAY_BUFFER_ARB, mesh->getVBONormals());
						glEnableClientState(GL_NORMAL_ARRAY);
						glNormalPointer(GL_FLOAT, 0, (char *) NULL);
						//glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
					} else {
						glDisableClientState(GL_NORMAL_ARRAY);
					}

					assertGl();

					//tex coords
					if (renderTextures && mesh->getTexture(0) != NULL) {
						if (duplicateTexCoords) {
							glActiveTexture(GL_TEXTURE0 + secondaryTexCoordUnit);

							glBindBufferARB(GL_ARRAY_BUFFER_ARB, mesh->getVBOTexCoords());
							glEnableClientState(GL_TEXTURE_COORD_ARRAY);
							glTexCoordPointer(2, GL_FLOAT, 0, (char *) NULL);		// Set The TexCoord Pointer To The TexCoord Buffer
							//glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
						}

						glActiveTexture(GL_TEXTURE0);

						glBindBufferARB(GL_ARRAY_BUFFER_ARB, mesh->getVBOTexCoords());
						glEnableClientState(GL_TEXTURE_COORD_ARRAY);
						glTexCoordPointer(2, GL_FLOAT, 0, (char *) NULL);		// Set The TexCoord Pointer To The TexCoord Buffer
						//glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
					} else {
						if (duplicateTexCoords) {
							glActiveTexture(GL_TEXTURE0 + secondaryTexCoordUnit);
							glDisableClientState(GL_TEXTURE_COORD_ARRAY);
						}
						glActiveTexture(GL_TEXTURE0);
						glDisableClientState(GL_TEXTURE_COORD_ARRAY);
					}
				} else {
					//printf("Rendering Mesh WITHOUT VBO's\n");

					//vertices
					glVertexPointer(3, GL_FLOAT, 0, mesh->getInterpolationData()->getVertices());

					//normals
					if (renderNormals) {
						glEnableClientState(GL_NORMAL_ARRAY);
						glNormalPointer(GL_FLOAT, 0, mesh->getInterpolationData()->getNormals());
					} else {
						glDisableClientState(GL_NORMAL_ARRAY);
					}

					assertGl();

					//tex coords
					if (renderTextures && mesh->getTexture(0) != NULL) {
						if (duplicateTexCoords) {
							glActiveTexture(GL_TEXTURE0 + secondaryTexCoordUnit);
							glEnableClientState(GL_TEXTURE_COORD_ARRAY);
							glTexCoordPointer(2, GL_FLOAT, 0, mesh->getTexCoords());
						}

						glActiveTexture(GL_TEXTURE0);
						glEnableClientState(GL_TEXTURE_COORD_ARRAY);
						glTexCoordPointer(2, GL_FLOAT, 0, mesh->getTexCoords());
					} else {
						if (duplicateTexCoords) {
							glActiveTexture(GL_TEXTURE0 + secondaryTexCoordUnit);
							glDisableClientState(GL_TEXTURE_COORD_ARRAY);
						}
						glActiveTexture(GL_TEXTURE0);
						glDisableClientState(GL_TEXTURE_COORD_ARRAY);
					}
				}

				if (getVBOSupported() == true && mesh->getFrameCount() == 1) {
					assertGl();

					glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, mesh->getVBOIndexes());
					glDrawRangeElements(GL_TRIANGLES, 0, vertexCount - 1, indexCount, GL_UNSIGNED_INT, (char *) NULL);
					glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
					glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

					//glDrawRangeElements(GL_TRIANGLES, 0, vertexCount-1, indexCount, GL_UNSIGNED_INT, mesh->getIndices());

					assertGl();
				} else {
					//draw model
					assertGl();

					glDrawRangeElements(GL_TRIANGLES, 0, vertexCount - 1, indexCount, GL_UNSIGNED_INT, mesh->getIndices());
				}
				// glow
				if (renderMode == rmNormal && mesh->getGlow() == true) {
					// glow off
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				}
				//assertions
				assertGl();
			}

			void ModelRendererGl::renderMeshNormals(Mesh *mesh) {
				if (getVBOSupported() == true && mesh->getFrameCount() == 1) {
					if (mesh->hasBuiltVBOEntities() == false) {
						mesh->BuildVBOs();
					}

					//printf("Rendering Mesh Normals with VBO's\n");

					//vertices
					glBindBufferARB(GL_ARRAY_BUFFER_ARB, mesh->getVBOVertices());
					glEnableClientState(GL_VERTEX_ARRAY);
					glVertexPointer(3, GL_FLOAT, 0, (char *) NULL);		// Set The Vertex Pointer To The Vertex Buffer
					//glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );

					//normals
					glBindBufferARB(GL_ARRAY_BUFFER_ARB, mesh->getVBONormals());
					glEnableClientState(GL_NORMAL_ARRAY);
					glNormalPointer(GL_FLOAT, 0, (char *) NULL);
					//glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );

					//misc vars
					uint32 vertexCount = mesh->getVertexCount();
					uint32 indexCount = mesh->getIndexCount();

					glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, mesh->getVBOIndexes());
					glDrawRangeElements(GL_TRIANGLES, 0, vertexCount - 1, indexCount, GL_UNSIGNED_INT, (char *) NULL);
					glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
					glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
				} else {
					//printf("Rendering Mesh Normals WITHOUT VBO's\n");

					glBegin(GL_LINES);
					for (unsigned int i = 0; i < mesh->getIndexCount(); ++i) {
						const Vec3f &vertex = mesh->getInterpolationData()->getVertices()[mesh->getIndices()[i]];
						const Vec3f &normal = vertex + mesh->getInterpolationData()->getNormals()[mesh->getIndices()[i]];

						glVertex3fv(vertex.ptr());
						glVertex3fv(normal.ptr());
					}
					glEnd();
				}
			}

		}
	}
} //end namespace
