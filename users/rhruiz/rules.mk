SRC += rhruiz.c

ifeq ($(strip $(RAW_ENABLE)), yes)
    SRC += rhruiz_raw_hid.c
endif
