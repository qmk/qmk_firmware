/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
    _BASE = 0,
    _MOVE = 1,
    _NUM = 2,
    _SETTINGS = 3,
};


// Aliases for readability
#define CTL_ESC  LCTL_T(KC_ESC)
#define MOVE_TAB LT(_MOVE, KC_TAB)
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: BASE
 *
 * ,-------------------------------------------.                              ,-----------------------------------------.
 * |MOVE/Tab|   B  |   É  |   P  |   O  |   È  |                              |   ^  |   V  |   D  |   L  |   J  |   Z  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |Ctrl/Esc|   A  |   U  |   I  |   E  |   ;  |                              |   C  |   T  |   S  |   R  |   N  |   M  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |    Ç   |   À  |   Y  |   X  |   :  |   K  |      | RGB  |  | SETNG|      |   ?  |   Q  |   G  |   H  |   F  |   W  |
 * `----------------------+------+------+------+ Space+------|  |------+ Enter+------+------+------+--------------------'
 *                        | MUTE | SUPER| ALT  |      | NUM  |  | MOVE |      | SHIFT|  ALT | TODO |
 *                        |      |      |      |      |(NUM) |  |(MOVE)|      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_BASE] = LAYOUT(
     MOVE_TAB, KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,                                           KC_Y,   KC_U,    KC_I,   KC_O,   KC_P, KC_LBRC,
     CTL_ESC , KC_A ,  KC_S   ,  KC_D  ,   KC_F ,   KC_G ,                                           KC_H,   KC_J,    KC_K,   KC_L,KC_SCLN, KC_QUOT,
     KC_BSLS , KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B , KC_SPC, RGB_TOG,  TG(_SETTINGS), KC_ENT,  KC_N,   KC_M, KC_COMM, KC_DOT,KC_SLSH, KC_RBRC,
                                KC_MUTE, KC_LGUI, KC_LALT, KC_SPC,TT(_NUM),  TT(_MOVE)   , KC_ENT,KC_RSFT,KC_RALT, RGB_TOG
    ),

/*
 * Navigation Layer: MOVE
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      | PrtSc|      |      |                              | PgUp | Home |   ↑  | End  | BkSpc| Insert |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | SUPER|  ALT | SHIFT| CTRL |CAPSLK|                              | PgDn |  ←   |   ↓  |   →  |  Del |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_MOVE] = LAYOUT(
      _______, _______, _______, KC_PSCR, _______, _______,                                     KC_PGUP, KC_HOME,   KC_UP,  KC_END, KC_BSPC, KC_INS,
      _______, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, KC_CAPS,                                     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL ,_______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,_______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Numbers Layer: NUM
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |   %  |      |      |      |      |        |  <--.
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|     |  test inversion
 * |    $   |   "  |  «   |  »   |  (   |  )   |                              |   @  |   +  |  -   |  /   |  *   |   =    |  <--'
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |  F12   |  F1  |  F2  |  F3  |  F4  |  F5  |      |      |  |      |      |  F6  |  F7  |  F8  |  F9  |  F10 |  F11   |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NUM] = LAYOUT(
      KC_GRV ,   KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,                                        KC_6,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , KC_EQL ,
      _______, _______, _______, _______, _______, _______,                                     KC_MINS, _______, _______, _______, _______, _______,
      KC_F12 ,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 ,  KC_F5 , _______, _______, _______, _______,  KC_F6 ,  KC_F7 ,  KC_F8 ,  KC_F9 , KC_F10 , KC_F11 ,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Settings Layer: SETTINGS
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SETTINGS] = LAYOUT(
      _______, RGB_M_P, RGB_M_B, RGB_M_R,RGB_M_SW,RGB_M_SN,                                     _______, _______, _______, _______, _______, _______,
      _______, RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T,RGB_M_TW,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG
    ),
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume or hue control
        if (clockwise) {
            switch (get_highest_layer(layer_state)) {
                #ifdef RGBLIGHT_ENABLE
                case _SETTINGS:
                    rgblight_decrease_hue_noeeprom();
                    break;
                #endif
                default:
                  tap_code(KC_VOLD);
            }
        } else {
            switch (get_highest_layer(layer_state)) {
                #ifdef RGBLIGHT_ENABLE
                case _SETTINGS:
                    rgblight_increase_hue_noeeprom();
                    break;
                #endif
                default:
                  tap_code(KC_VOLU);
            }
        }
    } else if (index == 1) {
        // Page up/Page down or RGB Brightness
        if (clockwise) {
            tap_code(KC_PGUP);
        } else {
            switch (get_highest_layer(layer_state)) {
                #ifdef RGBLIGHT_ENABLE
                case _SETTINGS:
                    rgblight_increase_val_noeeprom();
                    break;
                #endif
                default:
                  tap_code(KC_PGUP);
            }
        }
    }
    return false;
}
#endif // ENCODER_ENABLE