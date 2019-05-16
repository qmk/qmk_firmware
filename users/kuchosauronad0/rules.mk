SRC += kuchosauronad0.c \
	   process_records.c

LINK_TIME_OPTIMIZATION_ENABLE = yes

#ifneq ("$(wildcard $(USER_PATH)/secrets.c)","")
#     SRC += secrets.c
#endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
     SRC += tap_dances.c
endif

ifeq ($(strip $(LEADER_ENABLE)), yes)
     SRC += leader.c
endif

ifeq ($(strip $(NO_SECRETS)), yes)
     OPT_DEFS += -DNO_SECRETS
     ifneq ("$(wildcard $(USER_PATH)/secrets.c)","") # Include secrets.c if NO_SECRETS = yes
          SRC += secrets.c
     endif
endif
ifeq ($(strip $(UNICODEMAP_ENABLE)), yes)
     SRC += unicode.c
endif

ifeq ($(strip $(MACROS_ENABLED)), yes)
     OPT_DEFS += -DMACROS_ENABLED
endif

ifdef CONSOLE_ENABLE
     ifeq ($(strip $(KEYLOGGER_ENABLE)), yes)
         OPT_DEFS += -DKEYLOGGER_ENABLE
     endif
endif

ifeq ($(strip $(MAKE_BOOTLOADER)), yes)
     OPT_DEFS += -DMAKE_BOOTLOADER
endif
