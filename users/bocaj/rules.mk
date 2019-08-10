SRC += bocaj.c \
       process_records.c

ifneq ("$(wildcard $(USER_PATH)/secrets.c)","")
  SRC += secrets.c
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
  SRC += tap_dances.c
endif

# Caused problems when building via docker on Mac OS
# EXTRAFLAGS += -flto

ifeq ($(strip $(NO_SECRETS)), yes)
    OPT_DEFS += -DNO_SECRETS
endif

ifeq ($(strip $(MACROS_ENABLED)), yes)
    OPT_DEFS += -DMACROS_ENABLED
endif

ifeq ($(strip $(UCIS_ENABLE)), yes)
  SRC += send_unicode.c
endif

ifeq ($(strip $(UNICODEMAP_ENABLE)), yes)
  SRC += send_unicode.c
endif

ifeq ($(strip $(UNICODE_ENABLE)), yes)
  SRC += send_unicode.c
endif
