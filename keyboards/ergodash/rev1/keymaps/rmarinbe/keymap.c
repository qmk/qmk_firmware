/* Copyright 2021 Richard Marin B.
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

enum layers {
    _QWERTY,
    _NUMPAD,
    _SYMBOLS,
    _ADJUST,
    _MEDIA,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  NUMPAD,
  SYMBOLS,
  ADJUST,
  MEDIA,
};


enum combos {
  CMB_ENT1,
  CMB_ENT2,
  CMB_BSPC1,
  CMB_BSPC2,
  CMB_TAB,
  CMB_UNDS
};

const uint16_t PROGMEM ent1_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM ent2_combo[] = {KC_P5, KC_P6, COMBO_END};
const uint16_t PROGMEM bspc1_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM bspc2_combo[] = {KC_DLR, KC_LPRN, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM unds_combo[] = {KC_COMM, KC_DOT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [CMB_ENT1]  = COMBO(ent1_combo, KC_ENT),
  [CMB_ENT2]  = COMBO(ent2_combo, KC_ENT),
  [CMB_BSPC1] = COMBO(bspc1_combo, KC_BSPC),
  [CMB_BSPC2] = COMBO(bspc2_combo, KC_BSPC),
  [CMB_TAB]   = COMBO(tab_combo, KC_TAB),
  [CMB_UNDS]  = COMBO(unds_combo, KC_UNDS)
};

#define EISU LALT(KC_GRV)
#define LSH_D LSFT_T(KC_D)
#define LCTL_S LCTL_T(KC_S)
#define RSH_K RSFT_T(KC_K)
#define RCTL_L RCTL_T(KC_L)




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [0] = LAYOUT_4key(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, TO(3), TO(4), KC_6, KC_7, KC_8, KC_9, KC_0, KC_INS, KC_MINS, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_PGUP, KC_HOME, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_DEL, LSFT_T(KC_ESC), LCTL_T(KC_A), KC_S, KC_D, KC_F, KC_G, LT(4,KC_PGDN), LT(4,KC_END), KC_H, KC_J, KC_K, KC_L, LCTL_T(KC_SCLN), LSFT_T(KC_QUOT), KC_PIPE, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_LGUI, KC_RGUI, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_BSLS, LT(2,KC_ESC), TO(1), TO(2), KC_LALT, KC_SPC, LT(1,KC_SPC), KC_NO, KC_NO, LT(1,KC_ENT), KC_ENT, KC_RALT, TO(2), TO(1), LT(2,KC_CAPS)),
        [1] = LAYOUT_4key(KC_F11, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_CIRC, KC_NLCK, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F12, KC_MINS, KC_HASH, KC_EXLM, KC_LBRC, KC_RBRC, KC_COLN, KC_PIPE, KC_HOME, KC_ASTR, KC_P7, KC_P8, KC_P9, KC_PLUS, KC_GT, KC_TAB, KC_SLSH, KC_DLR, KC_LPRN, KC_RPRN, KC_COMM, KC_AMPR, KC_END, KC_SLSH, KC_P4, KC_P5, KC_P6, KC_MINS, KC_LT, KC_DQUO, KC_QUES, KC_AT, KC_LCBR, KC_RCBR, KC_SCLN, KC_QUOT, KC_NO, KC_PERC, KC_P1, KC_P2, KC_P3, KC_EQL, KC_CALC, KC_ESC, TO(0), TO(0), KC_LALT, KC_SPC, KC_SPC, KC_NO, KC_NO, KC_ENT, KC_P0, RALT_T(KC_P0), KC_PDOT, TO(0), KC_CAPS),
        [2] = LAYOUT_4key(KC_F11, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_ACL0, KC_FIND, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F12, KC_MINS, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_ACL1, KC_HOME, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL, KC_TAB, KC_BTN2, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_ACL2, KC_END, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, RCTL_T(KC_SCLN), RSFT_T(KC_QUOT), KC_PIPE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_BTN3, KC_RGUI, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSLS, KC_ESC, TO(0), TO(0), KC_LALT, KC_SPC, KC_BTN1, KC_NO, KC_NO, KC_ENT, KC_ENT, KC_RALT, TO(0), TO(0), KC_CAPS),
        [3] = LAYOUT_4key(RESET, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TO(0), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, BL_TOGG, BL_ON, BL_INC, BL_DEC, BL_OFF, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_TOG, RGB_SPI, RGB_HUI, RGB_HUD, RGB_SPD, KC_NO, KC_NO, RGB_VAD, RGB_SAD, RGB_SAI, RGB_VAI, KC_NO, KC_NO, KC_NO, KC_NO, RGB_M_P, RGB_M_B, RGB_M_G, RGB_M_K, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
        [4] = LAYOUT_4key(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MUTE, TO(0), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_SLEP, KC_NO, KC_NO, KC_NO, KC_MPRV, KC_MNXT, KC_NO, KC_VOLU, KC_WHOM, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MSTP, KC_MRWD, KC_MFFD, KC_MPLY, KC_VOLD, KC_WSCH, KC_WFAV, KC_WBAK, KC_WFWD, KC_WREF, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO)
};


// Initialize rgblight
void keyboard_post_init_user(void) {
	rgblight_enable_noeeprom();
	rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
	layer_state_set_user(layer_state);
	uint16_t user_hue = rgblight_get_hue();
	for (uint16_t i = 0; i <= 255; ++i) {
		rgblight_sethsv_noeeprom( (i + user_hue) % 256, 255, 255);
		wait_ms(5);
	}
	layer_state_set_user(layer_state);
};

// Turn on RGB underglow according to active layer
layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
		case _QWERTY: 
      rgblight_sethsv_noeeprom(100, 255, 0); 
      break;
		case _NUMPAD: 
      rgblight_sethsv_noeeprom(HSV_TEAL);
      break;
		case _SYMBOLS: 
      rgblight_sethsv_noeeprom(HSV_GREEN);
      break;
		case _MEDIA: 
      rgblight_sethsv_noeeprom(HSV_RED); 
      break;
		case _ADJUST: 
      rgblight_sethsv_noeeprom(HSV_PURPLE);
      break;
		default: 
      rgblight_sethsv_noeeprom(100, 255, 255);
      break;
	}
	return state;
};


void matrix_scan_user(void) {
    // Caps lock (blue)
    if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
    	backlight_disable();
    }   else {  
      backlight_enable();
    }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case NUMPAD:
      if (record->event.pressed) {
        layer_on(_NUMPAD);
      } else {
        layer_off(_NUMPAD);
      }
      return false;
      break;
    case SYMBOLS:
      if (record->event.pressed) {
        layer_on(_SYMBOLS);
      } else {
        layer_off(_SYMBOLS);
      }
      return false;
      break;
    case MEDIA:
      if (record->event.pressed) {
        layer_on(_MEDIA);
      } else {
        layer_off(_MEDIA);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
