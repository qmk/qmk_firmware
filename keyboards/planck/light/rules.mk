# MCU name
MCU = at90usb1286

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes         # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = yes            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
MIDI_ENABLE = yes           # MIDI support
AUDIO_ENABLE = yes           # Audio output
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = IS31FL3731

LAYOUTS = ortho_4x12 planck_mit
LAYOUTS_HAS_RGB = no
