BOOTMAGIC_ENABLE=no
COMMAND_ENABLE=no
SLEEP_LED_ENABLE=no
UNICODE_ENABLE=no
FORCE_NKRO ?= yes
DEBUG_ENABLE = no
CONSOLE_ENABLE = no
TAP_DANCE_ENABLE = yes
KEYLOGGER_ENABLE ?= yes

ADORE_AUTOLOG ?= no

ifeq (${FORCE_NKRO},yes)
OPT_DEFS += -DFORCE_NKRO
endif

ifeq (${ADORE_AUTOLOG},yes)
KEYLOGGER_ENABLE = yes
OPT_DEFS += -DADORE_AUTOLOG
endif

ifeq (${KEYLOGGER_ENABLE},yes)
OPT_DEFS += -DKEYLOGGER_ENABLE
CONSOLE_ENABLE = yes
endif

KEYMAP_VERSION = $(shell \
 if [ -d "${KEYMAP_PATH}/.git" ]; then \
  cd "${KEYMAP_PATH}" && git describe --abbrev=6 --dirty --always --tags --match 'v*' 2>/dev/null; \
 else echo QMK; fi)

KEYMAP_BRANCH = $(shell \
 if [ -d "${KEYMAP_PATH}/.git" ]; then \
  cd "${KEYMAP_PATH}"; \
 fi; \
 git rev-parse --abbrev-ref HEAD 2>/dev/null)

OPT_DEFS += -DKEYMAP_VERSION=\"$(KEYMAP_VERSION)\\\#$(KEYMAP_BRANCH)\"

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif
