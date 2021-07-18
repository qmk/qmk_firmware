#include "jotpad16.h"

void matrix_init_kb(void) {

	matrix_init_user();
}

void keyboard_pre_init_kb() {
    setPinOutput(JOTPAD16_LED1);
    setPinOutput(JOTPAD16_LED2);
    
    keyboard_pre_init_user();
}
