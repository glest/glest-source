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

#ifndef _CHATMANAGER_H_
#define _CHATMANAGER_H_

#ifdef WIN32
#   include <winsock2.h>
#   include <winsock.h>
#endif

#include <string>
#include "font.h"
#include <SDL.h>
#include <vector>
#include "leak_dumper.h"

using std::string;
using std::vector;
using Shared::Graphics::Font2D;
using Shared::Graphics::Font3D;

namespace Game {
	class Console;

	//
	// This interface describes the methods a callback object must implement
	//
	class
		CustomInputCallbackInterface {
	public:
		virtual void
			processInputText(string text, bool cancelled) = 0;
		virtual ~
			CustomInputCallbackInterface() {
		}
	};

	// =====================================================
	//      class ChatManager
	// =====================================================

	class
		ChatManager {

	private:
		bool
			editEnabled;
		bool
			teamMode;
		bool
			disableTeamMode;
		Console *
			console;
		string
			text;
		vector < int >
			textCharLength;
		int
			thisTeamIndex;
		bool
			inMenu;
		string
			manualPlayerNameOverride;
		int
			xPos;
		int
			yPos;
		int
			maxTextLength;
		Font2D *
			font;
		Font3D *
			font3D;

		string
			lastAutoCompleteSearchText;
		vector <
			string >
			autoCompleteTextList;

		CustomInputCallbackInterface *
			customCB;
		int
			maxCustomTextLength;

		string
			getTextWithLengthCheck(string text, int currentLength, int maxLength);
		void
			appendText(string addText, bool validateChars =
				true, bool addToAutoCompleteBuffer = true);
		void
			deleteText(int deleteCount, bool addToAutoCompleteBuffer = true);
		void
			updateAutoCompleteBuffer();

	public:
		ChatManager();
		void
			init(Console * console, int thisTeamIndex, const bool inMenu =
				false, string manualPlayerNameOverride = "");

		bool
			textInput(std::string text);
		void
			keyDown(SDL_KeyboardEvent key);
		void
			keyUp(SDL_KeyboardEvent key);
		void
			keyPress(SDL_KeyboardEvent c);
		void
			updateNetwork();

		bool
			getEditEnabled() const {
			return
				editEnabled;
		}
		bool
			getTeamMode() const {
			return
				teamMode;
		}
		bool
			getInMenu() const {
			return
				inMenu;
		}
		string
			getText() const {
			return
				text;
		}
		int
			getXPos() const {
			return
				xPos;
		}
		void
			setXPos(int xPos) {
			this->xPos = xPos;
		}
		int
			getYPos() const {
			return
				yPos;
		}
		void
			setYPos(int yPos) {
			this->yPos = yPos;
		}
		int
			getMaxTextLenght() const {
			return
				maxTextLength;
		}
		void
			setMaxTextLenght(int maxTextLength) {
			this->maxTextLength = maxTextLength;
		}
		Font2D *
			getFont() const {
			return
				font;
		}
		Font3D *
			getFont3D() const {
			return
				font3D;
		}
		void
			setFont(Font2D * font) {
			this->font = font;
		}
		void
			setFont3D(Font3D * font) {
			this->font3D = font;
		}
		void
			addText(string text);
		void
			switchOnEdit(CustomInputCallbackInterface * customCB =
				NULL, int maxCustomTextLength = -1);

		bool
			getDisableTeamMode() const {
			return
				disableTeamMode;
		}
		void
			setDisableTeamMode(bool value);

		void
			setAutoCompleteTextList(const vector < string > &list) {
			autoCompleteTextList = list;
		}

		bool
			isInCustomInputMode() const {
			return
				customCB !=
				NULL;
		};
	};

} //end namespace

#endif
