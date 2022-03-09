ifeq ($(strip $(CTPC)), yes)
  CONVERT_TO_PROTON_C=yes
endif

ifeq ($(strip $(CONVERT_TO_PROTON_C)), yes)
  SPLIT_KEYBOARD = no       # currently unsupported on ARM
  RGBLIGHT_ENABLE = no      # currently unsupported on ARM

  EXTRAFLAGS += -DUSE_PROTON_C
else
  # Currently moved to Pro Micro only section because of lack of Proton-C support
  SPLIT_KEYBOARD = yes
  RGBLIGHT_ENABLE = yes       # Enable WS2812 RGB underlight.
endif
