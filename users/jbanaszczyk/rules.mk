CONSOLE_ENABLE = yes
COMMAND_ENABLE = no

DO_NOT_SLEEP_ENABLE = yes

SRC += jbanaszczyk.c \
       do_not_sleep.c \
       process_records.c

#----------------------------------------

#ifneq ("$(wildcard $(USER_PATH)/secrets.c)","")
#    SRC += secrets.c
#endif

#ifeq ($(strip $(NO_SECRETS)), yes)
#    OPT_DEFS += -DNO_SECRETS
#endif

ifeq ($(strip $(DO_NOT_SLEEP_ENABLE)), yes)
    OPT_DEFS += -DDO_NOT_SLEEP
endif
