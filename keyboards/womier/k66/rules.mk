## chip/board settings
# - the next two should match the directories in
#   <chibios>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
MCU_FAMILY = SN32
MCU_SERIES = SN32F260

# Linker script to use
# - it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
#   or <this_dir>/ld/
MCU_LDSCRIPT = SN32F260

# Startup code to use
#  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
MCU_STARTUP = sn32f26x

# Board: it should exist either in <chibios>/os/hal/boards/
#  or <this_dir>/boards
BOARD = SN_SN32F260

# Cortex version
MCU  = cortex-m0

# ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
ARMV = 6

# BOOTLOADER = flash

OPT_DEFS = -Og

# Options to pass to dfu-util when flashing
# DFU_ARGS = -d 0483:df11 -a 0 -s 0x08000000:leave
# DFU_SUFFIX_ARGS = -p DF11 -v 0483

#RGB_MATRIX_ENABLE = IS31FL3731

# Build Options
#   comment out to disable the options.
#
# EXTRAFLAGS+=-flto
LTO_ENABLE = yes
BACKLIGHT_ENABLE = no
MAGIC_ENABLE = no
MAGIC_KEYCODE_ENABLE = no
BOOTMAGIC_ENABLE = no  # Virtual DIP switch configuration
## (Note that for BOOTMAGIC on Teensy LC you have to use a custom .ld script.)
MOUSEKEY_ENABLE = no # Mouse keys
EXTRAKEY_ENABLE = yes # Audio control and System control
CONSOLE_ENABLE = no  # Console for debug
COMMAND_ENABLE = no    # Commands for debug and configuration
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE = no     # USB Nkey Rollover
AUDIO_ENABLE = no
RGBLIGHT_ENABLE = no
SERIAL_LINK_ENABLE = no
WAIT_FOR_USB = no
CUSTOM_MATRIX = yes
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = custom
# CH_CFG_NO_IDLE_THREAD = yes
# VIA_ENABLE = yes

EXTRALDFLAGS = --specs=nano.specs
USE_PROCESS_STACKSIZE = 0x180
USE_EXCEPTIONS_STACKSIZE = 0x100

ALLOW_WARNINGS=yes

SRC = matrix.c led_matrix.c
