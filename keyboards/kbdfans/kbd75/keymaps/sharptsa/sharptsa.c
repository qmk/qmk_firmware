#include "sharptsa.h"

void keyboard_post_init_user(void) {
    keyboard_post_init_rgb_light();
    set_default_keyboard_rgb();
}

//Set rbg layers when layer is active
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    return state;
}

//Set rbg layer when caps lock is active
bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

void matrix_scan_user(void) {
    td_led_dance_stop();
}
