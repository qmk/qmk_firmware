# CPU frequency divided by two since AVR is at 3.3 V
F_CPU = 8000000

# External oscillator is 16 MHz
F_USB = 16000000

RGB_MATRIX_CUSTOM_KB = yes  # Custom keyboard effects

# Add System76 EC command interface as well as I2C and USB mux drivers
SRC += system76_ec.c usb_mux.c
I2C_DRIVER_REQUIRED = yes
