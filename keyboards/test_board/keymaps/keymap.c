#include QMK_KEYBOARD_H

// Layers
enum layers {
    _BASE,
};

// Define encoder behavior
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
    return true;
}

// Keymap definition
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_1, KC_2, KC_3, KC_4, KC_5,
        KC_Q, KC_W, KC_E, KC_R, KC_T,
        KC_A, KC_S, KC_D, KC_F, KC_G,
        KC_Z, KC_X, KC_C, KC_V, KC_B,
        KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_ENT
    ),
};

// OLED display content
#ifdef OLED_ENABLE
void oled_task_user(void) {
    oled_write_ln_P(PSTR("Test Board"), false);
}
#endif

// RGB lighting initialization
void keyboard_post_init_user(void) {
    // Turn on RGB lighting
    rgblight_enable();
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_MOOD);
}
