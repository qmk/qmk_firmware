# https://docs.qmk.fm/#/getting_started_make_guide?id=rulesmk-options
# MCU name

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp

# Build Options
EXTRAKEY_ENABLE = yes	# Audio control and System control(+450)
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes		# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = yes  # Enable keyboard backlight functionality
MIDI_ENABLE = no
AUDIO_ENABLE = no
KEY_LOCK_ENABLE = yes
RGBLIGHT_ENABLE = no
BLUETOOTH_ENABLE = no
