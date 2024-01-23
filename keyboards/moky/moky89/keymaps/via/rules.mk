ENCODER_MAP_ENABLE = yes
VIA_ENABLE = yes

ifeq ($(strip $(CONSOLE_ENABLE)), yes)
    KEYBOARD_SHARED_EP := yes
endif
