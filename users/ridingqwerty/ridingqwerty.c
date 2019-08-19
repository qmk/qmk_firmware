#include "ridingqwerty.h"

__attribute__((weak))
void matrix_init_keymap(void) {}

void matrix_init_user(void) {
#if defined(UNICODEMAP_ENABLED)
    set_unicode_input_mode(UC_LNX);
#endif
}
