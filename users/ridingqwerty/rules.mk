#LEADER_ENABLE = yes

SRC += ridingqwerty.c \
       process_records.c

ifneq ("$(wildcard $(USER_PATH)/secrets.c)","")
  SRC += secrets.c
endif
