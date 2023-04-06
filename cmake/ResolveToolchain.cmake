function(resolve_toolchain PROCESSOR TOOLCHAIN_STR)
    unset(${TOOLCHAIN_STR} PARENT_SCOPE)
    if(
        ${PROCESSOR} MATCHES "^at.*"
        )
            set(${TOOLCHAIN_STR} "avr" PARENT_SCOPE)
            set(QMK_EXTENSION ".hex" PARENT_SCOPE)
            include(FindAVRToolchain)
            find_avr_toolchain()
    elseif(
        ${PROCESSOR} MATCHES "^STM.*" OR
        ${PROCESSOR} MATCHES "^WB32.*" OR
        ${PROCESSOR} MATCHES "^MK.*" OR
        ${PROCESSOR} MATCHES "RP2040" OR
        ${PROCESSOR} MATCHES "^GD32.*"
        )
            set(${TOOLCHAIN_STR} "arm-none-eabi" PARENT_SCOPE)
            set(QMK_EXTENSION ".bin" PARENT_SCOPE)
            include(FindARMToolchain)
            find_arm_toolchain()
    elseif(
        ${PROCESSOR} MATCHES "risc-v"
        )
            set(${TOOLCHAIN_STR} "riscv32-unknown-elf" PARENT_SCOPE)
            set(QMK_EXTENSION ".bin" PARENT_SCOPE)
    else()
        message(FATAL_ERROR "Could not find toolchain for ${PROCESSOR}")
    endif()
endfunction()

function(find_toolchain TOOLCHAIN TOOLCHAIN_ROOT_STR)
    unset(${TOOLCHAIN_STR} PARENT_SCOPE)
    if(UNIX)
        set(OS_SUFFIX "")
        find_path(TOOLCHAIN_ROOT
            NAMES
                ${TOOLCHAIN}-gcc${OS_SUFFIX}
            PATHS
                "${CMAKE_SOURCE_DIR}/toolchains/avr-gcc/avr-gcc-12.1.0-x64-linux/bin/"
                "${CMAKE_SOURCE_DIR}/toolchains/gcc-arm-none-eabi-10.3-2021.10/bin/"
                /usr/bin/
                /usr/local/bin
                /bin/
                $ENV{AVR_ROOT}
        )
    elseif(WIN32)
        set(OS_SUFFIX ".exe")
        find_path(TOOLCHAIN_ROOT
            NAMES
                ${TOOLCHAIN}-gcc${OS_SUFFIX}
            PATHS
                "${CMAKE_SOURCE_DIR}/toolchains/avr-gcc-12.1.0-x64-windows/bin"
                "${CMAKE_SOURCE_DIR}/toolchains/gcc-arm-none-eabi-10.3-2021.10/bin/"
                $ENV{AVR_ROOT}
        )
    else()
        message(FATAL_ERROR "Unsure how to handle this OS")
    endif(UNIX)
    set(${TOOLCHAIN_ROOT_STR} ${TOOLCHAIN_ROOT} PARENT_SCOPE)
endfunction(find_toolchain)