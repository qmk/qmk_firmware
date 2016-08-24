include message.mk

# Directory common source files exist
TOP_DIR = .
TMK_DIR = tmk_core
TMK_PATH = $(TOP_DIR)/$(TMK_DIR)
LIB_PATH = $(TOP_DIR)/lib

QUANTUM_DIR = quantum
QUANTUM_PATH = $(TOP_DIR)/$(QUANTUM_DIR)

BUILD_DIR := $(TOP_DIR)/.build

SERIAL_DIR := $(QUANTUM_DIR)/serial_link
SERIAL_PATH := $(QUANTUM_PATH)/serial_link
SERIAL_SRC := $(wildcard $(SERIAL_PATH)/protocol/*.c)
SERIAL_SRC += $(wildcard $(SERIAL_PATH)/system/*.c)
SERIAL_DEFS += -DSERIAL_LINK_ENABLE

VPATH += $(TOP_DIR)
VPATH += $(TMK_PATH)
VPATH += $(QUANTUM_PATH)
VPATH += $(QUANTUM_PATH)/keymap_extras
VPATH += $(QUANTUM_PATH)/audio
VPATH += $(QUANTUM_PATH)/process_keycode
VPATH += $(SERIAL_PATH)