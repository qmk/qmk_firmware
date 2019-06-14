#include "brandonschlack.h"

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

void matrix_scan_user(void) {
    matrix_scan_cmd_tab();
    matrix_scan_keymap();
}

__attribute__ ((weak))
layer_state_t layer_state_set_keymap (layer_state_t state) {
    return state;
}

// on layer change, no matter where the change was initiated
// Then runs keymap's layer change check
layer_state_t layer_state_set_user(layer_state_t state) {
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    state = layer_state_set_rgb(state);
#endif // RGBLIGHT_ENABLE
    return layer_state_set_keymap (state);
}
