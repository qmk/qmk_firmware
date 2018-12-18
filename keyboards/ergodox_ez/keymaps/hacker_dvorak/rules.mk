# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file
NKRO_ENABLE       = yes  # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
TAP_DANCE_ENABLE  = yes
MOUSEKEY_ENABLE   = yes  # Mouse keys(+4700b).
EXTRAKEY_ENABLE   = yes  # Audio control and System control(+450b).
SLEEP_LED_ENABLE  = yes  # Turn off leds when computer is sleeping.
KEY_LOCK_ENABLE   = yes  # (+1730b)
RGBLIGHT_ENABLE   = yes
LEADER_ENABLE     = yes


UNICODE_ENABLE    = no  # For Unicode.
COMMAND_ENABLE    = no  # Commands for debug and configuration
SWAP_HANDS_ENABLE = no  # Allow swapping hands of keyboard.


# This are by default off:
# CONSOLE_ENABLE    = no  # Console for debug(+400)
# BOOTMAGIC_ENABLE  = no  # Virtual DIP switch configuration(+1000)
# API_SYSEX_ENABLE  = no
# MIDI_ENABLE       = no
# UNICODEMAP_ENABLE = no
# BLUETOOTH_ENABLE  = no
# AUDIO_ENABLE      = no
# FAUXCLICKY_ENABLE = no
# VARIABLE_TRACE    = no
# BACKLIGHT_ENABLE  = no
# RGB_MATRIX_ENABLE = no
# COMBO_ENABLE      = no


# This don't need argument:
# CUSTOM_MATRIX    # Custom matrix file for the ErgoDox EZ
# SPLIT_KEYBOARD
