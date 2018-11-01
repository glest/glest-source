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

#ifndef _GLEST_GAME_CONSOLE_H_
#   define _GLEST_GAME_CONSOLE_H_

#   ifdef WIN32
#      include <winsock2.h>
#      include <winsock.h>
#   endif

#   include <utility>
#   include <string>
#   include <vector>
#   include <stdexcept>
#   include "font.h"
#   include "leak_dumper.h"
#   include "vec.h"

using
std::string;
using
std::vector;
using
std::pair;
using namespace
std;

namespace
	Glest {
	namespace
		Game {

		using
			Shared::Graphics::Font;
		using
			Shared::Graphics::Font2D;
		using
			Shared::Graphics::Font3D;
		using
			Shared::Graphics::FontChangedCallbackInterface;
		using
			Shared::Graphics::Vec4f;
		// =====================================================
		//      class Console
		//
		//      In-game console that shows various types of messages
		// =====================================================

		class
			ConsoleLineInfo {
		public:
			string
				text;
			float
				timeStamp;
			int
				PlayerIndex;
			string
				originalPlayerName;
			Vec4f
				color;
			bool
				teamMode;
		};

		class
			Console :
			public
			FontChangedCallbackInterface {

		public:

			typedef
				vector <
				ConsoleLineInfo >
				Lines;
			typedef
				Lines::const_iterator
				LineIterator;

		private:
			float
				timeElapsed;
			Lines
				lines;
			Lines
				storedLines;
			string
				stringToHighlight;

			//config
			int
				maxLines;
			int
				maxStoredLines;
			float
				timeout;
			int
				xPos;
			int
				yPos;
			int
				lineHeight;
			Font2D *
				font;
			Font3D *
				font3D;
			string
				font2DUniqueId;
			string
				font3DUniqueId;

			bool
				onlyChatMessagesInStoredLines;

			string
				instanceName;
			string
				fontCallbackName;

			string
				getNewUUD();

		public:

			Console();
			virtual ~
				Console();

			void
				registerGraphicComponent(const std::string & containerName,
					const std::string & objName);
			string
				getInstanceName() const {
				return
					instanceName;
			}
			void
				setInstanceName(const string & value) {
				instanceName = value;
			}
			string
				getFontCallbackName() const {
				return
					fontCallbackName;
			}

			int
				getStoredLineCount() const {
				return (int)
					storedLines.
					size();
			}
			int
				getLineCount() const {
				return (int)
					lines.
					size();
			}
			bool
				getOnlyChatMessagesInStoredLines() const {
				return
					onlyChatMessagesInStoredLines;
			}
			void
				setOnlyChatMessagesInStoredLines(bool value) {
				this->onlyChatMessagesInStoredLines = value;
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
				getLineHeight() const {
				return
					lineHeight;
			}
			void
				setLineHeight(int lineHeight) {
				this->lineHeight = lineHeight;
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
				setFont(Font2D * font);
			void
				setFont3D(Font3D * font);
			string
				getStringToHighlight() const {
				return
					stringToHighlight;
			}
			void
				setStringToHighlight(const string & stringToHighlight) {
				this->stringToHighlight = stringToHighlight;
			}
			void
				resetFonts();


			//string getLine(int i) const;
			//string getStoredLine(int i) const;
			ConsoleLineInfo
				getLineItem(int i) const;
			ConsoleLineInfo
				getStoredLineItem(int i) const;

			void
				clearStoredLines();
			void
				addStdMessage(const string & s, bool clearOtherLines = false);
			void
				addStdMessage(const string & s, const string & failText,
					bool clearOtherLines = false);

			void
				addStdScenarioMessage(const string & s, bool clearOtherLines = false);
			void
				addLineOnly(const string & line);
			void
				addLine(const string & line, bool playSound = false, int playerIndex =
					-1, Vec4f textColor = Vec4f(1.f, 1.f, 1.f, 1.f), bool teamMode =
					false, bool clearOtherLines = false);
			void
				addLine(const string & line, bool playSound, const string & playerName,
					Vec4f textColor = Vec4f(1.f, 1.f, 1.f, 1.f), bool teamMode =
					false);
			void
				addLine(const string & line, bool playSound, Vec4f textColor) {
				addLine(line, playSound, "", textColor, false);
			}
			void
				update();
			bool
				isEmpty();

			virtual void
				FontChangedCallback(std::string fontUniqueId, Font * font);
		};

	}
}                              //end namespace

#endif
