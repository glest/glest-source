# common libraries

OPTION(BUILD_MAP_EDITOR "Build map editor" ON)
SET(TARGET_NAME "zetaglest_editor")
MESSAGE(STATUS "Build ${TARGET_NAME} = ${BUILD_MAP_EDITOR}")

IF(BUILD_MAP_EDITOR)
	SET(EXTERNAL_LIBS "")
	SET(TARGET_NAME_MANPAGE "${TARGET_NAME}.6")
	ADD_DEFINITIONS("-std=c++11")

	FIND_PACKAGE(${SDL_VERSION_NAME} REQUIRED)
	INCLUDE_DIRECTORIES(${${SDL_VERSION_NAME}_INCLUDE_DIR})
	SET(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${${SDL_VERSION_NAME}_LIBRARY})

	FIND_PACKAGE(OpenGL REQUIRED)
	INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
	SET(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${OPENGL_LIBRARY})

	IF(STATIC_wxWidgets)
		SET(wxWidgets_USE_STATIC ON)
		# ^ This is not needed here (once, globally is enough) if every find run returns the same status.
		# With wx this is not so 100% sure.
	ENDIF()
	# It was noticed that when using MinGW gcc it is essential that 'core' is mentioned before 'base'.
	# Optimal order most likely is gl > core > base, in some cases it may do difference.
	FIND_PACKAGE(wxWidgets REQUIRED COMPONENTS gl core base)
	IF(UNIX)
		# wxWidgets include (this will do all the magic to configure everything)
		INCLUDE( ${wxWidgets_USE_FILE} )

		SET(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${wxWidgets_LIBRARIES})

		IF(STATIC_wxWidgets)
			IF(wxWidgets_USE_STATIC)
				MESSAGE(STATUS "==========> wxWidgets using STATIC libs:")
			ELSE()
				MESSAGE(STATUS "==========> wxWidgets STATIC libs NOT found:")
			ENDIF()
		ENDIF()
		MESSAGE(STATUS " wxWidgets: ${wxWidgets_INCLUDE_DIRS} ;/;  ${wxWidgets_LIBRARIES}")
	ENDIF()

    find_package(PkgConfig REQUIRED)
    IF(FORCE_STREFLOP_SOFTWRAPPER)
        pkg_search_module(STREFLOP streflop-soft)
    ELSE()
        IF(HAS_SSE_EXTENSIONS AND NOT ${FORCE_MAX_SSE_LEVEL} MATCHES "0")
            pkg_search_module(STREFLOP streflop-sse)
        ELSE()
            IF(HAS_X87_SUPPORT)
                pkg_search_module(STREFLOP streflop-x87)
            ELSE()
                pkg_search_module(STREFLOP streflop-soft)
            ENDIF()
        ENDIF()
    ENDIF()
    IF(NOT STREFLOP_FOUND)
        pkg_search_module(STREFLOP streflop)
    ENDIF()
    MESSAGE(STATUS "Search for Library STREFLOP result = ${STREFLOP_FOUND} libs: ${STREFLOP_LIBRARIES} include dirs: ${STREFLOP_INCLUDE_DIRS}")

    IF(FORCE_EMBEDDED_LIBS)
        SET(STREFLOP_FOUND OFF)
        MESSAGE(STATUS "FORCING USE of EMBEDDED Libraries...")
    ENDIF()

    IF(WANT_USE_STREFLOP)
        IF(STREFLOP_FOUND)
            INCLUDE_DIRECTORIES(${STREFLOP_INCLUDE_DIRS} ${STREFLOP_INCLUDE_DIRS}/streflop)
            SET(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${STREFLOP_LIBRARIES})

		    ADD_DEFINITIONS("-DUSE_STREFLOP_PKG")
        ENDIF()
    ENDIF()

	#########################################################################################
	# megaglest map editor

	SET(DIRS_WITH_SRC
	    . )

	SET(GLEST_MAIN_INCLUDE_ROOT "../glest_game/")
	SET(GLEST_LIB_INCLUDE_ROOT "../shared_lib/include/")

	SET(GLEST_LIB_INCLUDE_DIRS
	    ${GLEST_LIB_INCLUDE_ROOT}platform/common
	#    ${GLEST_LIB_INCLUDE_ROOT}platform/${SDL_VERSION_SNAME}
	    ${GLEST_LIB_INCLUDE_ROOT}platform/posix
	    ${GLEST_LIB_INCLUDE_ROOT}util
	    ${GLEST_LIB_INCLUDE_ROOT}graphics
	    ${GLEST_LIB_INCLUDE_ROOT}graphics/gl
	    ${GLEST_LIB_INCLUDE_ROOT}map
	    ${GLEST_MAIN_INCLUDE_ROOT}facilities
	    ${GLEST_MAIN_INCLUDE_ROOT}game
            ${GLEST_LIB_INCLUDE_ROOT}xml/rapidxml
	    ${GLEST_MAIN_INCLUDE_ROOT}global)

	IF(WANT_USE_STREFLOP AND NOT STREFLOP_FOUND)
		SET(GLEST_LIB_INCLUDE_DIRS
			${GLEST_LIB_INCLUDE_DIRS}
    			${GLEST_LIB_INCLUDE_ROOT}streflop)
	ENDIF()

	INCLUDE_DIRECTORIES( ${GLEST_LIB_INCLUDE_DIRS} )

	IF(WIN32)
		INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/source/shared_lib/include/platform/win32)
	ENDIF()
	INCLUDE_DIRECTORIES( ${GLEST_LIB_INCLUDE_ROOT}platform/${SDL_VERSION_SNAME} )

	SET(ZG_SOURCE_FILES "../glest_game/global/config.cpp")

	FOREACH(DIR IN LISTS DIRS_WITH_SRC)
		INCLUDE_DIRECTORIES( ${DIR} )

		set(SRC_DIR_TO_GLOB ${DIR})
		FILE(GLOB SRC_FILES_FROM_THIS_DIR ${SRC_DIR_TO_GLOB}/*.cpp)
		SET(ZG_SOURCE_FILES ${ZG_SOURCE_FILES} ${SRC_FILES_FROM_THIS_DIR})
		FILE(GLOB INCLUDE_FILES_FROM_THIS_DIR ${SRC_DIR_TO_GLOB}/*.h)
		SET(ZG_INCLUDE_FILES ${ZG_INCLUDE_FILES} ${INCLUDE_FILES_FROM_THIS_DIR})
		IF(APPLE)
			FILE(GLOB SRC_FILES_FROM_THIS_DIR ${SRC_DIR_TO_GLOB}/*.mm)
			#MESSAGE(STATUS "SRC_FILES_FROM_THIS_DIR: ${SRC_FILES_FROM_THIS_DIR}")
			SET(ZG_SOURCE_FILES ${ZG_SOURCE_FILES} ${SRC_FILES_FROM_THIS_DIR})
			FILE(GLOB SRC_FILES_FROM_THIS_DIR ${SRC_DIR_TO_GLOB}/*.m)
			#MESSAGE(STATUS "SRC_FILES_FROM_THIS_DIR: ${SRC_FILES_FROM_THIS_DIR}")
			SET(ZG_SOURCE_FILES ${ZG_SOURCE_FILES} ${SRC_FILES_FROM_THIS_DIR})
			ENDIF(APPLE)
	ENDFOREACH(DIR)

	SET_SOURCE_FILES_PROPERTIES(${ZG_INCLUDE_FILES} PROPERTIES HEADER_FILE_ONLY 1)

	ADD_EXECUTABLE(${TARGET_NAME} ${ZG_SOURCE_FILES} ${ZG_INCLUDE_FILES})

	SET(MG_STREFLOP "")
	IF(WANT_USE_STREFLOP)
		SET(MG_STREFLOP "streflop")
	ENDIF()

	IF(WIN32)
		TARGET_LINK_LIBRARIES(${TARGET_NAME} stdc++ gcc odbc32 wsock32 winspool winmm shell32 comctl32 ctl3d32  advapi32 wsock32 opengl32 glu32 ole32 oleaut32 uuid mingw32 ddraw dsound dxguid ws2_32 iphlpapi wsock32 libogg libvorbis libvorbisfile zlib jpeg libpng xerces-c2_8_0 OpenAL32 libcurl winmm gdi32 opengl32 glu32 ${SDL_VERSION_NAME} ${SDL_VERSION_NAME}main lua5.1 ${MG_STREFLOP} libzetaglest stdc++ moldname mingwex msvcrt user32 kernel32)
	ENDIF()

	IF(WANT_USE_STREFLOP AND NOT STREFLOP_FOUND)
		TARGET_LINK_LIBRARIES(${TARGET_NAME} ${MG_STREFLOP})
	ENDIF()

	TARGET_LINK_LIBRARIES(${TARGET_NAME} libzetaglest)
	TARGET_LINK_LIBRARIES(${TARGET_NAME} ${EXTERNAL_LIBS})

	# Installation of the program
	INSTALL(TARGETS
		${TARGET_NAME}
		DESTINATION "${INSTALL_DIR_BIN}")
		# Installation of the program manpage file
	INSTALL(FILES
		"${PROJECT_SOURCE_DIR}/man/${TARGET_NAME_MANPAGE}"
		DESTINATION ${INSTALL_DIR_MAN})

		# Installation of the program config and image files
	INSTALL(FILES
		"${PROJECT_SOURCE_DIR}/mk/shared/map_editor.ico"
		DESTINATION ${INSTALL_DIR_INI})

ENDIF()
