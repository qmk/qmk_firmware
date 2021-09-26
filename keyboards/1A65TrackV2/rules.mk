# MCU name
MCU = atmega32u4
BOOTLOADER = qmk-dfu	    # Elite - C

# Build Options
#   comment out to disable the options.
#
BACKLIGHT_ENABLE = no
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # USB Nkey Rollover
AUDIO_ENABLE = no
RGBLIGHT_ENABLE = yes	    # Using the WS2812b strip	    
MIDI_ENABLE = no            # MIDI support (+2400 to 4200, depending on config)
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
FAUXCLICKY_ENABLE = no      # Use buzzer to emulate clicky switches
HD44780_ENABLE = no 		# Enable support for HD44780 based LCDs (+400)
NO_SUSPEND_POWER_DOWN = no
UNICODEMAP_ENABLE = no
ENCODER_ENABLE = yes
SPLIT_KEYBOARD = yes	    # Enable split keyboard functionalities
POINTING_DEVICE_ENABLE = yes 	#Trackball support
SRC += spi_master.c
SRC += pmw/pmw.c
DISABLE_JTAG = yes
LTO_ENABLE = yes
SPACE_CADET_ENABLE=no

EXTRAFLAGS        += -flto