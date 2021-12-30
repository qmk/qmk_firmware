SRC += ericgebhart.c
SRC += tap_dances.c
SRC += process_records.c
SRC += caps_word.c

CUSTOM_OLED_DRIVER ?= yes
ifeq ($(strip $(OLED_ENABLE)), yes)
    ifeq ($(strip $(CUSTOM_OLED_DRIVER)), yes)
        SRC += $(USER_PATH)/oled_stuff.c
        OPT_DEFS += -DCUSTOM_OLED_DRIVER_CODE
    endif
endif

EXTRAFLAGS += -flto

MOUSEKEY_ENABLE  = yes # Mouse keys
EXTRAKEY_ENABLE  = yes # Audio control and System control
COMMAND_ENABLE   = no # Commands for debug and configuration
NKRO_ENABLE      = no # USB Nkey Rollover - for issues, see github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
SWAP_HANDS_ENABLE= no # Allow swapping hands of keyboard
KEY_LOCK_ENABLE  = yes # Enable the KC_LOCK key
TAP_DANCE_ENABLE = no # Enable the tap dance feature.
CONSOLE_ENABLE   = no  # Console for debug

BOOTMAGIC_ENABLE = no  # Virtual DIP switch configuration
UNICODE_ENABLE   = no
SLEEP_LED_ENABLE = no
API_SYSEX_ENABLE = no
