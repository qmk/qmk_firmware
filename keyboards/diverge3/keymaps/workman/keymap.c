/* Copyright 2017 IslandMan93
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

// KEYMAP
extern keymap_config_t keymap_config;

#define _WORKMAN_P 0
#define _GAME 1
#define _RAISE 2

#define _______ KC_TRNS

#define SHIFT_MOD   MOD_BIT(KC_LSFT)
#define SPACE_RAISE LT(_RAISE, KC_SPC)
#define ENT_RAISE   LT(_RAISE, KC_ENT)
#define PAGE_PREV   S(LCTL(KC_TAB))
#define PAGE_NEXT   LCTL(KC_TAB)

enum custom_keycodes
{
  LO_BSPC = SAFE_RANGE,
  LO_1,
  LO_2,
  LO_3,
  LO_4,
  LO_5,
  LO_6,
  LO_7,
  LO_8,
  LO_9,
  LO_0,
};

bool process_record_user(uint16_t keycode, keyrecord_t* record)
{
    if (record->event.pressed) {
        switch (keycode) {
            case LO_BSPC:
                if (record->event.pressed) {
                    if (get_mods() & SHIFT_MOD) {
                        uint8_t current_mods = get_mods();
                        clear_mods();
                        SEND_STRING(SS_TAP(X_DELETE));
                        set_mods(current_mods);
                    } else {
                        SEND_STRING(SS_TAP(X_BSPACE));
                    }
                }
                return false;
            case LO_1:
                if (record->event.pressed) {
                    uint8_t current_mods = get_mods();
                    if (current_mods & SHIFT_MOD) {
                        clear_mods();
                        SEND_STRING("1");
                        set_mods(current_mods);
                    } else {
                        SEND_STRING("!");
                    }
                }
                return false;
            case LO_2:
                if (record->event.pressed) {
                    uint8_t current_mods = get_mods();
                    if (current_mods & SHIFT_MOD) {
                        clear_mods();
                        SEND_STRING("2");
                        set_mods(current_mods);
                    } else {
                        SEND_STRING("@");
                    }
                }
                return false;
            case LO_3:
                if (record->event.pressed) {
                    uint8_t current_mods = get_mods();
                    if (current_mods & SHIFT_MOD) {
                        clear_mods();
                        SEND_STRING("3");
                        set_mods(current_mods);
                    } else {
                        SEND_STRING("#");
                    }
                }
                return false;
            case LO_4:
                if (record->event.pressed) {
                    uint8_t current_mods = get_mods();
                    if (current_mods & SHIFT_MOD) {
                        clear_mods();
                        SEND_STRING("4");
                        set_mods(current_mods);
                    } else {
                        SEND_STRING("$");
                    }
                }
                return false;
            case LO_5:
                if (record->event.pressed) {
                    uint8_t current_mods = get_mods();
                    if (current_mods & SHIFT_MOD) {
                        clear_mods();
                        SEND_STRING("5");
                        set_mods(current_mods);
                    } else {
                        SEND_STRING("%");
                    }
                }
                return false;
            case LO_6:
                if (record->event.pressed) {
                    uint8_t current_mods = get_mods();
                    if (current_mods & SHIFT_MOD) {
                        clear_mods();
                        SEND_STRING("6");
                        set_mods(current_mods);
                    } else {
                        SEND_STRING("^");
                    }
                }
                return false;
            case LO_7:
                if (record->event.pressed) {
                    uint8_t current_mods = get_mods();
                    if (current_mods & SHIFT_MOD) {
                        clear_mods();
                        SEND_STRING("7");
                        set_mods(current_mods);
                    } else {
                        SEND_STRING("&");
                    }
                }
                return false;
            case LO_8:
                if (record->event.pressed) {
                    uint8_t current_mods = get_mods();
                    if (current_mods & SHIFT_MOD) {
                        clear_mods();
                        SEND_STRING("8");
                        set_mods(current_mods);
                    } else {
                        SEND_STRING("*");
                    }
                }
                return false;
            case LO_9:
                if (record->event.pressed) {
                    uint8_t current_mods = get_mods();
                    if (current_mods & SHIFT_MOD) {
                        clear_mods();
                        SEND_STRING("9");
                        set_mods(current_mods);
                    } else {
                        SEND_STRING("(");
                    }
                }
                return false;
            case LO_0:
                if (record->event.pressed) {
                    uint8_t current_mods = get_mods();
                    if (current_mods & SHIFT_MOD) {
                        clear_mods();
                        SEND_STRING("0");
                        set_mods(current_mods);
                    } else {
                        SEND_STRING(")");
                    }
                }
                return false;
        }
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_WORKMAN_P] = LAYOUT(
        KC_ESC,  LO_1,    LO_2,      LO_3,      LO_4,    LO_5,    LO_6,                            LO_6,      LO_7,        LO_8,    LO_9,    LO_0,   KC_MINS, KC_ESC,
        KC_GRV,  KC_Q,    KC_D,      KC_R,      KC_W,    KC_B,    KC_LPRN,                         KC_RPRN,   KC_J,        KC_F,    KC_U,    KC_P,   KC_SCLN, KC_EQL,
        KC_TAB,  KC_A,    KC_S,      KC_H,      KC_T,    KC_G,    KC_LCBR,                         KC_RCBR,   KC_Y,        KC_N,    KC_E,    KC_O,   KC_I,    KC_BSLS,
        KC_LCTL, KC_Z,    KC_X,      KC_M,      KC_C,    KC_V,    KC_LBRC,                         KC_RBRC,   KC_K,        KC_L,    KC_COMM, KC_DOT, KC_SLSH, KC_QUOT,
        KC_LSFT, RESET,   PAGE_PREV, PAGE_NEXT, KC_END,  KC_LGUI, KC_LALT, TG(_GAME),     LO_BSPC, ENT_RAISE, SPACE_RAISE, KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT, KC_RCTL),

    [_GAME] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,      KC_3,      KC_4,    KC_5,    KC_6,                            KC_6,      KC_7,        KC_8,    KC_9,    KC_0,   KC_MINS, KC_ESC,
        KC_GRV,  KC_Q,    KC_D,      KC_R,      KC_W,    KC_B,    KC_LPRN,                         KC_RPRN,   KC_J,        KC_F,    KC_U,    KC_P,   KC_SCLN, KC_EQL,
        KC_TAB,  KC_A,    KC_S,      KC_H,      KC_T,    KC_G,    KC_LCBR,                         KC_RCBR,   KC_Y,        KC_N,    KC_E,    KC_O,   KC_I,    KC_BSLS,
        KC_LCTL, KC_Z,    KC_X,      KC_M,      KC_C,    KC_V,    KC_LBRC,                         KC_RBRC,   KC_K,        KC_L,    KC_COMM, KC_DOT, KC_SLSH, KC_QUOT,
        KC_LSFT, KC_F1,   KC_F2,     KC_3,      KC_F5,   KC_SPC,  KC_LALT, TG(_GAME),     LO_BSPC, ENT_RAISE, SPACE_RAISE, KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT, KC_RCTL),

    [_RAISE] = LAYOUT(
        _______, KC_F1,   KC_F2,     KC_F3,     KC_F4,   KC_F5,   KC_F6,                           KC_F6,     KC_F7,       KC_F8,   KC_F9,   KC_F10,  KC_F11,  RESET,
        _______, _______, _______,   _______,   _______, _______, BL_INC,                          KC_VOLU,   _______,     _______, _______, _______, _______, KC_F12,
        _______, _______, _______,   _______,   _______, _______, BL_DEC,                          KC_VOLD,   KC_LEFT,     KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
        _______, _______, _______,   _______,   _______, _______, BL_BRTG,                         KC_MUTE,   _______,     _______, KC_MPRV, KC_MNXT, KC_MPLY, _______,
        _______, _______, _______,   _______,   _______, _______, BL_TOGG, _______,       _______, _______,   _______,     _______, _______, _______, _______, _______),

};