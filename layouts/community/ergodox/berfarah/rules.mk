BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
COMMAND_ENABLE     = no
SLEEP_LED_ENABLE   = yes
FORCE_NKRO        ?= yes
DEBUG_ENABLE       = no
CONSOLE_ENABLE     = no
TAP_DANCE_ENABLE   = no
MOUSEKEY_ENABLE    = no
ifdef RGBLIGHT_ENABLE
RGBLIGHT_ANIMATION = yes
endif

ifeq (${FORCE_NKRO},yes)
OPT_DEFS += -DFORCE_NKRO
endif

