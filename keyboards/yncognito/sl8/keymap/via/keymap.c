#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT_1x8_knob(
		KC_1, KC_3, KC_5, KC_7, KC_AUDIO_VOL_DOWN, 
		KC_2, KC_4, KC_6, TO(1), KC_AUDIO_VOL_UP),

	[1] = LAYOUT_1x8_knob(
		KC_Q, KC_E, KC_T, KC_U, KC_PGUP, 
		KC_W, KC_R, KC_Y, TO(2), KC_PGDN),

	[2] = LAYOUT_1x8_knob(
		RESET, KC_S, KC_F, KC_H, KC_UP, 
		KC_A, RGB_MOD, RGB_TOG, TO(0), KC_DOWN),

	[3] = LAYOUT_1x8_knob(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)

	};

void matrix_init_user(void) {
	DDRC = 0xFF;
	PORTC = 0xFF;
	DDRF = 0xFF;
	PORTF = 0xFF;
}


void encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t layer = biton32(layer_state);
    if (index == 0)  {
    if (clockwise) {
      tap_code16(dynamic_keymap_get_keycode(layer,0,4));
    } else {
      tap_code16(dynamic_keymap_get_keycode(layer,1,4));
    }
  }
}
