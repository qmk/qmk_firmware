SRC += ridingqwerty.c \
       process_records.c

ifneq ("$(wildcard $(USER_PATH)/secrets.c)","")
  SRC += secrets.c
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
  SRC += tapdances.c
endif

ifeq ($(strip $(UNICODEMAP_ENABLE)), yes)
  SRC += unicode.c
endif
