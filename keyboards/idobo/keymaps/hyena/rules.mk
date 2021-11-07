UNICODE_ENABLE    = no
UNICODEMAP_ENABLE = yes

ifeq ($(strip $(UNICODEMAP_ENABLE)), yes)
  SRC += unicode.c
endif
