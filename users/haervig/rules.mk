SRC += haervig.c

ifeq ($(strip $(DANISH_ENABLE)), yes)
    OPT_DEFS += -DDANISH_ENABLE
endif
