# MCU name
MCU = atmega32u4

# Interrupt driven control endpoint task(+60)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

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
#   change yes to no to disable

VIA_ENABLE = yes			# Use Via
OLED_DRIVER_ENABLE = yes	# OLED Screen
RGBLIGHT_ENABLE = yes       # Enable keyboard RGB underglow
EXTRAKEY_ENABLE = yes       # Audio control and System control
ENCODER_ENABLE = yes        # Use rotary encoder
LTO_ENABLE = yes            # Link-time optimization
WPM_ENABLE = yes			# Bongo Cat WPM meter
NO_USB_STARTUP_CHECK = yes	# OSX Fix stated in Readme
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
BOOTMAGIC_ENABLE = yes       # Virtual DIP switch configuration
TAP_DANCE_ENABLE = yes

SRC += matrix.c \
       bitc_led.c \
       remote_kb.c \
	   i2c_master.c  \
       tmk_core/common/uart.c

