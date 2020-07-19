#include "gotham.h"

__attribute__((weak)) void keyboard_pre_init_keymap(void) {}
__attribute__((weak)) void matrix_init_keymap(void) {}
__attribute__((weak)) void keyboard_post_init_keymap(void) {}
__attribute__((weak)) void matrix_scan_keymap(void) {}
__attribute__((weak)) void suspend_power_down_keymap(void) {}
__attribute__((weak)) void suspend_wakeup_init_keymap(void) {}
__attribute__((weak)) layer_state_t layer_state_set_keymap(layer_state_t state) { return state; }
__attribute__((weak)) bool led_update_keymap(led_t led_state) { return true; }

void keyboard_pre_init_user(void) {
    keyboard_pre_init_keymap();
}

void matrix_init_user(void) {
    matrix_init_keymap();
}

void keyboard_post_init_user(void) {
    encoder_init_keymap();
    keyboard_post_init_keymap();
}

void matrix_scan_user(void) {
    matrix_scan_keymap();
}

void suspend_power_down_user(void) {
    suspend_power_down_keymap();
}

void suspend_wakeup_init_user(void) {
    suspend_wakeup_init_keymap();
}

layer_state_t layer_state_set_user(layer_state_t state) {
    layer_state_t keymap_result = layer_state_set_keymap(state);
    return keymap_result;
}

bool led_update_user(led_t led_state) {
    bool keymap_result = led_update_keymap(led_state);
    return keymap_result;
}
