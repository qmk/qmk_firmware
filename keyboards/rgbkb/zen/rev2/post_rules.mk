# Setup so that OLED can be turned on/off easily
ifeq ($(strip $(OLED_ENABLE)), yes)
  # Custom local font file
  OPT_DEFS += -DOLED_FONT_H=\"common/glcdfont.c\"
endif
