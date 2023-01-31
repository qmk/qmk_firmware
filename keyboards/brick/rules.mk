# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   comment out to disable the options.
#
# EXTRAFLAGS+=-flto
LTO_ENABLE = yes
BACKLIGHT_ENABLE = no
BOOTMAGIC_ENABLE = no 	# Virtual DIP switch configuration
MOUSEKEY_ENABLE = no    # Mouse keys
EXTRAKEY_ENABLE = yes   # Audio control and System control
CONSOLE_ENABLE = no     # Console for debug
COMMAND_ENABLE = no     # Commands for debug and configuration
SLEEP_LED_ENABLE = no   # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes       # USB Nkey Rollover
RGBLIGHT_ENABLE = yes    # RGB lighting
ENCODER_ENABLE = yes
AUDIO_ENABLE = no

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

# Extra compatibility with standard Planck's layouts
LAYOUTS += ortho_4x12
