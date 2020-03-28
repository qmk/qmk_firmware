MOUSEKEY_ENABLE = yes       # Mouse keys
TAP_DANCE_ENABLE = yes

RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
OLED_DRIVER_ENABLE = no
LTO_ENABLE = yes

# If you use connection the Rhymestone, please enable RS_EXTRA_LED
OPT_DEFS += -DRS_EXTRA_LED

# If you want to change the display of OLED, you need to change here
SRC +=  ./common/oled_helper.c \
