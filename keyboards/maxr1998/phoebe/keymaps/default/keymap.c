/* Copyright 2019 Max Rumpf (@Maxr1998)
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

#include "keymap_german.h"
#include "sendstring_german.h"

enum layers {
  _QWERTZ,
  _SC,
  _FN,
  _GAMING
};

#define KC_SC MO(_SC)
#define KC_FN MO(_FN)
#define G_1 TO(_GAMING)
#define G_0 TG(_GAMING)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTZ
 * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
 * │ Esc │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │  ?  │
 * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │ ^ ° │  Q  │  W  │  E  │  R  │  T  │  Z  │  U  │  I  │  O  │  P  │Bkspc│
 * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │ Tab │  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │ +*~ │Enter│
 * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │Shift│  Y  │  X  │  C  │  V  │  B  │  N  │  M  │  ,  │  .  │  ↑  │Shift│
 * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
 * │ Ctl │ Sup │ Alt │LeadK│SpcCh│   Space   │AltGr│ Fun │  ←  │  ↓  │  →  │
 * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
 */
[_QWERTZ] = LAYOUT(
  KC_ESC,  DE_1,    DE_2,    DE_3,    DE_4,    DE_5,    DE_6,    DE_7,    DE_8,    DE_9,    DE_0,    DE_QUES,
  KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    DE_PLUS, KC_ENT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   SC_RSPC,
  KC_LCTL, KC_LGUI, KC_LALT, KC_BTN1, KC_SC,       KC_SPC,       KC_ALGR, KC_FN,   KC_LEFT, KC_DOWN, KC_RGHT
),

/* Special characters
 * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
 * │     │     │     │     │     │     │     │     │     │     │     │     │
 * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │ ´ ` │     │     │     │     │     │     │     │     │     │     │     │
 * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │     │     │     │     │     │     │     │     │     │     │ # ' │     │
 * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │     │ <>| │     │     │     │     │     │     │     │     │ - _ │     │
 * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
 * │     │     │     │  X  │     │           │     │  X  │     │     │     │
 * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
*/
[_SC] = LAYOUT(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  DE_ACUT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, DE_HASH, _______,
  _______, DE_LABK, _______, _______, _______, _______, _______, _______, _______, _______, DE_MINS, _______,
  _______, _______, _______, XXXXXXX, _______,      _______,     _______, XXXXXXX, _______, _______, _______
),

/* Function layer
 * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
 * │     │ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F10 │ F11 │ F12 │
 * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │     │     │     │     │     │     │     │  Ü  │ F9  │  Ö  │ Pscr│ Del │
 * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │ Lck │  Ä  │  ß  │     │     │ GAME│     │RGB S│RGB B│RGB S│     │     │
 * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │     │     │     │     │     │     │     │RGBH-│RGB T│RGBH+│ Pg↑ │     │
 * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
 * │  X  │     │  X  │  X  │  X  │           │  X  │  X  │ Home│ Pg↓ │ End │
 * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
 */
[_FN] = LAYOUT(
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F10,  KC_F11,  KC_F12,
  _______, _______, _______, _______, _______, _______, _______, DE_UDIA, KC_F9,   DE_ODIA, KC_PSCR, KC_DEL,
  QK_LOCK, DE_ADIA, DE_SS,   _______, _______, G_1,     _______, RGB_M_P, RGB_M_SW,RGB_M_SN,_______, _______,
  _______, _______, _______, _______, _______, _______, _______, UG_HUED, UG_TOGG, UG_HUEU, KC_PGUP, _______,
  XXXXXXX, _______, XXXXXXX, KC_BTN2, XXXXXXX,      _______,     XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_END
),

/* Gaming
 * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
 * │     │     │     │     │     │     │     │     │     │     │     │     │
 * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │     │     │     │     │     │     │     │     │     │     │     │     │
 * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │     │     │     │     │     │     │     │     │     │     │     │     │
 * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │     │     │     │     │     │     │     │     │     │     │     │     │
 * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
 * │Space│     │     │     │     │    Ctl    │     │Leave│     │     │     │
 * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
*/
[_GAMING] = LAYOUT(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  KC_SPC,  XXXXXXX, _______, _______, _______,      KC_LCTL,     _______, G_0,     _______, _______, _______
)
};

#define MODS_ALGR_MASK (MOD_BIT(KC_ALGR))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DE_QUES:
            if (get_mods() & MODS_ALGR_MASK) {
                if (record->event.pressed) {
                    register_code(DE_SS);
                } else {
                    unregister_code(DE_SS);
                }
                return false;
            }
            break;
        case KC_Z:
            if (get_mods() & MODS_ALGR_MASK) {
                if (record->event.pressed) {
                    register_code(DE_LABK);
                } else {
                    unregister_code(DE_LABK);
                }
                return false;
            }
            break;
    }
    return true;
}
