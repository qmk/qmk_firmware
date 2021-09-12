# QMK Build Options
#   change to "no" to disable the options, or define them in the rules.mk in 
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
CONSOLE_ENABLE = no         # Console for debug(+400)
COMMAND_ENABLE = yes        # Commands for debug and configuration
NKRO_ENABLE = yes           # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
MIDI_ENABLE = no            # MIDI support (+2400 to 4200, depending on config)
AUDIO_ENABLE = no           # Audio output on port C6
UNICODE_ENABLE = no         # Unicode
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight. 
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
TAP_DANCE_ENABLE = no      # Enable Tap Dance
