#include "jotanck.h"

void matrix_init_kb(void) {
  matrix_init_user();
}

void keyboard_pre_init_user() {
  setPinOutput(JOTANCK_LED1);
  setPinOutput(JOTANCK_LED2);
}
