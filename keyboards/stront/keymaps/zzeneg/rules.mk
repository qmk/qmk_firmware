CONSOLE_ENABLE = yes

EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = yes
CAPS_WORD_ENABLE = yes
ENCODER_MAP_ENABLE = yes

POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c

QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS += st7789_spi
QUANTUM_PAINTER_LVGL_INTEGRATION = yes

OPT_DEFS = -O2

RAW_ENABLE = yes

SRC +=  lvgl_helpers.c \
  		./display.c \
		./fonts/montserrat_24_en_ru.c \
		./fonts/montserrat_48_digits.c \
		./icons/flag_uk.c \
		./icons/flag_ru.c \
		./icons/flag_pl.c \
		./images/fine.c
