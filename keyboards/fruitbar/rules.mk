# MCU name
MCU = atmega32u4

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = caterina

BOOTMAGIC_ENABLE = yes       # Virtual DIP switch configuration
EXTRAKEY_ENABLE = yes       # Audio control and System control
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes            # USB Nkey Rollover
TAP_DANCE_ENABLE = no
ENCODER_ENABLE = yes		# Encoder Enable
OLED_DRIVER_ENABLE = yes	# OLED Screen Enable
OLED_ENABLE = yes
WPM_ENABLE = yes