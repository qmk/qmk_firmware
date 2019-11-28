SRC += spacebarracecar.c

ifeq ($(strip $(GERMAN_ENABLE)), yes)
    OPT_DEFS += -DGERMAN_ENABLE
endif
