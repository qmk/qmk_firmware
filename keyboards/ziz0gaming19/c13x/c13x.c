#include "c13x.h"

const uint8_t PROGMEM row_pins[] = { F6, F5, D0, D4 };
const uint8_t PROGMEM col_pins[] = { F7, B1, B3, B2, B6, C6, D7, E6, B4, B5 };

void matrix_init_user(void) {
  // Optional: Add any initialization code here
}

void matrix_scan_user(void) {
  // Optional: Add any periodic code here
}
