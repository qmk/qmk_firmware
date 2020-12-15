# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file

SRC += tap.c
SRC += muse.c
SRC += matrix.c


LTO_ENABLE = yes
COMMAND_ENABLE = no
WEBUSB_ENABLE = yes
ORYX_ENABLE = yes
DYNAMIC_MACRO_ENABLE = no

RGBLIGHT_ENABLE =no
RGB_MATRIX_ENABLE = yes
TAP_DANCE_ENABLE = yes

