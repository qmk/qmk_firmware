macro(find_gcc TRIPLE)
if(UNIX)
    set(OS_SUFFIX "")
    find_path(TOOLCHAIN_ROOT
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
        "${CMAKE_SOURCE_DIR}/toolchains/avr-gcc/avr-gcc-12.1.0-x64-linux/bin/"
            /usr/bin/
            /usr/local/bin
            /bin/
            $ENV{AVR_ROOT}
    )
elseif(WIN32)
    set(OS_SUFFIX ".exe")
    find_path(TOOLCHAIN_ROOT
        NAMES
            ${TRIPLE}-gcc${OS_SUFFIX}
        PATHS
            "${CMAKE_SOURCE_DIR}/toolchains/avr-gcc/avr-gcc-12.1.0-x64-windows/bin/"
            "C:/Users/Jack/Downloads/avr-gcc-12.1.0-x64-windows/bin/"
            $ENV{AVR_ROOT}
    )
    find_path(MAKE_ROOT
        NAMES
            make${OS_SUFFIX}
        PATHS
            "${CMAKE_SOURCE_DIR}/toolchains/avr-gcc/avr-gcc-12.1.0-x64-windows/bin/"
            "C:/Users/Jack/Downloads/avr-gcc-12.1.0-x64-windows/bin/"
            $ENV{AVR_ROOT}
    )
else(UNIX)
    message(FATAL_ERROR "toolchain not supported on this OS")
endif(UNIX)
endmacro(find_gcc)

macro(find_toolchain)
find_gcc(avr)

if(NOT TOOLCHAIN_ROOT)
    include(GetAVR-GCC)
    find_gcc(avr)
endif(NOT TOOLCHAIN_ROOT)

if(NOT TOOLCHAIN_ROOT)
    message(FATAL_ERROR "Toolchain root could not be found!!!")
endif(NOT TOOLCHAIN_ROOT)

message("Found toolchain: ${TOOLCHAIN_ROOT}")
message("Found make:      ${MAKE_ROOT}")

endmacro()