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

#ifndef _SERVERLINE_H_
#define _SERVERLINE_H_

#ifdef WIN32
#   include <winsock2.h>
#   include <winsock.h>
#endif

#include "masterserver_info.h"
#include "components.h"
#include "lang.h"
#include "world.h"

#include "leak_dumper.h"

namespace Game {
	// ===============================
	//      ServerLine
	// ===============================

	class ServerLine {
	private:

		MasterServerInfo masterServerInfo;
		int lineHeight;
		int baseY;
		bool compatible;
		GraphicButton selectButton;
		GraphicLabel wrongVersionLabel;

		//general info:
		GraphicLabel glestVersionLabel;
		GraphicLabel platformLabel;
		//GraphicLabel binaryCompileDateLabel;

		//game info:
		GraphicLabel serverTitleLabel;
		GraphicLabel ipAddressLabel;

		//game setup info:
		GraphicLabel techLabel;
		GraphicLabel mapLabel;
		GraphicLabel tilesetLabel;
		GraphicLabel activeSlotsLabel;

		GraphicLabel externalConnectPort;

		GraphicLabel country;
		GraphicLabel status;

		Texture2D *countryTexture;

		const char *containerName;

	public:
		ServerLine(MasterServerInfo * mServerInfo, int lineIndex, int baseY,
			int lineHeight, const char *containerName);
		virtual ~ServerLine();
		MasterServerInfo *getMasterServerInfo() {
			return &masterServerInfo;
		}
		const int getLineHeight() const {
			return lineHeight;
		}
		bool buttonMouseClick(int x, int y);
		bool buttonMouseMove(int x, int y);
		void setY(int y);
		//void setIndex(int value);
		void render();

		virtual void reloadUI();
	};

} //end namespace

#endif
