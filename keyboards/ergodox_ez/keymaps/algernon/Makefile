BOOTMAGIC_ENABLE=no
COMMAND_ENABLE=no
SLEEP_LED_ENABLE=no
UNICODE_ENABLE=no
FORCE_NKRO ?= yes

ifeq (${FORCE_NKRO},yes)
OPT_DEFS += -DFORCE_NKRO
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
