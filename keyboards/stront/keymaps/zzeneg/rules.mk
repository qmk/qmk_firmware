# CONSOLE_ENABLE = yes

EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = yes
CAPS_WORD_ENABLE = yes
ENCODER_MAP_ENABLE = yes
DYNAMIC_TAPPING_TERM_ENABLE = yes

POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c

RAW_ENABLE = yes

SRC +=  zzeneg_display.c \
		fonts/montserrat_20_en_ru.c \
		fonts/montserrat_48_digits.c \
		icons/flag_uk.c \
		icons/flag_ru.c
