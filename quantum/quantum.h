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
#include "keyboard.h"

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

#include "keymap_common.h"
#include "quantum_keycodes.h"
#include "keycode_config.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "bootloader.h"
#include "timer.h"
#include "sync_timer.h"
#include "gpio.h"
#include "atomic_util.h"
#include "host.h"
#include "led.h"
#include "action_util.h"
#include "action_tapping.h"
#include "print.h"
#include "debug.h"
#include "suspend.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef BOOTMAGIC_ENABLE
#    include "bootmagic.h"
#endif

#ifdef DEFERRED_EXEC_ENABLE
#    include "deferred_exec.h"
#endif

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
#    include "song_list.h"
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

#ifdef LEADER_ENABLE
#    include "leader.h"
#endif

#ifdef UNICODE_COMMON_ENABLE
#    include "unicode.h"
#endif

#ifdef UCIS_ENABLE
#    include "ucis.h"
#endif

#ifdef UNICODEMAP_ENABLE
#    include "unicodemap.h"
#endif

#ifdef KEY_OVERRIDE_ENABLE
#    include "process_key_override.h"
#endif

#ifdef TAP_DANCE_ENABLE
#    include "process_tap_dance.h"
#endif

#ifdef AUTO_SHIFT_ENABLE
#    include "process_auto_shift.h"
#endif

#ifdef DYNAMIC_TAPPING_TERM_ENABLE
#    include "process_dynamic_tapping_term.h"
#endif

#ifdef COMBO_ENABLE
#    include "process_combo.h"
#endif

#ifdef KEY_LOCK_ENABLE
#    include "process_key_lock.h"
#endif

#ifdef SPACE_CADET_ENABLE
#    include "process_space_cadet.h"
#endif

#ifdef PROGRAMMABLE_BUTTON_ENABLE
#    include "programmable_button.h"
#endif

#ifdef HD44780_ENABLE
#    include "hd44780.h"
#endif

#ifdef SEND_STRING_ENABLE
#    include "send_string.h"
#endif

#ifdef HAPTIC_ENABLE
#    include "haptic.h"
#endif

#ifdef OLED_ENABLE
#    include "oled_driver.h"
#endif

#ifdef ST7565_ENABLE
#    include "st7565.h"
#endif

#ifdef QUANTUM_PAINTER_ENABLE
#    include "qp.h"
#endif

#ifdef DIP_SWITCH_ENABLE
#    include "dip_switch.h"
#endif

#ifdef DYNAMIC_MACRO_ENABLE
#    include "process_dynamic_macro.h"
#endif

#ifdef SECURE_ENABLE
#    include "secure.h"
#endif

#ifdef DYNAMIC_KEYMAP_ENABLE
#    include "dynamic_keymap.h"
#endif

#ifdef JOYSTICK_ENABLE
#    include "joystick.h"
#endif

#ifdef DIGITIZER_ENABLE
#    include "digitizer.h"
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

#ifdef POINTING_DEVICE_ENABLE
#    include "pointing_device.h"
#endif

#ifdef MOUSEKEY_ENABLE
#    include "mousekey.h"
#endif

#ifdef CAPS_WORD_ENABLE
#    include "caps_word.h"
#    include "process_caps_word.h"
#endif

#ifdef AUTOCORRECT_ENABLE
#    include "process_autocorrect.h"
#endif

#ifdef TRI_LAYER_ENABLE
#    include "tri_layer.h"
#endif

#ifdef REPEAT_KEY_ENABLE
#    include "repeat_key.h"
#    include "process_repeat_key.h"
#endif

void set_single_persistent_default_layer(uint8_t default_layer);

#define IS_LAYER_ON(layer) layer_state_is(layer)
#define IS_LAYER_OFF(layer) !layer_state_is(layer)

#define IS_LAYER_ON_STATE(state, layer) layer_state_cmp(state, layer)
#define IS_LAYER_OFF_STATE(state, layer) !layer_state_cmp(state, layer)

uint16_t get_record_keycode(keyrecord_t *record, bool update_layer_cache);
uint16_t get_event_keycode(keyevent_t event, bool update_layer_cache);
bool     pre_process_record_quantum(keyrecord_t *record);
bool     pre_process_record_kb(uint16_t keycode, keyrecord_t *record);
bool     pre_process_record_user(uint16_t keycode, keyrecord_t *record);
bool     process_action_kb(keyrecord_t *record);
bool     process_record_kb(uint16_t keycode, keyrecord_t *record);
bool     process_record_user(uint16_t keycode, keyrecord_t *record);
void     post_process_record_kb(uint16_t keycode, keyrecord_t *record);
void     post_process_record_user(uint16_t keycode, keyrecord_t *record);

void reset_keyboard(void);
void soft_reset_keyboard(void);

bool shutdown_kb(bool jump_to_bootloader);
bool shutdown_user(bool jump_to_bootloader);

void register_code16(uint16_t code);
void unregister_code16(uint16_t code);
void tap_code16(uint16_t code);
void tap_code16_delay(uint16_t code, uint16_t delay);

const char *get_numeric_str(char *buf, size_t buf_len, uint32_t curr_num, char curr_pad);
const char *get_u8_str(uint8_t curr_num, char curr_pad);
const char *get_u16_str(uint16_t curr_num, char curr_pad);
