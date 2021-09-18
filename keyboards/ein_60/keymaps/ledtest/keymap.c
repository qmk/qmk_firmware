/* Copyright 2021 klackygears
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

enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _FUNCTION,
    };

enum custom_keycodes {
  RGBRST = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
     * ,-----------------------------------------.  ,------.  ,----------------------------------------.
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |  | Esc  |  |RGBRST|RGBHUI|RGBSAI|RGBVAI|RGBSPI| Bksp |
     * |------+------+------+------+------+------|  `------'  |------+------+------+------+------+------|
     * | Func |   A  |   S  |   D  |   F  |   G  |            |RGBRMO|RGBHUD|RGBSAD|RGBVAD|RGBSPD|Enter |
     * |------+------+------+------+------+------|            |------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |            |RGBTOG|   M  |   ,  |   .  |   /  |  '   |
     * |------+------+------|--------------------+  ,------.  +--------------------|------+------+------|
     * | Ctrl |  `   | GUI  | Alt  |Lower |Space |  |Space |  |Space |Raise | Left | Down |  Up  |Right |
     * `-----------------------------------------'  `------'  `-----------------------------------------'
     */
    [_QWERTY] = LAYOUT(
     KC_TAB,        KC_Q,   KC_W,    KC_E,    KC_R,       KC_T,   KC_MUTE,  RGBRST,     RGB_HUI,    RGB_SAI, RGB_VAI, RGB_SPI, KC_BSPC,
     MO(_FUNCTION), KC_A,   KC_S,    KC_D,    KC_F,       KC_G,             RGB_MOD,    RGB_HUD,    RGB_SAD, RGB_VAD, RGB_SPD, KC_ENT,
     OSM(MOD_LSFT), KC_Z,   KC_X,    KC_C,    KC_V,       KC_B,             RGB_TOG,    KC_M,       KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT,
     KC_LCTL,       KC_GRV, KC_LGUI, KC_LALT, MO(_LOWER), KC_SPC, KC_SPC,   KC_CAPS,    MO(_RAISE), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),
    /* Lower
     * ,-----------------------------------------.  ,------.  ,-----------------------------------------.
     * | Esc  |   !  |   @  |   #  |   $  |   %  |  |      |  |   ^  |   &  |   *  |   (  |   )  | Del  |
     * |------+------+------+------+------+------|  `------'  |------+------+------+------+------+------|
     * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |            |      |   _  |   +  |   {  |   }  |Enter |
     * |------+------+------+------+------+------|            |------+------+------+------+------+------|
     * |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |            |      |      |      | Mute |      |  |   |
     * |------+------+------|--------------------+  ,------.  +--------------------|------+------+------|
     * |      |      |      |      |Lower | Bksp |  |      |  | Bksp |Raise | Next | Vol- | Vol+ | Play |
     * `-----------------------------------------'  `------'  `-----------------------------------------'
     */
    [_LOWER] = LAYOUT(
     KC_ESC,  KC_EXLM,  KC_AT,   KC_HASH, KC_DLR,  KC_PERC,  _______,  KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
     KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,              _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______,
     KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             _______, _______, _______, KC_MUTE, _______, KC_PIPE,
     _______, _______,  _______, _______, _______, KC_BSPC,  _______,  KC_BSPC, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
    ),
    /* Raise
     * ,-----------------------------------------.  ,------.  ,-----------------------------------------.
     * | Esc  |   1  |   2  |   3  |   4  |   5  |  |      |  |   6  |   7  |   8  |   9  |   0  | Del  |
     * |------+------+------+------+------+------|  `------'  |------+------+------+------+------+------|
     * |      |   4  |   5  |   6  |   +  |  F5  |            |  F6  |   -  |   =  |   [  |   ]  |Enter |
     * |------+------+------+------+------+------|            |------+------+------+------+------+------|
     * |Enter |   7  |   8  |   9  |   -  |  F11 |            |  F12 |ISO # |ISO / | Mute |      |   \  |
     * |------+------+------|--------------------+  ,------.  +--------------------|------+------+------|
     * |      |   ,  |   0  |  .   |Lower | Bksp |  |      |  | Bksp |Raise | Next | Vol- | Vol+ | Play |
     * `-----------------------------------------'  `------'  `-----------------------------------------'
     */
    [_RAISE] = LAYOUT(
     KC_ESC,  KC_1,    KC_2,  KC_3,   KC_4,    KC_5,     _______,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
     _______, KC_4,    KC_5,  KC_6,   KC_PLUS, KC_F5,              KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______,
     KC_ENT,  KC_7,    KC_8,  KC_9,   KC_MINS, KC_F11,             KC_F12,  KC_NUHS, KC_NUBS, KC_MUTE, _______, KC_BSLS,
     _______, KC_COMM, KC_0,  KC_DOT, _______, KC_BSPC,  _______,  KC_BSPC, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
    ),
    /* Adjust (Lower + Raise)
     * ,-----------------------------------------.  ,------.  ,-----------------------------------------.
     * |      |      |      |      |      |      |  |      |  |RGBRST|RGBMOD|RGBVAI|RGBSAI|RGBHUI|      |
     * |------+------+------+------+------+------|  `------'  |------+------+------+------+------+------|
     * |      |      |      |      |      |      |            |      |RGBRMO|RGBVAD|RGBSAD|RGBHUD|RGBTOG|
     * |------+------+------+------+------+------|            |------+------+------+------+------+------|
     * |      |      |      |      |      |      |            |      |      |      |      |      |BLSTEP|
     * |------+------+------|--------------------+  ,------.  +--------------------|------+------+------|
     * |      |      |      |      |      |      |  |      |  |      |      |      |      |      | RESET|
     * `-----------------------------------------'  `------'  `-----------------------------------------'
     */
    [_ADJUST] = LAYOUT(
     _______, _______, _______, _______, _______, _______, _______, RGBRST,  RGB_MOD, RGB_VAI, RGB_SAI, RGB_HUI, _______,
     _______, _______, _______, _______, _______, _______,          _______, RGB_RMOD,RGB_VAD, RGB_SAD, RGB_HUD, RGB_TOG,
     _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, BL_STEP,
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET
    ),
    /* Function
     * ,-----------------------------------------.  ,------.  ,-----------------------------------------.
     * |      |      |      |      |      |      |  |      |  |      |      |  Up  |      |      |      |
     * |------+------+------+------+------+------|  `------'  |------+------+------+------+------+------|
     * |      |      |      |      |      |      |            |      | Left | Down |Right |      |      |
     * |------+------+------+------+------+------|            |------+------+------+------+------+------|
     * | Caps |      |      |      |      |      |            |      |      |      |      |      |      |
     * |------+------+------|--------------------+  ,------.  +--------------------|------+------+------|
     * |      |      |      |      |      |      |  |      |  |      |      |      |      |      |      |
     * `-----------------------------------------'  `------'  `-----------------------------------------'
     */
    [_FUNCTION] = LAYOUT(
     _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_UP,   _______, _______, _______,
     _______, _______, _______, _______, _______, _______,          _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
     KC_CAPS, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
        }
      #endif
      break;
  }
  return true;
}
