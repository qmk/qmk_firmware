INTROSPECTION_KEYMAP_C = keymap/keymap.c # keymaps
SRC += ericgebhart.c
SRC += process_records.c
SRC += $(USER_PATH)/lang/locales.c
SRC += $(USER_PATH)/extensions/extensions.c
SRC += $(USER_PATH)/extensions/tap_hold.c
SRC += $(USER_PATH)/extensions/accented_keys.c
SRC += $(USER_PATH)/extensions/altlocal_keys.c
SRC += $(USER_PATH)/extensions/tap_dances.c
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
SRC += $(USER_PATH)/oled/oled_stuff.c
SRC += $(USER_PATH)/oled/oled_cartes.c
SRC += $(USER_PATH)/oled/oled_layers.c

VPATH += $(USER_PATH)/layer_names
VPATH += $(USER_PATH)/oled
VPATH += $(USER_PATH)/extensions
VPATH += $(USER_PATH)/base_layers
VPATH += $(USER_PATH)/defs
VPATH += $(USER_PATH)/keyboards
VPATH += $(USER_PATH)/keymap
VPATH += $(USER_PATH)/lang
VPATH += $(USER_PATH)/layers
VPATH += $(USER_PATH)/mod_layers
VPATH += $(USER_PATH)/oled

# MCU=STM32F411
# BOARD=QMK_PROTON_C
# SOFT_SERIAL_PIN=D2
# # Bootloader selection
# BOOTLOADER = stm32-dfu

# WS2812_DRIVER = pwm
# SERIAL_DRIVER = usart
# AUDIO_ENABLE = no
# LTO_ENABLE = no
# CONVERT_TO_PROTON_C = yes

# so the keyboard's code doesn't add stuff we don't need.
# when we use our own oled renders.
# oled_custom_enable should also be set in config.h.
OLED_ENABLE = yes
OLED_CUSTOM_ENABLE = yes

ifeq ($(strip $(OLED_CUSTOM_ENABLE)), yes)
        SRC += $(USER_PATH)/oled/oled_stuff.c
endif


MOUSEKEY_ENABLE  = yes # Mouse keys
EXTRAKEY_ENABLE  = no # Audio control and System control
COMMAND_ENABLE   = no # Commands for debug and configuration
NKRO_ENABLE      = no # Enable N-Key Rollover
SWAP_HANDS_ENABLE= no # Allow swapping hands of keyboard
KEY_LOCK_ENABLE  = no # Enable the KC_LOCK key
TAP_DANCE_ENABLE = no # Enable the tap dance feature.
KEY_OVERRIDE_ENABLE = no
CONSOLE_ENABLE   = no  # Console for debug or keylogging.


BOOTMAGIC_ENABLE = no  # Enable Bootmagic Lite
UNICODE_ENABLE   = no
SLEEP_LED_ENABLE = no

LTO_ENABLE = yes

SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
COMBO_ENABLE = yes
CAPS_WORD_ENABLE = yes

ENCODER_ENABLE = no
RGBLIGHT_ENABLE = no
BACKLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = no
