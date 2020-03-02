#include "brandonschlack.h"

user_config_t user_config;

/**
 * Resets user config in EEPROM
 *
 * Default is use rgb for layer indication
 */
void eeconfig_init_user(void) {
    user_config.raw = 0;
    user_config.rgb_layer_change = true;
    user_config.rgb_theme = 0;
    eeconfig_update_user(user_config.raw);
}

__attribute__((weak))
void matrix_init_keymap(void){ }

void matrix_init_user(void) {
    matrix_init_keymap();
}

__attribute__((weak))
void keyboard_post_init_keymap(void){ }

/**
 * Reads user config from EEPROM,
 * calls RGB init if RGBs enabled
 */
void keyboard_post_init_user(void){
    // Read the user config from EEPROM
    user_config.raw = eeconfig_read_user();
    // Do RGB things if RGBs enabled
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    keyboard_post_init_rgb();
#endif
    keyboard_post_init_keymap();
}

__attribute__ ((weak))
void shutdown_keymap(void) {}

/**
 * On shutdown,
 * If RGBs enabled,
 * then set RGB color to Red
 */
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

/**
 * Set rgb_matrix suspend state to true if not already
 */
void suspend_power_down_user(void) {
    #ifdef RGB_MATRIX_ENABLE
    if (!g_suspend_state) {
        rgb_matrix_set_suspend_state(true);
    }
    #endif //RGB_MATRIX_ENABLE
    suspend_power_down_keymap();
}

__attribute__ ((weak))
void suspend_wakeup_init_keymap(void) {}

/**
 * Set rgb_matrix suspend state to false if not already
 */
void suspend_wakeup_init_user(void) {
    #ifdef RGB_MATRIX_ENABLE
    if (g_suspend_state) {
        rgb_matrix_set_suspend_state(false);
    }
    #endif //RGB_MATRIX_ENABLE
    suspend_wakeup_init_keymap();
}

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

/**
 * Checks for Super CMD↯TAB
 */
void matrix_scan_user(void) {
    matrix_scan_cmd_tab();
    matrix_scan_keymap();
}

__attribute__ ((weak))
layer_state_t default_layer_state_set_keymap(layer_state_t state) {
    return state;
}

/**
 * For macropads, if a new default layer is set from DF()
 * then automatically set that layer with layer_move()
 */
layer_state_t default_layer_state_set_user(layer_state_t state) {
#if defined(IS_MACROPAD)
    layer_move(get_highest_layer(state));
#endif
    return default_layer_state_set_keymap(state);
}

__attribute__ ((weak))
layer_state_t layer_state_set_keymap(layer_state_t state) {
    return state;
}

/**
 * Do RGB things (like layer indication) on layer change
 */
layer_state_t layer_state_set_user(layer_state_t state) {
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    state = layer_state_set_rgb(state);
#endif // RGBLIGHT_ENABLE
    return layer_state_set_keymap(state);
}
