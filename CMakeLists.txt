PROJECT (pocketbook_doom)
CMAKE_MINIMUM_REQUIRED (VERSION 2.6.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_C_STANDARD 99)

IF (NOT PLATFORM)
	SET (PLATFORM FC)
ENDIF (NOT PLATFORM)

IF (PLATFORM STREQUAL "NX")
	SET (TOOLCHAIN_PATH "../../PBSDK")
	SET (TOOLCHAIN_PREFIX "arm-linux")
	SET (TOOLCHAIN_INSTALL "")
	ADD_DEFINITIONS(-DPLATFORM_NX)
ELSE ()
	SET (TOOLCHAIN_PATH "../../FRSCSDK")
	SET (TOOLCHAIN_PREFIX "arm-none-linux-gnueabi")
	SET (TOOLCHAIN_INSTALL "sysroot/usr")
	ADD_DEFINITIONS(-DPLATFORM_FC)
ENDIF (PLATFORM STREQUAL "NX")
#SET (CMAKE_VERBOSE_MAKEFILE ON)

IF (NOT TARGET_TYPE)
	SET (TARGET_TYPE Linux)
ENDIF (NOT TARGET_TYPE)

IF (NOT CMAKE_BUILD_TYPE)
	SET (CMAKE_BUILD_TYPE Debug)
ENDIF (NOT CMAKE_BUILD_TYPE)


IF (TARGET_TYPE STREQUAL "ARM")
	SET(CMAKE_INSTALL_PREFIX "${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}/${TOOLCHAIN_INSTALL}" CACHE PATH "Install path prefix" FORCE)

	SET (CMAKE_C_COMPILER ${CMAKE_CURRENT_SOURCE_DIR}/${TOOLCHAIN_PATH}/bin/${TOOLCHAIN_PREFIX}-gcc)
	SET (CMAKE_CXX_COMPILER ${CMAKE_CURRENT_SOURCE_DIR}/${TOOLCHAIN_PATH}/bin/${TOOLCHAIN_PREFIX}-g++)
	SET (CMAKE_LINK ${CMAKE_CURRENT_SOURCE_DIR}/${TOOLCHAIN_PATH}/bin/${TOOLCHAIN_PREFIX}-g++)
	SET (CMAKE_ARR ${CMAKE_CURRENT_SOURCE_DIR}/${TOOLCHAIN_PATH}/bin/${TOOLCHAIN_PREFIX}-arr)
	SET (CMAKE_STRIP ${CMAKE_CURRENT_SOURCE_DIR}/${TOOLCHAIN_PATH}/bin/${TOOLCHAIN_PREFIX}-strip)

	SET (TARGET_INCLUDE ${TOOLCHAIN_PATH}/include)
	SET (TARGET_LIB pthread inkview freetype z)
ELSE()
	SET(CMAKE_INSTALL_PREFIX "${TOOLCHAIN_PATH}" CACHE PATH "Install path prefix" FORCE)

	FIND_PACKAGE (Freetype REQUIRED)
	FIND_PACKAGE (JPEG REQUIRED)
	FIND_PACKAGE (ZLIB REQUIRED)
	FIND_PACKAGE (CURL REQUIRED)
	FIND_PACKAGE (GTK2 REQUIRED)
	SET (TARGET_INCLUDE ${CMAKE_INSTALL_PREFIX}/include ${FREETYPE_INCLUDE_DIRS} ${JPEG_INCLUDE_DIRS} ${ZLIB_INCLUDE_DIRS} ${CURL_INCLUDE_DIRS})
	SET (TARGET_LIB c m pthread inkview ${FREETYPE_LIBRARIES} ${JPEG_LIBRARIES} ${ZLIB_LIBRARIES} ${GTK2_LIBRARIES} ${CURL_LIBRARIES}) 
	LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/${CMAKE_INSTALL_PREFIX}/lib)
ENDIF(TARGET_TYPE STREQUAL "ARM")

IF (CMAKE_BUILD_TYPE STREQUAL "Debug")

	IF (TARGET_TYPE STREQUAL "Linux")
		MESSAGE (STATUS "Build for Linux Debug")
		SET (CMAKE_C_FLAGS_DEBUG "-DDEBUG -W -Wall -Wextra -O0 -g3 -DIVSAPP -Wint-conversion")
		SET (CMAKE_CXX_FLAGS_DEBUG "-DDEBUG -W -Wall -Wextra -O0 -g3 -DIVSAPP -Wint-conversion")
	ENDIF (TARGET_TYPE STREQUAL "Linux")

	IF (TARGET_TYPE STREQUAL "Windows")
		MESSAGE (STATUS "Build for Windows Debug")
		SET (CMAKE_C_FLAGS_DEBUG "-DDEBUG -W -Wall -Wextra -O0 -g3 -DIVSAPP")
		SET (CMAKE_CXX_FLAGS_DEBUG "-DDEBUG -W -Wall -Wextra -O0 -g3 -DIVSAPP")
	ENDIF (TARGET_TYPE STREQUAL "Windows")

	IF (TARGET_TYPE STREQUAL "ARM")
		MESSAGE (STATUS "Build for ARM Debug")
		SET (CMAKE_C_FLAGS_DEBUG "-DDEBUG -fsigned-char -W -Wall -Wextra -Wno-format-y2k -fomit-frame-pointer -O0 -g3 -DNORMALUNIX -DLINUX ")
		SET (CMAKE_CXX_FLAGS_DEBUG "-DDEBUG -fsigned-char -W -Wall -Wextra -Wno-format-y2k -fomit-frame-pointer -O0 -g3 -DNORMALUNIX -DLINUX ")
	ENDIF (TARGET_TYPE STREQUAL "ARM")

ELSE ()

	IF (TARGET_TYPE STREQUAL "Linux")
		MESSAGE (STATUS "Build for Linux Release")
		SET (CMAKE_C_FLAGS_RELEASE "-DNDEBUG -Wint-conversion -s -Wall -O2 -DIVSAPP -DNORMALUNIX -DLINUX -D_DEFAULT_SOURCE")
		SET (CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -Wint-conversion -s -Wall -O2 -DIVSAPP -DNORMALUNIX -DLINUX -D_DEFAULT_SOURCE")
	ENDIF (TARGET_TYPE STREQUAL "Linux")

	IF (TARGET_TYPE STREQUAL "Windows")
		MESSAGE (STATUS "Build for Windows Release")
		SET (CMAKE_C_FLAGS_RELEASE "-DNDEBUG -s -Wall -O2 -DIVSAPP")
		SET (CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -s -Wall -O2 -DIVSAPP")
	ENDIF (TARGET_TYPE STREQUAL "Windows")

	IF (TARGET_TYPE STREQUAL "ARM")
		MESSAGE (STATUS "Build for ARM Release")
		SET (CMAKE_C_FLAGS_RELEASE "-DNDEBUG -s -fsigned-char -Wall -O2 -Wno-format-y2k -fomit-frame-pointer -DNORMALUNIX -DLINUX -D_DEFAULT_SOURCE -DSNDSERV")
		SET (CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -s -fsigned-char -Wall -O2 -Wno-format-y2k -fomit-frame-pointer -DNORMALUNIX -DLINUX -D_DEFAULT_SOURCE -DSNDSERV")
	ENDIF (TARGET_TYPE STREQUAL "ARM")

ENDIF (CMAKE_BUILD_TYPE STREQUAL "Debug")


SET (SRC_LIST
	  ${CMAKE_SOURCE_DIR}/doomgeneric_pocketbook.c
	  ${CMAKE_SOURCE_DIR}/src/dummy.c
    ${CMAKE_SOURCE_DIR}/src/am_map.c
    ${CMAKE_SOURCE_DIR}/src/doomdef.c
    ${CMAKE_SOURCE_DIR}/src/doomstat.c
    ${CMAKE_SOURCE_DIR}/src/dstrings.c
    ${CMAKE_SOURCE_DIR}/src/d_event.c
    ${CMAKE_SOURCE_DIR}/src/d_items.c
    ${CMAKE_SOURCE_DIR}/src/d_iwad.c
    ${CMAKE_SOURCE_DIR}/src/d_loop.c
    ${CMAKE_SOURCE_DIR}/src/d_main.c
    ${CMAKE_SOURCE_DIR}/src/d_mode.c
    ${CMAKE_SOURCE_DIR}/src/d_net.c
    ${CMAKE_SOURCE_DIR}/src/f_finale.c
    ${CMAKE_SOURCE_DIR}/src/f_wipe.c
    ${CMAKE_SOURCE_DIR}/src/g_game.c
    ${CMAKE_SOURCE_DIR}/src/hu_lib.c
    ${CMAKE_SOURCE_DIR}/src/hu_stuff.c
    ${CMAKE_SOURCE_DIR}/src/info.c
    ${CMAKE_SOURCE_DIR}/src/i_cdmus.c
    ${CMAKE_SOURCE_DIR}/src/i_endoom.c
    ${CMAKE_SOURCE_DIR}/src/i_joystick.c
    ${CMAKE_SOURCE_DIR}/src/i_scale.c
    ${CMAKE_SOURCE_DIR}/src/i_sound.c
    ${CMAKE_SOURCE_DIR}/src/i_system.c
    ${CMAKE_SOURCE_DIR}/src/i_timer.c
    ${CMAKE_SOURCE_DIR}/src/memio.c
    ${CMAKE_SOURCE_DIR}/src/m_argv.c
    ${CMAKE_SOURCE_DIR}/src/m_bbox.c
    ${CMAKE_SOURCE_DIR}/src/m_cheat.c
    ${CMAKE_SOURCE_DIR}/src/m_config.c
    ${CMAKE_SOURCE_DIR}/src/m_controls.c
    ${CMAKE_SOURCE_DIR}/src/m_fixed.c
    ${CMAKE_SOURCE_DIR}/src/m_menu.c
    ${CMAKE_SOURCE_DIR}/src/m_misc.c
    ${CMAKE_SOURCE_DIR}/src/m_random.c
    ${CMAKE_SOURCE_DIR}/src/p_ceilng.c
    ${CMAKE_SOURCE_DIR}/src/p_doors.c
    ${CMAKE_SOURCE_DIR}/src/p_enemy.c
    ${CMAKE_SOURCE_DIR}/src/p_floor.c
    ${CMAKE_SOURCE_DIR}/src/p_inter.c
    ${CMAKE_SOURCE_DIR}/src/p_lights.c
    ${CMAKE_SOURCE_DIR}/src/p_map.c
    ${CMAKE_SOURCE_DIR}/src/p_maputl.c
    ${CMAKE_SOURCE_DIR}/src/p_mobj.c
    ${CMAKE_SOURCE_DIR}/src/p_plats.c
    ${CMAKE_SOURCE_DIR}/src/p_pspr.c
    ${CMAKE_SOURCE_DIR}/src/p_saveg.c
    ${CMAKE_SOURCE_DIR}/src/p_setup.c
    ${CMAKE_SOURCE_DIR}/src/p_sight.c
    ${CMAKE_SOURCE_DIR}/src/p_spec.c
    ${CMAKE_SOURCE_DIR}/src/p_switch.c
    ${CMAKE_SOURCE_DIR}/src/p_telept.c
    ${CMAKE_SOURCE_DIR}/src/p_tick.c
    ${CMAKE_SOURCE_DIR}/src/p_user.c
    ${CMAKE_SOURCE_DIR}/src/r_bsp.c
    ${CMAKE_SOURCE_DIR}/src/r_data.c
    ${CMAKE_SOURCE_DIR}/src/r_draw.c
    ${CMAKE_SOURCE_DIR}/src/r_main.c
    ${CMAKE_SOURCE_DIR}/src/r_plane.c
    ${CMAKE_SOURCE_DIR}/src/r_segs.c
    ${CMAKE_SOURCE_DIR}/src/r_sky.c
    ${CMAKE_SOURCE_DIR}/src/r_things.c
    ${CMAKE_SOURCE_DIR}/src/sha1.c
    ${CMAKE_SOURCE_DIR}/src/sounds.c
    ${CMAKE_SOURCE_DIR}/src/statdump.c
    ${CMAKE_SOURCE_DIR}/src/st_lib.c
    ${CMAKE_SOURCE_DIR}/src/st_stuff.c
    ${CMAKE_SOURCE_DIR}/src/s_sound.c
    ${CMAKE_SOURCE_DIR}/src/tables.c
    ${CMAKE_SOURCE_DIR}/src/v_video.c
    ${CMAKE_SOURCE_DIR}/src/wi_stuff.c
    ${CMAKE_SOURCE_DIR}/src/w_checksum.c
    ${CMAKE_SOURCE_DIR}/src/w_file.c
    ${CMAKE_SOURCE_DIR}/src/w_main.c
    ${CMAKE_SOURCE_DIR}/src/w_wad.c
    ${CMAKE_SOURCE_DIR}/src/z_zone.c
    ${CMAKE_SOURCE_DIR}/src/w_file_stdc.c
    ${CMAKE_SOURCE_DIR}/src/i_input.c
    ${CMAKE_SOURCE_DIR}/src/i_video.c
    ${CMAKE_SOURCE_DIR}/src/doomgeneric.c)	

ADD_EXECUTABLE (pocketbook_doom ${SRC_LIST}) 


INCLUDE_DIRECTORIES(${TARGET_INCLUDE})
TARGET_LINK_LIBRARIES (pocketbook_doom ${TARGET_LIB})

INSTALL (TARGETS pocketbook_doom DESTINATION bin)
