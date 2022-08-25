/* Copyright 2022 Garrett Davis (@Gardego5)
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

/* This controls special press and hold keys.
 * Maps right arrow to F15 when held, to be used for push to talk.
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(0, KC_RIGHT):
            if (!record->tap.count) {
                if (record->event.pressed) {
                    register_code16(KC_F15);
                } else {
                    unregister_code16(KC_F15);
                }
            return false;
        }
        return true;
    }

  return true;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Base Layer
   * ,-------------------------------------------------------------------------.
   * | Esc |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |Bspace |
   * |-------------------------------------------------------------------------+
   * | Tab  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |Sh/Ent|
   * |-------------------------------------------------------------------------+
   * | Shift |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |  '  |
   * |-------------------------------------------------------------------------+
   * | Ctrl| Alt |  L3 | Gui |  L2  |   Space   |  L1  | Left| Down|  Up|Rt/F15|
   * `-------------------------------------------------------------------------'
   */

LAYOUT(
KC_ESC , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
KC_TAB , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_SFTENT,
KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_QUOT,
KC_LCTL, KC_LALT, MO(3)  , KC_LGUI, MO(2)  ,     KC_SPC      , MO(1)  , KC_LEFT, KC_DOWN, KC_UP  , LT(0, KC_RIGHT)
),

  /* FN Layer 1
   * ,-------------------------------------------------------------------------.
   * | ` ~ |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  | Delete|
   * |-------------------------------------------------------------------------+
   * | Tab  |  <  |  >  |  (  |  )  |     |     |  -  |  =  |  [  |  ]  |Sh/Ent|
   * |-------------------------------------------------------------------------+
   * | Shift |     |     |     |     |     |     |     |  ,  |  .  |  \  |Caps |
   * |-------------------------------------------------------------------------+
   * | Ctrl| Alt |  L3 | Gui |  L2  |   Space   |  L1  | Home| PgDn| PgUp| End |
   * `-------------------------------------------------------------------------'
   */

LAYOUT( /* Right */
KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_DEL ,
KC_TRNS, KC_LT  , KC_GT  , KC_LPRN, KC_RPRN, KC_NO  , KC_NO  , KC_MINS, KC_EQL , KC_LBRC, KC_RBRC, KC_TRNS,
KC_TRNS, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_TRNS, KC_TRNS, KC_BSLS, KC_CAPS,
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS     , KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

  /* FN Layer 2
   * ,-------------------------------------------------------------------------.
   * |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 |  F12  |
   * |-------------------------------------------------------------------------+
   * | Tab  |     | Mute| Vol-| Vol+|     |     | Left| Down|  Up |Right|Sh/Ent|
   * |-------------------------------------------------------------------------+
   * | Shift |     |Med<<|Pause|Med>>|     |     |     |LMous|RMous|     |     |
   * |-------------------------------------------------------------------------+
   * | Ctrl| Alt |  L3 | Gui |  L2  |   Space   |  L1  |<Mous|vMous|^Mous|>Mous|
   * `-------------------------------------------------------------------------'
   */

LAYOUT( /* Left */
KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,
KC_TRNS, KC_NO  , KC_MUTE, KC_VOLD, KC_VOLU, KC_NO  , KC_NO  , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_TRNS,
KC_TRNS, KC_NO  , KC_MPRV, KC_MPLY, KC_MNXT, KC_NO  , KC_NO  , KC_NO  , KC_BTN1, KC_BTN2, KC_NO  , KC_NO  ,
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS     , KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R
),

  /* FN Layer 3
   * ,-------------------------------------------------------------------------.
   * | Esc | RGB | RGB |     |     |     |#Lock|  7  |  8  |  9  |     |Bspace |
   * |-------------------------------------------------------------------------+
   * | Tab  |  /  |  *  |  -  |  +  |  =  |     |  4  |  5  |  6  |     |Sh/Ent|
   * |-------------------------------------------------------------------------+
   * | Shift |     |     |     |     |     |     |  1  |  2  |  3  |  Up |     |
   * |-------------------------------------------------------------------------+
   * | Ctrl| Alt |  L3 | Gui |  L2  |   Space   |   0  |  .  | Left| Down|Right|
   * `-------------------------------------------------------------------------'
   */

LAYOUT( /* 3 */
KC_ESC , RGB_TOG, RGB_MOD, KC_NO  , KC_NO  , KC_NO  , KC_NLCK, KC_P7  , KC_P8  , KC_P9  , KC_NO  , KC_BSPC,
KC_TRNS, KC_PSLS, KC_PAST, KC_PMNS, KC_PPLS, KC_PEQL, KC_NO  , KC_P4  , KC_P5  , KC_P6  , KC_NO  , KC_TRNS,
KC_TRNS, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_P1  , KC_P2  , KC_P3  , KC_UP  , KC_NO  ,
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS     , KC_P0  , KC_PDOT, KC_LEFT, KC_DOWN, KC_RGHT
),
};
