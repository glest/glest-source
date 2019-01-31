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

#ifndef _MAIN_H_
#define _MAIN_H_

#include <ctime>
#include "program.h"
#include "window_gl.h"
#include "leak_dumper.h"

using Shared::Platform::MouseButton;
using Shared::Platform::MouseState;

namespace Game {
	// =====================================================
	//      class MainWindow
	//
	///     Main program window
	// =====================================================

	class MainWindow :
		public WindowGl {
	private:
		Program * program;
		PopupMenu popupMenu;
		int
			cancelLanguageSelection;
		bool triggerLanguageToggle;
		string triggerLanguage;

		void
			showLanguages();

	public:
		explicit MainWindow(Program * program);
		~MainWindow();

		void
			setProgram(Program * program);

		virtual void
			eventMouseDown(int x, int y, MouseButton mouseButton);
		virtual void
			eventMouseUp(int x, int y, MouseButton mouseButton);
		virtual void
			eventMouseDoubleClick(int x, int y, MouseButton mouseButton);
		virtual void
			eventMouseMove(int x, int y, const MouseState * mouseState);
		virtual
			bool
			eventTextInput(std::string text);
		virtual
			bool
			eventSdlKeyDown(SDL_KeyboardEvent key);
		virtual void
			eventKeyDown(SDL_KeyboardEvent key);
		virtual void
			eventMouseWheel(int x, int y, int zDelta);
		virtual void
			eventKeyUp(SDL_KeyboardEvent key);
		virtual void
			eventKeyPress(SDL_KeyboardEvent c);
		virtual void
			eventActivate(bool active);
		virtual void
			eventResize(SizeState sizeState);
		virtual void
			eventClose();
		virtual void
			eventWindowEvent(SDL_WindowEvent event);

		virtual void
			render();
		void
			toggleLanguage(string language);
		bool getTriggerLanguageToggle()const {
			return
				triggerLanguageToggle;
		}
		string
			getTriggerLanguage() const {
			return
				triggerLanguage;
		}

		virtual int
			getDesiredScreenWidth();
		virtual int
			getDesiredScreenHeight();

	protected:
		virtual void
			eventToggleFullScreen(bool isFullscreen);
	};

} //end namespace

#endif
