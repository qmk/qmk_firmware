ifneq ($(strip $(KEYBOARD_LOCAL_FEATURES_MK)),)
  include $(strip $(KEYBOARD_LOCAL_FEATURES_MK))
endif
