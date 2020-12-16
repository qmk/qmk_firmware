CFLAGS += -Wno-error=deprecated

EXTRALDFLAGS += -Wl,--build-id=none


SRC += muse.c
SRC += tap.c
# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file

CONSOLE_ENABLE = no
COMMAND_ENABLE = no

WEBUSB_ENABLE = yes
ORYX_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes
TAP_DANCE_ENABLE = yes
RGBLIGHT_ENABLE = yes
