# Space and "Red" modifier are keys I want in the easiest-to-reach position in
# the thumb row. Depending on the angle and height of the Mitosis and the type
# of keycaps you use, the upper row or the lower row of thumb keys might be more
# comfortable for you. I put red/space on the upper row and blue/shift on the
# lower, but to swap that, set MITOSIS_DATAGROK_BOTTOMSPACE = yes. This has the
# effect of swapping only the four center keys on the upper row of thumb keys with that
# of the lower row of thumb keys.
MITOSIS_DATAGROK_BOTTOMSPACE = no

# I used to use a pro micro clocked at 8Mhz. It can't reach the same baud rate
# that the standard 16Mhz-clocked pro micro can, so the baud rate needs to be
# lowered. Set this to "yes" to do that. See also
# https://github.com/reversebias/mitosis/pull/10
MITOSIS_DATAGROK_SLOWUART = no

AUDIO_ENABLE = no # audio output
FAUXCLICKY_ENABLE = no
BOOTMAGIC_ENABLE = no	# Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no	# Mouse keys(+4700)
EXTRAKEY_ENABLE = yes	# Audio control and System control(+450)
CONSOLE_ENABLE = no	# Console for debug(+400)
COMMAND_ENABLE = no	# Commands for debug and configuration
UNICODE_ENABLE = no	# Unicode
BACKLIGHT_ENABLE = no	# Enable keyboard backlight functionality
BLUETOOTH_ENABLE = no	# Enable Bluetooth with the Adafruit EZ-Key HID
MIDI_ENABLE = no	# MIDI controls

ifeq ($(strip $(MITOSIS_DATAGROK_BOTTOMSPACE)), yes)
		OPT_DEFS += -DMITOSIS_DATAGROK_BOTTOMSPACE
endif
ifeq ($(strip $(MITOSIS_DATAGROK_SLOWUART)), yes)
		OPT_DEFS += -DMITOSIS_DATAGROK_SLOWUART
endif

# vim: set ts=8 noet:
