# MCU Configuration
# Note: processor and bootloader are defined in keyboard.json

# I2C0 for AS5600 (via QMK i2c_master)
I2C_DRIVER_REQUIRED = yes

# Enable RGB Matrix (required for VIA lighting menu)
RGB_MATRIX_ENABLE = yes

# Custom matrix scan with extended row-settle delay (see matrix.c).
# Required so SW9 (the only key on row 3 / GP11) is detected reliably.
SRC += matrix.c

# Custom OLED driver on I2C1 (see oled_custom.c). Lives at the keyboard
# level so every keymap (default, via, ...) gets a working display.
SRC += oled_custom.c

# Shared "keycode -> short label" helper used by both the keyboard-level
# basic OLED (macro2040.c) and richer keymap renderers (extended/keymap.c).
SRC += keycode_label.c
