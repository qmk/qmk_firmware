# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina  # controller pro micro
# BOOTLOADER = atmel-dfu   # controller Elite-C



# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = no       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no       # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
KEY_LOCK_ENABLE = yes       # kc_lock use


OLED_ENABLE = no
OLED_DRIVER = SSD1306      # OLED display
SPLIT_KEYBOARD = yes       # split type

