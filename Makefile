ifndef VERBOSE
.SILENT:
endif

# Directory common source filess exist
TOP_DIR ?= .
TMK_DIR = $(TOP_DIR)/tmk_core

QUANTUM_DIR = quantum
QUANTUM_PATH = $(TOP_DIR)/$(QUANTUM_DIR)

ifdef KEYBOARD_DIR
	KEYBOARD_PATH = $(TOP_DIR)/keyboard/$(KEYBOARD_DIR)
	KEYBOARD_FILE = $(KEYBOARD_DIR).c
	KEYBOARD = $(KEYBOARD_DIR)
else
	ifdef keyboard
		KEYBOARD = $(keyboard)
	endif
	ifndef KEYBOARD
$(error Please specify a keyboard with keyboard=<keyboard>)
	endif
	KEYBOARD_PATH = $(TOP_DIR)/keyboard/$(KEYBOARD)
	ifneq ("$(wildcard $(KEYBOARD_PATH)/$(KEYBOARD).c)","")
		KEYBOARD_FILE = $(KEYBOARD).c
		include $(KEYBOARD_PATH)/Makefile
	else 
$(error "$(KEYBOARD_PATH)/$(KEYBOARD).c" does not exist)
	endif
	KEYBOARD_DIR = $(KEYBOARD)
endif

ifdef KEYMAP_DIR
	KEYMAP_PATH = $(KEYBOARD_PATH)/keymaps/$(KEYMAP_DIR)
	KEYMAP_FILE = keymaps/$(KEYMAP_DIR)/keymap.c
	KEYMAP = $(KEYMAP_DIR)
else
	ifdef keymap
		KEYMAP = $(keymap)
	endif
	ifndef KEYMAP
		KEYMAP = default
	endif
	KEYMAP_PATH = $(KEYBOARD_PATH)/keymaps/$(KEYMAP)
	ifneq ("$(wildcard $(KEYMAP_PATH)/keymap.c)","")
		KEYMAP_FILE = keymaps/$(KEYMAP)/keymap.c
		include $(KEYMAP_PATH)/Makefile
	else 
$(error "$(KEYMAP_PATH)/keymap.c" does not exist)
	endif
	KEYMAP_DIR = $(KEYMAP)
endif

TARGET = $(KEYBOARD)_$(KEYMAP)

# # project specific files
SRC += $(KEYBOARD_FILE) \
	$(KEYMAP_FILE) \
	$(QUANTUM_DIR)/quantum.c \
	$(QUANTUM_DIR)/keymap_common.c \
	$(QUANTUM_DIR)/led.c

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
VPATH += $(TMK_DIR)
VPATH += $(QUANTUM_PATH)
VPATH += $(QUANTUM_PATH)/keymap_extras
VPATH += $(QUANTUM_PATH)/audio

include $(TMK_DIR)/protocol/lufa.mk
include $(TMK_DIR)/common.mk
include $(TMK_DIR)/rules.mk