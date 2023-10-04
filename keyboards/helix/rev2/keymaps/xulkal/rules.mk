RGBLIGHT_ENABLE = yes
# Helix specific define for correct RGBLED_NUM
OPT_DEFS += -DRGBLED_BACK

OLED_ENABLE = yes
# Helix specific font file
OPT_DEFS += -DOLED_FONT_H=\"common/glcdfont.c\"
# Xulkal specific oled define
OPT_DEFS += -DOLED_90ROTATION

SPLIT_KEYBOARD = yes

# Explicitly disable helix standard post-processing
KEYBOARD_LOCAL_FEATURES_MK :=
