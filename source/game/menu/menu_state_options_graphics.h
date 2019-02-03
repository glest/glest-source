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

#ifndef _MENUSTATEOPTIONS_GRAPHICS_H_
#define _MENUSTATEOPTIONS_GRAPHICS_H_

#include "main_menu.h"
#include "leak_dumper.h"

namespace Game {
	// ===============================
	//      class MenuStateOptionsGraphics
	// ===============================
	class MenuStateOptionsGraphics :public MenuState {
	private:

		GraphicButton buttonOk;
		GraphicButton buttonReturn;
		GraphicButton buttonAutoConfig;
		GraphicButton buttonVideoInfo;

		GraphicButton buttonKeyboardSetup;        // configure the keyboard
		GraphicButton buttonVideoSection;
		GraphicButton buttonAudioSection;
		GraphicButton buttonMiscSection;
		GraphicButton buttonNetworkSettings;

		GraphicLabel labelShadows;
		GraphicListBox listBoxShadows;
		GraphicLabel labelFilter;
		GraphicListBox listBoxFilter;
		GraphicLabel labelFilterMaxAnisotropy;
		GraphicListBox listBoxFilterMaxAnisotropy;

		GraphicLabel labelTextures3D;
		GraphicCheckBox checkBoxTextures3D;
		GraphicLabel labelLights;
		GraphicListBox listBoxLights;
		GraphicLabel labelUnitParticles;
		GraphicCheckBox checkBoxUnitParticles;

		GraphicLabel labelTilesetParticles;
		GraphicCheckBox checkBoxTilesetParticles;

		GraphicLabel labelScreenModes;
		GraphicListBox listBoxScreenModes;
		vector < ModeInfo > modeInfos;

		GraphicLabel labelFullscreenWindowed;
		GraphicCheckBox checkBoxFullscreenWindowed;


		GraphicLabel labelMapPreview;
		GraphicCheckBox checkBoxMapPreview;

		GraphicMessageBox mainMessageBox;
		int mainMessageBoxState;

		GraphicLabel labelEnableTextureCompression;
		GraphicCheckBox checkBoxEnableTextureCompression;

		GraphicLabel labelRainEffect;
		GraphicLabel labelRainEffectSeparator;
		GraphicCheckBox checkBoxRainEffect;
		GraphicCheckBox checkBoxRainEffectMenu;

		GraphicLabel labelGammaCorrection;
		GraphicListBox listBoxGammaCorrection;

		GraphicLabel labelShadowIntensity;
		GraphicListBox listBoxShadowIntensity;

		GraphicLabel labelShadowTextureSize;
		GraphicListBox listBoxShadowTextureSize;

		GraphicLabel labelSelectionType;
		GraphicListBox listBoxSelectionType;

		ProgramState **parentUI;
		time_t screenModeChangedTimer;

	public:
		MenuStateOptionsGraphics(Program * program, MainMenu * mainMenu,
			ProgramState ** parentUI = NULL);

		void mouseClick(int x, int y, MouseButton mouseButton);
		void mouseMove(int x, int y, const MouseState * mouseState);
		void render();
		//virtual void keyDown(SDL_KeyboardEvent key);
		virtual void keyPress(SDL_KeyboardEvent c);
		//virtual bool isInSpecialKeyCaptureEvent();

		virtual void reloadUI();


	private:
		void saveConfig();
		void setActiveInputLable(GraphicLabel * newLable);
		void showMessageBox(const string & text, const string & header,
			bool toggle);
		void revertScreenMode();
		void setupTransifexUI();
		virtual void update();
	};

} //end namespace

#endif
