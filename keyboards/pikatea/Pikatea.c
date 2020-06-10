#include "pikatea.h"

void matrix_init_kb(void) {
	matrix_init_user();
}

void encoder_update_kb(uint8_t index, bool clockwise) {
    encoder_update_user(index, clockwise);
}