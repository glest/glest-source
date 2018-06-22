# Build ZetaGlest for Windows

**To build ZetaGlest for the first time:**

1. Download Git for Windows (or make sure it is installed), and make sure that `git` is in the `PATH` environment variable.
   To check, open `cmd` and write `git`. If you get a `not recognized` error, then continue with step 1, otherwise skip to step 2. Usually `git.exe` is located in `C:\Program Files\Git\bin` after installation. To add it to `PATH`, right-click on `This PC` -> `Properties` -> `Advanced system settings` -> `Advanced` tab -> `Environment Variables`, and under `System variables` double-click on `PATH`, and add the path to `git` as a listing and click `OK`.
2. Go to the target directory and clone this repository by running the following command in the command prompt: `git clone https://github.com/ZetaGlest/zetaglest-source.git` (or if you have your own fork, replace the first "ZetaGlest" in the URL with your GitHub username).
3. Make sure Visual Studio 2015 or 2017 is installed, and that **Windows 8.1 SDK** and Windows Universal CRT SDK (maybe) are included in the installation. If Visual Studio is installed in a different directory than the default, run the following command before running the script:
`SET ProgramFiles(x86)=dir` where `dir` should be replaced with the directory containing the Visual Studio installation, usually `Program Files (x86)`. If Windows is 32-bit, omit the `(x86)` part.
4. Run `setup.bat` in `/mk/windows`.
5. The built binaries will be found in the corresponding Visual Studio version and platform selected in `/mk/windows`.
6. Run and enjoy! :)

**Project overview:**

- `glest_game` is the executable game binary

- `libglest` is a shared static library for ZetaGlest's components

- `g3d_viewer` is a `.g3d` model viewer

- `map_editor` is a ZetaGlest map editor and viewer. ZetaGlest maps are stored in the `.gbm` and the `.mgm` formats.

- `libstreflop` is a cross-platform float processing library to ensure rounding is the same across machines

- `g2xml` converts `.g3d` ZetaGlest 3D models into a readable XML formatted layout

*Side-note for developers who want to debug:*

To be able to run ZetaGlest from within Visual Studio using the debugger, you need to:

1. Set `glest_game` as the startup project.
2. Right-click `glest_game` -> `Properties` -> `Debugging` and change `Working Directory` to `$(SolutionDir)$(TargetName)\`
   Do this also for `g3d_viewer` and `map_editor`.

Configuration in Visual Studio **must be left as `Release`**, and it must match the project architecture as otherwise it won't compile. The settings involved are the following:

![VS Image](https://i.imgur.com/UFURP4x.png)

Although the configuration *must be set as `Release`*, one can still use debugging options by making the following changes in the project properties.

To manually emulate `Debug`:

	Inline Function Expansion: Disabled
	Enable Intrinsic Functions: No
	Favor Size Or Speed: Neither
	Preprocessor: DEBUG instead of NDEBUG
	
To manually emulate `Release`:

	Inline Function Expansion: Any Suitable
	Enable Intrinsic Functions: Yes
	Favor Size Or Speed: Favor fast code
	Preprocessor: NDEBUG instead of DEBUG
