SRC += ishtob.c
ifneq ("$(wildcard $(USER_PATH)/macros_private.c)","")
  SRC += macros_private.c
endif
ifeq ($(strip $(NO_SECRETS)), yes)
    OPT_DEFS += -DNO_SECRETS
endif
