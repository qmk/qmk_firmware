SRC += narze.c

ifeq ($(strip $(COMBO_ENABLE)), yes)
    SRC += superduper.c
endif
