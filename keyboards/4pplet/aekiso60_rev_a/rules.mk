# MCU name
MCU = atmega32u2

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = atmel-dfu

# Build Options
#   comment out to disable the options.
#
# BOOTMAGIC_ENABLE 		= no	# Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE 		= no	# Mouse keys(+4700)
EXTRAKEY_ENABLE 		= yes	# Audio control and System control(+450)
CONSOLE_ENABLE 			= no # Console for debug(+400)
# COMMAND_ENABLE 		= no # Commands for debug and configuration
NKRO_ENABLE 			= no # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
MIDI_ENABLE 			= no # MIDI controls
AUDIO_ENABLE 			= no
UNICODE_ENABLE 			= no # Unicode
RAW_ENABLE 				= yes
BACKLIGHT_ENABLE 		= no 
RGBLIGHT_ENABLE 		= no
VIA_ENABLE				= yes
