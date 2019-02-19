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

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#ifdef WIN32
#include <winsock2.h>
#include <winsock.h>
#endif

#include <string>
#include "texture.h"
#include "util.h"
#include "command_type.h"
#include "game_util.h"
#include "leak_dumper.h"

using std::string;

using Shared::Graphics::Texture2D;
using Shared::Graphics::Vec4f;
using Shared::Util::replaceBy;

namespace Game {
	// =====================================================
	// 	class Display
	//
	///	Display for unit commands, and unit selection
	// =====================================================

	class Display {
	public:
		static const int cellSideCount = 4;
		static const int upCellCount = 36;
		static const int downCellCount = cellSideCount * cellSideCount;
		static const int colorCount = 9;
		static const int imageSize = 40;
		static const int invalidPos = -1;
		static const int downY = imageSize * 7;
		static const int infoStringY = imageSize * 2;

	private:
		string title;
		string text;
		string infoText;
		const Texture2D *upImages[upCellCount];
		const Texture2D *downImages[downCellCount];
		float lightLevels[downCellCount];
		const CommandType *commandTypes[downCellCount];
		CommandClass commandClasses[downCellCount];
		int progressBar;
		int downSelectedPos;
		Vec4f colors[colorCount];
		int currentColor;

		int upCellSideCount;
		int upImageSize;
		int maxUpIndex;


	public:
		Display();

		//get
		string getTitle() const {
			return title;
		}
		string getText() const {
			return text;
		}
		string getInfoText() const {
			return infoText;
		}
		const Texture2D *getUpImage(int index) const {
			return upImages[index];
		}
		const Texture2D *getDownImage(int index) const {
			return downImages[index];
		}
		float getLightLevel(int index) const {
			return lightLevels[index];
		}
		const CommandType *getCommandType(int i) const {
			return commandTypes[i];
		}
		CommandClass getCommandClass(int i)	const {
			return commandClasses[i];
		}
		Vec4f getColor() const;
		int getProgressBar() const {
			return progressBar;
		}
		int getDownSelectedPos() const {
			return downSelectedPos;
		}
		int getUpCellSideCount() const {
			return upCellSideCount;
		}
		int getUpImageSize() const {
			return upImageSize;
		}

		//set
		void setTitle(const string title) {
			this->title = formatString(title);
		}
		void setText(const string &text) {
			this->text = formatString(text);
		}
		void setInfoText(const string infoText) {
			this->infoText = formatString(infoText);
		}
		void setUpImage(int i, const Texture2D *image);
		void setDownImage(int i, const Texture2D *image) {
			downImages[i] = image;
		}
		void setCommandType(int i, const CommandType *ct) {
			commandTypes[i] = ct;
		}
		void setCommandClass(int i, const CommandClass cc) {
			commandClasses[i] = cc;
		}
		void setLightLevel(int i, float lightLevel) {
			lightLevels[i] = lightLevel;
		}
		void setProgressBar(int i) {
			progressBar = i;
		}
		void setDownSelectedPos(int i) {
			downSelectedPos = i;
		}

		//misc
		void clear();
		void switchColor();
		int computeDownIndex(int x, int y) const;
		int computeDownX(int index) const;
		int computeDownY(int index) const;
		int computeUpX(int index) const;
		int computeUpY(int index) const;

		void saveGame(XmlNode *rootNode) const;
		void loadGame(const XmlNode *rootNode);

	private:
		void calculateUpDimensions(int index);
	};

} //end namespace 

#endif
