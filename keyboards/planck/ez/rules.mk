# MCU name
MCU = STM32F303

# Build Options
#   comment out to disable the options.
#
BACKLIGHT_ENABLE = no
BOOTMAGIC_ENABLE = yes  # Virtual DIP switch configuration
## (Note that for BOOTMAGIC on Teensy LC you have to use a custom .ld script.)
MOUSEKEY_ENABLE = yes # Mouse keys
EXTRAKEY_ENABLE = yes # Audio control and System control
CONSOLE_ENABLE = no  # Console for debug
COMMAND_ENABLE = no    # Commands for debug and configuration
#SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes     # USB Nkey Rollover
CUSTOM_MATRIX = no # Custom matrix file
AUDIO_ENABLE = yes
RGBLIGHT_ENABLE = no
# SERIAL_LINK_ENABLE = yes
ENCODER_ENABLE = yes
RGB_MATRIX_ENABLE = IS31FL3737

LAYOUTS += ortho_4x12
