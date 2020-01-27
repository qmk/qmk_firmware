# MCU name
MCU = STM32F103

# GENERIC STM32F103C8T6 board - stm32duino bootloader
OPT_DEFS = -DCORTEX_VTOR_INIT=0x2000
MCU_LDSCRIPT = STM32F103x8_stm32duino_bootloader
BOARD = GENERIC_STM32_F103

DFU_ARGS = -d 1eaf:0003 -a2 -R
DFU_SUFFIX_ARGS = -v 1eaf -p 0003

# project specific files
VPATH += keyboards/cannonkeys/bluepill
SRC =	led.c \
      keyboard.c

#BOOTMAGIC_ENABLE = yes	# Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = yes	# Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes	    # USB Nkey Rollover
BACKLIGHT_ENABLE = yes
RGBLIGHT_ENABLE = yes

LAYOUTS = ortho_4x12
