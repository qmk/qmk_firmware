/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

enum custom_layers {
    _QWERTY,
    _SYMBOLS,
    _NAV,
};

#define XXX KC_NO
#define SYMBOLS MO(_SYMBOLS)
#define NAV MO(_NAV)
/*
static uint16_t default_animation = RGB_MATRIX_SOLID_COLOR;
static int default_speed = 50;
// Init
void keyboard_post_init_user(void) {
    rgb_matrix_sethsv_noeeprom(HSV_PURPLE);
    rgb_matrix_mode_noeeprom(default_animation);
    rgb_matrix_set_speed_noeeprom(default_speed);
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    HSV hsv = {0, 255, 255};

    if (layer_state_is(layer_state, 2)) {
        hsv = {130, 255, 255};
    } else {
        hsv = {30, 255, 255};
    }

    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }
    RGB rgb = hsv_to_rgb(hsv);

    for (uint8_t i = led_min; i <= led_max; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], 0x01)) { // 0x01 == LED_FLAG_MODIFIER
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}
*/

void pointing_device_init_kb(void) {
#ifdef PMW3360_CPI
    pointing_device_set_cpi(PMW3360_CPI);
#endif
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base (qwerty)
     * ,-----------------------------------------,                                           ,-----------------------------------------,
     * |  TAB |   q  |   w  |   e  |   r  |   t  |                                           |   y  |   u  |   i  |   o  |   p  |  -   |
     * |------+------+------+------+------+------|                                           |-------------+------+------+-------------|
     * |      |   a  |   s  |   d  |   f  |   g  |                               (TRACKBALL) |   h  |   j  |   k  |   l  |   '  |  ;   |
     * |------+------+------+------+------|------|------|------|------,        |------|------|------|------+------+------+-------------|
     * |      |   z  |   x  |   c  |   v  |   b  | ESC  | BACK | FWD  |        |  <   |  >   |   n  |   m  |   ,  |   .  |   /  | PLAY |
     * |------+------+------+------,------,------,------,------,------,      ,------,------,------,------,------+------+------+--------,
     *                             |  BS  |  DEL | CMD  |  LT  |             | CMD  |  LT  |ENTER |      |        ,------,
     *                             |      |      |      |      |             |      |      |  +   |SPACE |        |  up  |
     *                             |      |      |      |      |             |      |      |CMDent|      | ,------+------+-----,
     *                             '------+------+------+------'             '------'------+------+------' | left |------|right|
     *                                    '------+------'                                  '------+------' '------+------+-----'
     *                                    | SHIFT| ALT  |                                  | PLAY | CTRL |        | down |
     *                                    '------+------'                                  '------+------'        '------'
     */
[_SYMBOLS] = LAYOUT( \
    KC_TAB,    KC_EXLM,    KC_AT,    KC_LPRN,    KC_RPRN,    KC_TILD,             KC_PPLS,    KC_P1,    KC_P2,    KC_P3,    KC_PMNS,    KC_MINUS,
    KC_LSFT,   KC_HASH,    KC_DLR,    KC_LCBR,    KC_RCBR,    KC_GRV,           KC_PAST,    KC_P4,    KC_P5,    KC_P6,    KC_SLASH, KC_BSLS,
    XXX,    KC_PERC,    KC_CIRC,    KC_LBRC,    KC_RBRC,    KC_PIPE,         KC_AMPR,    KC_P7,    KC_P8, KC_P9,  KC_P0, XXX,
                KC_BSPC, KC_DEL,  KC_ESC, KC_LBRC, KC_RBRC,             KC_COMM, KC_DOT, KC_LGUI, SYMBOLS, KC_ENTER, KC_SPACE,
                                KC_LSFT, KC_LALT, KC_LGUI, KC_R,            KC_MPLY, KC_LCTL, KC_LEFT, KC_UP, KC_DOWN, KC_RIGHT
),
[_QWERTY] = LAYOUT( \
    KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINUS,
    KC_LSFT,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_SCLN,
    XXX,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH, KC_P,
                KC_BSPC, KC_DEL,  KC_ESC, KC_LBRC, KC_RBRC,             KC_COMM, KC_DOT, KC_LGUI, KC_R, KC_ENTER, KC_SPACE,
                                KC_LSFT, KC_LALT, KC_LGUI, KC_R,        KC_MPLY, KC_LCTL, KC_LEFT, KC_UP, KC_DOWN, KC_RIGHT
),
[_NAV] = LAYOUT( \
    KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINUS,
    KC_LSFT,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_SCLN,
    KC_ESC,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH, KC_P,
                KC_BSPC, KC_DEL,  KC_ESC, KC_LBRC, KC_RBRC,        KC_MPLY, KC_LCTL, KC_LGUI, KC_R, KC_ENTER, KC_SPACE,
                                KC_LSFT, KC_LALT, KC_LGUI, KC_R,        KC_COMM, KC_DOT, KC_LEFT, KC_UP, KC_DOWN, KC_RIGHT
)
};
