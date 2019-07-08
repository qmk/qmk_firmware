#include QMK_KEYBOARD_H

enum custom_keycodes {
  UP_URL = SAFE_RANGE,
  MAC,
  LINUX,
  NUMB,
  COLLAPSE_METHODS_LINUX,
  COLLAPSE_METHODS_MAC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_ortho_4x4(
       LCTL(KC_C), LCTL(LSFT(KC_V)),   LCTL(KC_A),  TO(1),
       LCTL(LALT(KC_L)), LSFT(KC_F10),   LCTL(LALT(KC_5)),   LSFT(KC_F6),
       LCTL(KC_E), LCTL(KC_O),  LCTL(KC_SPACE),   LCTL(KC_0),
       COLLAPSE_METHODS_LINUX, LCTL(LSFT(KC_EQUAL)), LINUX, MO(2)
   ),
   [1] = LAYOUT_ortho_4x4(
        LGUI(KC_C), LCTL(LSFT(KC_V)),   LCTL(KC_A),  TO(2),
        LCTL(LALT(KC_L)), LSFT(KC_F10),   LCTL(LALT(KC_5)),   LSFT(KC_F6),
        LCTL(KC_E), LCTL(KC_O),  LCTL(KC_SPACE),   LCTL(KC_0),
        COLLAPSE_METHODS_MAC, LSFT(LCTL(KC_EQUAL)), MAC, MO(2)
    ),
  [2] = LAYOUT_ortho_4x4(
        KC_7, KC_8,   KC_9,  TO(0),
        KC_4, KC_5,   KC_6,   KC_SLSH,
        KC_1, KC_2,   KC_3,   KC_MINS,
        KC_0, KC_ENT, NUMB, MO(0)
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case UP_URL:
            if (record->event.pressed) {
                SEND_STRING("http://1upkeyboards.com");
            }
            return false;
            break;
        case MAC:
      	    if (record->event.pressed) {
                SEND_STRING("MAC");
            }
            return false;
            break;
      	case LINUX:
        	    if (record->event.pressed) {
                SEND_STRING("LINUX");
            }
            return false;
            break;
        case NUMB:
            if (record->event.pressed) {
              SEND_STRING("NUMPAD");
            }
            return false;
            break;
      	case COLLAPSE_METHODS_LINUX:
      	    if (record->event.pressed) {
          		SEND_STRING(SS_LCTRL(SS_LSFT(SS_TAP(X_KP_ASTERISK)))"1");
      	    }
      	    return false;
      	    break;
          case COLLAPSE_METHODS_MAC:
      	    if (record->event.pressed) {
          		SEND_STRING(SS_LALT(SS_LCTRL(SS_TAP(X_KP_ASTERISK)))"1");
      	    }
      	    return false;
      	    break;
    }
    return true;
}

void led_set_user(uint8_t usb_led) {

  #ifndef CONVERT_TO_PROTON_C
  /* Map RXLED to USB_LED_NUM_LOCK */
	if (usb_led & (1 << USB_LED_NUM_LOCK)) {
		DDRB |= (1 << 0); PORTB &= ~(1 << 0);
	} else {
		DDRB &= ~(1 << 0); PORTB &= ~(1 << 0);
	}

  /* Map TXLED to USB_LED_CAPS_LOCK */
	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
		DDRD |= (1 << 5); PORTD &= ~(1 << 5);
	} else {
		DDRD &= ~(1 << 5); PORTD &= ~(1 << 5);
	}
  #endif
}
