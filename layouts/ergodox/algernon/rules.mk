BOOTMAGIC_ENABLE=no
COMMAND_ENABLE=no
SLEEP_LED_ENABLE=no
FORCE_NKRO = yes
DEBUG_ENABLE = no
CONSOLE_ENABLE = no
TAP_DANCE_ENABLE = yes
KEYLOGGER_ENABLE = yes
UCIS_ENABLE = yes
MOUSEKEY_ENABLE = no

AUTOLOG_ENABLE = no

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

LAYOUT_ERGODOX_VERSION = $(shell \
 if [ -d "${LAYOUT_ERGODOX_PATH}/.git" ]; then \
  cd "${LAYOUT_ERGODOX_PATH}" && git describe --abbrev=6 --dirty --always --tags --match 'v*' 2>/dev/null; \
 else echo QMK; fi)

LAYOUT_ERGODOX_BRANCH = $(shell \
 if [ -d "${LAYOUT_ERGODOX_PATH}/.git" ]; then \
  cd "${LAYOUT_ERGODOX_PATH}"; \
 fi; \
 git rev-parse --abbrev-ref HEAD 2>/dev/null)

OPT_DEFS += -DLAYOUT_ERGODOX_VERSION=\"$(LAYOUT_ERGODOX_VERSION)\\\#$(LAYOUT_ERGODOX_BRANCH)\"


