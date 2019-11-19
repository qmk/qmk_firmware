#include "rev1.h"

__attribute__((weak))
void matrix_init_user(void) {}

void matrix_init_kb(void) {
    is_master = (uint8_t)is_keyboard_master();
    matrix_init_user();
}
