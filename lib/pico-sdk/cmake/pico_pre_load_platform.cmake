# PICO_CMAKE_CONFIG: PICO_PLATFORM, platform to build for e.g. rp2040/host, default=rp2040 or environment value, group=build
if (DEFINED ENV{PICO_PLATFORM} AND (NOT PICO_PLATFORM))
    set(PICO_PLATFORM $ENV{PICO_PLATFORM})
    message("Using PICO_PLATFORM from environment ('${PICO_PLATFORM}')")
else()
    if (NOT PICO_PLATFORM)
        set(PICO_PLATFORM "rp2040")
        pico_message("Defaulting PICO_PLATFORM to ${PICO_PLATFORM} since not specified.")
    else()
        message("PICO platform is ${PICO_PLATFORM}.")
    endif()
endif ()

set(PICO_PLATFORM ${PICO_PLATFORM} CACHE STRING "PICO Build platform (e.g. rp2040, host)")

# PICO_CMAKE_CONFIG: PICO_CMAKE_PRELOAD_PLATFORM_FILE, custom CMake file to use to set up the platform environment, default=none, group=build
set(PICO_CMAKE_PRELOAD_PLATFORM_FILE "" CACHE INTERNAL "")
set(PICO_CMAKE_PRELOAD_PLATFORM_DIR "${CMAKE_CURRENT_LIST_DIR}/preload/platforms" CACHE INTERNAL "")

if (NOT PICO_CMAKE_PRELOAD_PLATFORM_FILE)
    set(PICO_CMAKE_PRELOAD_PLATFORM_FILE ${PICO_CMAKE_PRELOAD_PLATFORM_DIR}/${PICO_PLATFORM}.cmake CACHE INTERNAL "")
endif ()

if (NOT EXISTS "${PICO_CMAKE_PRELOAD_PLATFORM_FILE}")
    message(FATAL_ERROR "${PICO_CMAKE_PRELOAD_PLATFORM_FILE} does not exist. \
    Either specify a valid PICO_PLATFORM (or PICO_CMAKE_PRELOAD_PLATFORM_FILE).")
endif ()

include(${PICO_CMAKE_PRELOAD_PLATFORM_FILE})
