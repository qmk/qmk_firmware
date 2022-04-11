#include "functions.h"

// Get current language layer
inline int get_language() {
    if (layer_state_cmp(default_layer_state, QGMLW_NO)) {
        return QGMLW_NO;
    }
    if (layer_state_cmp(default_layer_state, QGMLW_US)) {
        return QGMLW_US;
    }
    return -1;
}

// Placeholder function for dead key fix
void tap_dead_key(uint16_t keycode) { tap_code16(keycode); }
