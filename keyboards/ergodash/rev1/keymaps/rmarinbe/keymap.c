#include QMK_KEYBOARD_H
extern keymap_config_t keymap_config;

enum layers {
    _QWERTY,
    _NUMPAD,
    _SYMBOLS,
    _ADJUST,
    _MOVE,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  NUMPAD,
  SYMBOLS,
  ADJUST,
  MOVE,
};

#define EISU LALT(KC_GRV)
#define LSH_D LSFT_T(KC_D)
#define LCTL_S LCTL_T(KC_S)
#define RSH_K RSFT_T(KC_K)
#define RCTL_L RCTL_T(KC_L)



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [0] = LAYOUT_4key(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, TO(3), TO(4), KC_6, KC_7, KC_8, KC_9, KC_0, KC_INS, KC_UNDS, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_PGUP, KC_HOME, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_DEL, KC_CAPS, KC_A, LCTL_T(KC_S), LSFT_T(KC_D), KC_F, KC_G, KC_PGDN, KC_END, KC_H, KC_J, RSFT_T(KC_K), RCTL_T(KC_L), KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_LALT, KC_RALT, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_BSLS, LT(4,KC_ESC), TO(1), TO(2), KC_LGUI, LT(2,KC_SPC), LT(1,KC_TAB), KC_NO, KC_NO, LT(1,KC_BSPC), LT(2,KC_ENT), LT(4,KC_APP), TO(2), TO(1), KC_BSPC),
        [1] = LAYOUT_4key(KC_F11, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, TO(0), KC_NLCK, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F12, KC_MINS, KC_EQL, KC_COMM, KC_LBRC, KC_RBRC, KC_COLN, KC_AMPR, KC_PERC, KC_ASTR, KC_P7, KC_P8, KC_P9, KC_PLUS, KC_GT, KC_CAPS, KC_QUOT, KC_DQUO, KC_LPRN, KC_RPRN, KC_SCLN, KC_PIPE, KC_CALC, KC_SLSH, KC_P4, KC_P5, KC_P6, KC_MINS, KC_LT, KC_LSFT, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_LALT, KC_RALT, KC_P0, KC_P1, KC_P2, KC_P3, KC_EQL, KC_CIRC, KC_BSPC, TO(0), TO(0), KC_NO, KC_SPC, KC_TAB, KC_NO, KC_NO, KC_BSPC, KC_ENT, KC_P0, KC_PDOT, TO(0), KC_BSPC),
        [2] = LAYOUT_4key(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_QUES, KC_PIPE, KC_NO, KC_NO, KC_NO, KC_LBRC, KC_RBRC, KC_NO, KC_CAPS, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_SLSH, KC_BSLS, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, KC_EQL, KC_1, KC_2, KC_3, KC_4, KC_5, KC_NO, KC_NO, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_ESC, TO(0), TO(0), KC_NO, KC_SPC, KC_TAB, KC_NO, KC_NO, KC_BSPC, KC_ENT, KC_NO, TO(0), TO(0), KC_BSPC),
        [3] = LAYOUT_4key(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TO(0), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RESET, RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, KC_NO, KC_NO, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, KC_NO, KC_NO, KC_NO, KC_NO, BL_TOGG, BL_BRTG, BL_INC, BL_DEC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
        [4] = LAYOUT_4key(KC_NO, KC_NO, KC_ACL0, KC_ACL1, KC_ACL2, KC_NO, KC_MUTE, TO(0), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_SLEP, KC_NO, KC_NO, KC_BTN2, KC_MS_U, KC_BTN1, KC_NO, KC_VOLU, KC_MPLY, KC_MRWD, KC_NO, KC_NO, KC_MFFD, KC_NO, KC_NO, KC_NO, KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_R, KC_VOLD, KC_MSTP, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_NO, KC_NO, KC_NO, KC_WH_D, KC_BTN3, KC_WH_U, KC_NO, KC_NO, KC_NO, KC_MPRV, KC_NO, KC_NO, KC_MNXT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO)
};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}



// Initialize rgblight
void keyboard_post_init_user(void) {
	rgblight_enable_noeeprom();
	rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
	layer_state_set_user(layer_state);
	uint16_t user_hue = rgblight_get_hue();
	for (uint16_t i = 0; i < 256; ++i) {
		rgblight_sethsv_noeeprom( (i + user_hue) % 256, 255, 255);
		wait_ms(5);
	}
	layer_state_set_user(layer_state);
};


// Turn on RGB underglow according to active layer
uint32_t layer_state_set_user(uint32_t state) {
	switch (biton32(state)) {
		case _QWERTY: 
      rgblight_sethsv_noeeprom(100, 255, 0); 
      break;
		case _NUMPAD: 
      rgblight_sethsv_noeeprom(HSV_TEAL);
      break;
		case _SYMBOLS: 
      rgblight_sethsv_noeeprom(HSV_PURPLE); 
      break;
		case _MOVE: 
      rgblight_sethsv_noeeprom(HSV_GREEN);
      break;
		case _ADJUST: 
      rgblight_sethsv_noeeprom(HSV_GOLD);
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
         print("mode just switched to qwerty and this is a huge string\n");
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
    case MOVE:
      if (record->event.pressed) {
        layer_on(_MOVE);
      } else {
        layer_off(_MOVE);
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
