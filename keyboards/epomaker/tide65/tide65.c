#include QMK_KEYBOARD_H

// clang-format off
void keyboard_pre_init_user(void) {
    setPinOutput(A5);
    writePinHigh(A5);
}
// clang-format on
