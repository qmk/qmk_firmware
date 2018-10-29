BOOTMAGIC_ENABLE=no
COMMAND_ENABLE=no
SLEEP_LED_ENABLE=no
NKRO_ENABLE = yes
FORCE_NKRO = no
DEBUG_ENABLE = no
CONSOLE_ENABLE = no
TAP_DANCE_ENABLE = yes
KEYLOGGER_ENABLE = no
UCIS_ENABLE = no
MOUSEKEY_ENABLE = no
AUTOLOG_ENABLE = no
RGBLIGHT_ENABLE = yes
RGBLIGHT_ANIMATION = yes
EXTRAKEY_ENABLE = yes
LEADER_ENABLE = yes

OPT_DEFS += -DUSER_PRINT

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
