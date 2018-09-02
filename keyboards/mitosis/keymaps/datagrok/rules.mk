AUDIO_ENABLE = yes # audio output
FAUXCLICKY_ENABLE = no
# I used to use a pro micro clocked at 8Mhz. It can't reach the same baud rate
# that the standard 16Mhz-clocked pro micro can, so the baud rate needs to be
# lowered. Set this to "yes" to do that. See also
# https://github.com/reversebias/mitosis/pull/10
MITOSIS_DATAGROK_SLOWUART = no

BOOTMAGIC_ENABLE = no	# Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no	# Mouse keys(+4700)
EXTRAKEY_ENABLE = yes	# Audio control and System control(+450)
CONSOLE_ENABLE = no	# Console for debug(+400)
COMMAND_ENABLE = no	# Commands for debug and configuration
UNICODE_ENABLE = no	# Unicode
BACKLIGHT_ENABLE = no	# Enable keyboard backlight functionality
BLUETOOTH_ENABLE = no	# Enable Bluetooth with the Adafruit EZ-Key HID
MIDI_ENABLE = no	# MIDI controls
ifeq ($(strip $(MITOSIS_DATAGROK_SLOWUART)), yes)
		OPT_DEFS += -DMITOSIS_DATAGROK_SLOWUART
endif

# vim: set ts=8 noet:
