#include QMK_KEYBOARD_H

void keyboard_post_init_user(void) {
#if defined(DEBUG_MATRIX_SCAN_RATE)
    debug_enable = true;
#endif
}
