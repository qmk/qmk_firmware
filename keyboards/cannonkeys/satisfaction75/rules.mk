# MCU name
MCU = STM32F072
BOARD = GENERIC_STM32_F072XB

# Bootloader selection
BOOTLOADER = stm32-dfu

# Wildcard to allow APM32 MCU
DFU_SUFFIX_ARGS = -v FFFF -p FFFF

# Build Options
#   comment out to disable the options.
#

SRC += led.c \
      satisfaction_encoder.c \
      satisfaction_oled.c

BOOTMAGIC_ENABLE = lite     # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = yes	# Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
SLEEP_LED_ENABLE = no   # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes	    # USB Nkey Rollover
CUSTOM_MATRIX = no # Custom matrix file
ENCODER_ENABLE = yes
QWIIC_ENABLE = yes
QWIIC_DRIVERS += MICRO_OLED
#BACKLIGHT_ENABLE = yes

DEFAULT_FOLDER = cannonkeys/satisfaction75/rev1

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
