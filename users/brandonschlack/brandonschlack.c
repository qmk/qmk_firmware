#include "brandonschlack.h"

__attribute__((weak))
void keyboard_post_init_keymap(void){ }

void keyboard_post_init_user(void){
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    keyboard_post_init_rgb();
#endif
    keyboard_post_init_keymap();
}

__attribute__ ((weak))
void shutdown_keymap(void) {}

void shutdown_user (void) {
    #ifdef RGBLIGHT_ENABLE
        rgblight_enable_noeeprom();
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_sethsv_noeeprom(0, 255, 127);
    #endif // RGBLIGHT_ENABLE
    #ifdef RGB_MATRIX_ENABLE
        rgb_matrix_set_color_all( 0xFF, 0x00, 0x00 );
    #endif //RGB_MATRIX_ENABLE
    shutdown_keymap();
}

__attribute__ ((weak))
void suspend_power_down_keymap(void) {}

void suspend_power_down_user(void) {
    #ifdef RGB_MATRIX_ENABLE
        rgb_matrix_set_suspend_state(true);
    #endif //RGB_MATRIX_ENABLE
    suspend_power_down_keymap();
}

__attribute__ ((weak))
void suspend_wakeup_init_keymap(void) {}

void suspend_wakeup_init_user(void) {
    #ifdef RGB_MATRIX_ENABLE
        rgb_matrix_set_suspend_state(false);
    #endif //RGB_MATRIX_ENABLE
    suspend_wakeup_init_keymap();
}

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
