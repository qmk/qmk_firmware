# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

SPLIT_KEYBOARD = yes
OLED_ENABLE = yes
ENCODER_ENABLE = yes
WPM_ENABLE = yes
EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
LTO_ENABLE = yes

BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no       # Mouse keys(+4700)
CONSOLE_ENABLE = no        # Console for debug(+400)
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = no            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
UNICODE_ENABLE = no         # Unicode
RGBLIGHT_ENABLE = no   # Enable WS2812 RGB underlight.

