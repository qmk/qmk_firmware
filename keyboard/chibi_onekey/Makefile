# Target file name (without extension).
PROJECT = ch
TARGET = alps64

# Directory common source files exist
TMK_DIR = ../../tmk_core

# Directory keyboard dependent files exist
TARGET_DIR = .

# project specific files
SRC =	matrix.c \
	    led.c

ifdef KEYMAP
    SRC := keymap_$(KEYMAP).c $(SRC)
else
    SRC := keymap_plain.c $(SRC)
endif

CONFIG_H = config.h

# chip/board
MCU_FAMILY = STM32
MCU_SERIES = STM32F0xx
# linker script to use
MCU_MODEL_FAMILY = STM32F072xB
# the directory in board/
BOARD = ST_STM32F072B_DISCOVERY
# ARM version, M0/M1 are 6, M3/M4/M7 are 7
ARMV = 6
# If you want to be able to jump to bootloader from firmware (on STM32 MCUs),
# set the correct BOOTLOADER_ADDRESS here. Otherwise leave commented out.
# It is chip dependent, the correct number can be looked up here (page 175):
# http://www.st.com/web/en/resource/technical/document/application_note/CD00167594.pdf
# This also requires a patch to chibios: <tmk_dir>/tmk_core/
BOOTLOADER_ADDRESS = 0x1FFFC800

# Build Options
#   comment out to disable the options.
#
#BOOTMAGIC_ENABLE = yes	# Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = yes	# Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend
#NKRO_ENABLE = yes	# USB Nkey Rollover

include $(TMK_DIR)/tool/chibios/common.mk
include $(TMK_DIR)/tool/chibios/chibios.mk
