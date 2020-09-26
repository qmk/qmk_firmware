#include QMK_KEYBOARD_H
#include "jarred.h"

#define LAYOUT_ortho_4x12_wrapper(...) LAYOUT_ortho_4x12(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QW] = LAYOUT_ortho_4x12_wrapper(QWERTY_4x12),
    [_GAME] = LAYOUT_ortho_4x12_wrapper(GAME_4x12),
    [_LW] = LAYOUT_ortho_4x12_wrapper(LOWER_4x12),
    [_NV] = LAYOUT_ortho_4x12_wrapper(NAV_4x12),
    [_NP] = LAYOUT_ortho_4x12_wrapper(NUMPAD_4x12),
    [_MS] = LAYOUT_ortho_4x12_wrapper(MOUSE_4x12)
};

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_indicators_user(void) {
    #ifdef KEYBOARD_planck_light
    // Disable light in middle of 2U position of Planck Light
    rgb_matrix_set_color(42, 0, 0, 0);
    #endif
}
#endif
