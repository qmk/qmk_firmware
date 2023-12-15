/* Copyright 2022 Daniel Weeks (@xanimos)
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

#ifdef RGB_MATRIX_ENABLE
#include "ctrl.h"

#include "md_rgb_matrix.h"
#include "rgb_matrix.h"
#include "config_led.h"

led_config_t g_led_config = { {
    {   0,   1,   2,   3,   4,   5,   6,   7 },
    {  16,  17,  18,  19,  20,  21,  22,  23 },
    {  33,  34,  35,  36,  37,  38,  39,  40 },
    {  50,  51,  52,  53,  54,  55,  56,  57 },
    {  63,  64,  65,  66,  67,  68,  69,  70 },
    {  76,  77,  78,  79,  80,  81,  82,  83 },
    {   8,   9,  10,  11,  12,  13,  14,  15 },
    {  24,  25,  26,  27,  28,  29,  30,  31 },
    {  41,  42,  43,  44,  45,  46,  47,  48 },
    {  58,  59,  60,  61,  62,  75,  49,  32 },
    {  71,  72,  73,  74,  84,  85,  86, NO_LED }
}, {
  // KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, KC_SCRL, KC_PAUS
    {   7,   5 }, {  31,   5 }, {  43,   5 }, {  55,   5 }, {  67,   5 }, {  85,   5 }, {  97,   5 }, { 109,   5 },
    { 121,   5 }, { 139,   5 }, { 151,   5 }, { 163,   5 }, { 175,   5 }, { 193,   5 }, { 205,   5 }, { 217,   5 },
  // KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_INS, KC_HOME, KC_PGUP
    {   7,  20 }, {  19,  20 }, {  31,  20 }, {  43,  20 }, {  55,  20 }, {  67,  20 }, {  79,  20 }, {  91,  20 },
    { 103,  20 }, { 115,  20 }, { 127,  20 }, { 139,  20 }, { 151,  20 }, { 169,  20 }, { 193,  20 }, { 205,  20 },
    { 217,  20 },
  // KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL, KC_END, KC_PGDN
    {  10,  30 }, {  25,  30 }, {  37,  30 }, {  49,  30 }, {  61,  30 }, {  73,  30 }, {  85,  30 }, {  97,  30 },
    { 109,  30 }, { 121,  30 }, { 133,  30 }, { 145,  30 }, { 157,  30 }, { 172,  30 }, { 193,  30 }, { 205,  30 },
    { 217,  30 },
  // KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT
    {  11,  39 }, {  28,  39 }, {  40,  39 }, {  52,  39 }, {  64,  39 }, {  76,  39 }, {  88,  39 }, { 100,  39 },
    { 112,  39 }, { 124,  39 }, { 136,  39 }, { 148,  39 }, { 168,  39 },
  // KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP
    {  14,  49 }, {  34,  49 }, {  46,  49 }, {  58,  49 }, {  70,  49 }, {  82,  49 }, {  94,  49 }, { 106,  49 },
    { 118,  49 }, { 130,  49 }, { 142,  49 }, { 165,  49 }, { 205,  49 },
  // KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(1), KC_APP, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    {   8,  59 }, {  23,  59 }, {  38,  59 }, {  83,  59 }, { 129,  59 }, { 144,  59 }, { 159,  59 }, { 174,  59 },
    { 193,  59 }, { 205,  59 }, { 217,  59 },
  // Underglow / Border
    { 224,  64 }, { 204,  64 }, { 186,  64 }, { 167,  64 }, { 149,  64 }, { 130,  64 }, { 112,  64 }, {  94,  64 },
    {  75,  64 }, {  57,  64 }, {  38,  64 }, {  20,  64 }, {   0,  64 }, {   0,  47 }, {   0,  32 }, {   0,  17 },
    {   0,   0 }, {  20,   0 }, {  38,   0 }, {  57,   0 }, {  75,   0 }, {  94,   0 }, { 112,   0 }, { 130,   0 },
    { 149,   0 }, { 167,   0 }, { 186,   0 }, { 204,   0 }, { 224,   0 }, { 224,  17 }, { 224,  32 }, { 224,  47 }
}, {
  // KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, KC_SCRL, KC_PAUS
    1, 4, 4, 4, 4, 1, 1, 1,
    1, 4, 4, 4, 4, 1, 1, 1,
  // KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_INS, KC_HOME, KC_PGUP
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 1, 1, 1,
    1,
  // KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL, KC_END, KC_PGDN
    1, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 1, 1,
    1,
  // KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT
    1, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 1,
  // KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP
    1, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 1, 1,
  // KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(1), KC_APP, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    1, 1, 1, 4, 1, 1, 1, 1,
    1, 1, 1,
  // Underglow / Border
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2
} };


#ifdef USB_LED_INDICATOR_ENABLE
bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    md_rgb_matrix_indicators_advanced(led_min, led_max);
    return rgb_matrix_indicators_advanced_user(led_min, led_max);
}
#endif // USB_LED_INDICATOR_ENABLE

#endif
