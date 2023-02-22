BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
CONSOLE_ENABLE = yes   # Console for debug
BACKLIGHT_ENABLE = no  # Enable keyboard backlight functionality
NKRO_ENABLE = yes
LTO_ENABLE = yes

SRC += init.c
SRC += spidey3.c

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
  SRC += layer_rgb.c
endif
ifeq ($(strip $(UNICODEMAP_ENABLE)), yes)
  SRC += spidey3_unicode.c
endif
