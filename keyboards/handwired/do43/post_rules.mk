ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += do43_oled.c
endif

ifeq ($(strip $(COMBO_ENABLE)), yes)
    SRC += combos.c
endif
