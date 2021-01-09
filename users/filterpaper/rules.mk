# Disable defaults for space
VIA_ENABLE = no
NKRO_ENABLE = no
STENO_ENABLE = no
UNICODE_ENABLE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no
TERMINAL_ENABLE = no
KEY_LOCK_ENABLE = no
BOOTMAGIC_ENABLE = no
VELOCIKEY_ENABLE = no
SLEEP_LED_ENABLE = no
TAP_DANCE_ENABLE = no
SWAP_HANDS_ENABLE = no
SPACE_CADET_ENABLE = no

RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = no

# Common features
LEADER_ENABLE = yes
EXTRAKEY_ENABLE = yes

# Platform and keyboard specific settings
ifneq ($(PLATFORM),CHIBIOS)
	LTO_ENABLE = yes
endif
ifeq ($(strip $(KEYBOARD)), the_mark)
	RGBLIGHT_ENABLE = yes
endif
ifeq ($(strip $(KEYBOARD)), bm40hsrgb) || ($(strip $(KEYBOARD)), kbdfans/kbd67/mkiirgb/v2)
	RGB_MATRIX_ENABLE = yes
endif
ifeq ($(strip $(KEYBOARD)), crkbd/rev1/common)
	BOOTLOADER = atmel-dfu
	WPM_ENABLE = yes
	SPLIT_KEYBOARD = yes
	OLED_DRIVER_ENABLE = yes
endif

# Common keyboard codes
SRC += keyboard.c
