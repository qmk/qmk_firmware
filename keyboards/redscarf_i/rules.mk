# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE   = no      # Mouse keys
EXTRAKEY_ENABLE   = yes     # Audio control and System control
CONSOLE_ENABLE    = no      # Console for debug
COMMAND_ENABLE    = no      # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE  = no      # Breathing sleep LED during USB suspend
BACKLIGHT_ENABLE  = yes     # Enable keyboard backlight functionality
RGBLIGHT_ENABLE   = no      # Enable keyboard RGB underglow
AUDIO_ENABLE      = no      # Audio output

LAYOUTS = ortho_5x4 ortho_6x4 numpad_5x4 numpad_6x4
