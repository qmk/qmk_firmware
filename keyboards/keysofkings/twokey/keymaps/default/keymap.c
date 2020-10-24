#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	LAYOUT(
		LT(1, KC_MUTE), 
		LT(4, KC_MPLY), LT(7, KC_MNXT)),		

	LAYOUT(
		KC_TRNS, 
		TO(2), TO(3)),

	LAYOUT(
		TO(0), 
		RGB_TOG, RGB_MOD),

	LAYOUT(
		TO(0), 
		RGB_HUI, RGB_HUD),

	LAYOUT(
		TO(5), 
		KC_TRNS, TO(6)),

	LAYOUT(
		TO(0), 
		RGB_SAI, RGB_SAD),

	LAYOUT(
		TO(0), 
		RGB_VAI, RGB_VAD),

	LAYOUT(
		TO(8), 
		TO(9), KC_TRNS),

	LAYOUT(
		TO(0), 
		CK_TOGG, MU_TOG),

	LAYOUT(
		TO(0), 
		RESET, EEPROM_RESET),
};

void matrix_init_user(void) {
  debug_config.matrix = 1;
  debug_config.keyboard = 1;
  debug_config.enable = 1;
}

void encoder_update_user(int8_t index, bool clockwise) {
  if (index == 0) {
    if (clockwise) {
      tap_code(KC_VOLD);
    } else {
      tap_code(KC_VOLU);
    }
    #    ifdef AUDIO_CLICKY
            clockwise ? clicky_freq_up() : clicky_freq_down();
#    endif
  }
}

