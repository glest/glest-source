# Windows
ZetaGlest build system for Windows

To build ZetaGlest for the first time:

1. Download Git for Windows (or make sure it is installed)
2. Go to the target directory and clone this repository by running the following command in the command prompt: git clone https://github.com/ZetaGlest/zetaglest-source.git
3. After cloning, run `clone-deps.bat` in `/mk/windows`
4. Run `build-zg.bat` in `/mk/windows`.
5. The built binaries will be found in the corresponding Visual Studio version and platform selected in `/mk/windows`.

Note: Before pushing changes to this folder, make sure that you run `delete-all-deps.bat` and `clean-all.bat` before you do so.
