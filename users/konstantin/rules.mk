SRC += konstantin.c
ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
    SRC += rgb.c
endif
ifneq (,$(filter yes IS31FL3731 IS31FL3733,$(RGB_MATRIX_ENABLE)))
    SRC += rgb.c
endif
ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    SRC += tap_dance.c
endif
ifneq (,$(filter yes,$(UNICODE_ENABLE) $(UNICODEMAP_ENABLE)))
    SRC += unicode.c
endif

EXTRAFLAGS += -flto
