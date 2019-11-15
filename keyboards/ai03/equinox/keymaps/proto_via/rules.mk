# project specific files
SRC =	keyboards/wilba_tech/wt_main.c

# Build Options
RAW_ENABLE = yes
DYNAMIC_KEYMAP_ENABLE = yes

# Fix for prototype missing COL0, COL1, using backlight and RGB underglow I/O pins
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality on B7 by default
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
