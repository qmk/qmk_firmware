#include "planck.h"

__attribute__ ((weak))
void matrix_init_kb(void) {
	// Turn status LED on, with the exception of THK
	#if defined(__AVR_ATmega32U4__)
	setPinOutput(E6);
	writePinHigh(E6);
	#endif

	matrix_init_user();
}

const uint8_t music_map[MATRIX_ROWS][MATRIX_COLS] = LAYOUT_planck_grid(
	36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
	24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
	12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
	 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11
);

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    if (get_highest_layer(layer_state) > 0) {
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    } else {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
}
#endif
