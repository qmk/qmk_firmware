/* Copyright 2019 eswai
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

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  BASE,
  RAISE,
  LOWER,
  ADJUST,
};

// Layers
enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
};

#define _____   KC_TRNS
#define XXXXX   KC_NO
#define KFUNC   TD(FUNC)
#define ALTSPC  ALT_T(KC_SPC)
#define CMDSPC  CMD_T(KC_SPC)
#define CTLENT  CTL_T(KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_ESC  ,KC_1 ,KC_2 ,KC_3 ,KC_4 ,KC_5    ,KC_GRV   ,KC_EQL  ,KC_6    ,KC_7    ,KC_8 ,KC_9   ,KC_0   , \
    KC_TAB  ,KC_U ,KC_I ,KC_E ,KC_R ,KC_W    ,KC_MINS  ,KC_Q    ,KC_P    ,KC_BSPC ,KC_T ,KC_O   ,KC_Y        ,KC_HOME , KC_PGUP, \
    KC_LCTL ,KC_K ,KC_D ,KC_G ,KC_S ,KC_QUOT ,KC_SCLN  ,KC_BSLS ,KC_F    ,KC_H    ,KC_L ,KC_A   ,KC_J        ,KC_END  , KC_DEL, \
    KC_LSFT ,KC_B ,KC_Z ,KC_X ,KC_M ,KC_C    ,KC_LBRC  ,KC_RBRC ,KC_COMM ,KC_N    ,KC_V ,KC_DOT ,KC_SLSH     ,KC_UP   , \
    KC_LCTL ,KC_LCMD ,KC_LALT ,MO(_LOWER) ,LSFT_T(KC_SPC),LSFT_T(KC_ENT),MO(_RAISE) , KC_RCTL       ,KC_LEFT ,KC_DOWN ,KC_RGHT
  )

};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
