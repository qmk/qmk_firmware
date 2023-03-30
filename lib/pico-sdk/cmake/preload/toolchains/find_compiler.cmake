# Toolchain file is processed multiple times, however, it cannot access CMake cache on some runs.
# We store the search path in an environment variable so that we can always access it.
if (NOT "${PICO_TOOLCHAIN_PATH}" STREQUAL "")
    set(ENV{PICO_TOOLCHAIN_PATH} "${PICO_TOOLCHAIN_PATH}")
endif ()

# Find the compiler executable and store its path in a cache entry ${compiler_path}.
# If not found, issue a fatal message and stop processing. PICO_TOOLCHAIN_PATH can be provided from
# commandline as additional search path.
function(pico_find_compiler compiler_path compiler_exe)
    # Search user provided path first.
    find_program(
            ${compiler_path} ${compiler_exe}
            PATHS ENV PICO_TOOLCHAIN_PATH
            PATH_SUFFIXES bin
            NO_DEFAULT_PATH
    )

    # If not then search system paths.
    if ("${${compiler_path}}" STREQUAL "${compiler_path}-NOTFOUND")
        if (DEFINED ENV{PICO_TOOLCHAIN_PATH})
            message(WARNING "PICO_TOOLCHAIN_PATH specified ($ENV{PICO_TOOLCHAIN_PATH}), but ${compiler_exe} not found there")
        endif()
        find_program(${compiler_path} ${compiler_exe})
    endif ()
    if ("${${compiler_path}}" STREQUAL "${compiler_path}-NOTFOUND")
        set(PICO_TOOLCHAIN_PATH "" CACHE PATH "Path to search for compiler.")
        message(FATAL_ERROR "Compiler '${compiler_exe}' not found, you can specify search path with\
            \"PICO_TOOLCHAIN_PATH\".")
    endif ()
endfunction()
