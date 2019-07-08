#include "wulkan.h"

void matrix_init_kb(void) {
  matrix_init_user();
  set_unicode_input_mode(UC_LNX);
}
