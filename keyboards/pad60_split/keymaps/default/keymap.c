/* Copyright 2018 mythosmann
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
#define _BL 0
#define _FL 1
// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* base layer
  ,-------.-------.-------.-------.-------.-------.
  |  Esc  |   1   |   2   |   3   |   4   |   5   |
  |       |       |       |       |       |       |
  |-------+-------+-------+-------+-------+-------|
  |  Tab  |   Q   |   W   |   E   |   R   |   T   |
  |       |       |       |       |       |       |
  |-------+-------+-------+-------+-------+-------|
  |   `   |   A   |   S   |   D   |   F   |   G   |
  |       |       |       |       |       |       |
  |-------+-------+-------+-------+-------+-------|
  | Shift |   Z   |   X   |   C   |   V   |   B   |
  |       |       |       |       |       |       |
  |-------'-------+-------+-------+-------'-------|
  |     Ctrl      | LAlt  | RAlt  |     Space     |
  |               |       |       |               |
  `-----------------------------------------------'
  ,-------.-------.-------.-------.-------.-------.
  |   6   |   7   |   8   |   9   |   0   | BkSpc |
  |       |       |       |       |       |       |
  |-------+-------+-------+-------+-------+-------|
  |   Y   |   U   |   I   |   O   |   P   |   \   |
  |       |       |       |       |       |       |
  |-------+-------+-------+-------+-------+-------|
  |   H   |   J   |   K   |   L   |   ;   |   '   |
  |       |       |       |       |       |       |
  |-------+-------+-------+-------+-------+-------|
  |   N   |   M   |   ,   |   .   |   /   | Enter |
  |       |       |       |       |       |       |
  |-------'-------+-------+-------+-------'-------|
  |    Space      | Ralt  | Gui   | Rctrl |  Fn   |
  |               |       |       |       |       |
  `-----------------------------------------------'
  */

  [_BL] = LAYOUT( /* Base */
    // +---------+---------+---------+---------+---------+---------+
         KC_5    , KC_4    , KC_3    , KC_2    , KC_1    ,KC_ESC   ,
    // |---------|---------|---------|---------|---------|---------|
         KC_T    , KC_R    , KC_E    , KC_W    , KC_Q    ,KC_TAB   ,
    // |---------|---------|---------|---------|---------|---------|
         KC_G    , KC_F    , KC_D    , KC_S    , KC_A    ,KC_GRV   ,
    // |---------|---------|---------|---------|---------|---------|
         KC_B    , KC_V    , KC_C    , KC_X    , KC_Z    ,KC_LSFT  ,
    // |---------|---------|---------|---------|---------|---------|
        KC_SPC   , KC_SPC  , KC_LALT  , MO(_FL), KC_LCTL , KC_LCTL ,
    // +=========+=========+=========+=========+=========+=========+
    // +---------+---------+---------+---------+---------+---------+
        KC_6     , KC_7    , KC_8    , KC_9    , KC_0    , KC_BSPC ,
    // |---------|---------|---------|---------|---------|---------|
        KC_Y     , KC_U    , KC_I    , KC_O    , KC_P    , KC_BSLS ,
    // |---------|---------|---------|---------|---------|---------|
        KC_H     , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_QUOT ,
    // |---------|---------|---------|---------|---------|---------|
        KC_N     , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_ENT  ,
    // |---------|---------|---------|---------|---------|---------|
                   KC_SPC  , KC_RALT , MO(_FL) , KC_RCTL , TG(_FL)
    // +=========+=========+=========+=========+=========+=========+
  ),
  /* function layer
  ,-------.-------.-------.-------.-------.-------.
  |  F12  |  F1   |  F2   |  F3   |  F4   |  F5   |
  |       |       |       |       |       |       |
  |-------+-------+-------+-------+-------+-------|
  |       |       |       |       | MuTog | ClkUp |
  |       |       |       |       |       |       |
  |-------+-------+-------+-------+-------+-------|
  |       |       |       |       |       | ClkOn |
  |       |       |       |       |       |       |
  |-------+-------+-------+-------+-------+-------|
  |       |       |       |       |       | ClkDn |
  |       |       |       |       |       |       |
  |-------'-------+-------+-------+-------'-------|
  |               |       |       |               |
  |               |       |       |               |
  `-----------------------------------------------'
  ,-------.-------.-------.-------.-------.-------.
  |  F6   |  F7   |  F8   |  F9   |  F10  |  F11  |
  |       |       |       |       |       |       |
  |-------+-------+-------+-------+-------+-------|
  |       |       |       |       |       |       |
  |       |       |       |       |       |       |
  |-------+-------+-------+-------+-------+-------|
  |       |       |       |       |       |       |
  |       |       |       |       |       |       |
  |-------+-------+-------+-------+-------+-------|
  |       |       |       |       |       |       |
  |       |       |       |       |       |       |
  |-------'-------+-------+-------+-------'-------|
  |               |       |       |       |       |
  |               |       |       |       |       |
  `-----------------------------------------------'
  */

  [_FL] = LAYOUT( /* Functions */
    // +---------+---------+---------+---------+---------+---------+
        KC_F12    ,KC_F1    ,KC_F2    ,KC_F3    ,KC_F4    ,KC_F5    ,
    // |---------|---------|---------|---------|---------|---------|
        KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,AU_ON    ,MU_ON    ,CK_UP    ,
    // |---------|---------|---------|---------|---------|---------|
        KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,AU_OFF   ,MU_OFF  ,CK_TOGG  ,
    // |---------|---------|---------|---------|---------|---------|
        KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,MU_TOG  ,CK_DOWN  ,
    // |---------|---------|---------|---------|---------|---------|
        KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,
    // +=========+=========+=========+=========+=========+=========+
    // +---------+---------+---------+---------+---------+---------+
        KC_F6    ,KC_F7    ,KC_F8    ,KC_F9    ,KC_F10   ,KC_F11   ,
    // |---------|---------|---------|---------|---------|---------|
        KC_TRNS  ,KC_MINS  ,KC_EQL   ,KC_RBRC  ,KC_LBRC  ,KC_TRNS  ,
    // |---------|---------|---------|---------|---------|---------|
        KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_UP    ,KC_TRNS  ,
    // |---------|---------|---------|---------|---------|---------|
        KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_LEFT  ,KC_DOWN  ,KC_RIGHT ,
    // |---------|---------|---------|---------|---------|---------|
             KC_TRNS       ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS
    // +=========+=========+=========+=========+=========+=========+
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QMKBEST:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("QMK is the best thing ever!");
      } else {
        // when keycode QMKBEST is released
      }
      break;
    case QMKURL:
      if (record->event.pressed) {
        // when keycode QMKURL is pressed
        SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
      } else {
        // when keycode QMKURL is released
      }
      break;
  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
