# AVR MCU options
MCU = atmega32u4       # MCU name
BOOTLOADER = atmel-dfu # Bootloader selection
F_CPU = 8000000# CPU frequency divided by two since AVR is at 3.3 V
F_USB = 16000000# External oscillator is 16 MHz

# Feature options
BOOTMAGIC_ENABLE = yes      # Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and system control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
DYNAMIC_KEYMAP_ENABLE = yes # Reconfigurable keyboard without flashing firmware
NKRO_ENABLE = yes           # USB N-key rollover
RAW_ENABLE = yes            # Raw HID commands (used by Keyboard Configurator)
RGB_MATRIX_ENABLE = yes     # RGB matrix
RGB_MATRIX_DRIVER = WS2812
RGB_MATRIX_CUSTOM_KB = yes  # Custom keyboard effects

# Build options
LTO_ENABLE = yes # Link-time optimization for smaller binary
SRC += usb_mux.c# Add USB mux driver
QUANTUM_LIB_SRC += i2c_master.c# Add I2C driver
