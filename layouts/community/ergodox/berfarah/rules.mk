BOOTMAGIC_ENABLE   = no
COMMAND_ENABLE     = no
SLEEP_LED_ENABLE   = yes
FORCE_NKRO        ?= yes
DEBUG_ENABLE       = no
CONSOLE_ENABLE     = no
TAP_DANCE_ENABLE   = no
MOUSEKEY_ENABLE    = no
RGBLIGHT_ENABLE    = yes
RGBLIGHT_ANIMATION = yes

ifeq (${FORCE_NKRO},yes)
OPT_DEFS += -DFORCE_NKRO
endif

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif
