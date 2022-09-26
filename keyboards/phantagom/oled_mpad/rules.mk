# MCU name
MCU = RP2040
# Bootloader selection
BOOTLOADER = rp2040
# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
WPM_ENABLE = yes
OLED_ENABLE = yes
OLED_DRIVER = SSD1306

OPT_DEFS += -DHAL_USE_I2C=TRUE

LAYOUTS = numpad_6x5
