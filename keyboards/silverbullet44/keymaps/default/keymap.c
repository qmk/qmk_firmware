/* Copyright %YEAR% %YOUR_NAME%
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
//enum custom_keycodes {
//  QMKBEST = SAFE_RANGE,
//  QMKURL
//};

#define _QWERTY 0
#define _CURSOL 1
#define _CALC 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  RGBRST,
  KC_00,
};
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define CALC LT(_CALC,   KC_ESC)
#define CUSL LT(_CURSOL, KC_TAB)
#define REVERSE(kc) \
case kc: \
  if (keyboard_report->mods & MOD_BIT(KC_LSFT)) { \
    if (record->event.pressed) { \
      unregister_code(KC_LSFT); \
      register_code(kc); \
      unregister_code(kc); \
      register_code(KC_LSFT); \
    } \
/*  } else if (keyboard_report->mods & MOD_BIT(KC_RSFT)) { \
    if (record->event.pressed) { \
      unregister_code(KC_RSFT); \
      register_code(kc); \
      unregister_code(kc); \
      register_code(KC_RSFT);
    } */ \
  } else { \
    if (record->event.pressed) { \
      register_code(KC_LSFT); \
      register_code(kc); \
      unregister_code(kc); \
      unregister_code(KC_LSFT); \
  } \
  } \
  return false; \
  break;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |                                  |   6  |   7  |   8  |   9  |   0  |  \   |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                                  |   Y  |   U  |   I  |   O  |   P  |  =   |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |   G  |                                  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |LCTRL |   Z  |   X  |   C  |   V  |   B  |-------.-------.  ,---------------|   N  |   M  |   ,  |   .  |   /  |  -   |
 * `-----------------------------------------/       /       /   \       \      \----------------------------------------'
 *                          | Alt  | Bksp | / Shift / Calc  /     \ Cursol\ CTRL | Del  |  App  |
 *                          |  F5  |      |/ Space /  Esc  /       \  Tab  \ Enter\     |  F12  |
 *                          `-----------------------------'         '---------------------------'
 */
 [_QWERTY] = LAYOUT( \
    KC_TAB,   KC_Q, KC_W, KC_E, KC_R, KC_T,                KC_Y,   KC_U,    KC_I,    KC_O,   KC_P,    KC_EQL,  \
    KC_LSFT,  KC_A, KC_S, KC_D, KC_F, KC_G,                KC_H,   KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT, \
    KC_LCTRL, KC_Z, KC_X, KC_C, KC_V, KC_B,                KC_N,   KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_MINS, \
    LALT_T(KC_F5), KC_BSPC, LSFT_T(KC_SPC), CALC,    CUSL, LCTL_T(KC_ENT), KC_DEL, GUI_T(KC_F12) \
  ),

/* Cursol
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * |  `   |  F1  |  F2  |  F3  |  F4  |  F5  |                                  |  F6  |  F7  |  F8  |  F9  |  F10 |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |  F1  |  F2  | PgUp |  F4  |  F5  |                                  |  F6  |  F7  |  Up  |  F9  | F10  |PrtSc |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |  ~   | Home | PgDw | End  |  (   |                                  |  )   | Left | Down |Right | F8   | F11  |
 * |------+------+------+------+------+------+                                  +------+------+------+------+------+------|
 * |      |  `  | CLft |  F3  | CRgt |  (   |-------.-------.  ,---------------|  )   | OSL  |  F8  | OSR  |      |      |
 * `-----------------------------------------/       /       /   \       \      \----------------------------------------'
 *                          | LAlt | LGUI | /       /       /     \       \      \  |      |      |
 *                          |      |      |/ LOWER /       /       \       \      \ |      |      |
 *                          `-----------------------------'         '-----------------------------'
 */
 [_CURSOL] = LAYOUT( \
  RESET ,  KC_F1,   KC_F2,      KC_PGUP, KC_F4,      KC_F5,                         KC_F6,   KC_F7,        KC_UP,   KC_F9,        KC_F10,  RGBRST,  \
  _______, KC_TILD, KC_HOME,    KC_PGDN, KC_END,     KC_LPRN,                       KC_RPRN, KC_LEFT,      KC_DOWN, KC_RGHT,      KC_PIPE, KC_F11,  \
  _______, KC_GRV,  C(KC_LEFT), KC_F3,   C(KC_RGHT), KC_LPRN,                       KC_RPRN, LCA(KC_LEFT), KC_F8,   LCA(KC_RGHT), KC_BSLS, _______, \
                                _______,    _______, C(KC_SPC), ADJUST,    _______, _______, _______, _______ \
  ),

/* Calculater
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * |  ~   |      |      |      |      |      |                                  |      | NmLk |      |      |      |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |  1   |  2   |  3   |  4   |  5   |                                  |  6   |  7   |  8   |  9   |  +   |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |  @   |  #   |  $   |  %   |  [   |                                  |  ]   |  4   |  5   |  6   |  ~   |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |  ^   |  &   |  *   |  !   |  {   |-------.-------.  ,---------------|  }   |  1   |  2   |  3   |  =   |      |
 * `-----------------------------------------/       /       /   \       \       \----------------------------------------'
 *                          |      |      | /-------/       /     \       \-------\  |      |      |
 *                          |      |      |/       /       /       \       \   0   \ |  00  |  .   |
 *                          `-----------------------------'         '------------------------------'
 */
 [_CALC] = LAYOUT( \
  _______, KC_1,    KC_2,     KC_3,     KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_PPLS, _______, \
  _______, KC_AT,   KC_HASH,  KC_DLR,   KC_PERC, KC_LBRC,                   KC_RBRC, KC_4,    KC_5,    KC_6,    KC_TILD, _______, \
  _______, KC_CIRC, KC_AMPR,  KC_ASTR,  KC_EXLM, KC_LCBR,                   KC_RCBR, KC_1,    KC_2,    KC_3,    KC_PEQL, _______, \
                              _______, _______, _______, _______,   ADJUST, KC_0,    KC_00,   KC_PDOT \
  ),

/*   ADJUST
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * |RESET |      |      |      |      |      |                                  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                                  | SPD+ | SPD+ | VAL+ | SAD+ | HUE+ |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                                  | SPD- | MOD- | VAL- | SAD- | HUE- |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.-------.  ,---------------|      |      |      |      |      |      |
 * `-----------------------------------------/       /       /   \       \       \----------------------------------------'
 *                          |      |      | /-------/       /     \       \-------\  |      |      |
 *                          |      |      |/       /       /       \       \       \ |      |      |
 *                          `-----------------------------'         '------------------------------'
*/

 [_ADJUST] = LAYOUT( \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, _______, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      RGB_SPI, RGB_MOD,  RGB_VAI, RGB_SAI, RGB_HUI, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      RGB_SPD, RGB_RMOD, RGB_VAD, RGB_SAD, RGB_HUD, XXXXXXX, \
                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
  )
};


#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif
int RGB_current_mode;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    REVERSE(KC_SCLN)
    case KC_00:
      if (record->event.pressed) {
        SEND_STRING("00");
      }
      return false;
      break;
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
