# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina  # ProMicro
#BOOTLOADER = atmel-dfu  # Elite-C, SeaMicro etc.

# Build Options
#   change yes to no to disable
#
AUDIO_ENABLE = no           # Audio output
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
BLUETOOTH_ENABLE = no       # Enable Bluetooth
BOOTMAGIC_ENABLE = lite     # Enable Bootmagic Lite
COMMAND_ENABLE = no         # Commands for debug and configuration
CONSOLE_ENABLE = no         # Console for debug
DEBOUNCE_TYPE = sym_eager_pk
EXTRAKEY_ENABLE = no        # Audio control and System control
LTO_ENABLE = yes            # Link time optimise, reduce firmware size
MOUSEKEY_ENABLE = no        # Mouse keys
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes           # USB Nkey Rollover
OLED_DRIVER = SSD1306
OLED_ENABLE = yes
RGBLIGHT_ENABLE = yes       # Enable keyboard RGB underglow
