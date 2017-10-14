# Copyright 2017 Fred Sundvik
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

SERIAL_DIR := $(QUANTUM_DIR)/serial_link
SERIAL_PATH := $(QUANTUM_PATH)/serial_link
SERIAL_SRC := $(wildcard $(SERIAL_PATH)/protocol/*.c)
SERIAL_SRC += $(wildcard $(SERIAL_PATH)/system/*.c)
SERIAL_DEFS += -DSERIAL_LINK_ENABLE
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

ifeq ($(strip $(STENO_ENABLE)), yes)
    OPT_DEFS += -DSTENO_ENABLE
	VIRTSER_ENABLE := yes
	SRC += $(QUANTUM_DIR)/process_keycode/process_steno.c
endif

ifeq ($(strip $(VIRTSER_ENABLE)), yes)
    OPT_DEFS += -DVIRTSER_ENABLE
endif

ifeq ($(strip $(FAUXCLICKY_ENABLE)), yes)
    OPT_DEFS += -DFAUXCLICKY_ENABLE
    SRC += $(QUANTUM_DIR)/fauxclicky.c
endif

ifeq ($(strip $(POINTING_DEVICE_ENABLE)), yes)
	SRC += $(QUANTUM_DIR)/pointing_device.c
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
    SRC += $(QUANTUM_DIR)/rgblight.c
    CIE1931_CURVE = yes
    LED_BREATHING_TABLE = yes
    ifeq ($(strip $(RGBLIGHT_CUSTOM_DRIVER)), yes)
        OPT_DEFS += -DRGBLIGHT_CUSTOM_DRIVER
    else
	    SRC += ws2812.c
    endif
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    OPT_DEFS += -DTAP_DANCE_ENABLE
    SRC += $(QUANTUM_DIR)/process_keycode/process_tap_dance.c
endif

ifeq ($(strip $(KEY_LOCK_ENABLE)), yes)
    OPT_DEFS += -DKEY_LOCK_ENABLE
    SRC += $(QUANTUM_DIR)/process_keycode/process_key_lock.c
endif

ifeq ($(strip $(PRINTING_ENABLE)), yes)
    OPT_DEFS += -DPRINTING_ENABLE
    SRC += $(QUANTUM_DIR)/process_keycode/process_printer.c
    SRC += $(TMK_DIR)/protocol/serial_uart.c
endif

ifeq ($(strip $(AUTO_SHIFT_ENABLE)), yes)
    OPT_DEFS += -DAUTO_SHIFT_ENABLE
    SRC += $(QUANTUM_DIR)/process_keycode/process_auto_shift.c
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

ifeq ($(strip $(TERMINAL_ENABLE)), yes)
    SRC += $(QUANTUM_DIR)/process_keycode/process_terminal.c
    OPT_DEFS += -DTERMINAL_ENABLE
endif

ifeq ($(strip $(USB_HID_ENABLE)), yes)
    include $(TMK_DIR)/protocol/usb_hid.mk
endif

QUANTUM_SRC:= \
    $(QUANTUM_DIR)/quantum.c \
    $(QUANTUM_DIR)/keymap_common.c \
    $(QUANTUM_DIR)/keycode_config.c \
    $(QUANTUM_DIR)/process_keycode/process_leader.c

ifndef CUSTOM_MATRIX
    QUANTUM_SRC += $(QUANTUM_DIR)/matrix.c
endif
