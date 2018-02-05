//
//      program.h:
//
//      This file is part of ZetaGlest <https://github.com/ZetaGlest>
//
//      Copyright (C) 2018  The ZetaGlest team
//
//      ZetaGlest is a fork of MegaGlest <https://megaglest.org>
//
//      This program is free software: you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation, either version 3 of the License, or
//      (at your option) any later version.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program.  If not, see <https://www.gnu.org/licenses/>

#ifndef _GLEST_GAME_PROGRAM_H_
#   define _GLEST_GAME_PROGRAM_H_

#   ifdef WIN32
#      include <winsock2.h>
#      include <winsock.h>
#   endif

#   include "context.h"
#   include "platform_util.h"
#   include "window_gl.h"
#   include "socket.h"
#   include "components.h"
#   include "window.h"
#   include "simple_threads.h"
#   include "stats.h"
#   include "leak_dumper.h"

#   ifndef PRINT_DEBUG
#      	define PRINT_DEBUG printf("[DEBUG] "); printf
#   endif

using Shared::Platform::MouseButton;
using Shared::Graphics::Context;
using Shared::Platform::WindowGl;
using Shared::Platform::SizeState;
using Shared::Platform::MouseState;
using Shared::PlatformCommon::PerformanceTimer;
using Shared::Platform::Ip;
using
  namespace
  Shared::PlatformCommon;

namespace Glest
{
  namespace Game
  {

    class Program;
    class MainWindow;
    class GameSettings;

// =====================================================
//      class ProgramState
//
///     Base class for all program states:
/// Intro, MainMenu, Game, BattleEnd (State Design pattern)
// =====================================================

    class ProgramState
    {
    protected:
      Program * program;

      int
        mouseX;
      int
        mouseY;
      int
        mouse2dAnim;

      int
        startX;
      int
        startY;
      bool forceMouseRender;

      int
        fps;
      int
        lastFps;

    public:

      static const char *
        MAIN_PROGRAM_RENDER_KEY;

      explicit ProgramState (Program * program);
      virtual ~ ProgramState ()
      {
      };

      int
      getFps () const
      {
        return
          fps;
      }
      int
      getLastFps () const
      {
        return
          lastFps;
      }

//virtual void render()=0;
      virtual
        bool
      canRender (bool sleepIfCannotRender = true);
      virtual void
      render ();
      virtual void
      update ();
      virtual void
      updateCamera ()
      {
      };
      virtual void
      tick ();
      virtual void
      init ()
      {
      };
      virtual void
      load ()
      {
      };
      virtual void
      end ()
      {
      };
      virtual void
      mouseDownLeft (int x, int y)
      {
      };
      virtual void
      mouseUpLeft (int x, int y)
      {
      };
      virtual void
      mouseUpRight (int x, int y)
      {
      }
      virtual void
      mouseUpCenter (int x, int y)
      {
      }
      virtual void
      mouseDownRight (int x, int y)
      {
      };
      virtual void
      mouseDownCenter (int x, int y)
      {
      }
      virtual void
      mouseDoubleClickLeft (int x, int y)
      {
      };
      virtual void
      mouseDoubleClickRight (int x, int y)
      {
      }
      virtual void
      mouseDoubleClickCenter (int x, int y)
      {
      }
      virtual void
      eventMouseWheel (int x, int y, int zDelta)
      {
      }
      virtual void
      mouseMove (int x, int y, const MouseState * mouseState);
      virtual
        bool
      textInput (std::string text)
      {
        return false;
      };
      virtual void
      keyDown (SDL_KeyboardEvent key)
      {
      };
      virtual
        bool
      sdlKeyDown (SDL_KeyboardEvent key)
      {
        return false;
      };
      virtual void
      keyUp (SDL_KeyboardEvent key)
      {
      };
      virtual void
      keyPress (SDL_KeyboardEvent c)
      {
      };
      virtual void
      setStartXY (int X, int Y)
      {
        startX = X;
        startY = Y;
      }
      virtual void
      restoreToStartXY ();
      virtual
        bool
      isInSpecialKeyCaptureEvent ()
      {
        return false;
      }
      virtual
        bool
      quitTriggered ()
      {
        return false;
      }
      virtual
        Stats
      quitAndToggleState ()
      {
        return Stats ();
      };
      virtual Program *
      getProgram ()
      {
        return program;
      }
      virtual const Program *
      getProgramConstPtr ()
      {
        return program;
      }
      virtual void
      setForceMouseRender (bool value)
      {
        forceMouseRender = value;
      }
      virtual void
      consoleAddLine (string line)
      {
      };

      virtual void
      reloadUI ()
      {
      };
      virtual void
      addPerformanceCount (string key, int64 value)
      {
      };

    protected:
      virtual void
      incrementFps ();
    };

// ===============================
//      class Program
// ===============================

    class Program
    {
    private:
      static const int
        maxTimes;
      SimpleTaskThread *
        soundThreadManager;

    class ShowMessageProgramState:
      public ProgramState
      {
        GraphicMessageBox msgBox;
        int
          mouseX;
        int
          mouseY;
        int
          mouse2dAnim;
        string msg;
        bool userWantsExit;

      public:
        ShowMessageProgramState (Program * program, const char *msg);

        virtual void
        render ();
        virtual void
        mouseDownLeft (int x, int y);
        virtual void
        mouseMove (int x, int y, const MouseState & mouseState);
        virtual void
        keyPress (SDL_KeyboardEvent c);
        virtual void
        update ();
        virtual
          bool
        wantExit ()
        {
          return userWantsExit;
        }
      };


    private:
      ProgramState * programState;

      PerformanceTimer fpsTimer;
      PerformanceTimer updateTimer;
      PerformanceTimer updateCameraTimer;

      WindowGl *
        window;
      static Program *
        singleton;

      GraphicMessageBox msgBox;
      int
        skipRenderFrameCount;

      bool messageBoxIsSystemError;
      ProgramState *
        programStateOldSystemError;

//bool masterserverMode;
      bool shutdownApplicationEnabled;
      static
        bool
        wantShutdownApplicationAfterGame;

      static
        bool
        tryingRendererInit;
      static
        bool
        rendererInitOk;

    public:
      Program ();
      virtual ~ Program ();

      static
        bool
      getTryingRendererInit ()
      {
        return tryingRendererInit;
      }
      static
        bool
      getRendererInitOk ()
      {
        return rendererInitOk;
      }

      static Program *
      getInstance ()
      {
        return singleton;
      }

      static void
      setWantShutdownApplicationAfterGame (bool value)
      {
        wantShutdownApplicationAfterGame = value;
      }
      static
        bool
      getWantShutdownApplicationAfterGame ()
      {
        return wantShutdownApplicationAfterGame;
      }

//bool isMasterserverMode() const;
      bool isShutdownApplicationEnabled ()const
      {
        return
          shutdownApplicationEnabled;
      }
      void
      setShutdownApplicationEnabled (bool value)
      {
        shutdownApplicationEnabled = value;
      }

      GraphicMessageBox *
      getMsgBox ()
      {
        return &msgBox;
      }
      void
      initNormal (WindowGl * window);
      void
      initServer (WindowGl * window, bool autostart =
                  false, bool openNetworkSlots =
                  false, bool masterserverMode = false);
      void
      initServer (WindowGl * window, GameSettings * settings);
      void
      initSavedGame (WindowGl * window, bool masterserverMode =
                     false, string saveGameFile = "");
      void
      initClient (WindowGl * window, const Ip & serverIp, int portNumber =
                  -1);
      void
      initClientAutoFindHost (WindowGl * window);
      void
      initScenario (WindowGl * window, string autoloadScenarioName);

//main
      bool textInput (std::string text);
      void
      keyDown (SDL_KeyboardEvent key);
      bool sdlKeyDown (SDL_KeyboardEvent key);
      void
      keyUp (SDL_KeyboardEvent key);
      void
      keyPress (SDL_KeyboardEvent c);

      void
      loop ();
      void
      loopWorker ();
      void
      resize (SizeState sizeState);
      void
      showMessage (const char *msg);
      bool isMessageShowing ();

//misc
      void
      setState (ProgramState * programStateNew, bool cleanupOldState = true);
      ProgramState *
      getState ()
      {
        return programState;
      }
      WindowGl *
      getWindow ()
      {
        return window;
      }
      const WindowGl *
      getWindowConstPtr () const
      {
        return
          window;
      }
      void
      init (WindowGl * window, bool initSound = true, bool toggleFullScreen =
            false);
      void
      exit ();

      virtual void
      simpleTask (BaseThread * callingThread, void *userdata);

      void
      mouseDownLeft (int x, int y);
      void
      eventMouseMove (int x, int y, const MouseState * ms);

      void
      renderProgramMsgBox ();
      bool isInSpecialKeyCaptureEvent ()
      {
        return programState->isInSpecialKeyCaptureEvent ();
      }

//void reInitGl();
//void resetSoundSystem();
      void
      stopSoundSystem ();
      void
      startSoundSystem ();

      virtual void
      consoleAddLine (string line);

      virtual SimpleTaskThread *
      getSoundThreadManager (bool takeOwnership);
      virtual void
      reloadUI ();

    private:

      void
      setDisplaySettings ();
      void
      restoreDisplaySettings ();
      void
      restoreStateFromSystemError ();
      void
      initResolution ();
    };

}}                              //end namespace

#endif
