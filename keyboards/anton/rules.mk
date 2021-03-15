# MCU name
MCU = STM32F103

# Bootloader selection
BOARD = STM32F103C8_BOARD_FOR_ANTON



# project specific files
# VPATH += keyboards/cannonkeys/bluepill
# SRC =	keyboard.c

#BOOTMAGIC_ENABLE = yes	# Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = yes	# Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
#SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes	      # USB Nkey Rollover
#RGBLIGHT_ENABLE = yes
#WS2812_DRIVER = spi
#ENCODER_ENABLE = yes
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

# enable terminal
# TERMINAL_ENABLE = yes
