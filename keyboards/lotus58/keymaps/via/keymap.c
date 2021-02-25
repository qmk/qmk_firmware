/* Copyright 2021 4EBOOT
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
#include QMK_KEYBOARD_H
#include "oled.c"
#include "encoder.c"


#define GRAVE_MODS  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT)|MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI)|MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))

enum custom_layers {
  _BL,
  _FL, // lower
  _CL  // raise
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * _BL
 * ,-----------------------------------------.            ,-------------------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |            |       |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|            |   D   |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |            |   I   |   Y  |   U  |   I  |   O  |   P  |  \|  |
 * |------+------+------+------+------+------|            |   S   |------+------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    |   P   |   H  |   J  |   K  |   L  |  :;  |  "'  |
 * |------+------+------+------+------+------| Knob  |    |       |------+------+------+------+------+------|
 * | LCTR |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |  ,<  |  .>  |  /?  |  Ent |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt |  DEL |Lower | / Space /       \ BKSP \  |Raise |  +=  |  {[  |  ]}  |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[0] = LAYOUT( \
  KC_ESC,    KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                          KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_MINS, \
  KC_TAB,    KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_BSLS, \
  KC_LSFT,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,   XXXXXXX,      XXXXXXX, KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT, \
  KC_LCTL,   KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,   KC_SPC,       KC_BSPC, KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_ENT, \
                              KC_LGUI, KC_LALT, KC_DEL, MO(_FL),      MO(_CL), KC_EQL,  KC_LBRC, KC_RBRC \
),
/*
 *
 * ,-----------------------------------------.            ,-------------------------------------------------.
 * | Reset|  F1  |  F2  |  F3  |  F4  |  F5  |            |       |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|            |   D   |------+------+------+------+------+------|
 * |      |      |      | Mute | PrtSc|      |            |   I   |      |      |      |      |      | F12  |
 * |------+------+------+------+------+------|            |   S   |------+------+------+------+------+------|
 * | Caps |      | Prev | P/P  | Next |      |-------.    |   P   | Left | Down |  Up  | Right|      |  '   |
 * |------+------+------+------+------+------|  Knob |    |       |------+------+------+------+------+------|
 * |      |      | BrDo |      | BrUp |      |-------|    |-------|      | Home | Ins  | End  |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt |      |LOWER | /Space  /       \BackSc\  |RAISE |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
*/

[1] = LAYOUT( \
  RESET,    KC_F1,    KC_F2,    KC_F3,     KC_F4,    KC_F5,                          KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11, \
  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC__MUTE,  KC_PSCR,  XXXXXXX,                        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
  KC_CAPS,  XXXXXXX,  KC_MPRV,  KC_MPLY,   KC_MNXT,  XXXXXXX, XXXXXXX,     XXXXXXX,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  XXXXXXX,  KC_QUOT, \
  XXXXXXX,  XXXXXXX,  KC_BRID,  XXXXXXX,   KC_BRIU,  XXXXXXX, KC_SPC,      KC_BSPC,  XXXXXXX,  KC_HOME,  KC_INS,   KC_END,   XXXXXXX,  XXXXXXX, \
                                KC_LGUI,   KC_LALT,  XXXXXXX, MO(_FL),     MO(_CL),  XXXXXXX,  XXXXXXX,  XXXXXXX \
),
/*
 *
 * ,-----------------------------------------.            ,-------------------------------------------------.
 * |      |      |      |      |      |      |            |       |      |      | Slash|  *   | Back |      |
 * |------+------+------+------+------+------|            |   D   |------+------+------+------+------+------|
 * |      |      |      |      |      |      |            |   I   |      |  7   |  8   |  9   |  -   |      |
 * |------+------+------+------+------+------|            |   S   |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    |   P   |      |  4   |  5   |  6   |  +   |      |
 * |------+------+------+------+------+------|  Knob |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |  1   |  2   |  3   |Enter |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt |      |LOWER | /Space  /       \BackSc\  |RAISE |  0   | space|  .   |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'-----------
 *
*/

[2] = LAYOUT( \
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                       XXXXXXX,  XXXXXXX,  KC_PSLS,  KC_PAST,  KC_BSPC,  XXXXXXX, \
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                       XXXXXXX,  KC_P7,    KC_P8,    KC_P9,    KC_PMNS,  XXXXXXX, \
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX,  KC_P4,    KC_P5,    KC_P6,    KC_PLUS,  XXXXXXX, \
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, KC_SPC,      KC_BSPC, XXXXXXX,  KC_P1,    KC_P2,    KC_P3,    KC_PENT,  XXXXXXX, \
                                KC_LGUI,  KC_LALT,  XXXXXXX, MO(_FL),     MO(_CL), KC_P0,    KC_SPC,   KC_PDOT \
),
[3] = LAYOUT( \
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, KC_SPC,      KC_BSPC, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
                                KC_LGUI,  KC_LALT,  XXXXXXX, MO(_FL),     MO(_CL), XXXXXXX,  XXXXXXX,  KC_PDOT \
)
};


const rgblight_segment_t PROGMEM _BL_Light[] = RGBLIGHT_LAYER_SEGMENTS(
    {0,57, HSV_WHITE}
);


const rgblight_segment_t PROGMEM _FL_Light[] = RGBLIGHT_LAYER_SEGMENTS(
    {0,57, HSV_GREEN}
);


const rgblight_segment_t PROGMEM _CL_Light[] = RGBLIGHT_LAYER_SEGMENTS(
    {0,57, HSV_RED}
);


const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    _BL_Light,
    _FL_Light,
    _CL_Light
);


void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
}
