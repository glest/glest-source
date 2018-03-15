# Windows
ZetaGlest build system for Windows

To build ZetaGlest for the first time:

1. Download Git for Windows (or make sure it is installed)
2. Go to the target directory and clone this repository by running the following command in the command prompt: git clone https://github.com/ZetaGlest/zetaglest-source.git
3. After cloning, run `clone-deps.bat` in `/mk/windows`
4. Run `build-zg.bat` in `/mk/windows`.
5. The built binaries will be found in the corresponding Visual Studio version and platform selected in `/mk/windows`.

Configuration in Visual Studio must be left as "Release", otherwise it won't compile,
but one can still use debugging options by making the following changes in the project properties:

Debug:

	Optimization=Disabled
	Inline Function Expansion: Disabled
	Enable Intrinsic Functions: No
	Favor Size Or Speed: Neither
	Preprocessor: DEBUG instead of NDEBUG
	Code Generation->Basic Runtime Checks: Both
	
Release:

	Optimization=Full
	Inline Function Expansion: Any Suitable
	Enable Intrinsic Functions: Yes
	Favor Size Or Speed: Favor fast code
	Preprocessor: NDEBUG instead of DEBUG
	Code Generation->Basic Runtime Checks: Default