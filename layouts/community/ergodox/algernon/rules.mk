BOOTMAGIC_ENABLE=no
COMMAND_ENABLE=no
SLEEP_LED_ENABLE=no
FORCE_NKRO ?= yes
DEBUG_ENABLE = no
CONSOLE_ENABLE = no
TAP_DANCE_ENABLE = yes
KEYLOGGER_ENABLE ?= yes
UCIS_ENABLE = yes
MOUSEKEY_ENABLE = no

AUTOLOG_ENABLE ?= no

ifeq (${FORCE_NKRO},yes)
OPT_DEFS += -DFORCE_NKRO
endif

ifeq (${AUTOLOG_ENABLE},yes)
KEYLOGGER_ENABLE = yes
OPT_DEFS += -DAUTOLOG_ENABLE
endif

ifeq (${KEYLOGGER_ENABLE},yes)
OPT_DEFS += -DKEYLOGGER_ENABLE
CONSOLE_ENABLE = yes
endif

OPT_DEFS += -DUSER_PRINT

LAYOUT_ergodox_VERSION = $(shell \
 if [ -d "${LAYOUT_ergodox_PATH}/.git" ]; then \
  cd "${LAYOUT_ergodox_PATH}" && git describe --abbrev=6 --dirty --always --tags --match 'v*' 2>/dev/null; \
 else echo QMK; fi)

LAYOUT_ergodox_BRANCH = $(shell \
 if [ -d "${LAYOUT_ergodox_PATH}/.git" ]; then \
  cd "${LAYOUT_ergodox_PATH}"; \
 fi; \
 git rev-parse --abbrev-ref HEAD 2>/dev/null)

OPT_DEFS += -DLAYOUT_ergodox_VERSION=\"$(LAYOUT_ergodox_VERSION)\\\#$(LAYOUT_ergodox_BRANCH)\"
