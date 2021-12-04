# MCU name
MCU = atmega32u4

# Allow flashing with usbasp
AVRDUDE_MCU = $(MCU)

# CPU frequency divided by two since AVR is at 3.3 V
F_CPU = 8000000

# External oscillator is 16 MHz
F_USB = 16000000

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build options
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
DYNAMIC_KEYMAP_ENABLE = yes # Reconfigurable keyboard without flashing firmware
NKRO_ENABLE = yes           # USB N-key rollover
RAW_ENABLE = yes            # Raw HID commands (used by Keyboard Configurator)
RGBLIGHT_ENABLE = no        # RGB backlight (conflicts with RGB matrix)
RGB_MATRIX_ENABLE = yes     # RGB matrix
RGB_MATRIX_DRIVER = WS2812
RGB_MATRIX_CUSTOM_KB = yes  # Custom keyboard effects
USB_6KRO_ENABLE = no        # USB 6-key rollover
LTO_ENABLE = yes            # Link-time optimization for smaller binary

# Add System76 EC command interface
SRC += ../system76_ec.c

# Add I2C driver
QUANTUM_LIB_SRC += i2c_master.c

# Add USB mux driver
SRC += usb_mux.c
