macro(find_avr_toolchain)
    find_toolchain(avr TOOLCHAIN_ROOT)

    if(NOT TOOLCHAIN_ROOT)
        include(GetAVRToolchain)
        find_toolchain(avr TOOLCHAIN_ROOT)
    endif()

    find_program(DFU_PROGRAMMER NAMES dfu-programmer PATHS ${CMAKE_SOURCE_DIR}/toolchains/dfu-programmer/)
    if(${DFU_PROGRAMMER} STREQUAL "DFU_PROGRAMMER-NOTFOUND")
        include(GetDfuProgrammer)
        find_program(DFU_PROGRAMMER NAMES dfu-programmer PATHS ${CMAKE_SOURCE_DIR}/toolchains/dfu-programmer/)
    endif()

    if(NOT TOOLCHAIN_ROOT)
        message(FATAL_ERROR "AVR Toolchain could not be found")
    endif()

    message(STATUS "AVR toolchain found: ${TOOLCHAIN_ROOT}")
endmacro()