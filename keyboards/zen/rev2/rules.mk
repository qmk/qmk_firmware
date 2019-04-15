ENCODER_ENABLE = yes

OLED_DRIVER_ENABLE = no
OLED_ROTATE90 = yes

# Setup so that OLED and 90 degree rotation can be turned on/off easily
# with "OLED_DRIVER_ENABLE = yes" or "OLED_ROTATE90 = no" in user's rules.mk file
ifeq ($(strip $(OLED_DRIVER_ENABLE)), yes)
  # Custom local font file
  OPT_DEFS += -DOLED_FONT_H=\"common/glcdfont.c\"
  ifeq ($(strip $(OLED_DRIVER_ENABLE)), yes)
    OPT_DEFS += -DOLED_ROTATE90
  endif
endif
