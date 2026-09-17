/* Copyright 2021 Gary Kong
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
#include "version.h"

enum layers {
    BASE, // default layer
    SYMB, // symbols
    MDIA,  // media keys
};

enum custom_keycodes {
  VRSN = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 *  -------------------------------------------             -------------------------------------------
 * |   =    |   1  |   2  |   3  |   4  |   5  |           |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+------|           |------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |           |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|           |------+------+------+------+------+--------|
 * | Caps   |   A  |   S  |   D  |   F  |   G  |           |   H  |   J  |   K  |   L  |   ;  |    '   |
 * |--------+------+------+------+------+------|           |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |           |   N  |   M  |   ,  |   .  |   /  | RShift |
 *  -------------------------------------------             -------------------------------------------
 *   | CTRL |GUI\` |ALT \ | Left |Right |                         |  Up  | Down |   [  |   ]  |  L1  |
 *    ----------------------------------                           ----------------------------------
 *                                         -------------         ---------------
 *                                        |Ctrl/ESC|LALT|       | RGUI |Ctrl/Alt|
 *                                  ------|------|------|       |------+--------+------
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 |Back  | Del  |------|       |------| Enter  |Space |
 *                                 |Space |      | End  |       | PgDn |        |      |
 *                                  --------------------         ----------------------
 *
 */
[BASE] = LAYOUT_6x7(
//  Left hand                                                                                             Right hand
    XXXXXXX,    XXXXXXX,        XXXXXXX,            XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    KC_EQL,     KC_1,           KC_2,               KC_3,       KC_4,       KC_5,       XXXXXXX,        XXXXXXX,  KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,
    KC_TAB,     KC_Q,           KC_W,               KC_E,       KC_R,       KC_T,       XXXXXXX,        XXXXXXX,  KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_BSLS,
    KC_CAPS,    KC_A,           KC_S,               KC_D,       KC_F,       KC_G,       XXXXXXX,        XXXXXXX,  KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,
    KC_LSFT,    KC_Z,           KC_X,               KC_C,       KC_V,       KC_B,                                 KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,
    KC_LCTL,    GUI_T(KC_GRV),  ALT_T(KC_BSLS),     KC_LEFT,    KC_RGHT,                                                      KC_UP,      KC_DOWN,    KC_LBRC,    KC_RBRC,    DF(SYMB),
                                                                         CTL_T(KC_ESC), KC_LALT,        KC_RGUI, CTL_T(KC_LNG1),
                                                                                        KC_HOME,        KC_PGUP,
                                                                        KC_BSPC, KC_DEL, KC_END,        KC_PGDN, KC_ENT, KC_SPC
),
/* Keymap 1: Sybol layer
 *
 *  -------------------------------------------             -------------------------------------------
 * |   F1   |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  |  F10 |  F11 |   F12  |
 * |--------+------+------+------+------+------|           |------+------+------+------+------+--------|
 * | Tab    |   !  |   @  |   {  |   }  |      |           |NUMLCK|   7  |   8  |   9  |   -  |    /   |
 * |--------+------+------+------+------+------|           |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |      |           |      |   4  |   5  |   6  |   +  |    *   |
 * |--------+------+------+------+------+------|           |------+------+------+------+------+--------|
 * | LShift |   %  |   ^  |   [  |   ]  |      |           |  L2  |   1  |   2  |   3  |   =  | RShift |
 *  -------------------------------------------             -------------------------------------------
 *   | CTRL |GUI\~`|ALT \ | Left | Right|                         |  Up  | Down |    . |   0  |      |
 *    ----------------------------------                           ----------------------------------
 *                                  -------------         ---------------
 *                                 |Ctrl/ESC|LALT|       | RGUI |Ctrl/Alt|
 *                           ------|------|------|       |------+--------+------
 *                          |      |      | Home |       | PgUp |        |      |
 *                          |BackSp| Del  |------|       |------|  Enter |Space |
 *                          |      |      | End  |       | PgDn |        |      |
 *                           --------------------         ----------------------
 *
 */
[SYMB] = LAYOUT_6x7(
//  Left hand                                                                                       Right hand
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      XXXXXXX,        XXXXXXX,    KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,
    _______,    KC_EXLM,    KC_AT,      KC_LCBR,    KC_RCBR,    XXXXXXX,    XXXXXXX,        XXXXXXX,    KC_NUM,     KC_P7 ,     KC_P8 ,     KC_P9,      KC_MINS,    KC_PSLS,
    XXXXXXX,    KC_HASH,    KC_DLR,     KC_LPRN,    KC_RPRN,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    KC_P4 ,     KC_P5 ,     KC_P6,      KC_PLUS,    KC_PAST,
    _______,    KC_PERC,    KC_CIRC,    KC_LBRC,    KC_RBRC,    XXXXXXX,                                DF(MDIA),   KC_P1 ,     KC_P2 ,     KC_P3,      KC_PEQL,    _______,
    _______,    _______,    _______,    _______,    _______,                                                        _______,    _______,    KC_PDOT,    KC_P0,      DF(BASE),
                                                                   _______, _______,        _______, _______,
                                                                            _______,        _______,
                                                          _______, _______, _______,        _______, _______, _______
),
/* Keymap 2: Media and mouse keys
 *
 *  -------------------------------------------             -------------------------------------------
 * | SLEEP  |BR_Up |BR_Dn |      |      |Eject |           | Prev | Play | Next | Mute |Vol_Up| Vol_Dn |
 * |--------+------+------+------+------+------|           |------+------+------+------+------+--------|
 * |        |      | Lclk | MsUp | Rclk |MsWhUp|           |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|           |------+------+------+------+------+--------|
 * | QK_BOOT  |      |MsLeft|MsDown|MsRght|MsWhDw|           |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|           |------|------+------+------+------+--------|
 * | LShift |      |MsWhL |      |MsWhR |      |           |      |      |      |      |      | RShift |
 *  -------------------------------------------             -------------------------------------------
 *   | CTRL |GUI\~`|ALT \ | Left | Right|                         |  Up  | Down |      |      |  L0  |
*    ----------------------------------                           -----------------------------------
 *                                  -------------         ---------------
 *                                 |Ctrl/ESC|LALT|       | RGUI |Ctrl/Alt|
 *                           ------|------|------|       |------+--------+------
 *                          |      |      | Home |       | PgUp |        |      |
 *                          |BackSp| Del  |------|       |------|  Enter |Space |
 *                          |      |      | End  |       | PgDn |        |      |
 *                           --------------------         ----------------------
 *
 */
[MDIA] = LAYOUT_6x7(
//  Left hand                                                                                          Right hand
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,      XXXXXXX,      XXXXXXX,       XXXXXXX,     XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,
    KC_SLEP,    KC_BRID,    KC_BRIU,    XXXXXXX,    XXXXXXX,      XXXXXXX,      KC_EJCT,       XXXXXXX,     KC_MPRV,    KC_MPLY,    KC_MNXT,  KC_MUTE,    KC_VOLD,    KC_VOLU,
    XXXXXXX,    XXXXXXX,    MS_BTN1,    MS_UP,      MS_BTN2,      MS_WHLU,      XXXXXXX,       XXXXXXX,     XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,
    QK_BOOT,    XXXXXXX,    MS_LEFT,    MS_DOWN,    MS_RGHT,      MS_WHLD,      XXXXXXX,       XXXXXXX,     XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,
    _______,    XXXXXXX,    MS_WHLL,    XXXXXXX,    MS_WHLR,      XXXXXXX,                                  DF(SYMB),   XXXXXXX,    XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,
    _______,    _______,    _______,    _______,    _______,                                                            _______,    _______,  XXXXXXX,    XXXXXXX,    DF(BASE),
                                                                       _______, _______,        _______, _______,
                                                                                _______,        _______,
                                                              _______, _______, _______,        _______, _______, _______
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case VRSN:
                SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
                return false;
        }
    }
    return true;
}

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
    bajjak_right_led_1_off();
    bajjak_right_led_2_off();
    bajjak_right_led_3_off();

    uint8_t layer = get_highest_layer(state);
    switch (layer) {
        case 0:
            break;
        case 1:
            bajjak_right_led_1_on();
            break;
        case 2:
            bajjak_right_led_2_on();
            break;
        case 3:
            bajjak_right_led_3_on();
            break;
        case 4:
            bajjak_right_led_1_on();
            bajjak_right_led_2_on();
            break;
        case 5:
            bajjak_right_led_1_on();
            bajjak_right_led_3_on();
            break;
        case 6:
            bajjak_right_led_2_on();
            bajjak_right_led_3_on();
            break;
        case 7:
            bajjak_right_led_1_on();
            bajjak_right_led_2_on();
            bajjak_right_led_3_on();
            break;
        default:
            break;
    }

    return state;
};
