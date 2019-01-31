CMAKE_MINIMUM_REQUIRED( VERSION 2.8.2 )
PROJECT( Glest )

# The Glest CMakeLists is not supported on Windows. To compile on Windows, please use
# setup.bat in mk/windows

#SET(CMAKE_VERBOSE_MAKEFILE ON)

# build type
IF(NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose build type: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
ENDIF()
SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS None Debug Release RelWithDebInfo MinSizeRel)

IF(NOT CMAKE_VERSION VERSION_LESS "3.1")
    cmake_policy(SET CMP0054 NEW)
ENDIF()

# add additional CMake modules
MESSAGE(STATUS "CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/mk/cmake/Modules)
IF(CMAKE_BUILD_TYPE)
	MESSAGE(STATUS "Build type for this compile will be: ${CMAKE_BUILD_TYPE}")
ENDIF()

# *BSD users should use eg++ and egcc. It's advised not to overwrite
# $CMAKE_CXX_COMPILER, but instead precede `cmake` at the command line
# using  CC=`which egcc` CXX=`which eg++`

IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    SET(CMAKE_COMPILER_IS_GNUCXX "YES")
#        ADD_DEFINITIONS("-Qunused-arguments -Wno-switch")
    ADD_DEFINITIONS("-Wno-switch")
ENDIF()

OPTION(BUILD_GLEST "Build Glest" ON)
OPTION(WANT_STATIC_LIBS "Builds as many static libs as possible." OFF)
OPTION(WANT_USE_OpenSSL "Use libOpenSSL during CURL linking." ON)
OPTION(WANT_USE_FriBiDi "Enable libFriBIDi support." ON)
OPTION(WANT_USE_GoogleBreakpad "Enable GoogleBreakpad support." OFF)
OPTION(WANT_USE_STREFLOP "Use the library streflop." OFF)
OPTION(WANT_USE_XercesC "Enable libXercesC support." OFF)

include(${CMAKE_SOURCE_DIR}/mk/cmake/Modules/SpecialMacros.cmake)
include(${CMAKE_SOURCE_DIR}/mk/cmake/Modules/ReqVersAndStaticConf.cmake)
MESSAGE(STATUS "=====================================================================")

SET(PKG_NAME "glest")

SET(PIC_FLAG "${PIC_FLAG} -fPIC")
IF(WANT_STATIC_LIBS AND "${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	# CMAKE_SIZEOF_VOID_P=8 => 64bit
	ADD_DEFINITIONS("${PIC_FLAG}")
ENDIF()

## Compiler flags, CPACK configuration and other Apple specific code.
# IF(APPLE)
#	 include(${PROJECT_SOURCE_DIR}/mk/macos/CMakeLists.txt)
# ENDIF(APPLE)

IF(CMAKE_COMPILER_IS_GNUCXX OR MINGW)
	IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        MESSAGE(STATUS "Detected CLANG Compiler...")
	ELSEIF(CMAKE_COMPILER_IS_GNUCXX)
		MESSAGE(STATUS "Detected GNUC Compiler...")
	ELSEIF(MINGW)
		MESSAGE(STATUS "Detected MINGW Compiler...")
	ENDIF()

    # Common generic GNU type compiler options that work with all generic GCC compatible compilers
    ADD_DEFINITIONS("-Wuninitialized -Wsign-compare -Wunused-function -Wunused-variable -Wreturn-type -fno-strict-aliasing")

	# For gcc warning options see: http://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
	IF(NOT MINGW)
		# For tons of verbose warnings add: -Wall
#		ADD_DEFINITIONS("-Wreturn-type -fno-strict-aliasing -frounding-math  -fsignaling-nans -mfpmath=sse -msse -rdynamic")
#		ADD_DEFINITIONS("-Wuninitialized -Wsign-compare -Wunused-function -Wunused-variable -Wreturn-type -fno-strict-aliasing -frounding-math  -fsignaling-nans -rdynamic")
	ELSE()
#		ADD_DEFINITIONS("-Wreturn-type -fno-strict-aliasing -frounding-math  -fsignaling-nans -mfpmath=sse -msse -DUNICODE")
#		ADD_DEFINITIONS("-Wuninitialized -Wsign-compare -Wunused-function -Wunused-variable -Wreturn-type -fno-strict-aliasing -frounding-math  -fsignaling-nans -DUNICODE")
        ADD_DEFINITIONS("-DUNICODE")
	ENDIF()

    # CLang specific Compiler Options
    IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

    # GCC specific Compiler Options
    ELSE()
        ADD_DEFINITIONS("-frounding-math -fsignaling-nans")
	
	IF((NOT CMAKE_GENERATOR STREQUAL Xcode) AND (NOT MINGW))
		# Debug compiler flags
		SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -no-pie -fno-pie")

		# Release compiler flags
		SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -no-pie -fno-pie")

		# Release with debug info compiler flags
		SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -no-pie -fno-pie")

#                IF(NOT MINGW)
#                        set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -rdynamic")
#                        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -rdynamic")
#                ENDIF()
	ENDIF()
    ENDIF()

	IF(WANT_USE_STREFLOP)
		OPTION(FORCE_STREFLOP_SOFTWRAPPER "Set the streflop library to be forced to use the software emulator" OFF)
		IF(NOT FORCE_MAX_SSE_LEVEL AND NOT FORCE_STREFLOP_SOFTWRAPPER)
			SET(FORCE_MAX_SSE_LEVEL "1" CACHE STRING "Set the max SSE level to use if supported (0-3)")
		ENDIF()

		IF(NOT FORCE_STREFLOP_SOFTWRAPPER)
			MESSAGE(STATUS "*NOTE: Checking for max SSE LEVEL [${FORCE_MAX_SSE_LEVEL}]")
			special_check_for_sse( ${FORCE_MAX_SSE_LEVEL} )
		ENDIF()

		ADD_DEFINITIONS("-DUSE_STREFLOP -DSTREFLOP_RANDOM_GEN_SIZE=32 -DLIBM_COMPILING_FLT32 -DN_SPECIALIZED=32")

		IF(HAS_SSE_EXTENSIONS AND NOT ${FORCE_MAX_SSE_LEVEL} MATCHES "0" AND NOT FORCE_STREFLOP_SOFTWRAPPER)
			ADD_DEFINITIONS("-DSTREFLOP_SSE")
			MESSAGE(STATUS "*NOTE: using SSE for STREFLOP.")
		ELSE()
			IF(NOT FORCE_STREFLOP_SOFTWRAPPER)
				special_check_for_x87()
			ENDIF()

			IF(HAS_X87_SUPPORT AND NOT FORCE_STREFLOP_SOFTWRAPPER)
				ADD_DEFINITIONS("-DSTREFLOP_X87")
				MESSAGE(STATUS "*NOTE: using X87 for STREFLOP.")
			ELSE()
				ADD_DEFINITIONS("-DSTREFLOP_SOFT")
				MESSAGE(STATUS "*NOTE: using SOFT emulation for STREFLOP.")
			ENDIF()
		ENDIF()
	ELSE()
		# We are temporarily trying to build without streflop. If out-of-syncs
		# become a problem, we'll probably replace streflop with libmpc or mpf4
		#
		# MESSAGE(STATUS "*WARNING: Disabled use of STREFLOP! Out of synchs may occur")
		MESSAGE(STATUS "libstreflop disabled")
	ENDIF()

        include(CheckCXXSourceRuns)

        check_cxx_source_runs("
        #include <execinfo.h>
        #include <stdio.h>
        int main()
        {
	const size_t max_depth = 6;
	void *stack_addrs[max_depth];
	size_t stack_depth = backtrace(stack_addrs, max_depth);
        }"
        HAS_GCC_BACKTRACE)

        IF(HAS_GCC_BACKTRACE)
            message(STATUS "Found GCC backtrace lib, will support backtraces")
            ADD_DEFINITIONS(-DHAS_GCC_BACKTRACE)
        ELSE()
            message(STATUS "**WARNING DID NOT Find GCC backtrace lib")
        ENDIF()

	# Debug compiler flags
	SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3")

	# Release compiler flags
	SET(CMAKE_CXX_FLAGS_RELEASE "-O3 ${CMAKE_CXX_FLAGS_RELEASE} -O3")
	IF(NOT CMAKE_GENERATOR STREQUAL Xcode)
		SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -s")  ## Strip binary
	ENDIF()

	# Release with debug info compiler flags
	SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 ${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -g -O3")

	# Release minimum size compiler flags
	IF(NOT CMAKE_GENERATOR STREQUAL Xcode)
		SET(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "${CMAKE_EXE_LINKER_FLAGS_MINSIZEREL} -s")  ## Strip binary
	ENDIF()

	# see if this fixes compile issue for tomreyn: libpthread.so.0: error adding symbols: DSO missing from command line
	IF(UNIX)
		MESSAGE(STATUS "*NOTE: Apply fix for: libpthread.so.0: error adding symbols: DSO missing from command line")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
		set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -pthread")
		SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -pthread")
		SET(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "${CMAKE_EXE_LINKER_FLAGS_MINSIZEREL} -pthread")
	ENDIF()

	IF(NOT INSTALL_DIR_BIN)
		SET(INSTALL_DIR_BIN "${CMAKE_INSTALL_PREFIX}/games/" CACHE PATH "The installation path for binaries")
	ENDIF()
# The data dir will get defined as a macro at compile-time
	IF(NOT INSTALL_DIR_DATA)
		SET(INSTALL_DIR_DATA "${CMAKE_INSTALL_PREFIX}/share/glest/" CACHE PATH "The installation path for data files")
	ENDIF()
	SET(INSTALL_DIR_INI "${INSTALL_DIR_DATA}")
	IF(NOT INSTALL_DIR_DESKTOP)
		SET(INSTALL_DIR_DESKTOP "${CMAKE_INSTALL_PREFIX}/applications/" CACHE PATH "The installation path for desktop files")
	ENDIF()
	IF(NOT INSTALL_DIR_ICON)
		SET(INSTALL_DIR_ICON "${CMAKE_INSTALL_PREFIX}/share/pixmaps/" CACHE PATH "The installation path for icon files")
	ENDIF()
	IF(NOT INSTALL_DIR_MAN)
		SET(INSTALL_DIR_MAN "${CMAKE_INSTALL_PREFIX}/share/man/man6/" CACHE PATH "The installation path for manpage files")
	ENDIF()

	string(TOUPPER "${CMAKE_BUILD_TYPE}" GLEST_BUILD_TYPE)

	# We do some funky character escaping to get the right stuff written out to
	# the final Makefile so we get the GIT Global Revsion #
	string(REPLACE "'" "\"" CMAKE_CXX_FLAGS_${GLEST_BUILD_TYPE} "${CMAKE_CXX_FLAGS_${GLEST_BUILD_TYPE}}")

	message(STATUS "CMAKE_CXX_FLAGS_${GLEST_BUILD_TYPE}: ${CMAKE_CXX_FLAGS_${GLEST_BUILD_TYPE}}")

	# Win32 specific Compiler Flags
	IF(WIN32)
		ADD_DEFINITIONS("-D_WINDOWS -D_WIN32 -D_STDCALL_SUPPORTED -D_M_IX86 -DXML_LIBRARY -D_LIB -DCURL_STATICLIB")
	ENDIF()
ENDIF()

IF(UNIX AND NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
	OPTION(WANT_DEPRECATION_WARNINGS "Want to see warnings related with deprecated code parts." OFF)
	# We don't wanna see bug reports with deprecation warnings from OSes where game isn't
	# actively developed, and where usually those warnings can make "make log" completely unreadable.
	# Main targets are: bsd and macos

	MARK_AS_ADVANCED(CLEAR wxWidgets_CONFIG_EXECUTABLE)
	# This variable may be sometimes necessary to set manually.
ELSE()
	OPTION(WANT_DEPRECATION_WARNINGS "Want to see warnings related with deprecated code parts." ON)
ENDIF()
IF(NOT WANT_DEPRECATION_WARNINGS)
	ADD_DEFINITIONS(-Wno-deprecated -Wno-deprecated-declarations)
ENDIF()
MARK_AS_ADVANCED(WANT_DEPRECATION_WARNINGS)

SET(SDL_WINDOWS_DIR_DINC "SDL-2.0.x")
SET(SDL_VERSION_NAME "SDL2")
SET(SDL_VERSION_SNAME "sdl")

# output binaries to the top level of the build directory
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

# Check if sources exist
IF(EXISTS "${PROJECT_SOURCE_DIR}/source/")
	MESSAGE(STATUS "**Found game source code.")

	ADD_SUBDIRECTORY( ${PROJECT_SOURCE_DIR}/source/shared_lib )
	ADD_SUBDIRECTORY( ${PROJECT_SOURCE_DIR}/source/game )
	#if(wxWidgets_FOUND)
		ADD_SUBDIRECTORY( ${PROJECT_SOURCE_DIR}/source/map_editor )
		ADD_SUBDIRECTORY( ${PROJECT_SOURCE_DIR}/source/g3d_viewer )
	#else()
	#  MESSAGE(STATUS "WARNING... the following game tools will NOT be built since we cannot find wxWidgets on this machine")
	#  MESSAGE(STATUS "map editor, g3d viewer")
	#endif()
ENDIF()

#
# Check if data exists
# The option to actually install data is set in the data CMakeLists.txt
# file. It defaults to OFF. The INSTALL_DIR_DATA path is always set
# regardless (because of the rules above) and is defined as the macro DATADIR
# at compile-time. That allows the binary to find the data no matter
# where it is, and whether or not it has actually been installed
#
IF(EXISTS "${PROJECT_SOURCE_DIR}/../glest-data/CMakeLists.txt")
    MESSAGE(STATUS "**Found game data.")
	# using CMAKE_BINARY_DIR as last parameter will output cmake files into the same
	# directory as the source build.
	ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/../glest-data ${CMAKE_BINARY_DIR}/data)
ENDIF()

IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    MESSAGE(WARNING ">> CLANG is NOT currently compatible as it does not support the following essential GCC compiler settings: -frounding-math -fsignaling-nans")
ENDIF()

# FIXME: This should output all defines. For example, DATADIR is defined in
# the game source and sharedlib cmake file as well
get_directory_property( DirDefs DIRECTORY ${CMAKE_SOURCE_DIR} COMPILE_DEFINITIONS )
foreach( d ${DirDefs} )
    message( STATUS "=====> Found Define: " ${d} )
endforeach()

MARK_AS_ADVANCED(${SDL_VERSION_NAME}MAIN_LIBRARY)
MARK_AS_ADVANCED(${SDL_VERSION_NAME}_INCLUDE_DIR)
MARK_AS_ADVANCED(${SDL_VERSION_NAME}_LIBRARY)
MARK_AS_ADVANCED(wxWidgets_CONFIG_EXECUTABLE)
MARK_AS_ADVANCED(wxWidgets_wxrc_EXECUTABLE)
MARK_AS_ADVANCED(wxWidgets_USE_DEBUG)
