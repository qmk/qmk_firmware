macro(find_gcc TRIPLE)
if(UNIX)
    set(OS_SUFFIX "")
    find_path(ARM_TOOLCHAIN_ROOT
        NAMES
            ${TRIPLE}-gcc${OS_SUFFIX}
        PATHS
            "${CMAKE_SOURCE_DIR}/toolchains/avr-gcc/avr-gcc-12.1.0-x64-linux/bin/"
            /usr/bin/
            /usr/local/bin
            /bin/
            $ENV{AVR_ROOT}
    )
    find_path(MAKE_ROOT
        NAMES
            make${OS_SUFFIX}
        PATHS
            "${CMAKE_SOURCE_DIR}/toolchains/avr-gcc-12.1.0-x64-linux/bin/"
            /usr/bin/
            /usr/local/bin
            /bin/
            $ENV{AVR_ROOT}
    )
elseif(WIN32)
    set(OS_SUFFIX ".exe")
    find_path(ARM_TOOLCHAIN_ROOT
        NAMES
            ${TRIPLE}-gcc${OS_SUFFIX}
        PATHS
            "${CMAKE_SOURCE_DIR}/toolchains/avr-gcc-12.1.0-x64-windows/bin"
            "${CMAKE_SOURCE_DIR}/toolchains/gcc-arm-none-eabi-10.3-2021.10/bin/"
            "C:/Users/Jack/Downloads/avr-gcc-12.1.0-x64-windows/bin/"
            $ENV{AVR_ROOT}
    )
    find_path(MAKE_ROOT
        NAMES
            make${OS_SUFFIX}
        PATHS
            "${CMAKE_SOURCE_DIR}/toolchains/avr-gcc-12.1.0-x64-windows/bin/"
            "C:/Users/Jack/Downloads/avr-gcc-12.1.0-x64-windows/bin/"
            $ENV{AVR_ROOT}
    )
else(UNIX)
    message(FATAL_ERROR "toolchain not supported on this OS")
endif(UNIX)
endmacro(find_gcc)

macro(find_arm_toolchain)
    find_gcc(arm-none-eabi)

    if(NOT ARM_TOOLCHAIN_ROOT)
        include(GetARMToolchain)
        find_gcc(arm-none-eabi)
    endif()

    if(NOT ARM_TOOLCHAIN_ROOT)
        message(FATAL_ERROR "ARM Toolchain could not be found")
    endif()

    set(TOOLCHAIN_ROOT ${ARM_TOOLCHAIN_ROOT})
    message("ARM toolchain found: ${ARM_TOOLCHAIN_ROOT}")
    message("Found make: ${MAKE_ROOT}")
endmacro()