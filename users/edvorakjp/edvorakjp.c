#include "edvorakjp.h"

void matrix_init_user(void) {
    edvorakjp_status_init();
    matrix_init_keymap();
}

__attribute__((weak)) void matrix_init_keymap() {}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, L_EDVORAKJP_LOWER, L_EDVORAKJP_RAISE, L_EDVORAKJP_ADJUST);
    return layer_state_set_keymap(state);
}

__attribute__((weak)) layer_state_t layer_state_set_keymap(layer_state_t state) { return state; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool process_record_user_result = process_record_keymap(keycode, record) && process_record_edvorakjp_swap_scln(keycode, record) && process_record_edvorakjp_config(keycode, record) && process_record_layer(keycode, record) && process_record_ime(keycode, record);
    return process_record_user_result;
}

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }
