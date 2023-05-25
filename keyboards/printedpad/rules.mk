
ifeq ($(KEYMAP), noah)
	SRC += oled2.c
else
	SRC += oled1.c
endif

OLED_ENABLE = yes
LTO_ENABLE = yes