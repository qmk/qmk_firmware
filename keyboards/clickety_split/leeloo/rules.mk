# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina       # Pro Micro
#BOOTLOADER = atmel-dfu		# Elite-C

# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = no      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = no       # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = no           # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
AUDIO_ENABLE = no          # Audio output
RGBLIGHT_ENABLE = no       # Enable WS2812 RGB underlight.
SWAP_HANDS_ENABLE = no     # Enable one-hand typing
TAP_DANCE_ENABLE = no      # Enable Tap Dance
COMBO_ENABLE = no          # Enable Combos

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no      # Breathing sleep LED during USB suspend

# To enable Rotary Encoders
ENCODER_ENABLE = no

# To enable OLED Displays
OLED_ENABLE = no
OLED_DRIVER = SSD1306      # OLED display

SPLIT_KEYBOARD = yes
DEFAULT_FOLDER = clickety_split/leeloo/rev1
