# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = no        # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE  = yes       # Mouse keys(+4700)
EXTRAKEY_ENABLE  = yes       # Audio control and System control(+450)
CONSOLE_ENABLE   = yes       # Console for debug(+400)
COMMAND_ENABLE   = no        # Commands for debug and configuration
BACKLIGHT_ENABLE = no        # Enable keyboard backlight functionality
BLUETOOTH_ENABLE = no        # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE  = no        # Enable WS2812 RGB underlight.
                             #   note: this option is not for Planck `light`
NKRO_ENABLE      = yes       # Nkey Rollover - if this doesn't work, see here:
# https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work

MIDI_ENABLE          = no
UNICODE_ENABLE       = no
KEY_LOCK_ENABLE      = yes
DYNAMIC_MACRO_ENABLE = no    # TODO: fix this later

# # for `rev4`
# AUDIO_ENABLE         = no    # Audio output on port C6
# DEBOUNCE_TYPE        = sym_defer_g

# for `light` and `rev6`
AUDIO_ENABLE         = yes   # Audio output on port C6
DEBOUNCE_TYPE        = sym_defer_pk
