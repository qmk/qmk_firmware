#
# AVR GCC Toolchain file
#
# @author Natesh Narain
# @since Feb 06 2016

set(TRIPLE "avr")

# find the toolchain root directory

if(UNIX)
    set(OS_SUFFIX "")
    find_path(TOOLCHAIN_ROOT
        NAMES
            ${TRIPLE}-gcc${OS_SUFFIX}
        PATHS
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
            "C:/Users/Jack/Downloads/avr-gcc-12.1.0-x64-windows/bin/"
            $ENV{AVR_ROOT}
    )
else(UNIX)
    message(FATAL_ERROR "toolchain not supported on this OS")
endif(UNIX)

if(NOT TOOLCHAIN_ROOT)
    message(FATAL_ERROR "Toolchain root could not be found!!!")
endif(NOT TOOLCHAIN_ROOT)

# setup the AVR compiler variables

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)
set(CMAKE_CROSS_COMPILING 1)

set(CMAKE_MAKE_PROGRAM "${TOOLCHAIN_ROOT}/make${OS_SUFFIX}"                      CACHE PATH "make"    FORCE)
set(CMAKE_C_COMPILER   "${TOOLCHAIN_ROOT}/${TRIPLE}-gcc${OS_SUFFIX}"     CACHE PATH "gcc"     FORCE)
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_ROOT}/${TRIPLE}-g++${OS_SUFFIX}"     CACHE PATH "g++"     FORCE)
set(CMAKE_AR           "${TOOLCHAIN_ROOT}/${TRIPLE}-ar${OS_SUFFIX}"      CACHE PATH "ar"      FORCE)
set(CMAKE_AS           "${TOOLCHAIN_ROOT}/${TRIPLE}-as${OS_SUFFIX}"      CACHE PATH "as"      FORCE)
set(CMAKE_LINKER       "${TOOLCHAIN_ROOT}/${TRIPLE}-ld${OS_SUFFIX}"      CACHE PATH "linker"  FORCE)
set(CMAKE_NM           "${TOOLCHAIN_ROOT}/${TRIPLE}-nm${OS_SUFFIX}"      CACHE PATH "nm"      FORCE)
set(CMAKE_OBJCOPY      "${TOOLCHAIN_ROOT}/${TRIPLE}-objcopy${OS_SUFFIX}" CACHE PATH "objcopy" FORCE)
set(CMAKE_OBJDUMP      "${TOOLCHAIN_ROOT}/${TRIPLE}-objdump${OS_SUFFIX}" CACHE PATH "objdump" FORCE)
set(CMAKE_STRIP        "${TOOLCHAIN_ROOT}/${TRIPLE}-strip${OS_SUFFIX}"   CACHE PATH "strip"   FORCE)
set(CMAKE_RANLIB       "${TOOLCHAIN_ROOT}/${TRIPLE}-ranlib${OS_SUFFIX}"  CACHE PATH "ranlib"  FORCE)
set(AVR_SIZE           "${TOOLCHAIN_ROOT}/${TRIPLE}-size${OS_SUFFIX}"    CACHE PATH "size"    FORCE)

# set(CMAKE_EXE_LINKER_FLAGS "-L /usr/lib/gcc/avr/4.8.2")

# avr uploader config
find_program(AVR_UPLOAD
    NAME
        avrdude
    PATHS
        /usr/bin/
        $ENV{AVR_ROOT}
)

# setup the avr exectable macro

# set(AVR_LINKER_LIBS "-lc -lm -lgcc -Wl,-lprintf_flt -Wl,-u,vfprintf")

add_compile_options(
    $<$<COMPILE_LANGUAGE:C>:-std=gnu11>
    $<$<COMPILE_LANGUAGE:CXX>:-std=gnu++14>
    # -flto
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
    # LTO_ENABLE
)

include_directories("C:/Users/Jack/Downloads/avr-gcc-12.1.0-x64-windows/avr/include")

macro(add_qmk_executable target_name)

    # add_subdirectory(${CMAKE_SOURCE_DIR}/platforms/avr platforms/avr)
    # add_subdirectory(${CMAKE_SOURCE_DIR}/tmk_core/protocol/lufa tmk_core/protocol/lufa)

    set(elf_file ${target_name}-${QMK_MCU}.elf)
    set(map_file ${target_name}-${QMK_MCU}.map)
    set(hex_file ${target_name}-${QMK_MCU}.hex)
    set(lst_file ${target_name}-${QMK_MCU}.lst)

    add_link_options(-Wl,--gc-sections,-Map=${map_file})

    # create elf file
    add_executable(${elf_file}
        ${ARGN}
    )

    target_link_libraries(${elf_file} 
    PUBLIC 
        quantum 
        tmk_core_protocol
        tmk_core_protocol_lufa
        platforms
        platforms_avr
    )

    # set_target_properties(
    #     ${elf_file}

    #     PROPERTIES
    #         COMPILE_FLAGS "-mmcu=${QMK_MCU} -g -w -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics"
    #         LINK_FLAGS    "-mmcu=${QMK_MCU} -Wl,-Map,${map_file}"
    # )

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

    # build the intel hex file for the device
    add_custom_target(
        ${target_name}
        ALL
        DEPENDS ${hex_file} ${lst_file} "print-size-${elf_file}" "print-size-${hex_file}"
    )

    set_target_properties(
        ${target_name}

        PROPERTIES
            OUTPUT_NAME ${elf_file}
    )
endmacro(add_qmk_executable)
