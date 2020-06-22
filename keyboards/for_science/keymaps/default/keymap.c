/* Copyright 2017 Paul James (paul@peej.co.uk)
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
#include "for_science.h"

#define _______ KC_TRNS

#define _BASE 0
#define _LAYER 3
#define _MOD_LAYER 5
#define _FUNCT 10

#define SFT_A SFT_T(KC_A)
#define SFT_F1 SFT_T(KC_F1)
#define SFT_Z SFT_T(KC_Z)
#define SFT_F6 SFT_T(KC_F6)
#define LAY_X LT(_LAYER, KC_X)
#define LAY_F7 LT(_LAYER, KC_F7)
#define LAY_SLS LT(_LAYER, KC_SLSH)
#define LAY_SPC LT(_LAYER, KC_SPACE)

#define LOCK LGUI(KC_L)
#define MAC_LCK LGUI(LCTL(KC_Q))

#define MODS_SHIFT (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
#define MODS_CTRL (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTRL))
#define MODS_ALT (MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))
#define MODS_GUI (MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI))
#define MODS_ANY (MODS_CTRL|MODS_ALT|MODS_GUI)

#define LAYER MO(_LAYER)
#define FUNCT MO(_FUNCT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * ,----------------------------------------   ----------------------------------------.
 * |  Tab  |  Esc  |   (   |   {   |   [   |   |   ]   |   }   |   )   |   '   | BkSp  |
 * |   ~   |   `   |   <   |   _   |   -   |   |   +   |   =   |   >   |   \   |  Del  |
 * |-------+-------+-------+-------+-------+   |-------+-------+-------+-------+-------|
 * |   Q   |   W   |   E   |   R   |   T   |   |   Y   |   U   |   I   |   O   |   P   |
 * |   1   |   2   |   3   |   4   |   5   |   |   6   |   7   |   8   |   9   |   0   |
 * |-------+-------+-------+-------+-------+   |-------+-------+-------+-------+-------|
 * |   A   |   S   |   D   |   F   |   G   |   |   H   |   J   |   K   |   L   | Enter |
 * |  F1   |  F2      F3   |  F4   |  F5   |   | PgUp  | Home  |  Up   |  End  |   ;   |
 * |-Shift-+-------+-------+-------+-------+   |-------+-------+-------+-------+-------|
 * |   Z   |   X   |   C   |   V   |   B   |   |   N   |   M   |   ,   |   .   |   /   |
 * |  F6   |  F7   |  F8   |  F9   |  F10  |   | PgDn  | Left  | Down  | Right |       |
 * `-Shift---Layer-+-------+-------+-------+   |-------+-------+-------+---------Layer-'
 *                 | Ctrl  |  Gui  |  Alt  |   | Space | Layer | Shift |
 *                 |       |       |       |   | Funct |       |       |
 *                 `------------------------   `-Layer-----------------'
 */

[_BASE] = KEYMAP(
    KC_TAB,  KC_ESC,  KC_LPRN, KC_LCBR, KC_LBRC,    KC_RBRC, KC_RCBR, KC_RPRN, KC_QUOT, KC_BSPC,
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    SFT_A,   KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L,    KC_ENT,
    SFT_Z,   LAY_X,   KC_C,    KC_V,    KC_B,       KC_N,    KC_M,    KC_COMM, KC_DOT,  LAY_SLS,
                      KC_LCTL, KC_LGUI, KC_LALT,    LAY_SPC, LAYER,   KC_RSFT
),

[_LAYER] = KEYMAP(
    KC_TILD, KC_GRV,  KC_LABK, KC_UNDS, KC_MINS,    KC_PLUS, KC_EQL,  KC_RABK, KC_BSLS, KC_DEL,
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    SFT_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_SCLN,
    SFT_F6,  LAY_F7,  KC_F8,   KC_F9,   KC_F10,     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______,
                      _______, _______, _______,    FUNCT,   _______, _______
),

[_MOD_LAYER] = KEYMAP(
    KC_TILD, _______, _______, _______, _______,    KC_Q,    _______, _______, _______, _______,
    KC_TAB,  _______, _______, _______, _______,    _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______,
                      _______, _______, _______,    _______, _______, _______
),

[_FUNCT] = KEYMAP(
    RESET,   _______, _______, _______, LOCK,       MAC_LCK, _______, _______, _______, MAGIC_SWAP_LALT_LGUI,
    _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______,
                      _______, _______, _______,    _______, _______, _______
),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keyboard_report->mods & MODS_ANY) {
        if (record->event.pressed) {
            layer_on(_MOD_LAYER);
        } else {
            layer_off(_MOD_LAYER);
        }
    }

    if (record->event.pressed) {
        if (keycode == KC_BSPC && keyboard_report->mods & MODS_ALT) {
            SEND_STRING(SS_TAP(X_DELETE));
            return false;
        }
    }

    return true;
};
