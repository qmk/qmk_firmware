SRC += $(USER_PATH)/itg.c \
       $(USER_PATH)/keyrecords/process_records.c \

ifneq ("$(wildcard $(USER_PATH)/keyrecords/secrets.c)","")
  SRC += $(USER_PATH)/keyrecords/secrets.c
endif

ifeq ($(strip $(NO_SECRETS)), yes)
  OPT_DEFS += -DNO_SECRETS
endif

VIRTSER_ENABLE = yes
FORCE_NKRO = yes
MOUSEKEY_ENABLE = no
