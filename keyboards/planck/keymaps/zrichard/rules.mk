# Please remove if no longer applicable
$(warning THIS FILE MAY BE TOO LARGE FOR YOUR KEYBOARD)
$(warning Please disable some options in the Makefile to resolve)

# NOTE: the maximum .hex file size on Planck is 7000h (28672 decimal)


# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE  = yes 	# Mouse keys(+4700)
EXTRAKEY_ENABLE  = yes 	# Audio control and System control(+450)
CONSOLE_ENABLE   = no 	# Console for debug(+400)
COMMAND_ENABLE   = no 	# Commands for debug and configuration
NKRO_ENABLE      = yes 	# Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = yes 	# Enable keyboard backlight functionality
MIDI_ENABLE      = yes 	# MIDI controls
AUDIO_ENABLE     = no 	# Audio output on port C6
UNICODE_ENABLE   = no 	# Unicode
BLUETOOTH_ENABLE = no  	# Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE  = no  	# Enable WS2812 RGB underlight. 
TAP_DANCE_ENABLE = no	# Enable double or n tap macros
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend

