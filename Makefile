ifndef VERBOSE
.SILENT:
endif

.DEFAULT_GOAL := all

space := $(subst ,, )
ESCAPED_ABS_PATH = $(subst $(space),_SPACE_,$(abspath $1))
starting_makefile := $(call ESCAPED_ABS_PATH,$(firstword $(MAKEFILE_LIST)))
mkfile_path := $(call ESCAPED_ABS_PATH,$(lastword $(MAKEFILE_LIST))))
abs_tmk_root := $(patsubst %/,%,$(dir $(mkfile_path)))

ifneq (,$(findstring /keyboards/,$(starting_makefile)))
	possible_keyboard:=$(patsubst %/,%,$(dir $(patsubst $(abs_tmk_root)/keyboards/%,%,$(starting_makefile))))
	ifneq (,$(findstring /keymaps/,$(possible_keyboard)))
		KEYMAP_DIR:=$(lastword $(subst /keymaps/, ,$(possible_keyboard)))
		KEYBOARD_DIR:=$(firstword $(subst /keymaps/, ,$(possible_keyboard)))
		ifneq (,$(findstring /,$(KEYBOARD_DIR)))
			# SUBPROJECT_DIR:=$(lastword $(subst /, ,$(KEYBOARD_DIR)))
			# KEYBOARD_DIR:=$(firstword $(subst /, ,$(KEYBOARD_DIR)))
			tmk_root = ../../..
		else
			tmk_root = ../../../..
		endif
	else
		KEYMAP_DIR:=default
		KEYBOARD_DIR:=$(possible_keyboard)
		ifneq (,$(findstring /,$(KEYBOARD_DIR)))
			# SUBPROJECT_DIR:=$(lastword $(subst /, ,$(KEYBOARD_DIR)))
			# KEYBOARD_DIR:=$(firstword $(subst /, ,$(KEYBOARD_DIR)))
			tmk_root = ../../..
		else
			tmk_root = ../..
		endif
	endif
else
	tmk_root = .
endif
# $(info $(KEYBOARD_DIR))
# $(info $(KEYMAP_DIR))
# $(info $(SUBPROJECT_DIR))

# Directory common source filess exist
TOP_DIR = $(tmk_root)
TMK_DIR = tmk_core
TMK_PATH = $(TOP_DIR)/$(TMK_DIR)
LIB_PATH = $(TOP_DIR)/lib

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

MASTER ?= left
ifdef master
	MASTER = $(master)
endif


# converts things to keyboards/subproject
ifneq (,$(findstring /,$(KEYBOARD)))
	TEMP:=$(KEYBOARD)
	KEYBOARD:=$(firstword $(subst /, ,$(TEMP)))
	SUBPROJECT:=$(lastword $(subst /, ,$(TEMP)))
endif

KEYBOARD_PATH = $(TOP_DIR)/keyboards/$(KEYBOARD)

ifdef sub
	SUBPROJECT=$(sub)
endif
ifdef subproject
	SUBPROJECT=$(subproject)
endif

ifneq ("$(wildcard $(KEYBOARD_PATH)/$(KEYBOARD).c)","")
	KEYBOARD_FILE = keyboards/$(KEYBOARD)/$(KEYBOARD).c
	ifneq ($(call ESCAPED_ABS_PATH,$(KEYBOARD_PATH)/Makefile),$(starting_makefile))
		-include $(KEYBOARD_PATH)/Makefile
	endif
else 
$(error "$(KEYBOARD_PATH)/$(KEYBOARD).c" does not exist)
endif

ifdef SUBPROJECT_DEFAULT
	SUBPROJECT?=$(SUBPROJECT_DEFAULT)
endif

ifdef SUBPROJECT
	SUBPROJECT_PATH = $(TOP_DIR)/keyboards/$(KEYBOARD)/$(SUBPROJECT)
	ifneq ("$(wildcard $(SUBPROJECT_PATH)/$(SUBPROJECT).c)","")
		OPT_DEFS += -DSUBPROJECT_$(SUBPROJECT)
		SUBPROJECT_FILE = keyboards/$(KEYBOARD)/$(SUBPROJECT)/$(SUBPROJECT).c
		ifneq ($(call ESCAPED_ABS_PATH,$(SUBPROJECT_PATH)/Makefile),$(starting_makefile))
			-include $(SUBPROJECT_PATH)/Makefile
		endif
	else 
$(error "$(SUBPROJECT_PATH)/$(SUBPROJECT).c" does not exist)
	endif
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
	ifneq ($(call ESCAPED_ABS_PATH,$(KEYMAP_PATH)/Makefile),$(starting_makefile))
		-include $(KEYMAP_PATH)/Makefile
	endif
else 
	ifeq ("$(wildcard $(SUBPROJECT_PATH)/keymaps/$(KEYMAP)/keymap.c)","")
$(error "$(KEYMAP_PATH)/keymap.c" does not exist)
	else
		KEYMAP_PATH = $(SUBPROJECT_PATH)/keymaps/$(KEYMAP)
		KEYMAP_FILE = keyboards/$(KEYBOARD)/$(SUBPROJECT)/keymaps/$(KEYMAP)/keymap.c
		ifneq ($(call ESCAPED_ABS_PATH,$(KEYMAP_PATH)/Makefile),$(starting_makefile))
			-include $(KEYMAP_PATH)/Makefile
		endif
	endif
endif

ifdef SUBPROJECT
	TARGET ?= $(KEYBOARD)_$(SUBPROJECT)_$(KEYMAP)
else
	TARGET ?= $(KEYBOARD)_$(KEYMAP)
endif

BUILD_DIR = $(TOP_DIR)/.build

# Object files directory
#     To put object files in current directory, use a dot (.), do NOT make
#     this an empty or blank macro!
OBJDIR = $(BUILD_DIR)/obj_$(TARGET)



ifneq ("$(wildcard $(KEYMAP_PATH)/config.h)","")
	CONFIG_H = $(KEYMAP_PATH)/config.h
else
	CONFIG_H = $(KEYBOARD_PATH)/config.h
	ifdef SUBPROJECT
		ifneq ("$(wildcard $(SUBPROJECT_PATH)/$(SUBPROJECT).c)","")
			CONFIG_H = $(SUBPROJECT_PATH)/config.h
		endif
	endif
endif

# # project specific files
SRC += $(KEYBOARD_FILE) \
	$(KEYMAP_FILE) \
	$(QUANTUM_DIR)/quantum.c \
	$(QUANTUM_DIR)/keymap_common.c \
	$(QUANTUM_DIR)/keycode_config.c \
	$(QUANTUM_DIR)/process_keycode/process_leader.c

ifdef SUBPROJECT
	SRC += $(SUBPROJECT_FILE)
endif

ifdef SUBPROJECT
	SRC += $(SUBPROJECT_FILE)
endif

ifdef SUBPROJECT
	SRC += $(SUBPROJECT_FILE)
endif

ifndef CUSTOM_MATRIX
	SRC += $(QUANTUM_DIR)/matrix.c
endif

ifeq ($(strip $(MIDI_ENABLE)), yes)
    OPT_DEFS += -DMIDI_ENABLE
	SRC += $(QUANTUM_DIR)/process_keycode/process_midi.c
endif

ifeq ($(strip $(AUDIO_ENABLE)), yes)
    OPT_DEFS += -DAUDIO_ENABLE
	SRC += $(QUANTUM_DIR)/process_keycode/process_music.c
	SRC += $(QUANTUM_DIR)/audio/audio.c
	SRC += $(QUANTUM_DIR)/audio/voices.c
	SRC += $(QUANTUM_DIR)/audio/luts.c
endif

ifeq ($(strip $(UCIS_ENABLE)), yes)
	OPT_DEFS += -DUCIS_ENABLE
	UNICODE_ENABLE = yes
endif

ifeq ($(strip $(UNICODE_ENABLE)), yes)
    OPT_DEFS += -DUNICODE_ENABLE
	SRC += $(QUANTUM_DIR)/process_keycode/process_unicode.c
endif

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
	OPT_DEFS += -DRGBLIGHT_ENABLE
	SRC += $(QUANTUM_DIR)/light_ws2812.c
	SRC += $(QUANTUM_DIR)/rgblight.c
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
	OPT_DEFS += -DTAP_DANCE_ENABLE
	SRC += $(QUANTUM_DIR)/process_keycode/process_tap_dance.c
endif

ifeq ($(strip $(SERIAL_LINK_ENABLE)), yes)
	SERIAL_DIR = $(QUANTUM_DIR)/serial_link
	SERIAL_PATH = $(QUANTUM_PATH)/serial_link
	SERIAL_SRC = $(wildcard $(SERIAL_PATH)/protocol/*.c)
	SERIAL_SRC += $(wildcard $(SERIAL_PATH)/system/*.c)
	SRC += $(patsubst $(QUANTUM_PATH)/%,%,$(SERIAL_SRC))
	OPT_DEFS += -DSERIAL_LINK_ENABLE
	VAPTH += $(SERIAL_PATH)
endif

# Optimize size but this may cause error "relocation truncated to fit"
#EXTRALDFLAGS = -Wl,--relax

# Search Path
VPATH += $(KEYMAP_PATH)
ifdef SUBPROJECT
	VPATH += $(SUBPROJECT_PATH)
endif
VPATH += $(KEYBOARD_PATH)
VPATH += $(TOP_DIR)
VPATH += $(TMK_PATH)
VPATH += $(QUANTUM_PATH)
VPATH += $(QUANTUM_PATH)/keymap_extras
VPATH += $(QUANTUM_PATH)/audio
VPATH += $(QUANTUM_PATH)/process_keycode


# We can assume a ChibiOS target When MCU_FAMILY is defined, since it's not used for LUFA
ifdef MCU_FAMILY
	PLATFORM=CHIBIOS
else
	PLATFORM=AVR
endif

include $(TMK_PATH)/common.mk
ifeq ($(PLATFORM),AVR)
	include $(TMK_PATH)/protocol/lufa.mk
	include $(TMK_PATH)/avr.mk
else ifeq ($(PLATFORM),CHIBIOS)
	include $(TMK_PATH)/protocol/chibios.mk
	include $(TMK_PATH)/chibios.mk
	OPT_OS = chibios
else
	$(error Unknown platform)
endif

ifeq ($(strip $(VISUALIZER_ENABLE)), yes)
	VISUALIZER_DIR = $(QUANTUM_DIR)/visualizer
	VISUALIZER_PATH = $(QUANTUM_PATH)/visualizer
	include $(VISUALIZER_PATH)/visualizer.mk
endif

include $(TMK_PATH)/rules.mk

GIT_VERSION := $(shell git describe --abbrev=6 --dirty --always --tags 2>/dev/null || date +"%Y-%m-%d-%H:%M:%S")
BUILD_DATE := $(shell date +"%Y-%m-%d-%H:%M:%S")
OPT_DEFS += -DQMK_KEYBOARD=\"$(KEYBOARD)\" -DQMK_KEYMAP=\"$(KEYMAP)\"

$(shell echo '#define QMK_VERSION "$(GIT_VERSION)"' > $(QUANTUM_PATH)/version.h)
$(shell echo '#define QMK_BUILDDATE "$(BUILD_DATE)"' >> $(QUANTUM_PATH)/version.h)
