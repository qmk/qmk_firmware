#
# AVR GCC Toolchain file
#
# @author Natesh Narain
# @since Feb 06 2016

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

include(ResolveToolchain)

set(QMK_TOOLCHAIN "avr")
set(QMK_PLATFORM "avr")
set(QMK_PROTOCOL "lufa")

if(UNIX)
    set(OS_SUFFIX "")
elseif(WIN32)
    set(OS_SUFFIX ".exe")
endif()

find_toolchain(avr TOOLCHAIN_ROOT)

# setup the AVR compiler variables

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)
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

# set(CMAKE_EXE_LINKER_FLAGS "-L /usr/lib/gcc/avr/4.8.2")

# avr uploader config
find_program(AVR_UPLOAD
    NAME
        avrdude
    PATHS
        /usr/bin/
        $ENV{AVR_ROOT}
)

find_program(CMAKE_MAKE_PROGRAM NAME make
    PATHS
    "${CMAKE_SOURCE_DIR}/toolchains/avr-gcc-12.1.0-x64-windows/bin/"
    "${CMAKE_SOURCE_DIR}/toolchains/avr-gcc-12.1.0-x64-linux/bin/"
    /usr/bin/
    /usr/local/bin
    /bin/
)

# setup the avr exectable macro

# set(AVR_LINKER_LIBS "-lc -lm -lgcc -Wl,-lprintf_flt -Wl,-u,vfprintf")

add_compile_options(
    $<$<COMPILE_LANGUAGE:C>:-std=gnu11>
    $<$<COMPILE_LANGUAGE:CXX>:-std=gnu++14>
    -flto
    # -mrelax
    -Os
    -Wall
    -Wstrict-prototypes
    -fcommon
    # -g
    $<$<BOOL:${WIN32}>:--param=min-pagesize=0>
    -funsigned-char
    -funsigned-bitfields
    -ffunction-sections
    -fdata-sections
    -fpack-struct
    -fshort-enums
    -mcall-prologues
    -fno-builtin-printf
    $<$<COMPILE_LANGUAGE:C>:-fno-inline-small-functions>
    $<$<COMPILE_LANGUAGE:C>:-fno-strict-aliasing>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
)

add_compile_definitions(
    F_CPU=16000000
    F_USB=16000000UL
    __AVR_ATmega32U4__
    LTO_ENABLE
)

add_link_options(
    -Wl,--gc-sections
)

macro(add_qmk_executable target_name)

    set(elf_file ${target_name}.elf)
    set(map_file ${target_name}.map)
    set(hex_file ${target_name}.hex)
    set(lst_file ${target_name}.lst)

    add_compile_options(
        -mmcu=${QMK_MCU}
    )

    add_link_options(
        -mmcu=${QMK_MCU}
        -Wl,-Map=${map_file}
    )

    # create elf file
    add_executable(${elf_file} ${ARGN})

    # add_executable(qmk ${ARGN})
    # set_target_properties(qmk
        # PROPERTIES OUTPUT_NAME ${elf_file}
    # )

    target_link_libraries(${elf_file} qmk)

    # set_target_properties(${elf_file}
    #     PROPERTIES
    #         COMPILE_FLAGS "-mmcu=${QMK_MCU} ${COMPILE_OPTIONS}"
    #         LINK_FLAGS    "-mmcu=${QMK_MCU} ${LINK_OPTIONS}"
    # )

    # add_custom_target(compileOptions
    #     COMMAND cmake -P ${CMAKE_SOURCE_DIR}/cmake/WriteCompileOptions.cmake
    #     COMMENT "Writing compile_flags.txt"
    # )

    # generate the lst file
    add_custom_command(
        OUTPUT ${lst_file}
        COMMAND ${CMAKE_OBJDUMP} -h -S ${elf_file} > ${lst_file}
        DEPENDS ${elf_file}
    )

    # create hex file
    add_custom_command(
        OUTPUT ${hex_file}
        # COMMAND ${CMAKE_OBJCOPY} -j .text -j .data -O ihex ${elf_file} ${hex_file}
        COMMAND ${CMAKE_OBJCOPY} -O ihex -R .eeprom -R .fuse -R .lock -R .signature ${elf_file} ${hex_file}
        DEPENDS ${elf_file}
    )

    add_custom_command(
        OUTPUT "print-size-${elf_file}"
        COMMAND ${AVR_SIZE} ${elf_file}
        DEPENDS ${elf_file}
    )

    add_custom_command(
        OUTPUT "print-size-${hex_file}"
        COMMAND ${AVR_SIZE} ${hex_file}
        DEPENDS ${hex_file}
    )

    add_custom_target(copy_hex
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${elf_file}> ${CMAKE_SOURCE_DIR}/build/${target_name}.hex
        DEPENDS ${hex_file}
    )

    # build the intel hex file for the device
    add_custom_target(${target_name} ALL
        DEPENDS ${hex_file} ${lst_file} "print-size-${elf_file}" "print-size-${hex_file}" copy_hex 
    )

    set_target_properties(${target_name}
        PROPERTIES OUTPUT_NAME ${elf_file}
    )


endmacro(add_qmk_executable)
