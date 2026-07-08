/* Copyright 2021 Gizmo Engineering
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

enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  /   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | CTRL |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  | GUI  |  Alt |Lower |  Back|    Space    |  Alt |Raise | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_1x2u(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_SLSH,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_ENT,
  KC_LCTL, KC_LGUI, KC_LALT, LOWER,   KC_BSPC,     KC_SPC,       KC_RALT, RAISE,   KC_LEFT, KC_DOWN, KC_RGHT
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   _  |   +  |   {  |   }  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   -  |   =  |   [  |   ]  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |RGB_TG|RGB_M |RGB_HU|RGB_SI|RGB_VI|RGB_SP|      |      |      |   |  |   \  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Debug |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_1x2u(
  _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______,  _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______,
  _______, _______,  _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______,
  _______, RM_TOGG,  RM_NEXT, RM_HUEU, RM_SATU, RM_VALU, RM_SPDU, _______, _______, _______, KC_PIPE, KC_BSLS,
  DB_TOGG, _______,  _______, _______, _______,     _______,      _______, _______, _______, _______, _______
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  | F7   |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CAPS | PSCR |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Home | End  | Ins  | Play |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  <<  |  >>  | Mute | Vol- | Vol+ |      |      |      |      | PgUp |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      | PgDn |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_1x2u(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_CAPS, KC_PSCR, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, KC_HOME, KC_END,  KC_INS,  KC_MPLY, _______, _______, _______, _______, _______, _______, _______,
  _______, KC_MPRV, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______, _______, KC_PGUP, _______,
  _______, _______, _______, _______, _______,     _______,      _______, _______, _______, KC_PGDN, _______
),

};

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_user(void)
{
    rgb_matrix_set_color(25, 0, 0, 0);
    rgb_matrix_set_color(30, 0, 0, 0);
    rgb_matrix_set_color(35, 0, 0, 0);
    rgb_matrix_set_color(42, 0, 0, 0);
    return false;
}

void keyboard_pre_init_user(void) {
    //   5, 9, 14, 19, 24, 30, 36, 40, 46, 51, 55,  60
    g_led_config.matrix_co[4][0] = 5;
    g_led_config.matrix_co[4][1] = 9;
    g_led_config.matrix_co[4][2] = 14;
    g_led_config.matrix_co[4][3] = 19;
    g_led_config.matrix_co[4][4] = 24;
    g_led_config.matrix_co[4][5] = 30;
    g_led_config.matrix_co[4][6] = 36;
    g_led_config.matrix_co[4][7] = 41;
    g_led_config.matrix_co[4][8] = 47;
    g_led_config.matrix_co[4][9] = 52;
    g_led_config.matrix_co[4][10] = 57;
    g_led_config.matrix_co[4][11] = 62;
}
#endif
