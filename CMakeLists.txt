CMAKE_MINIMUM_REQUIRED( VERSION 2.8.2 )
PROJECT( ZetaGlest )

#SET(CMAKE_VERBOSE_MAKEFILE ON)

#
# *NOTE: For now we assume some variation of GCC Compiler (or MingW for Windows binaries)
# VC++ users should not use CMake yet but rather the build-zg.bat file in mk/windows
#

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
IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    SET(CMAKE_COMPILER_IS_GNUCXX "YES")
#        ADD_DEFINITIONS("-Qunused-arguments -Wno-switch")
    ADD_DEFINITIONS("-Wno-switch")
ENDIF()

OPTION(BUILD_ZETAGLEST_MODEL_IMPORT_EXPORT_TOOLS "Build model import/export tools" ON)
OPTION(BUILD_ZETAGLEST_MODEL_VIEWER "Build model viewer" ON)
OPTION(BUILD_ZETAGLEST_MAP_EDITOR "Build map editor" ON)
OPTION(BUILD_ZETAGLEST "Build ZetaGlest" ON)
OPTION(BUILD_ZETAGLEST_TESTS "Build ZetaGlest Unit Tests" OFF)
OPTION(WANT_STATIC_LIBS "Builds as many static libs as possible." OFF)
OPTION(WANT_USE_VLC "Use libVLC to play videos." ON)
OPTION(WANT_USE_OpenSSL "Use libOpenSSL during CURL linking." ON)
OPTION(WANT_USE_FriBiDi "Enable libFriBIDi support." ON)
OPTION(WANT_USE_GoogleBreakpad "Enable GoogleBreakpad support." ON)
OPTION(WANT_USE_STREFLOP "Use the library streflop." ON)
OPTION(WANT_USE_XercesC "Enable libXercesC support." OFF)

include(${CMAKE_SOURCE_DIR}/mk/cmake/Modules/SpecialMacros.cmake)
include(${CMAKE_SOURCE_DIR}/mk/cmake/Modules/ReqVersAndStaticConf.cmake)
MESSAGE(STATUS "=====================================================================")

SET(PKG_NAME "zetaglest")
# read version
FILE(READ ${PROJECT_SOURCE_DIR}/source/glest_game/facilities/game_util.cpp ZG_VERSION_H_CONTENTS)
MESSAGE(STATUS "Determining version number system type to use:")
SET(Begin_otv_string "string glestVersionString")
STRING(REGEX MATCH "${Begin_otv_string}[ \t]*=[ \t]*\"[ \t]*v[ \t]*([0-9][^\\.]*)(\\.)([^\\.]*)(\\.)([^\"\\.;]*)\";" _threePartMatch "${ZG_VERSION_H_CONTENTS}")
STRING(REGEX MATCH "${Begin_otv_string}[ \t]*=[ \t]*\"[ \t]*v[ \t]*([0-9][^\\.]*)(\\.)([^\"\\.;]*)\";" _twoPartMatch "${ZG_VERSION_H_CONTENTS}")
STRING(REGEX MATCH "${Begin_otv_string}[ \t]*=[ \t]*\"[ \t]*v[ \t]*([0-9][^\"\\.;]*)\";" _onePartMatch "${ZG_VERSION_H_CONTENTS}")
IF(_threePartMatch)
	MESSAGE(STATUS "** Trying 3 part versioning ")
	STRING(REGEX REPLACE "[^=]*=[ \t]*\"[ \t]*v[ \t]*([0-9][^\\.]*)\\.[^\\.]*\\..*" "\\1" VER_MAJOR "${_threePartMatch}")
	STRING(REGEX REPLACE "[^=]*=[ \t]*\"[ \t]*v[ \t]*[0-9][^\\.]*\\.([^\\.]*)\\..*" "\\1" VER_MINOR "${_threePartMatch}")
	STRING(REGEX REPLACE "[^=]*=[ \t]*\"[ \t]*v[ \t]*[0-9][^\\.]*\\.[^\\.]*\\.([^\"\\.;]*).*" "\\1" VER_PATCH "${_threePartMatch}")
	SET(ZETAGLEST_VERSION "${VER_MAJOR}.${VER_MINOR}.${VER_PATCH}")
ELSEIF(_twoPartMatch)
	MESSAGE(STATUS "** Trying 2 part versioning ")
	STRING(REGEX REPLACE "[^=]*=[ \t]*\"[ \t]*v[ \t]*([0-9][^\\.]*)\\..*" "\\1" VER_MAJOR "${_twoPartMatch}")
	STRING(REGEX REPLACE "[^=]*=[ \t]*\"[ \t]*v[ \t]*[0-9][^\\.]*\\.([^\"\\.;]*).*" "\\1" VER_MINOR "${_twoPartMatch}")
	SET(VER_PATCH "0")
	SET(ZETAGLEST_VERSION "${VER_MAJOR}.${VER_MINOR}")
ELSEIF(_onePartMatch)
	MESSAGE(STATUS "** Trying 1 part versioning ")
	STRING(REGEX REPLACE "[^=]*=[ \t]*\"[ \t]*v[ \t]*([0-9][^\"\\.;]*).*" "\\1" VER_MAJOR "${_onePartMatch}")
	SET(VER_MINOR "0")
	SET(VER_PATCH "0")
	SET(ZETAGLEST_VERSION "${VER_MAJOR}")
ENDIF()
FOREACH(ver_var VER_MAJOR;VER_MINOR;VER_PATCH;ZETAGLEST_VERSION)
	STRING(REGEX REPLACE "[ \t]" "" "${ver_var}" "${${ver_var}}")
ENDFOREACH()
MESSAGE(STATUS "Detected ZetaGlest Version is [v${ZETAGLEST_VERSION}] ")

SET(PIC_FLAG "${PIC_FLAG} -fPIC")
IF(WANT_STATIC_LIBS AND "${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	# CMAKE_SIZEOF_VOID_P=8 => 64bit
	ADD_DEFINITIONS("${PIC_FLAG}")
ENDIF()

## Compiler flags, CPACK configuration and other Apple specific code.
IF(APPLE)
	include(${PROJECT_SOURCE_DIR}/mk/macos/CMakeLists.txt)
ENDIF(APPLE)

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

#                IF(NOT MINGW)
#                        set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -rdynamic")
#                        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -rdynamic")
#                ENDIF()
    ENDIF()

	#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    #MESSAGE(STATUS "*TEST: Checking for max SSE LEVEL [${FORCE_MAX_SSE_LEVEL}]")

	OPTION(FORCE_STREFLOP_SOFTWRAPPER "Set the streflop library to be forced to use the software emulator" OFF)
    IF(NOT FORCE_MAX_SSE_LEVEL AND NOT FORCE_STREFLOP_SOFTWRAPPER)
        SET(FORCE_MAX_SSE_LEVEL "1" CACHE STRING "Set the max SSE level to use if supported (0-3)")
    ENDIF()

    IF(NOT FORCE_STREFLOP_SOFTWRAPPER)
        MESSAGE(STATUS "*NOTE: Checking for max SSE LEVEL [${FORCE_MAX_SSE_LEVEL}]")
        special_check_for_sse( ${FORCE_MAX_SSE_LEVEL} )
    ENDIF()

	IF(WANT_USE_STREFLOP)
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
		MESSAGE(STATUS "*WARNING: Disabled use of STREFLOP! Out of synchs may occur")
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
	SET(CMAKE_CXX_FLAGS_RELEASE "-O3 ${CMAKE_CXX_FLAGS_RELEASE} -O3 ")
	IF(NOT CMAKE_GENERATOR STREQUAL Xcode)
		SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -s")  ## Strip binary
	ENDIF()

	# Release with debug info compiler flags
	SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 ${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -g -O3 ")

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

	IF(NOT ZETAGLEST_BIN_INSTALL_PATH)
		SET(ZETAGLEST_BIN_INSTALL_PATH "${CMAKE_INSTALL_PREFIX}/games" CACHE STRING "The installation path for binaries")
	ENDIF()
	IF(NOT ZETAGLEST_DATADIR)
		SET(ZETAGLEST_DATADIR "${CMAKE_INSTALL_PREFIX}/share/zetaglest/" CACHE STRING "The installation path for data files")
	ENDIF()
	SET(ZETAGLEST_INI_INSTALL_PATH "${ZETAGLEST_DATADIR}")
	IF(NOT ZETAGLEST_DESKTOP_INSTALL_PATH)
		SET(ZETAGLEST_DESKTOP_INSTALL_PATH "${CMAKE_INSTALL_PREFIX}/applications/" CACHE STRING "The installation path for desktop files")
	ENDIF()
	IF(NOT ZETAGLEST_ICON_INSTALL_PATH)
		SET(ZETAGLEST_ICON_INSTALL_PATH "${CMAKE_INSTALL_PREFIX}/share/pixmaps/" CACHE STRING "The installation path for icon files")
	ENDIF()
	IF(NOT ZETAGLEST_MANPAGE_INSTALL_PATH)
		SET(ZETAGLEST_MANPAGE_INSTALL_PATH "${CMAKE_INSTALL_PREFIX}/share/man/man6/" CACHE STRING "The installation path for manpage files")
	ENDIF()

	string(TOUPPER "${CMAKE_BUILD_TYPE}" ZG_BUILD_TYPE)

	SET(CMAKE_CXX_FLAGS_{ZG_BUILD_TYPE} "${CMAKE_CXX_FLAGS_${ZG_BUILD_TYPE}} -DDATADIR=${ZETAGLEST_DATADIR}")

	IF(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD" OR
			${CMAKE_SYSTEM_NAME} MATCHES "OpenBSD" OR
			${CMAKE_SYSTEM_NAME} MATCHES "NetBSD")
		SET (CMAKE_CXX_COMPILER "eg++" CACHE STRING "On BSD systems, the compiler to use")
	ENDIF()

	# We do some funky character escaping to get the right stuff written out to
	# the final Makefile so we get the GIT Global Revsion #
	string(REPLACE "'" "\"" CMAKE_CXX_FLAGS_${ZG_BUILD_TYPE} "${CMAKE_CXX_FLAGS_${ZG_BUILD_TYPE}}")

	message(STATUS "CMAKE_CXX_FLAGS_${ZG_BUILD_TYPE}: ${CMAKE_CXX_FLAGS_${ZG_BUILD_TYPE}}")

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

IF(WIN32)
	SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}
		${PROJECT_SOURCE_DIR}/source/win32_deps/lib
		${PROJECT_SOURCE_DIR}/source/win32_deps/xerces-c-src_2_8_0/lib
		${PROJECT_SOURCE_DIR}/source/win32_deps/wxWidgets-2.8.10/lib)

	SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH}
		${PROJECT_SOURCE_DIR}/source/win32_deps/include
		${PROJECT_SOURCE_DIR}/source/win32_deps/openal-soft-1.12.854/include
		${PROJECT_SOURCE_DIR}/source/win32_deps/openal-soft-1.12.854
		${PROJECT_SOURCE_DIR}/source/win32_deps/xerces-c-src_2_8_0/include
		${PROJECT_SOURCE_DIR}/source/win32_deps/libogg-1.2.1/include
		${PROJECT_SOURCE_DIR}/source/win32_deps/lua-5.1/src
		${PROJECT_SOURCE_DIR}/source/win32_deps/jpeg-8b
		${PROJECT_SOURCE_DIR}/source/win32_deps/lpng141
		${PROJECT_SOURCE_DIR}/source/win32_deps/zlib-1.2.5
		${PROJECT_SOURCE_DIR}/source/win32_deps/curl-7.21.3/include
		${PROJECT_SOURCE_DIR}/source/win32_deps/${SDL_WINDOWS_DIR_DINC}/include
		${PROJECT_SOURCE_DIR}/source/win32_deps/wxWidgets-2.8.10/include)

	link_directories(${PROJECT_SOURCE_DIR}/source/win32_deps/lib)
	link_directories(${PROJECT_SOURCE_DIR}/source/win32_deps/xerces-c-src_2_8_0/lib)
	link_directories(${PROJECT_SOURCE_DIR}/source/win32_deps/wxWidgets-2.8.10/lib)
	include_directories("${PROJECT_SOURCE_DIR}/source/win32_deps/Microsoft\ DirectX\ SDK \(November 2007\)/Include")
	include_directories(${PROJECT_SOURCE_DIR}/source/win32_deps/openal-soft-1.12.854/include)
ENDIF()

# Check if sources exist
IF(EXISTS "${PROJECT_SOURCE_DIR}/source/")
	MESSAGE(STATUS "**Found game source code.")

	ADD_SUBDIRECTORY( ${PROJECT_SOURCE_DIR}/source/shared_lib )
	ADD_SUBDIRECTORY( ${PROJECT_SOURCE_DIR}/source/glest_game )
	#if(wxWidgets_FOUND)
		ADD_SUBDIRECTORY( ${PROJECT_SOURCE_DIR}/source/glest_map_editor )
		ADD_SUBDIRECTORY( ${PROJECT_SOURCE_DIR}/source/g3d_viewer )
	#else()
	#  MESSAGE(STATUS "WARNING... the following game tools will NOT be built since we cannot find wxWidgets on this machine")
	#  MESSAGE(STATUS "map editor, g3d viewer")
	#endif()
	ADD_SUBDIRECTORY( ${PROJECT_SOURCE_DIR}/source/tools/glexemel )

    ADD_SUBDIRECTORY( ${PROJECT_SOURCE_DIR}/source/tests )
ENDIF()

# Check if data exist
IF(EXISTS "${PROJECT_SOURCE_DIR}/data/glest_game/CMakeLists.txt")
    MESSAGE(STATUS "**Found game data.")
	ADD_SUBDIRECTORY( ${PROJECT_SOURCE_DIR}/data/glest_game )
ENDIF()

#get_directory_property( DirDefs COMPILE_DEFINITIONS )
#MESSAGE(STATUS ">>>> NOTICE Compiler definitions used: ${DirDefs}")
#MESSAGE(STATUS "END of compile defs...")
IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    MESSAGE(WARNING ">> CLANG is NOT currently compatible as it does not support the following essential GCC compiler settings: -frounding-math -fsignaling-nans")
ENDIF()

get_directory_property( DirDefs DIRECTORY ${CMAKE_SOURCE_DIR} COMPILE_DEFINITIONS )
foreach( d ${DirDefs} )
    message( STATUS "=====> Found Define: " ${d} )
endforeach()
#MESSAGE( STATUS "=====> DirDefs: " ${DirDefs} )
#MESSAGE(STATUS "*** Compiler definitions are [${COMPILE_DEFINITIONS}]")

MARK_AS_ADVANCED(${SDL_VERSION_NAME}MAIN_LIBRARY)
MARK_AS_ADVANCED(${SDL_VERSION_NAME}_INCLUDE_DIR)
MARK_AS_ADVANCED(${SDL_VERSION_NAME}_LIBRARY)
MARK_AS_ADVANCED(wxWidgets_CONFIG_EXECUTABLE)
MARK_AS_ADVANCED(wxWidgets_wxrc_EXECUTABLE)
MARK_AS_ADVANCED(wxWidgets_USE_DEBUG)
