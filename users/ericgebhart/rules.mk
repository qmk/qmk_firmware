SRC += ericgebhart.c
SRC += tap_dances.c
SRC += process_records.c
SRC += caps_word.c
SRC += altlocal_keys.c

VPATH += keyboards/gboards

OLED_ENABLE = yes

ifeq ($(strip $(OLED_ENABLE)), yes)
        SRC += $(USER_PATH)/oled_stuff.c
endif


MOUSEKEY_ENABLE  = yes # Mouse keys
EXTRAKEY_ENABLE  = yes # Audio control and System control
COMMAND_ENABLE   = no # Commands for debug and configuration
NKRO_ENABLE      = no # Enable N-Key Rollover
SWAP_HANDS_ENABLE= no # Allow swapping hands of keyboard
KEY_LOCK_ENABLE  = no
TAP_DANCE_ENABLE = no # Enable the tap dance feature.
CONSOLE_ENABLE   = no  # Console for debug

BOOTMAGIC_ENABLE = no  # Enable Bootmagic Lite
UNICODE_ENABLE   = no
SLEEP_LED_ENABLE = no

LTO_ENABLE = yes

SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
COMBO_ENABLE = yes
