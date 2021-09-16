# As long as the users rules.mk has include $(KEYBOARD)/post_rules.mk this will be run after to properly setup any keyboard features and defines

ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += do43_oled.c
endif

ifeq ($(strip $(COMBO_ENABLE)), yes)
    SRC += combos.c
endif
