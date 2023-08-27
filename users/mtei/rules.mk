VPATH += $(USER_PATH)/$(PLATFORM_PATH)
VPATH += $(USER_PATH)/$(PLATFORM_PATH)/$(PLATFORM_KEY)

CUSTOM_MATRIX_DELAY = on-demand

ifneq ($(strip $(USROPT)),)
  include $(USER_PATH)/user_options.mk
endif
include $(USER_PATH)/user_featues.mk
