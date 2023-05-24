SRC += alinelena.c
ifeq ($(strip $(UNICODEMAP_ENABLE)), yes)
  SRC += alinelena_unicode.c
endif
