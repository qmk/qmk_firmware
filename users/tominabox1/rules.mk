# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
CONSOLE_ENABLE = no
TAP_DANCE_ENABLE = yes
NKRO_ENABLE = yes


ifeq ($(strip $(KEYBOARD)), crkbd/rev1)
RGB_MATRIX_ENABLE = WS2812
EXTRAFLAGS += -flto

BOOTLOADER = qmk-dfu

OLED_DRIVER_ENABLE = yes
endif

SRC += tominabox1.c
