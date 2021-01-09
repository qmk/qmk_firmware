# Disable space saving defaults
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

# Disable RGB by default
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = no

# Common features
LEADER_ENABLE = yes
EXTRAKEY_ENABLE = yes

ifneq ($(PLATFORM),CHIBIOS)
	LTO_ENABLE = yes
endif

ifeq ($(strip $(KEYBOARD)), the_mark)
	RGBLIGHT_ENABLE = yes
endif

ifeq ($(strip $(KEYBOARD)), bm40hsrgb)
	RGB_MATRIX_ENABLE = yes
else ifeq ($(strip $(KEYBOARD)), kbdfans/kbd67/mkiirgb/v2)
	VIA_ENABLE = yes
	RGB_MATRIX_ENABLE = yes
endif

ifeq ($(strip $(KEYBOARD)), crkbd/rev1/common)
	BOOTLOADER = atmel-dfu
	SPLIT_KEYBOARD = yes
	OLED_DRIVER_ENABLE = yes
	WPM_ENABLE = yes
	SRC += oled.c
	#SRC += oled-mods.c
endif

SRC += keyboard.c

