# I use an 8Mhz Pro Micro
F_CPU = 8000000
# Necessary, with above change?
F_USB = $(F_CPU)

BOOTMAGIC_ENABLE = no	# Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no	# Mouse keys(+4700)
EXTRAKEY_ENABLE = yes	# Audio control and System control(+450)
CONSOLE_ENABLE = no	# Console for debug(+400)
COMMAND_ENABLE = no	# Commands for debug and configuration
UNICODE_ENABLE = no	# Unicode
BACKLIGHT_ENABLE = no	# Enable keyboard backlight functionality
BLUETOOTH_ENABLE = no	# Enable Bluetooth with the Adafruit EZ-Key HID
MIDI_ENABLE = no	# MIDI controls
# vim: set ts=8 noet:
