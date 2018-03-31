# Windows
ZetaGlest build system for Windows

To build ZetaGlest for the first time:

1. Download Git for Windows (or make sure it is installed)
2. Go to the target directory and clone this repository by running the following command in the command prompt: `git clone https://github.com/ZetaGlest/zetaglest-source.git` (or if you have your own fork, replace the first "ZetaGlest" in the URL with your GitHub username).
3. After cloning, run `setup.bat` in `/mk/windows`.
4. The built binaries will be found in the corresponding Visual Studio version and platform selected in `/mk/windows`.
5. Run and enjoy! :)

*Side-note for developers who want to debug:*

To be able to run ZetaGlest from within Visual Studio using the debugger, you need to:

	1. Set `glest_game` as the startup project.
	2. Right-click `glest_game` -> Properties -> Debugging and change `Working Directory` to `$(SolutionDir)$(TargetName)\`
	   Do this for `g3d_viewer` and `map_editor`.

Configuration in Visual Studio must be left as "Release", otherwise it won't compile, but one can still use debugging options by making the following changes in the project properties:

Debug:

	Inline Function Expansion: Disabled
	Enable Intrinsic Functions: No
	Favor Size Or Speed: Neither
	Preprocessor: DEBUG instead of NDEBUG
	
Release:

	Inline Function Expansion: Any Suitable
	Enable Intrinsic Functions: Yes
	Favor Size Or Speed: Favor fast code
	Preprocessor: NDEBUG instead of DEBUG
