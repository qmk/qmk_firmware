set(CMAKE_EXPORT_COMPILE_COMMANDS on)

include(ResolveToolchain)

set(QMK_TOOLCHAIN "arm-none-eabi")
set(QMK_PLATFORM "chibios")
set(QMK_PROTOCOL "chibios")

if(UNIX)
    set(OS_SUFFIX "")
elseif(WIN32)
    set(OS_SUFFIX ".exe")
endif()

find_toolchain(arm-none-eabi TOOLCHAIN_ROOT)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CROSS_COMPILING 1)

set(CMAKE_C_COMPILER   "${TOOLCHAIN_ROOT}/${QMK_TOOLCHAIN}-gcc${OS_SUFFIX}"     CACHE PATH "gcc"     FORCE)
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_ROOT}/${QMK_TOOLCHAIN}-g++${OS_SUFFIX}"     CACHE PATH "g++"     FORCE)
set(CMAKE_AR           "${TOOLCHAIN_ROOT}/${QMK_TOOLCHAIN}-ar${OS_SUFFIX}"      CACHE PATH "ar"      FORCE)
set(CMAKE_AS           "${TOOLCHAIN_ROOT}/${QMK_TOOLCHAIN}-as${OS_SUFFIX}"      CACHE PATH "as"      FORCE)
set(CMAKE_LINKER       "${TOOLCHAIN_ROOT}/${QMK_TOOLCHAIN}-ld${OS_SUFFIX}"      CACHE PATH "linker"  FORCE)
set(CMAKE_NM           "${TOOLCHAIN_ROOT}/${QMK_TOOLCHAIN}-nm${OS_SUFFIX}"      CACHE PATH "nm"      FORCE)
set(CMAKE_OBJCOPY      "${TOOLCHAIN_ROOT}/${QMK_TOOLCHAIN}-objcopy${OS_SUFFIX}" CACHE PATH "objcopy" FORCE)
set(CMAKE_OBJDUMP      "${TOOLCHAIN_ROOT}/${QMK_TOOLCHAIN}-objdump${OS_SUFFIX}" CACHE PATH "objdump" FORCE)
set(CMAKE_STRIP        "${TOOLCHAIN_ROOT}/${QMK_TOOLCHAIN}-strip${OS_SUFFIX}"   CACHE PATH "strip"   FORCE)
set(CMAKE_RANLIB       "${TOOLCHAIN_ROOT}/${QMK_TOOLCHAIN}-ranlib${OS_SUFFIX}"  CACHE PATH "ranlib"  FORCE)
set(AVR_SIZE           "${TOOLCHAIN_ROOT}/${QMK_TOOLCHAIN}-size${OS_SUFFIX}"    CACHE PATH "size"    FORCE)

find_program(CMAKE_MAKE_PROGRAM NAME make
    PATHS
    "${CMAKE_SOURCE_DIR}/toolchains/avr-gcc-12.1.0-x64-windows/bin/"
    "${CMAKE_SOURCE_DIR}/toolchains/avr-gcc-12.1.0-x64-linux/bin/"
    /usr/bin/
    /usr/local/bin
    /bin/
)

add_compile_options(
    $<$<COMPILE_LANGUAGE:C>:-std=gnu11>
    $<$<COMPILE_LANGUAGE:CXX>:-std=gnu++14>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
    # -flto
    -Os
    -Wall
    -Wstrict-prototypes
    # -fcommon
    # -g

    -fomit-frame-pointer
    -ffunction-sections
    -fdata-sections
    -fno-common
    -fshort-wchar
    -fno-builtin-printf
    # -funsigned-char
    # -funsigned-bitfields
    # -ffunction-sections
    # -fdata-sections
    # -fpack-struct
    # -fshort-enums
    # -fno-builtin-printf
    # $<$<COMPILE_LANGUAGE:C>:-fno-inline-small-functions>
    # $<$<COMPILE_LANGUAGE:C>:-fno-strict-aliasing>
    # $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
)

add_compile_definitions(
    THUMB_PRESENT
    THUMB_NO_INTERWORKING
    PROTOCOL_CHIBIOS
    MCU_${MCU_FAMILY}
    PLATFORM_SUPPORTS_SYNCHRONIZATION
    PORT_IGNORE_GCC_VERSION_CHECK=1
)

add_link_options(
    -Wl,--gc-sections
    -nostartfiles
    -Wl,--no-wchar-size-warning
    --specs=nano.specs
    -mthumb
    -mno-thumb-interwork
    -mno-unaligned-access
)

if(${USE_FPU})
    add_compile_definitions(
        CORTEX_USE_FPU=TRUE
    )
    add_link_options(
        -mfloat-abi=hard
        -mfpu=fpv4-sp-d16
        -fsingle-precision-constant
    )
else()
    add_compile_definitions(
        CORTEX_USE_FPU=FALSE
    )
endif()

macro(add_qmk_executable target_name)

    set(elf_file ${target_name}.elf)
    set(map_file ${target_name}.map)
    set(hex_file ${target_name}.hex)
    set(lst_file ${target_name}.lst)

    # create elf file
    add_executable(${elf_file} ${ARGN})

    target_link_libraries(${elf_file} qmk)

    # generate the lst file
    add_custom_command(
        OUTPUT ${lst_file}

        COMMAND
            ${CMAKE_OBJDUMP} -h -S ${elf_file} > ${lst_file}

        DEPENDS ${elf_file}
    )

    # create hex file
    add_custom_command(
        OUTPUT ${hex_file}

        COMMAND
            ${CMAKE_OBJCOPY} -j .text -j .data -O ihex ${elf_file} ${hex_file}

        DEPENDS ${elf_file}
    )

    add_custom_command(
        OUTPUT "print-size-${elf_file}"

        COMMAND
            ${AVR_SIZE} ${elf_file}

        DEPENDS ${elf_file}
    )

    add_custom_command(
        OUTPUT "print-size-${hex_file}"

        COMMAND
            ${AVR_SIZE} ${hex_file}

        DEPENDS ${hex_file}
    )

    add_custom_target(copy_hex
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${elf_file}> ${CMAKE_SOURCE_DIR}/build/${target_name}.hex
        DEPENDS ${hex_file}
    )

    # build the intel hex file for the device
    add_custom_target(
        ${target_name}
        ALL
        DEPENDS ${hex_file} ${lst_file} "print-size-${elf_file}" "print-size-${hex_file}" copy_hex
    )

    set_target_properties(
        ${target_name}

        PROPERTIES
            OUTPUT_NAME ${elf_file}
    )
endmacro(add_qmk_executable)
