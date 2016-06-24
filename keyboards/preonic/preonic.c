#include "preonic.h"

void matrix_init_kb(void) {

    // Turn status LED on
    DDRE |= (1<<6);
    PORTE |= (1<<6);

	matrix_init_user();
};