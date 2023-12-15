/* Copyright 2020 Brandon Schlack
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

#include "quantum.h"
#include "version.h"
#include "eeprom.h"
#include "process_records.h"
#ifdef TAP_DANCE_ENABLE
#   include "tap_dances.h"
#endif // TAP_DANCE_ENABLE
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
#   include "rgb_bs.h"
#endif

/* TODO Layer Names */
enum bs_layers {
    _BASE = 0,
    _M1 = 1,
    _M2 = 2,
    _M3 = 3,
    _M4 = 4,
    _FN1 = 5,
    _M1_FN1 = 6,
    _M2_FN1 = 7,
    _M3_FN1 = 8,
    _M4_FN1 = 9,
    _FN2 = 10,
    _M1_FN2 = 11,
    _M2_FN2 = 12,
    _M3_FN2 = 13,
    _M4_FN2 = 14,
    _ADJUST = 15 // 15: Change keyboard settings
};

#define _MACRO _M1
#define _LOWER _FN1
#define _RAISE _FN2

/* TODO User EECONFIG */
typedef union {
  uint32_t raw;
  struct {
    bool     rgb_layer_change :1;
    uint8_t  rgb_theme :4;
  };
} user_config_t;
extern user_config_t user_config;

void matrix_init_keymap(void);
void keyboard_post_init_keymap(void);
void shutdown_keymap(void);
void suspend_power_down_keymap(void);
void suspend_wakeup_init_keymap(void);
void matrix_scan_keymap(void);
layer_state_t default_layer_state_set_keymap(layer_state_t state);
layer_state_t layer_state_set_keymap(layer_state_t state);
bool led_update_keymap(led_t led_state);

#ifdef STOPLIGHT_LED
typedef struct {
    bool     is_active :1;
    uint8_t  index     :7;
    uint16_t timer     :16;
} stoplight_led_t;

void led_stoplight_start(void);
void led_stoplight_set(pin_t pin);
void led_stoplight_end(void);
void matrix_scan_led_stoplight(void);
#endif
