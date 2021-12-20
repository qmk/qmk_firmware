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

BOOTMAGIC_ENABLE = lite       # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes            # USB Nkey Rollover
RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
TAP_DANCE_ENABLE = no
ENCODER_ENABLE = yes		# Encoder Enable
OLED_DRIVER_ENABLE = yes	# OLED Screen Enable
