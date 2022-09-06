# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no      # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = yes      # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no      # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no           # USB Nkey Rollover
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
BLUETOOTH_ENABLE = no      # Enable Bluetooth
AUDIO_ENABLE = yes         # Audio output

ENCODER_ENABLE = yes       # ENables the use of one or more encoders
OLED_DRIVER_ENABLE = yes   # Enables the use of OLED displays
HAPTIC_ENABLE += DRV2605L  # Supported but not included by defaut

LTO_ENABLE = yes
