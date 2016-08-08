ifndef VERBOSE
.SILENT:
endif

.DEFAULT_GOAL := all

include message.mk


# Directory common source filess exist
TOP_DIR = .
TMK_DIR = tmk_core
TMK_PATH = $(TOP_DIR)/$(TMK_DIR)
LIB_PATH = $(TOP_DIR)/lib

QUANTUM_DIR = quantum
QUANTUM_PATH = $(TOP_DIR)/$(QUANTUM_DIR)


MASTER ?= left
ifdef master
	MASTER = $(master)
endif

KEYBOARD_PATH := keyboards/$(KEYBOARD)
KEYBOARD_C := $(KEYBOARD_PATH)/$(KEYBOARD).c

ifneq ("$(wildcard $(KEYBOARD_C))","")
    include $(KEYBOARD_PATH)/rules.mk
else 
    $(error "$(KEYBOARD_C)" does not exist)
endif


ifneq ($(SUBPROJECT),)
    SUBPROJECT_PATH := keyboards/$(KEYBOARD)/$(SUBPROJECT)
    SUBPROJECT_C := $(SUBPROJECT_PATH)/$(SUBPROJECT).c
    ifneq ("$(wildcard $(SUBPROJECT_C))","")
        OPT_DEFS += -DSUBPROJECT_$(SUBPROJECT)
        include $(SUBPROJECT_PATH)/rules.mk
    else 
        $(error "$(SUBPROJECT_PATH)/$(SUBPROJECT).c" does not exist)
    endif
endif

MAIN_KEYMAP_PATH := $(KEYBOARD_PATH)/keymaps/$(KEYMAP)
MAIN_KEYMAP_C := $(MAIN_KEYMAP_PATH)/keymap.c
SUBPROJ_KEYMAP_PATH := $(SUBPROJECT_PATH)/keymaps/$(KEYMAP)
SUBPROJ_KEYMAP_C := $(SUBPROJ_KEYMAP_PATH)/keymap.c
ifneq ("$(wildcard $(SUBPROJ_KEYMAP_C))","")
    -include $(SUBPROJ_KEYMAP_PATH)/Makefile
    KEYMAP_C := $(SUBPROJ_KEYMAP_C)
    KEYMAP_PATH := $(SUBPROJ_KEYMAP_PATH)
else ifneq ("$(wildcard $(MAIN_KEYMAP_C))","")
    -include $(MAIN_KEYMAP_PATH)/Makefile
    KEYMAP_C := $(MAIN_KEYMAP_C)
    KEYMAP_PATH := $(MAIN_KEYMAP_PATH)
else
    $(error "$(MAIN_KEYMAP_C)/keymap.c" does not exist)
endif

ifneq ($(SUBPROJECT),)
	TARGET ?= $(KEYBOARD)_$(SUBPROJECT)_$(KEYMAP)
else
	TARGET ?= $(KEYBOARD)_$(KEYMAP)
endif

BUILD_DIR = $(TOP_DIR)/.build

# Object files directory
#     To put object files in current directory, use a dot (.), do NOT make
#     this an empty or blank macro!
OBJDIR := $(BUILD_DIR)/obj_$(TARGET)


ifneq ("$(wildcard $(KEYMAP_PATH)/config.h)","")
	CONFIG_H = $(KEYMAP_PATH)/config.h
else
	CONFIG_H = $(KEYBOARD_PATH)/config.h
	ifneq ($(SUBPROJECT),)
		ifneq ("$(wildcard $(SUBPROJECT_C))","")
			CONFIG_H = $(SUBPROJECT_PATH)/config.h
		endif
	endif
endif

# # project specific files
SRC += $(KEYBOARD_C) \
	$(KEYMAP_C) \
	$(QUANTUM_DIR)/quantum.c \
	$(QUANTUM_DIR)/keymap_common.c \
	$(QUANTUM_DIR)/keycode_config.c \
	$(QUANTUM_DIR)/process_keycode/process_leader.c

ifneq ($(SUBPROJECT),)
	SRC += $(SUBPROJECT_C)
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
ifneq ($(SUBPROJECT),)
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