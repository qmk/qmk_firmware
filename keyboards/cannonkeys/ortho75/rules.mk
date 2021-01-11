# project specific files
VPATH += keyboards/cannonkeys/bluepill
SRC =	led.c \
      keyboard.c

# GENERIC STM32F103C8T6 board - stm32duino bootloader
OPT_DEFS = -DCORTEX_VTOR_INIT=0x2000
MCU_LDSCRIPT = STM32F103x8_stm32duino_bootloader
BOARD = GENERIC_STM32_F103

# OPT_DEFS =
# MCU_LDSCRIPT = STM32F103x8
# BOARD = GENERIC_STM32_F103

## chip/board settings
# the next two should match the directories in
#  <chibios>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
MCU_FAMILY = STM32
MCU_SERIES = STM32F1xx
# linker script to use
# it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
#  or <this_dir>/ld/
# startup code to use
# is should exist in <chibios>/os/common/ports/ARMCMx/compilers/GCC/mk/
MCU_STARTUP = stm32f1xx
# it should exist either in <chibios>/os/hal/boards/
#  or <this_dir>/boards
# Cortex version
# Teensy LC is cortex-m0; Teensy 3.x are cortex-m4
MCU  = cortex-m3
# ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
ARMV = 7
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

DFU_ARGS = -d 1eaf:0003 -a 2 -R

#BOOTMAGIC_ENABLE = yes	# Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = yes	# Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes	    # USB Nkey Rollover
BACKLIGHT_ENABLE = yes
RGBLIGHT_ENABLE = yes
ENCODER_ENABLE = yes

LAYOUTS = ortho_5x15
