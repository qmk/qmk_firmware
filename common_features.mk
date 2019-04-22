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
    SRC += $(QUANTUM_DIR)/process_keycode/process_clicky.c
    ifeq ($(PLATFORM),AVR)
        SRC += $(QUANTUM_DIR)/audio/audio.c
    else
        SRC += $(QUANTUM_DIR)/audio/audio_arm.c
    endif
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
    OPT_DEFS += -DPOINTING_DEVICE_ENABLE
    OPT_DEFS += -DMOUSE_ENABLE
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
    POST_CONFIG_H += $(QUANTUM_DIR)/rgblight_post_config.h
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

VALID_MATRIX_TYPES := yes IS31FL3731 IS31FL3733 IS31FL3737 WS2812 custom

LED_MATRIX_ENABLE ?= no
ifneq ($(strip $(LED_MATRIX_ENABLE)), no)
    ifeq ($(filter $(LED_MATRIX_ENABLE),$(VALID_MATRIX_TYPES)),)
        $(error LED_MATRIX_ENABLE="$(LED_MATRIX_ENABLE)" is not a valid matrix type)
    else
        OPT_DEFS += -DLED_MATRIX_ENABLE -DBACKLIGHT_ENABLE -DBACKLIGHT_CUSTOM_DRIVER
        SRC += $(QUANTUM_DIR)/led_matrix.c
        SRC += $(QUANTUM_DIR)/led_matrix_drivers.c
    endif
endif

ifeq ($(strip $(LED_MATRIX_ENABLE)), IS31FL3731)
    OPT_DEFS += -DIS31FL3731
    COMMON_VPATH += $(DRIVER_PATH)/issi
    SRC += is31fl3731-simple.c
    SRC += i2c_master.c
endif

RGB_MATRIX_ENABLE ?= no

ifneq ($(strip $(RGB_MATRIX_ENABLE)), no)
ifeq ($(filter $(RGB_MATRIX_ENABLE),$(VALID_MATRIX_TYPES)),)
    $(error RGB_MATRIX_ENABLE="$(RGB_MATRIX_ENABLE)" is not a valid matrix type)
endif
    OPT_DEFS += -DRGB_MATRIX_ENABLE
    SRC += $(QUANTUM_DIR)/color.c
    SRC += $(QUANTUM_DIR)/rgb_matrix.c
    SRC += $(QUANTUM_DIR)/rgb_matrix_drivers.c
    CIE1931_CURVE = yes
endif

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
	RGB_MATRIX_ENABLE = IS31FL3731
endif

ifeq ($(strip $(RGB_MATRIX_ENABLE)), IS31FL3731)
    OPT_DEFS += -DIS31FL3731 -DSTM32_I2C -DHAL_USE_I2C=TRUE
    COMMON_VPATH += $(DRIVER_PATH)/issi
    SRC += is31fl3731.c
    SRC += i2c_master.c
endif

ifeq ($(strip $(RGB_MATRIX_ENABLE)), IS31FL3733)
    OPT_DEFS += -DIS31FL3733 -DSTM32_I2C -DHAL_USE_I2C=TRUE
    COMMON_VPATH += $(DRIVER_PATH)/issi
    SRC += is31fl3733.c
    SRC += i2c_master.c
endif

ifeq ($(strip $(RGB_MATRIX_ENABLE)), IS31FL3737)
    OPT_DEFS += -DIS31FL3737 -DSTM32_I2C -DHAL_USE_I2C=TRUE
    COMMON_VPATH += $(DRIVER_PATH)/issi
    SRC += is31fl3737.c
    SRC += i2c_master.c
endif

ifeq ($(strip $(RGB_MATRIX_ENABLE)), WS2812)
    OPT_DEFS += -DWS2812
    SRC += ws2812.c
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
    ifeq ($(strip $(AUTO_SHIFT_MODIFIERS)), yes)
        OPT_DEFS += -DAUTO_SHIFT_MODIFIERS
    endif
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
    ifeq ($(strip $(BACKLIGHT_CUSTOM_DRIVER)), yes)
        OPT_DEFS += -DBACKLIGHT_CUSTOM_DRIVER
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
    OPT_DEFS += -DUSER_PRINT
endif

ifeq ($(strip $(USB_HID_ENABLE)), yes)
    include $(TMK_DIR)/protocol/usb_hid.mk
endif

ifeq ($(strip $(ENCODER_ENABLE)), yes)
    SRC += $(QUANTUM_DIR)/encoder.c
    OPT_DEFS += -DENCODER_ENABLE
endif

ifeq ($(strip $(HAPTIC_ENABLE)), DRV2605L)
    COMMON_VPATH += $(DRIVER_PATH)/haptic
    SRC += haptic.c
    SRC += DRV2605L.c
    SRC += i2c_master.c
    OPT_DEFS += -DHAPTIC_ENABLE
    OPT_DEFS += -DDRV2605L
endif

ifeq ($(strip $(HAPTIC_ENABLE)), SOLENOID)
    COMMON_VPATH += $(DRIVER_PATH)/haptic
    SRC += haptic.c
    SRC += solenoid.c
    OPT_DEFS += -DHAPTIC_ENABLE
    OPT_DEFS += -DSOLENOID_ENABLE
endif

ifeq ($(strip $(HD44780_ENABLE)), yes)
    SRC += drivers/avr/hd44780.c
    OPT_DEFS += -DHD44780_ENABLE
endif

ifeq ($(strip $(VELOCIKEY_ENABLE)), yes)
    OPT_DEFS += -DVELOCIKEY_ENABLE
    SRC += $(QUANTUM_DIR)/velocikey.c
endif

ifeq ($(strip $(DYNAMIC_KEYMAP_ENABLE)), yes)
    OPT_DEFS += -DDYNAMIC_KEYMAP_ENABLE
    SRC += $(QUANTUM_DIR)/dynamic_keymap.c
endif

ifeq ($(strip $(LEADER_ENABLE)), yes)
  SRC += $(QUANTUM_DIR)/process_keycode/process_leader.c
  OPT_DEFS += -DLEADER_ENABLE
endif

include $(DRIVER_PATH)/qwiic/qwiic.mk

QUANTUM_SRC:= \
    $(QUANTUM_DIR)/quantum.c \
    $(QUANTUM_DIR)/keymap_common.c \
    $(QUANTUM_DIR)/keycode_config.c

# Include the standard or split matrix code if needed
ifneq ($(strip $(CUSTOM_MATRIX)), yes)
    ifeq ($(strip $(SPLIT_KEYBOARD)), yes)
        QUANTUM_SRC += $(QUANTUM_DIR)/split_common/matrix.c
    else
        QUANTUM_SRC += $(QUANTUM_DIR)/matrix.c
    endif
endif

DEBOUNCE_DIR:= $(QUANTUM_DIR)/debounce
# Debounce Modules. Set DEBOUNCE_TYPE=custom if including one manually.
DEBOUNCE_TYPE?= sym_g
ifneq ($(strip $(DEBOUNCE_TYPE)), custom)
    QUANTUM_SRC += $(DEBOUNCE_DIR)/$(strip $(DEBOUNCE_TYPE)).c
endif

ifeq ($(strip $(SPLIT_KEYBOARD)), yes)
    POST_CONFIG_H += $(QUANTUM_DIR)/split_common/post_config.h
    OPT_DEFS += -DSPLIT_KEYBOARD

    # Include files used by all split keyboards
    QUANTUM_SRC += $(QUANTUM_DIR)/split_common/split_util.c

    # Determine which (if any) transport files are required
    ifneq ($(strip $(SPLIT_TRANSPORT)), custom)
        QUANTUM_SRC += $(QUANTUM_DIR)/split_common/transport.c
        # Functions added via QUANTUM_LIB_SRC are only included in the final binary if they're called.
        # Unused functions are pruned away, which is why we can add multiple drivers here without bloat.
        QUANTUM_LIB_SRC += $(QUANTUM_DIR)/split_common/serial.c \
                           i2c_master.c \
                           i2c_slave.c
    endif
    COMMON_VPATH += $(QUANTUM_PATH)/split_common
endif

ifeq ($(strip $(OLED_DRIVER_ENABLE)), yes)
    OPT_DEFS += -DOLED_DRIVER_ENABLE
    COMMON_VPATH += $(DRIVER_PATH)/oled
    QUANTUM_LIB_SRC += i2c_master.c
    SRC += oled_driver.c
endif
