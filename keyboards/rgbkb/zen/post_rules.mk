ifeq ($(strip $(CONVERT_TO)), proton_c)
  RGBLIGHT_ENABLE = no  # OOB incompatible with split on ARM
endif
