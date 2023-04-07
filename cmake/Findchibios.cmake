include(ParseMakefile)

# STM32F303

set(MCU "cortex-m4")
set(ARMV 7)
set(MCU_FAMILY "STM32")
set(MCU_SERIES "STM32F3xx")
string(TOUPPER ${MCU_SERIES} MCU_SERIES_UPPER)
set(MCU_LDSCRIPT "STM32F303xC")
set(MCU_STARTUP "stm32f3xx")
set(BOARD "GENERIC_STM32_F303XC")
set(USE_FPU TRUE)
set(UF2_FAMILY "STM32F3")
set(STM32_BOOTLOADER_ADDRESS 0x1FFFD800)
set(EEPROM_DRIVER "wear_leveling" FORCE)
set(WEAR_LEVELING_DRIVER "embedded_flash" FORCE)

target_compile_definitions(qmk PUBLIC
  QMK_MCU_FAMILY_${MCU_FAMILY}
  QMK_MCU_SERIES_${MCU_SERIES_UPPER}
)

target_compile_options(qmk PUBLIC
    -march=armv7-m
)

target_compile_definitions(qmk PUBLIC
    MCU_${MCU_FAMILY}
    __ARM_ARCH_7M__
)

# platforms/chibios/platform.mk

if(NOT DEFINED USE_PROCESS_STACKSIZE)
    set(USE_PROCESS_STACKSIZE 0x800)
endif()

if(NOT DEFINED USE_EXCEPTIONS_STACKSIZE)
    set(USE_EXCEPTIONS_STACKSIZE 0x400)
endif()

target_link_options(qmk PUBLIC
    -Wl,--defsym=__process_stack_size__=${USE_PROCESS_STACKSIZE},--defsym=__main_stack_size__=${USE_EXCEPTIONS_STACKSIZE}
)

if(NOT DEFINED MCU_PORT_NAME)
    set(MCU_PORT_NAME ${MCU_FAMILY})
endif()
set(MCU_ARCH ${MCU})
if(NOT DEFINED CHIBIOS_PORT)
    set(CHIBIOS_PORT "ARMv${ARMV}-M")
endif()
if(NOT DEFINED PLATFORM_NAME)
    set(PLATFORM_NAME platform)
endif()

set(CHIBIOS ${CMAKE_SOURCE_DIR}/lib/chibios)
set(CHIBIOS_CONTRIB ${CMAKE_SOURCE_DIR}/lib/chibios-contrib)

# port*.mk
include(chibios/ports/${CHIBIOS_PORT})

# platform.mk
include(chibios/ports/${MCU_SERIES})

# startup_*.mk - might need to convert these
find_file(STARTUP_MK startup_${MCU_STARTUP}.mk
    ${CHIBIOS}/os/common/ports/ARMCMx/compilers/GCC/mk
    ${CHIBIOS}/os/common/startup/ARMCMx/compilers/GCC/mk
    ${CHIBIOS_CONTRIB}/os/common/startup/ARMCMx/compilers/GCC/mk
)
get_filename_component(STARTUP_DIR ${STARTUP_MK} DIRECTORY)
ParseMakefile(${STARTUP_MK})
target_sources(qmk PUBLIC ${STARTUPSRC})
target_sources(qmk PUBLIC ${STARTUPASM})
target_include_directories(qmk PUBLIC ${STARTUPINC})

# board paths - we should just standardize these
find_path(BOARD_PATH
NAMES 
    boards/${BOARD}/board.mk 
    board/board.mk
PATHS
    ${QMK_KEYBOARD_FOLDER}/boards/${BOARD}
    ${CMAKE_SOURCE_DIR}/platforms/chibios/boards/${BOARD}
    ${CHIBIOS}/os/hal/
    ${CHIBIOS_CONTRIB}/os/hal/
)
# if(EXISTS ${BOARD_PATH}/rules.mk)
#     ParseMakefile(${BOARD_PATH}/rules.mk)
# endif()

if(EXISTS ${BOARD_PATH}/configs/config.h)
target_precompile_headers(qmk PUBLIC
    ${BOARD_PATH}/configs/config.h
)
endif()

if(EXISTS ${BOARD_PATH}/configs/post_config.h)
    target_precompile_headers(qmk PUBLIC
        ${BOARD_PATH}/configs/post_config.h
    )
endif()

find_file(BOARD_MK board.mk
    ${BOARD_PATH}/boards/${BOARD}
    ${BOARD_PATH}/board
)
ParseMakefile(${BOARD_MK})

target_sources(qmk PUBLIC ${BOARDSRC})
target_include_directories(qmk PUBLIC ${BOARDINC})

# allow board.c to be overriden
file(RELATIVE_PATH INIT_HOOK_RELATIVE ${CMAKE_BINARY_DIR}
    "${CMAKE_SOURCE_DIR}/tmk_core/protocol/chibios/init_hooks.h")
set_source_files_properties(${BOARDSRC} TARGET_DIRECTORY qmk PROPERTIES 
    # COMPILE_OPTIONS "-include ../../../tmk_core/protocol/chibios/init_hooks.h"
    COMPILE_OPTIONS "-include ${INIT_HOOK_RELATIVE}"
)

# bootloader
if(DEFINED STM32_BOOTLOADER_ADDRESS)
    target_compile_definitions(qmk PUBLIC STM32_BOOTLOADER_ADDRESS=${STM32_BOOTLOADER_ADDRESS})
endif()
if(DEFINED WB32_BOOTLOADER_ADDRESS)
    target_compile_definitions(qmk PUBLIC WB32_BOOTLOADER_ADDRESS=${WB32_BOOTLOADER_ADDRESS})
endif()

find_file(BOOTLOADER_DEFS_H bootloader_defs.h
    ${QMK_KEYBOARD_FOLDER}
    ${QMK_KEYBOARD_FOLDER}/boards/${BOARD}
    ${BOARD_PATH}/configs
)
if(EXISTS ${BOOTLOADER_DEFS_H})
    target_compile_options(qmk PUBLIC -include ${BOOTLOADER_DEFS_H})
endif()

# chconf directories
find_path(CHCONFDIR chconf.h
    ${QMK_KEYBOARD_FOLDER}
    ${CMAKE_SOURCE_DIR}/platforms/chibios/boards/${BOARD}/configs
    ${CMAKE_SOURCE_DIR}/platforms/chibios/boards/common/configs
)
target_include_directories(qmk PUBLIC ${CHCONFDIR})

# halconf directories
find_path(HALCONFDIR halconf.h
    ${QMK_KEYBOARD_FOLDER}
    ${CMAKE_SOURCE_DIR}/platforms/chibios/boards/${BOARD}/configs
    ${CMAKE_SOURCE_DIR}/platforms/chibios/boards/common/configs
)
target_include_directories(qmk PUBLIC ${HALCONFDIR})

# linker script
find_file(LDSCRIPT ${MCU_LDSCRIPT}.ld
    ${QMK_KEYBOARD_FOLDER}/ld
    ${CMAKE_SOURCE_DIR}/platforms/chibios/boards/${BOARD}/ld
    ${CMAKE_SOURCE_DIR}/platforms/chibios/boards/common/ld
    ${STARTUPLD}
    ${STARTUPLD_CONTRIB}
)
get_filename_component(LDSCRIPT_PATH ${LDSCRIPT} DIRECTORY)
target_link_options(qmk PUBLIC
    -T ${LDSCRIPT}
    -L ${LDSCRIPT_PATH}
)

# os/hal/hal.mk
target_sources(qmk PUBLIC
    ${CHIBIOS}/os/hal/src/hal.c
    ${CHIBIOS}/os/hal/src/hal_st.c
    ${CHIBIOS}/os/hal/src/hal_buffers.c
    ${CHIBIOS}/os/hal/src/hal_queues.c
    ${CHIBIOS}/os/hal/src/hal_flash.c
    ${CHIBIOS}/os/hal/src/hal_mmcsd.c
    ${CHIBIOS}/os/hal/src/hal_adc.c
    ${CHIBIOS}/os/hal/src/hal_can.c
    ${CHIBIOS}/os/hal/src/hal_crypto.c
    ${CHIBIOS}/os/hal/src/hal_dac.c
    ${CHIBIOS}/os/hal/src/hal_efl.c
    ${CHIBIOS}/os/hal/src/hal_gpt.c
    ${CHIBIOS}/os/hal/src/hal_i2c.c
    ${CHIBIOS}/os/hal/src/hal_i2s.c
    ${CHIBIOS}/os/hal/src/hal_icu.c
    ${CHIBIOS}/os/hal/src/hal_mac.c
    ${CHIBIOS}/os/hal/src/hal_mmc_spi.c
    ${CHIBIOS}/os/hal/src/hal_pal.c
    ${CHIBIOS}/os/hal/src/hal_pwm.c
    ${CHIBIOS}/os/hal/src/hal_rtc.c
    ${CHIBIOS}/os/hal/src/hal_sdc.c
    ${CHIBIOS}/os/hal/src/hal_serial.c
    ${CHIBIOS}/os/hal/src/hal_serial_usb.c
    ${CHIBIOS}/os/hal/src/hal_sio.c
    ${CHIBIOS}/os/hal/src/hal_spi.c
    ${CHIBIOS}/os/hal/src/hal_trng.c
    ${CHIBIOS}/os/hal/src/hal_uart.c
    ${CHIBIOS}/os/hal/src/hal_usb.c
    ${CHIBIOS}/os/hal/src/hal_wdg.c
    ${CHIBIOS}/os/hal/src/hal_wspi.c
)
target_include_directories(qmk PUBLIC
    ${CHIBIOS}/os/hal/include
)

# os/hal/osal/rt-nil/osal.mk
target_sources(qmk PUBLIC
    ${CHIBIOS}/os/hal/osal/rt-nil/osal.c
)
target_include_directories(qmk PUBLIC
    ${CHIBIOS}/os/hal/osal/rt-nil
)

# os/rt/rt.mk
target_sources(qmk PUBLIC
    ${CHIBIOS}/os/rt/src/chsys.c
    ${CHIBIOS}/os/rt/src/chrfcu.c
    ${CHIBIOS}/os/rt/src/chdebug.c
    ${CHIBIOS}/os/rt/src/chtrace.c
    ${CHIBIOS}/os/rt/src/chvt.c
    ${CHIBIOS}/os/rt/src/chschd.c
    ${CHIBIOS}/os/rt/src/chinstances.c
    ${CHIBIOS}/os/rt/src/chthreads.c
    ${CHIBIOS}/os/rt/src/chsys.c
    ${CHIBIOS}/os/rt/src/chrfcu.c
    ${CHIBIOS}/os/rt/src/chdebug.c
    ${CHIBIOS}/os/rt/src/chtrace.c
    ${CHIBIOS}/os/rt/src/chvt.c
    ${CHIBIOS}/os/rt/src/chschd.c
    ${CHIBIOS}/os/rt/src/chinstances.c
    ${CHIBIOS}/os/rt/src/chthreads.c
    ${CHIBIOS}/os/rt/src/chtm.c
    ${CHIBIOS}/os/rt/src/chstats.c
    ${CHIBIOS}/os/rt/src/chregistry.c
    ${CHIBIOS}/os/rt/src/chsem.c
    ${CHIBIOS}/os/rt/src/chmtx.c
    ${CHIBIOS}/os/rt/src/chcond.c
    ${CHIBIOS}/os/rt/src/chevents.c
    ${CHIBIOS}/os/rt/src/chmsg.c
    ${CHIBIOS}/os/rt/src/chdynamic.c
)
target_include_directories(qmk PUBLIC
    ${CHIBIOS}/os/rt/include
)

# os/oslib/oslib.mk
target_sources(qmk PUBLIC
    ${CHIBIOS}/os/oslib/src/chmboxes.c
    ${CHIBIOS}/os/oslib/src/chmemcore.c
    ${CHIBIOS}/os/oslib/src/chmemheaps.c
    ${CHIBIOS}/os/oslib/src/chmempools.c
    ${CHIBIOS}/os/oslib/src/chpipes.c
    ${CHIBIOS}/os/oslib/src/chobjcaches.c
    ${CHIBIOS}/os/oslib/src/chdelegates.c
    ${CHIBIOS}/os/oslib/src/chfactory.c
)
target_include_directories(qmk PUBLIC
    ${CHIBIOS}/os/oslib/include
)

# os/hal/lib/streams/streams.mk
target_sources(qmk PUBLIC
    ${CHIBIOS}/os/hal/lib/streams/chprintf.c
    ${CHIBIOS}/os/hal/lib/streams/chscanf.c
    ${CHIBIOS}/os/hal/lib/streams/memstreams.c
    ${CHIBIOS}/os/hal/lib/streams/nullstreams.c
    ${CHIBIOS}/os/hal/lib/streams/bufstreams.c
)
target_include_directories(qmk PUBLIC
    ${CHIBIOS}/os/hal/lib/streams
)

# resume platform.mk
target_sources(qmk PUBLIC
    ${CHIBIOS}/os/various/syscalls.c
)
target_include_directories(qmk PUBLIC
    ${CHIBIOS}/os/license
    ${CHIBIOS}/os/oslib/include
    ${CHIBIOS}/os/various
)