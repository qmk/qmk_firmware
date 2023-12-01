RGB_MATRIX_ENABLE = yes
RGBLIGHT_ENABLE = no
SPLIT_KEYBOARD = yes
TAP_DANCE_ENABLE = yes
MOUSEKEY_ENABLE = no
OLED_ENABLE = yes


# Link Time Optimization (Reduces compiled size)
LTO_ENABLE = yes

SRC += ./process_records.c

ifeq ($(TAP_DANCE_ENABLE),yes)
	SRC += ./tap_dances.c
endif

ifeq ($(OLED_ENABLE),yes)
	SRC += ./oled.c
endif
