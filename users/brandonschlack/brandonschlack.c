#include "brandonschlack.h"

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

void matrix_scan_user(void) {
    matrix_scan_cmd_tab();
    matrix_scan_keymap();
}
