# MCU Configuration
# Note: processor and bootloader are defined in keyboard.json

# i2c_master is used by the core OLED driver on I2C1. The AS5600 on I2C0 is
# driven directly via the ChibiOS API in macro2040.c.
I2C_DRIVER_REQUIRED = yes

# Human-readable keycode names for the keyboard-level OLED last-key display.
KEYCODE_STRING_ENABLE = yes
