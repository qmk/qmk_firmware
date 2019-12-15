RGBLIGHT_ENABLE = yes
# Enable RGBLIGHT Animations
OPT_DEFS += -DRGBLIGHT_ANIMATIONS
# Helix specific define for correct RGBLED_NUM
OPT_DEFS += -DRGBLED_BACK

OLED_DRIVER_ENABLE = yes
# Helix specific font file
OPT_DEFS += -DOLED_FONT_H=\"common/glcdfont.c\"
# Xulkal specific oled define
OPT_DEFS += -DOLED_90ROTATION

SPLIT_KEYBOARD = yes
