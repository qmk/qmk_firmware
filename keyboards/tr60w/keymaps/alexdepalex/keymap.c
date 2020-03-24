#include "tr60w.h"

enum userspace_layers {
  _FOO,
  _MAC,
  _WIN,
  _NAV,
  _ORG_ALT,
  _TRANS
};

enum custom_keycodes {
  LX_COPY = SAFE_RANGE,
  LX_PASTE,
  LX_LED_TEST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_FOO] = KEYMAP(
                KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_ESC, 
		LT(_NAV, KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, 
		KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_BSPC, 
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_LSFT, LT(_ORG_ALT, KC_GRV), 
		KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_RGUI, KC_RALT, KC_RCTL
    ),

	[_MAC] = KEYMAP(
                KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_ESC, 
		LT(_NAV, KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, 
		KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_BSPC, 
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_LSFT, LT(_ORG_ALT, KC_GRV), 
		KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_RGUI, KC_RALT, KC_RCTL
    ),

	[_WIN] = KEYMAP(
                KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_ESC, 
		LT(_NAV, KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, 
		KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_BSPC, 
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_LSFT, LT(_ORG_ALT, KC_GRV), 
		KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, KC_RGUI, KC_RCTL
    ),

	[_NAV] = KEYMAP(
                KC_INSERT, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, RESET, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDOWN, KC_PGUP, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_LCTL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC, 
		KC_TRNS, KC_TRNS, LX_LED_TEST, LX_COPY, LX_PASTE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

	[_ORG_ALT] = KEYMAP(
                KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, RESET, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, 
		KC_TRNS, KC_TRNS, RGB_MODE_FORWARD, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, KC_LEFT, KC_RIGHT, KC_TRNS, KC_DEL, 
		KC_TRNS, KC_TRNS, KC_TRNS, BL_TOGG, BL_DEC, BL_INC, BL_STEP, KC_TRNS, KC_TRNS, KC_TRNS, KC_DOWN, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

	[_TRANS] = KEYMAP(
                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LX_COPY:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_LCTRL)SS_TAP(X_INSERT)SS_UP(X_LCTRL));
      } else {
        // when keycode LX_COPY is released
      }
      break;
    case LX_PASTE:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_LSHIFT)SS_TAP(X_INSERT)SS_UP(X_LSHIFT));
      } else {
        // when keycode LX_PASTE is released
      }
      break;
    case LX_LED_TEST:
      if (record->event.pressed) {
        // rgblight_disable();
        rgblight_setrgb (0x44, 0x44, 0xFF);
      } else {
        // when keycode LX_LED_TEST is released
        // rgblight_enable();
        rgblight_setrgb (0x00, 0x00, 0xFF);
      }
      break;
  }
	return true;
}

uint32_t layer_state_set_user(uint32_t layer_state) {
  switch (biton32(layer_state)) {
    case _MAC:
        rgblight_setrgb (0x44, 0x44, 0xFF); break;
    case _WIN:
        rgblight_setrgb (0x00, 0x00, 0x00); break;
    case _NAV:
        rgblight_setrgb (0xFF, 0x44, 0x44); break;
    default:
        rgblight_setrgb (0x00, 0x00, 0x00); break;
  }
  return layer_state;
}

void led_set_user(uint8_t usb_led) {
	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
		DDRF |= (1 << 6); PORTF &= ~(1 << 6);
	} else {
		DDRF &= ~(1 << 6); PORTF &= ~(1 << 6);
	}
}
