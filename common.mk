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

COMMON_VPATH := $(TOP_DIR)
COMMON_VPATH += $(TMK_PATH)
COMMON_VPATH += $(QUANTUM_PATH)
COMMON_VPATH += $(QUANTUM_PATH)/keymap_extras
COMMON_VPATH += $(QUANTUM_PATH)/audio
COMMON_VPATH += $(QUANTUM_PATH)/process_keycode
COMMON_VPATH += $(QUANTUM_PATH)/api
COMMON_VPATH += $(SERIAL_PATH)

ifeq ($(strip $(API_SYSEX_ENABLE)), yes)
    OPT_DEFS += -DAPI_SYSEX_ENABLE
    SRC += $(QUANTUM_DIR)/api/api_sysex.c
    OPT_DEFS += -DAPI_ENABLE
    SRC += $(QUANTUM_DIR)/api.c
    MIDI_ENABLE=yes
endif

MUSIC_ENABLE := 0

ifeq ($(strip $(AUDIO_ENABLE)), yes)
    OPT_DEFS += -DAUDIO_ENABLE
    MUSIC_ENABLE := 1
    SRC += $(QUANTUM_DIR)/process_keycode/process_audio.c
    SRC += $(QUANTUM_DIR)/audio/audio.c
    SRC += $(QUANTUM_DIR)/audio/voices.c
    SRC += $(QUANTUM_DIR)/audio/luts.c
endif

ifeq ($(strip $(MIDI_ENABLE)), yes)
    OPT_DEFS += -DMIDI_ENABLE
    MUSIC_ENABLE := 1
    SRC += $(QUANTUM_DIR)/process_keycode/process_midi.c
endif

ifeq ($(MUSIC_ENABLE), 1)
    SRC += $(QUANTUM_DIR)/process_keycode/process_music.c
endif

ifeq ($(strip $(COMBO_ENABLE)), yes)
    OPT_DEFS += -DCOMBO_ENABLE
    SRC += $(QUANTUM_DIR)/process_keycode/process_combo.c
endif

ifeq ($(strip $(VIRTSER_ENABLE)), yes)
    OPT_DEFS += -DVIRTSER_ENABLE
endif

ifeq ($(strip $(FAUXCLICKY_ENABLE)), yes)
    OPT_DEFS += -DFAUXCLICKY_ENABLE
    SRC += $(QUANTUM_DIR)/fauxclicky.c
endif

ifeq ($(strip $(UCIS_ENABLE)), yes)
    OPT_DEFS += -DUCIS_ENABLE
    UNICODE_COMMON = yes
    SRC += $(QUANTUM_DIR)/process_keycode/process_ucis.c
endif

ifeq ($(strip $(UNICODEMAP_ENABLE)), yes)
    OPT_DEFS += -DUNICODEMAP_ENABLE
    UNICODE_COMMON = yes
    SRC += $(QUANTUM_DIR)/process_keycode/process_unicodemap.c
endif

ifeq ($(strip $(UNICODE_ENABLE)), yes)
    OPT_DEFS += -DUNICODE_ENABLE
    UNICODE_COMMON = yes
    SRC += $(QUANTUM_DIR)/process_keycode/process_unicode.c
endif

ifeq ($(strip $(UNICODE_COMMON)), yes)
    SRC += $(QUANTUM_DIR)/process_keycode/process_unicode_common.c
endif

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
    OPT_DEFS += -DRGBLIGHT_ENABLE
    SRC += $(QUANTUM_DIR)/light_ws2812.c
    SRC += $(QUANTUM_DIR)/rgblight.c
    CIE1931_CURVE = yes
    LED_BREATHING_TABLE = yes
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    OPT_DEFS += -DTAP_DANCE_ENABLE
    SRC += $(QUANTUM_DIR)/process_keycode/process_tap_dance.c
endif

ifeq ($(strip $(PRINTING_ENABLE)), yes)
    OPT_DEFS += -DPRINTING_ENABLE
    SRC += $(QUANTUM_DIR)/process_keycode/process_printer.c
    SRC += $(TMK_DIR)/protocol/serial_uart.c
endif

ifeq ($(strip $(SERIAL_LINK_ENABLE)), yes)
    SRC += $(patsubst $(QUANTUM_PATH)/%,%,$(SERIAL_SRC))
    OPT_DEFS += $(SERIAL_DEFS)
    VAPTH += $(SERIAL_PATH)
endif

ifneq ($(strip $(VARIABLE_TRACE)),)
    SRC += $(QUANTUM_DIR)/variable_trace.c
    OPT_DEFS += -DNUM_TRACED_VARIABLES=$(strip $(VARIABLE_TRACE))
ifneq ($(strip $(MAX_VARIABLE_TRACE_SIZE)),)
    OPT_DEFS += -DMAX_VARIABLE_TRACE_SIZE=$(strip $(MAX_VARIABLE_TRACE_SIZE))
endif
endif

ifeq ($(strip $(LCD_ENABLE)), yes)
    CIE1931_CURVE = yes
endif

ifeq ($(strip $(BACKLIGHT_ENABLE)), yes)
    ifeq ($(strip $(VISUALIZER_ENABLE)), yes)
        CIE1931_CURVE = yes
    endif
endif

ifeq ($(strip $(CIE1931_CURVE)), yes)
    OPT_DEFS += -DUSE_CIE1931_CURVE
    LED_TABLES = yes
endif

ifeq ($(strip $(LED_BREATHING_TABLE)), yes)
    OPT_DEFS += -DUSE_LED_BREATHING_TABLE
    LED_TABLES = yes
endif

ifeq ($(strip $(LED_TABLES)), yes)
    SRC += $(QUANTUM_DIR)/led_tables.c
endif
