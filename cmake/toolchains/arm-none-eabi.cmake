set(CMAKE_EXPORT_COMPILE_COMMANDS on)

include(ResolveToolchain)

set(QMK_TOOLCHAIN "arm-none-eabi")
set(QMK_PLATFORM "chibios")
set(QMK_PROTOCOL "chibios")
set(QMK_EXTENSION ".bin")

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
set(CMAKE_SIZE         "${TOOLCHAIN_ROOT}/${QMK_TOOLCHAIN}-size${OS_SUFFIX}"    CACHE PATH "size"    FORCE)

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

add_link_options(
    -Wl,--gc-sections
    -nostartfiles
    -Wl,--no-wchar-size-warning
    --specs=nano.specs
    -lm
)

macro(add_qmk_executable target_name)

    set(elf_file ${target_name}.elf)
    set(map_file ${target_name}.map)
    set(bin_file ${target_name}.bin)
    set(lst_file ${target_name}.lst)

    add_link_options(
        -Wl,-Map=${map_file},--cref
    )

    # create elf file
    add_executable(qmk ${ARGN})
    # add_executable(${elf_file} ${ARGN})
    # target_link_libraries(${elf_file} qmk)

    set_target_properties(qmk
        PROPERTIES
            OUTPUT_NAME ${elf_file}
    )

    # generate the lst file
    add_custom_command(
        OUTPUT ${lst_file}
        COMMAND ${CMAKE_OBJDUMP} -h -S ${elf_file} > ${lst_file}
        DEPENDS qmk
    )

    # add_custom_command(
    #     OUTPUT "print-size-${elf_file}"

    #     COMMAND
    #         ${CMAKE_SIZE} ${elf_file}

    #     DEPENDS ${elf_file}
    # )

    # add_custom_command(
    #     OUTPUT "print-size-${bin_file}"

    #     COMMAND
    #         ${CMAKE_SIZE} ${bin_file} sizeafter

    #     DEPENDS ${bin_file}
    # )

    add_custom_command(
        TARGET qmk
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O binary ${elf_file} ${CMAKE_SOURCE_DIR}/build/${bin_file}
        # COMMAND ${CMAKE_COMMAND} -E copy ${elf_file} ${CMAKE_SOURCE_DIR}/build/${elf_file}
        # COMMAND ${CMAKE_COMMAND} -E copy ${lst_file} ${CMAKE_SOURCE_DIR}/build/${lst_file}
        # COMMAND ${CMAKE_COMMAND} -E copy ${map_file} ${CMAKE_SOURCE_DIR}/build/${map_file}
    )

    # build the intel hex file for the device
    add_custom_target(${target_name} ALL
        DEPENDS ${elf_file} ${lst_file}
    )

    set_target_properties(${target_name}
        PROPERTIES
            OUTPUT_NAME ${bin_file}
    )
endmacro(add_qmk_executable)
