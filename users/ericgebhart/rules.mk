INTROSPECTION_KEYMAP_C = keymap/keymap.c # keymaps
SRC += ericgebhart.c

VPATH += $(USER_PATH)/perimeter
VPATH += $(USER_PATH)/layers
VPATH += $(USER_PATH)/mod_layers
VPATH += $(USER_PATH)/base_layers
VPATH += $(USER_PATH)/layer_names
VPATH += $(USER_PATH)/keyboards
VPATH += $(USER_PATH)/keymap
VPATH += $(USER_PATH)/lang

# for the combo macros in keymap_combos.h
# make sure its included somewhere.
VPATH += keyboards/gboards/g

OLED_ENABLE = no
OLED_CUSTOM_ENABLE = no

# I should check if this is still needed. I dont remember.
ifeq ($(strip $(OLED_CUSTOM_ENABLE)), yes)
        SRC += $(USER_PATH)/oled/oled_stuff.c
endif
VPATH += $(USER_PATH)/oled

SRC += $(USER_PATH)/oled/oled_stuff.c
SRC += $(USER_PATH)/oled/oled_cartes.c
SRC += $(USER_PATH)/oled/oled_layers.c

EXTRAKEY_ENABLE  = no # Audio control and System control
COMMAND_ENABLE   = no # Commands for debug and configuration
NKRO_ENABLE      = no # Enable N-Key Rollover
SWAP_HANDS_ENABLE= no # Allow swapping hands of keyboard
KEY_LOCK_ENABLE  = no
TAP_DANCE_ENABLE = no # Enable the tap dance feature.
UNICODE_ENABLE   = no
SLEEP_LED_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no

LTO_ENABLE = no  # optimizer saves space.

BOOTMAGIC_ENABLE = no  # Enable Bootmagic Lite

ENCODER_ENABLE = yes
RGBLIGHT_ENABLE = no
BACKLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = no
KEY_OVERRIDE_ENABLE = no

MOUSEKEY_ENABLE  = yes # Mouse keys
COMBO_ENABLE = yes
CAPS_WORD_ENABLE = yes

VPATH += $(USER_PATH)/extensions

VPATH += $(USER_PATH)/defs

SRC += $(USER_PATH)/extensions/extensions.c
SRC += $(USER_PATH)/extensions/tap_hold.c
SRC += $(USER_PATH)/extensions/accented_keys.c
SRC += $(USER_PATH)/extensions/altlocal_keys.c
SRC += $(USER_PATH)/extensions/encoders.c
SRC += $(USER_PATH)/extensions/swapper.c
SRC += $(USER_PATH)/extensions/mod_lock.c
SRC += $(USER_PATH)/extensions/smart_lock.c
SRC += $(USER_PATH)/extensions/nshot_mod.c
SRC += $(USER_PATH)/extensions/oneshot.c
SRC += $(USER_PATH)/extensions/unicode.c
SRC += $(USER_PATH)/extensions/send_string.c
SRC += $(USER_PATH)/extensions/console_key_logger.c
SRC += $(USER_PATH)/extensions/not_dead.c
SRC += $(USER_PATH)/extensions/alt_shift.c
SRC += $(USER_PATH)/extensions/quick_tap.c
SRC += $(USER_PATH)/extensions/adaptive_keys.c

SRC += process_records.c

CONSOLE_ENABLE   = yes  # Console for debug or keylogging.

ENCODER_ENABLE = no

SRC += $(USER_PATH)/lang/locales.c
