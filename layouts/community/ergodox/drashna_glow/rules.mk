USER_NAME := drashna

CORRECTED_LAYOUT := $(LAYOUTS_REPO)/$(LAYOUT)/drashna

SRC += $(CORRECTED_LAYOUT)/keymap.c

-include $(CORRECTED_LAYOUT)/rules.mk

ifeq ($(strip $(KEYBOARD)), ergodox_ez)
	RGBLIGHT_ENABLE = yes
	RGB_MATRIX_ENABLE = yes
	TAP_DANCE_ENABLE  = no
	CONSOLE_ENABLE     = no
	BOOTMAGIC_ENABLE   = lite

	UNICODE_ENABLE     = yes
	UNICDOEMAP_ENABLE  = no

	RGBLIGHT_TWINKLE   = no
	INDICATOR_LIGHTS   = no
	RGBLIGHT_STARTUP_ANIMATION = no
endif
