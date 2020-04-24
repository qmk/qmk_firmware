#If using a ProMicro and it has the QMK DFU bootloader instead of Caterina,
#run "make <keyboard>:<keymap> dfu=qmk" when compiling to ensure it is flagged properly after being flashed
ifeq ($(strip $(dfu)), qmk)
    BOOTLOADER = qmk-dfu
endif

AUDIO_ENABLE = yes           # Audio output (needs a pin configured in config.h, see docs/feature_audio.md)
BACKLIGHT_ENABLE = yes       # Enable keyboard backlight functionality on B7 by default
CONSOLE_ENABLE = no 		# Console for debug(+400)
COMMAND_ENABLE = no 		# Commands for debug and configuration
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
MIDI_ENABLE = no            # MIDI support (+2400 to 4200, depending on config)
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
FAUXCLICKY_ENABLE = no      # Use buzzer to emulate clicky switches
HD44780_ENABLE = no 		# Enable support for HD44780 based LCDs (+400)