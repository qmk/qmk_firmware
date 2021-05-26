# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes           # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
BLUETOOTH_ENABLE = no       # Enable Bluetooth
AUDIO_ENABLE = yes          # Audio output

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
