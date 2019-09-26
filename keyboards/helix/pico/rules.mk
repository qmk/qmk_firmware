SRC += local_drivers/i2c.c
SRC += local_drivers/serial.c
SRC += local_drivers/ssd1306.c
KEYBOARD_PATHS += $(KEYBOARD_TOP_DIR)/local_drivers

CUSTOM_MATRIX = yes

SRC += pico/matrix.c
SRC += pico/split_util.c
