include message.mk

# Directory common source files exist
TOP_DIR = .
TMK_DIR = tmk_core
TMK_PATH = $(TMK_DIR)
LIB_PATH = lib

QUANTUM_DIR = quantum
QUANTUM_PATH = $(QUANTUM_DIR)

DRIVER_DIR = drivers
DRIVER_PATH = $(DRIVER_DIR)

BUILD_DIR := .build

COMMON_VPATH := $(TOP_DIR)
COMMON_VPATH += $(TMK_PATH)
COMMON_VPATH += $(QUANTUM_PATH)
COMMON_VPATH += $(QUANTUM_PATH)/keymap_extras
COMMON_VPATH += $(QUANTUM_PATH)/audio
COMMON_VPATH += $(QUANTUM_PATH)/process_keycode
COMMON_VPATH += $(QUANTUM_PATH)/api
COMMON_VPATH += $(QUANTUM_PATH)/split_common
COMMON_VPATH += $(DRIVER_PATH)
