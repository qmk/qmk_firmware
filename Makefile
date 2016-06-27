ifndef VERBOSE
.SILENT:
endif

space := $(subst ,, )
starting_makefile := $(subst $(space),_SPACE_,$(abspath $(firstword $(MAKEFILE_LIST))))
mkfile_path := $(subst $(space),_SPACE_,$(abspath $(lastword $(MAKEFILE_LIST))))
abs_tmk_root := $(patsubst %/,%,$(dir $(mkfile_path)))

ifneq (,$(findstring /keyboards/,$(starting_makefile)))
	possible_keyboard:=$(patsubst %/,%,$(dir $(patsubst $(abs_tmk_root)/keyboards/%,%,$(starting_makefile))))
	ifneq (,$(findstring /keymaps/,$(possible_keyboard)))
		KEYBOARD_DIR:=$(firstword $(subst /keymaps/, ,$(possible_keyboard)))
		KEYMAP_DIR:=$(lastword $(subst /keymaps/, ,$(possible_keyboard)))
		tmk_root = ../../../..
	else
		KEYBOARD_DIR:=$(possible_keyboard)
		KEYMAP_DIR:=default
		tmk_root = ../..
	endif
else
	tmk_root = .
endif
# $(info $(KEYBOARD_DIR))
# $(info $(KEYMAP_DIR))

# Directory common source filess exist
TOP_DIR = $(tmk_root)
TMK_DIR = tmk_core
TMK_PATH = $(TOP_DIR)/$(TMK_DIR)

QUANTUM_DIR = quantum
QUANTUM_PATH = $(TOP_DIR)/$(QUANTUM_DIR)

ifdef keyboard
	KEYBOARD ?= $(keyboard)
endif
ifdef KEYBOARD_DIR
	KEYBOARD ?= $(KEYBOARD_DIR)
endif
ifndef KEYBOARD
	KEYBOARD=planck
endif
KEYBOARD_PATH = $(TOP_DIR)/keyboards/$(KEYBOARD)
ifneq ("$(wildcard $(KEYBOARD_PATH)/$(KEYBOARD).c)","")
	KEYBOARD_FILE = keyboards/$(KEYBOARD)/$(KEYBOARD).c
	ifndef ARCH
		include $(KEYBOARD_PATH)/Makefile
	endif
else 
$(error "$(KEYBOARD_PATH)/$(KEYBOARD).c" does not exist)
endif

ifdef keymap
	KEYMAP ?= $(keymap)
endif
ifdef KEYMAP_DIR
	KEYMAP ?= $(KEYMAP_DIR)
endif
ifndef KEYMAP
	KEYMAP = default
endif
KEYMAP_PATH = $(KEYBOARD_PATH)/keymaps/$(KEYMAP)
ifneq ("$(wildcard $(KEYMAP_PATH)/keymap.c)","")
	KEYMAP_FILE = keyboards/$(KEYBOARD)/keymaps/$(KEYMAP)/keymap.c
	-include $(KEYMAP_PATH)/Makefile
else 
$(error "$(KEYMAP_PATH)/keymap.c" does not exist)
endif

TARGET ?= $(KEYBOARD)_$(KEYMAP)

ifneq ("$(wildcard $(KEYMAP_PATH)/config.h)","")
	CONFIG_H = $(KEYMAP_PATH)/config.h
else
	CONFIG_H = $(KEYBOARD_PATH)/config.h
endif

# # project specific files
SRC += $(KEYBOARD_FILE) \
	$(KEYMAP_FILE) \
	$(QUANTUM_DIR)/quantum.c \
	$(QUANTUM_DIR)/keymap.c \
	$(QUANTUM_DIR)/keycode_config.c

ifndef CUSTOM_MATRIX
	SRC += $(QUANTUM_DIR)/matrix.c
endif

ifeq ($(strip $(AUDIO_ENABLE)), yes)
	SRC += $(QUANTUM_DIR)/audio/audio.c
	SRC += $(QUANTUM_DIR)/audio/voices.c
	SRC += $(QUANTUM_DIR)/audio/luts.c
endif

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
	SRC += $(QUANTUM_DIR)/light_ws2812.c
	SRC += $(QUANTUM_DIR)/rgblight.c
	OPT_DEFS += -DRGBLIGHT_ENABLE
endif

# Optimize size but this may cause error "relocation truncated to fit"
#EXTRALDFLAGS = -Wl,--relax

# Search Path
VPATH += $(KEYMAP_PATH)
VPATH += $(KEYBOARD_PATH)
VPATH += $(TOP_DIR)
VPATH += $(TMK_PATH)
VPATH += $(QUANTUM_PATH)
VPATH += $(QUANTUM_PATH)/keymap_extras
VPATH += $(QUANTUM_PATH)/audio

include $(TMK_PATH)/protocol/lufa.mk
include $(TMK_PATH)/common.mk
include $(TMK_PATH)/rules.mk

GIT_VERSION := $(shell git describe --abbrev=6 --dirty --always --tags 2>/dev/null || date +"%Y-%m-%d-%H:%M:%S")
BUILD_DATE := $(shell date +"%Y-%m-%d-%H:%M:%S")
OPT_DEFS += -DQMK_KEYBOARD=\"$(KEYBOARD)\" -DQMK_KEYMAP=\"$(KEYMAP)\"
OPT_DEFS += -DQMK_VERSION=\"$(GIT_VERSION)\" -DQMK_BUILDDATE=\"$(BUILD_DATE)\"
