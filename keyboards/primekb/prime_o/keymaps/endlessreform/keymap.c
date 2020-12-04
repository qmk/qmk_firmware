/* Copyright 2020 Jacob Keisling 
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

// Make 7 underscores syntactic sugar for KC_TRANS
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Layer shorthand
#define _BASE  0
#define _LOWER 1
#define _RAISE 2
#define _NAV   3

// Shorten keycodes for readability
#define LT_NBSP LT(_NAV, KC_BSPC)
#define MT_WSFT_CAPS MT(MOD_LGUI | MOD_LSFT, KC_CAPS)

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  CDFC = SAFE_RANGE,
  CDFR,
  DBRL,
  DBRR,
  PIPE,
  SPIP,
  TASK
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    LCTL(LALT(KC_DEL)),        KC_1,   KC_2,   KC_3,   KC_4,     KC_5,   KC_END,  KC_PGDN,  KC_PGUP,  KC_HOME,  KC_6,   KC_7,     KC_8,   KC_9,   KC_0,   KC_DEL,
    KC_TAB,         KC_Q,   KC_W,   KC_E,   KC_R,     KC_T,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   KC_Y,   KC_U,     KC_I,   KC_O,   KC_P,   KC_INS,
    LCTL_T(KC_ESC), KC_A,   KC_S,   KC_D,   KC_F,     KC_G,   KC_F5,   KC_F6,    KC_F7,    KC_F8,    KC_H,   KC_J,     KC_K,   KC_L,   KC_SCLN,KC_QUOT,
    KC_LSFT,        KC_Z,   KC_X,   KC_C,   KC_V,     KC_B,   KC_F1,   KC_F2,    KC_F3,    KC_F4,    KC_N,   KC_M,     KC_COMM,KC_DOT, KC_SLSH,KC_ENT,
    MT_WSFT_CAPS,   KC_LGUI,KC_LALT,LGUI(KC_TAB),MO(_LOWER),LT_NBSP,KC_LEFT, KC_DOWN,  KC_UP,    KC_RIGHT, KC_SPC, MO(_RAISE),LCTL(KC_LALT),  KC_RALT,KC_RGUI,LCTL(KC_LSFT)
  ),

  [_LOWER] = LAYOUT(
    RESET,  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
    KC_GRV, KC_F9,  KC_F10, KC_F11, KC_F12, KC_A,   _______,_______,_______,_______,KC_B,   KC_7,   KC_8,   KC_9,   KC_ASTR,KC_EQL,
    CDFC  ,KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_C,   _______,_______,_______,_______,KC_D,   KC_4,   KC_5,   KC_6,   KC_PLUS,KC_MINS,
    KC_BSLS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_E,   _______,_______,_______,_______,KC_F,   KC_1,   KC_2,   KC_3,   _______,_______,
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_X,   KC_0,   KC_COMM,KC_DOT, _______,RESET
  ),

  [_RAISE] = LAYOUT(
    XXXXXXX,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
    KC_TILD,KC_VOLD,KC_MSTP,KC_VOLU,_______,DBRL   ,_______,_______,_______,_______,DBRR   ,KC_AMPR,KC_ASTR,KC_LPRN,_______,_______,
    CDFR,   KC_MPRV,KC_MPLY,KC_MNXT,_______,KC_LPRN,PIPE   ,_______,_______,SPIP   ,KC_RPRN,KC_DLR, KC_PERC,KC_CIRC,_______,KC_UNDS,
    KC_PIPE,KC_LBRC,KC_RBRC,KC_LCBR,KC_RCBR,TASK   ,_______,_______,_______,_______,_______,KC_EXLM,KC_AT,  KC_HASH,_______,_______,
    _______,_______,_______,_______,_______,KC_DEL ,_______,_______,_______,_______,_______,_______,_______,_______,_______,XXXXXXX
  ),
  
  [_NAV] = LAYOUT(
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,      _______,_______,_______,_______,_______,_______,
    _______,_______,LCTL(KC_RIGHT),_______,_______,_______,_______,_______,_______,_______,KC_END, KC_PGDN,KC_PGUP,KC_HOME,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,      KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,LALT(KC_LEFT),LALT(KC_RIGHT),
    _______,_______,_______,_______,_______,LCTL(KC_LEFT),_______,_______,_______,_______,LCTL(LSFT(KC_LEFT)),LSFT(KC_HOME),LSFT(KC_END),LCTL(LSFT(KC_RIGHT)),_______,_______,
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,      _______,_______,_______,_______,_______,_______
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CDFC:
      if (record->event.pressed) {
        SEND_STRING("```");
      } else {
      }
      break;
    case CDFR:
      if (record->event.pressed) {
        SEND_STRING("```{r }" SS_TAP(X_LEFT));
      } else {
      }
      break;
    case DBRL:
      if (record->event.pressed) {
        SEND_STRING("[[");
      } else {
      }
      break;
    case DBRR:
      if (record->event.pressed) {
        SEND_STRING("]]");
      } else {
      }
      break;
    case PIPE:
      if (record->event.pressed) {
        SEND_STRING("%>%");
      } else {
      }
      break;
    case SPIP:
      if (record->event.pressed) {
        SEND_STRING("%<>%");
      } else {
      }
      break;
    case TASK:
      if (record->event.pressed) {
        SEND_STRING("- [ ] ");
      } else {
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
