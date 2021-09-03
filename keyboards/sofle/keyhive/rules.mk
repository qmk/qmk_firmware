MCU = atmega32u4


BOOTLOADER = atmel-dfu

# Build Options
# Comment out to disable the options.

SPLIT_KEYBOARD = yes    # Split keyboard
BOOTMAGIC_ENABLE = no   # Virtual DIP switch configuration
CONSOLE_ENABLE = no	    # Console for debug
EXTRAKEY_ENABLE = yes   # Audio control and System control
RGBLIGHT_ENABLE = yes   # RGB lighting
ENCODER_ENABLE = yes    # Encoders
MOUSEKEY_ENABLE = no    # Mouse keys
NKRO_ENABLE = yes       # Enables NKRO
LTO_ENABLE = yes        # Enables Link Time Optimization

OLED_ENABLE = yes       # Enables OLED Display
OLED_DRIVER = SSD1306	# Specify OLED driver
WPM_ENABLE = no         # WPM counter
