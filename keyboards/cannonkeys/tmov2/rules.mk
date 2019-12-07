# project specific files
# SRC = ssd1306.c
## chip/board settings
# the next two should match the directories in
#  <chibios>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
MCU_FAMILY = STM32
MCU_SERIES = STM32F0xx
# linker script to use
# it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
#  or <this_dir>/ld/
MCU_LDSCRIPT = STM32F072xB
# startup code to use
# is should exist in <chibios>/os/common/ports/ARMCMx/compilers/GCC/mk/
MCU_STARTUP = stm32f0xx
# it should exist either in <chibios>/os/hal/boards/
#  or <this_dir>/boards
BOARD = ST_STM32F072B_DISCOVERY
# Cortex version
# Teensy LC is cortex-m0; Teensy 3.x are cortex-m4
MCU  = cortex-m0
# ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
ARMV = 6
# If you want to be able to jump to bootloader from firmware on STM32 MCUs,
# set the correct BOOTLOADER_ADDRESS. Either set it here, or define it in
# ./bootloader_defs.h or in ./boards/<FOO>/bootloader_defs.h (if you have
# a custom board definition that you plan to reuse).
# If you're not setting it here, leave it commented out.
# It is chip dependent, the correct number can be looked up here (page 175):
# http://www.st.com/web/en/resource/technical/document/application_note/CD00167594.pdf
# This also requires a patch to chibios:
#   <tmk_dir>/tmk_core/tool/chibios/ch-bootloader-jump.patch
#STM32_BOOTLOADER_ADDRESS = 0x1FFFC800

# Build Options
#   comment out to disable the options.
#

# Options to pass to dfu-util when flashing
DFU_ARGS = -d 0483:df11 -a 0 -s 0x08000000:leave
DFU_SUFFIX_ARGS = -p DF11 -v 0483

# Build Options
#   comment out to disable the options.
#

# project specific files
VPATH += keyboards/cannonkeys/stm32f072
SRC =	keyboard.c \
      led.c

DFU_ARGS = -d 0483:df11 -a 0 -s 0x08000000:leave
DFU_SUFFIX_ARGS = -v 0483 -p DF11

BOOTMAGIC_ENABLE = lite	# Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = yes	# Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes	    # USB Nkey Rollover
CUSTOM_MATRIX = no # Custom matrix file
# BACKLIGHT_ENABLE = yes # This is broken on 072 right now
RGBLIGHT_ENABLE = yes

