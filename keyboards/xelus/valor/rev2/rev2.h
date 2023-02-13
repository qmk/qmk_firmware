/* Copyright 2023 Harrison Chan (Xelus)
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

#ifdef VIA_ENABLE
// custom ID codes
enum via_indicator_value {
    id_caps_lock_enable = 1,
    id_caps_lock_brightness,
    id_caps_lock_color,
    id_caps_lock_key,
    id_caps_lock_override,
    id_num_lock_enable,
    id_num_lock_brightness,
    id_num_lock_color,
    id_num_lock_key,
    id_num_lock_override,
    id_scroll_lock_enable,
    id_scroll_lock_brightness,
    id_scroll_lock_color,
    id_scroll_lock_key,
    id_scroll_lock_override,
    id_layer_indicator_enable,
    id_layer_indicator_brightness,
    id_layer_indicator_color,
    id_layer_indicator_key,
    id_layer_indicator_override
};

// struct to save things
typedef struct {
    bool enable_caps_lock:1;            // |
    bool enable_num_lock:1;             // |
    bool enable_scroll_lock:1;          // |
    bool enable_layer_indicator:1;      // |
    bool caps_override_bl:1;            // |
    bool num_override_bl:1;             // |
    bool scroll_override_bl:1;          // |
    bool layer_override_bl:1;           // 1 byte
    HSV caps_lock_indicator;    // 3 bytes
    HSV num_lock_indicator;     // 3 bytes
    HSV scroll_lock_indicator;  // 3 bytes
    HSV layer_indicator;        // 3 bytes
    uint8_t caps_lock_key;      // 1 byte
    uint8_t num_lock_key;       // 1 byte
    uint8_t scroll_lock_key;    // 1 byte
    uint8_t layer_indicator_key;// 1 byte
} indicator_settings_config;
// total 17 bytes

// function declaration
void indicator_config_set_value( uint8_t *data );
void indicator_config_get_value( uint8_t *data );
void indicator_config_save ( void );
void _set_color(HSV *color, uint8_t *data);
void _get_color(HSV *color, uint8_t *data);
#endif

// Matrix definition
#define ____ KC_NO

#define LAYOUT_alice_split_bs( \
  K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, K214, \
  K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114,       \
  K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213,             \
        K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314,       \
        K401,       K403,       K405, K406,       K408,       K410,             K413              \
) { \
  { K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014 }, \
  { K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114 }, \
  { K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214 }, \
  { ____, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314 }, \
  { ____, K401, ____, K403, ____, K405, K406, ____, K408, ____, K410, ____, ____, K413, ____ }  \
}

#define LAYOUT_all LAYOUT_alice_split_bs
