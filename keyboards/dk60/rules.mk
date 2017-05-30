MCU = atmega32u4
F_CPU = 16000000
ARCH = AVR8
F_USB = $(F_CPU)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT
OPT_DEFS += -DBOOTLOADER_SIZE=4096

BOOTMAGIC_ENABLE ?= yes	# Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE ?= no	# Mouse keys(+4700)
EXTRAKEY_ENABLE ?= yes	# Audio control and System control(+450)
# CONSOLE_ENABLE ?= yes	# Console for debug(+400)
# COMMAND_ENABLE ?= yes    # Commands for debug and configuration
KEYBOARD_LOCK_ENABLE ?= yes	# Allow locking of keyboard via magic key
NKRO_ENABLE ?= yes		# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
RGBLIGHT_ENABLE ?= no   # Enable keyboard underlight functionality (+4870)
BACKLIGHT_ENABLE ?= no  # Enable keyboard backlight functionality (+1150)
MIDI_ENABLE ?= no 		# MIDI controls
AUDIO_ENABLE ?= no
UNICODE_ENABLE ?= yes 		# Unicode
BLUETOOTH_ENABLE ?= no # Enable Bluetooth with the Adafruit EZ-Key HID
SLEEP_LED_ENABLE ?= yes
