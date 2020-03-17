
SRC += init.c
SRC += process_record_user.c

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
  SRC += rgb_caps_lock.c
endif
ifeq ($(strip $(UNICODEMAP_ENABLE)), yes)
  SRC += unicode.c
endif
