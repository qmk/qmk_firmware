#include "curry.h"

userspace_config_t userspace_config;

#define CURRY_UNICODE_MODE 1

void bootmagic_lite(void) {
    matrix_scan();
#if defined(DEBOUNCING_DELAY) && DEBOUNCING_DELAY > 0
    wait_ms(DEBOUNCING_DELAY * 2);
#elif defined(DEBOUNCE) && DEBOUNCE > 0
    wait_ms(DEBOUNCE * 2);
#else
    wait_ms(30);
#endif
    matrix_scan();
#if defined(BOOTMAGIC_ENABLE)
    if (matrix_get_row(BOOTMAGIC_LITE_ROW) & (1 << BOOTMAGIC_LITE_COLUMN)) {
        bootloader_jump();
    }
#endif
}

__attribute__((weak)) void keyboard_pre_init_keymap(void) {}

void keyboard_pre_init_user(void) {
    userspace_config.raw = eeconfig_read_user();
    keyboard_pre_init_keymap();
}

__attribute__((weak)) void matrix_init_keymap(void) {}

// Call user matrix init, set default RGB colors and then
// call the keymap's init function
void matrix_init_user(void) {
#if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
    set_unicode_input_mode(CURRY_UNICODE_MODE);
    get_unicode_input_mode();
#endif  // UNICODE_ENABLE
    matrix_init_keymap();
}

__attribute__((weak)) void keyboard_post_init_keymap(void) {}

void keyboard_post_init_user(void) {
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    keyboard_post_init_rgb();
#endif
    keyboard_post_init_keymap();
}

__attribute__((weak)) void shutdown_keymap(void) {}

void rgb_matrix_update_pwm_buffers(void);

// On RESET, set all RGB to red, shutdown the keymap.
void shutdown_user(void) {
#if defined(RGBLIGHT_ENABLE)
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(1);
    rgblight_setrgb(RGB_RED);
#endif

#if defined(RGB_MATRIX_ENABLE)
    rgb_matrix_set_color_all(0xFF, 0x00, 0x00);
    rgb_matrix_update_pwm_buffers();
#endif
    shutdown_keymap();
}

__attribute__((weak)) void suspend_power_down_keymap(void) {}

void suspend_power_down_user(void) { suspend_power_down_keymap(); }

__attribute__((weak)) void suspend_wakeup_init_keymap(void) {}

void suspend_wakeup_init_user(void) { suspend_wakeup_init_keymap(); }

__attribute__((weak)) void matrix_scan_keymap(void) {}

// No global matrix scan code, so just run keymap's matrix
// scan function
__attribute__((weak)) void matrix_scan_user(void) {
    static bool has_ran_yet;
    if (!has_ran_yet) {
        has_ran_yet = true;
        startup_user();
    }

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    matrix_scan_rgb();
#endif  // RGBLIGHT_ENABLE

    matrix_scan_keymap();
}

__attribute__((weak)) layer_state_t layer_state_set_keymap(layer_state_t state) { return state; }

// On Layer change, run keymap's layer change check
layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
#if defined(RGBLIGHT_ENABLE)
    state = layer_state_set_rgb(state);
#endif
    return layer_state_set_keymap(state);
}

__attribute__((weak)) layer_state_t default_layer_state_set_keymap(layer_state_t state) { return state; }

// Runs state check and changes underglow color and animation
layer_state_t default_layer_state_set_user(layer_state_t state) { return default_layer_state_set_keymap(state); }

__attribute__((weak)) void led_set_keymap(uint8_t usb_led) {}

// Any custom LED code goes here.
void led_set_user(uint8_t usb_led) { led_set_keymap(usb_led); }

__attribute__((weak)) void eeconfig_init_keymap(void) {}

void eeconfig_init_user(void) {
    userspace_config.raw              = 0;
    userspace_config.rgb_layer_change = true;
    eeconfig_update_user(userspace_config.raw);
#if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
    set_unicode_input_mode(CURRY_UNICODE_MODE);
    get_unicode_input_mode();
#else
    eeprom_update_byte(EECONFIG_UNICODEMODE, CURRY_UNICODE_MODE);
#endif
    eeconfig_init_keymap();
    keyboard_init();
}
