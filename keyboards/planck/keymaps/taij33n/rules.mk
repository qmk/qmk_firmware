# avrdude -p atmega32u4 -P /dev/ttyACM0 -c avr109 -U flash:w:../../planck_rev4_taij33n.hex
#
MCU = atmega32u4
F_CPU = 16000000
ARCH = AVR8
F_USB = $(F_CPU)
BOOTLOADER = caterina
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

# # Build Options
# #   change to "no" to disable the options, or define them in the makefile.mk in 
# #   the appropriate keymap folder that will get included automatically
# #
BOOTMAGIC_ENABLE 	= no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE 	= yes        # Mouse keys(+4700)
EXTRAKEY_ENABLE 	= yes       # Audio control and System control(+450)
CONSOLE_ENABLE 		= no         # Console for debug(+400)
COMMAND_ENABLE 		= no        # Commands for debug and configuration
NKRO_ENABLE 			= yes 		# Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE 	= no       # Enable keyboard backlight functionality
MIDI_ENABLE 			= no            # MIDI controls
AUDIO_ENABLE 			= no           # Audio output on port C6
UNICODE_ENABLE 		= no         # Unicode
BLUETOOTH_ENABLE 	= no       # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE 	= no        # Enable WS2812 RGB underlight.  Do not enable this with audio at the same time.
# TAP_DANCE_ENABLE = yes      # Enables the double-tap functionality of keys
#
# # Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE 	= no       # Breathing sleep LED during USB suspend

