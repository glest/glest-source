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

#include "object_type.h"

#include "renderer.h"
#include "leak_dumper.h"

namespace Game {
	// =====================================================
	//      class ObjectType
	// =====================================================

	void ObjectType::init(int modelCount, int objectClass, bool walkable,
		int height) {
		//      modeltypes.reserve(modelCount);
		this->objectClass = objectClass;
		this->walkable = walkable;
		this->height = height;
	}

	ObjectType::~ObjectType() {
		while (!(modeltypes.empty())) {
			delete modeltypes.back();
			modeltypes.pop_back();
			//Logger::getInstance().add("ObjectType", true);
		}
	}

	TilesetModelType *ObjectType::loadModel(const string & path,
		std::map < string,
		vector < pair < string,
		string > > >*loadedFileList,
		string parentLoader) {
		Model *model =
			Renderer::getInstance().newModel(rsGame, path, false,
				loadedFileList, &parentLoader);
		color = Vec4f(0.f);
		if (model && model->getMeshCount() > 0
			&& model->getMesh(0)->getTexture(0) != NULL) {
			const Pixmap2D *p =
				model->getMesh(0)->getTexture(0)->getPixmapConst();
			color = p->getPixel4f(p->getW() / 2, p->getH() / 2);
		}
		TilesetModelType *modelType = new TilesetModelType();
		modelType->setModel(model);
		modeltypes.push_back(modelType);
		return modelType;
	}

	void ObjectType::deletePixels() {
		for (int i = 0; i < (int) modeltypes.size(); ++i) {
			TilesetModelType *model = modeltypes[i];
			if (model->getModel() != NULL) {
				model->getModel()->deletePixels();
			}
		}
	}

} //end namespace
