#include QMK_KEYBOARD_H

#define _BL 0
#define _FN1 1
#define _FN2 2

enum custom_keycodes {
	SFT_ESC
};

#define MODS_SHIFT_MASK (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_BL] = LAYOUT_split_space(
		SFT_ESC,KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
		KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_ENT,
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_RSFT, KC_DOT,
		KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_SPC, KC_RCTL, MO(1), MO(2)),

	[_FN1] = LAYOUT_split_space(
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL,
		KC_TRNS, KC_PGUP, KC_VOLU, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_MINS, KC_EQL, KC_TRNS,
		KC_LSFT, KC_PGDN, KC_VOLD, KC_TRNS, KC_TRNS, KC_SCLN, KC_QUOT, KC_SLSH, KC_COMM, KC_TRNS, KC_HOME,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	[_FN2] = LAYOUT_split_space(
		KC_PWR, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, RESET,
		KC_TRNS, BL_TOGG, BL_STEP, BL_INC, BL_DEC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_CAPS, RGB_TOG, RGB_MOD, RGB_VAI, RGB_VAD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, KC_TRNS, KC_END,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_KANA)) {

	} else {

	}

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SFT_ESC:
      if (record->event.pressed) {
        if (get_mods() & MODS_SHIFT_MASK) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (get_mods() & MODS_SHIFT_MASK) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }

      return false;

    default:
      return true;
  }
}
