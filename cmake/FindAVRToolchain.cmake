macro(find_avr_toolchain)
    find_toolchain(avr TOOLCHAIN_ROOT MAKE_ROOT)

    if(NOT TOOLCHAIN_ROOT)
        include(GetAVRToolchain)
        find_toolchain(avr TOOLCHAIN_ROOT MAKE_ROOT)
    endif()

    if(NOT TOOLCHAIN_ROOT)
        message(FATAL_ERROR "AVR Toolchain could not be found")
    endif()

    message(STATUS "AVR toolchain found: ${TOOLCHAIN_ROOT}")
    message(STATUS "Found make: ${MAKE_ROOT}")
endmacro()