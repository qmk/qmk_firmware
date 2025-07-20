SRC += matrix.c he_switch_matrix.c graphics/display.c graphics/quinquefive.qff.c
CUSTOM_MATRIX = lite
ANALOG_DRIVER_REQUIRED = yes
QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS += sh1106_i2c

ifeq ($(strip $(VIA_ENABLE)), yes)
    SRC += via_he.c
endif
