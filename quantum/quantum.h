/* Copyright 2016-2018 Erez Zukerman, Jack Humbert, Yiancar
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "platform_deps.h"
#include "wait.h"
#include "matrix.h"
#include "keymap.h"

#ifdef BACKLIGHT_ENABLE
#    include "backlight.h"
#endif

#ifdef LED_MATRIX_ENABLE
#    include "led_matrix.h"
#endif

#if defined(RGBLIGHT_ENABLE)
#    include "rgblight.h"
#endif

#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix.h"
#endif

#include "action_layer.h"
#include "eeconfig.h"
#include "bootloader.h"
#include "bootmagic.h"
#include "timer.h"
#include "sync_timer.h"
#include "config_common.h"
#include "gpio.h"
#include "atomic_util.h"
#include "led.h"
#include "action_util.h"
#include "action_tapping.h"
#include "print.h"
#include "send_string.h"
#include "suspend.h"
#include <stddef.h>
#include <stdlib.h>

extern layer_state_t default_layer_state;

#ifndef NO_ACTION_LAYER
extern layer_state_t layer_state;
#endif

#if defined(SEQUENCER_ENABLE)
#    include "sequencer.h"
#    include "process_sequencer.h"
#endif

#if defined(MIDI_ENABLE) && defined(MIDI_ADVANCED)
#    include "process_midi.h"
#endif

#ifdef AUDIO_ENABLE
#    include "audio.h"
#    include "process_audio.h"
#    ifdef AUDIO_CLICKY
#        include "process_clicky.h"
#    endif
#endif

#ifdef STENO_ENABLE
#    include "process_steno.h"
#endif

#if defined(AUDIO_ENABLE) || (defined(MIDI_ENABLE) && defined(MIDI_BASIC))
#    include "process_music.h"
#endif

#if defined(BACKLIGHT_ENABLE) || defined(LED_MATRIX_ENABLE)
#    include "process_backlight.h"
#endif

#ifdef LEADER_ENABLE
#    include "process_leader.h"
#endif

#ifdef UNICODE_ENABLE
#    include "process_unicode.h"
#endif

#ifdef UCIS_ENABLE
#    include "process_ucis.h"
#endif

#ifdef UNICODEMAP_ENABLE
#    include "process_unicodemap.h"
#endif

#ifdef KEY_OVERRIDE_ENABLE
#    include "process_key_override.h"
#endif

#ifdef TAP_DANCE_ENABLE
#    include "process_tap_dance.h"
#endif

#ifdef PRINTING_ENABLE
#    include "process_printer.h"
#endif

#ifdef AUTO_SHIFT_ENABLE
#    include "process_auto_shift.h"
#endif

#ifdef COMBO_ENABLE
#    include "process_combo.h"
#endif

#ifdef KEY_LOCK_ENABLE
#    include "process_key_lock.h"
#endif

#ifdef TERMINAL_ENABLE
#    include "process_terminal.h"
#else
#    include "process_terminal_nop.h"
#endif

#ifdef SPACE_CADET_ENABLE
#    include "process_space_cadet.h"
#endif

#ifdef MAGIC_KEYCODE_ENABLE
#    include "process_magic.h"
#endif

#ifdef JOYSTICK_ENABLE
#    include "process_joystick.h"
#endif

#ifdef GRAVE_ESC_ENABLE
#    include "process_grave_esc.h"
#endif

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
#    include "process_rgb.h"
#endif

#ifdef HD44780_ENABLE
#    include "hd44780.h"
#endif

#ifdef HAPTIC_ENABLE
#    include "haptic.h"
#    include "process_haptic.h"
#endif

#ifdef OLED_ENABLE
#    include "oled_driver.h"
#endif

#ifdef ST7565_ENABLE
#    include "st7565.h"
#endif

#ifdef DIP_SWITCH_ENABLE
#    include "dip_switch.h"
#endif

#ifdef DYNAMIC_MACRO_ENABLE
#    include "process_dynamic_macro.h"
#endif

#ifdef DYNAMIC_KEYMAP_ENABLE
#    include "dynamic_keymap.h"
#endif

#ifdef VIA_ENABLE
#    include "via.h"
#endif

#ifdef WPM_ENABLE
#    include "wpm.h"
#endif

#ifdef USBPD_ENABLE
#    include "usbpd.h"
#endif

#ifdef ENCODER_ENABLE
#    include "encoder.h"
#endif

// For tri-layer
void          update_tri_layer(uint8_t layer1, uint8_t layer2, uint8_t layer3);
layer_state_t update_tri_layer_state(layer_state_t state, uint8_t layer1, uint8_t layer2, uint8_t layer3);

void set_single_persistent_default_layer(uint8_t default_layer);

#define IS_LAYER_ON(layer) layer_state_is(layer)
#define IS_LAYER_OFF(layer) !layer_state_is(layer)

#define IS_LAYER_ON_STATE(state, layer) layer_state_cmp(state, layer)
#define IS_LAYER_OFF_STATE(state, layer) !layer_state_cmp(state, layer)

uint16_t get_record_keycode(keyrecord_t *record, bool update_layer_cache);
uint16_t get_event_keycode(keyevent_t event, bool update_layer_cache);
bool     process_action_kb(keyrecord_t *record);
bool     process_record_kb(uint16_t keycode, keyrecord_t *record);
bool     process_record_user(uint16_t keycode, keyrecord_t *record);
void     post_process_record_kb(uint16_t keycode, keyrecord_t *record);
void     post_process_record_user(uint16_t keycode, keyrecord_t *record);

void reset_keyboard(void);

void startup_user(void);
void shutdown_user(void);

void register_code16(uint16_t code);
void unregister_code16(uint16_t code);
void tap_code16(uint16_t code);

void led_set_user(uint8_t usb_led);
void led_set_kb(uint8_t usb_led);
bool led_update_user(led_t led_state);
bool led_update_kb(led_t led_state);

void api_send_unicode(uint32_t unicode);
