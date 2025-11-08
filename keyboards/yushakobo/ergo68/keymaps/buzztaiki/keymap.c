#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_PSCR,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_LBRC, KC_RBRC,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G, KC_MINS,  KC_EQL,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  KC_DEL, KC_BSPC,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
        KC_LCTL,KC_LGUI,KC_LALT,  MO(1),  KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC, KC_RALT,  KC_APP, KC_LCTL
    ),
        [1] = LAYOUT(
        QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

void keyboard_post_init_user(void) {
    // turn off default backlight
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // RGB_MATRIX_INDICATOR_SET_COLOR(index, r, g, b)
    // g_led_config.matrix_co[row][col]

    // indicator for split keyboard connection status
    RGB_MATRIX_INDICATOR_SET_COLOR(g_led_config.matrix_co[1][6], 64, 32, 0);
    RGB_MATRIX_INDICATOR_SET_COLOR(g_led_config.matrix_co[6][6], 64, 32, 0);

    // lock state
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(0, 0, 0, 128);
    }
    if (host_keyboard_led_state().num_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(1, 0, 0, 128);
    }
    if (host_keyboard_led_state().scroll_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(2, 0, 0, 128);
    }

    // layer state
    switch (get_highest_layer(layer_state)) {
        case 1:
            RGB_MATRIX_INDICATOR_SET_COLOR(37, 0, 0, 128);

            RGB_MATRIX_INDICATOR_SET_COLOR(g_led_config.matrix_co[0][0], 0, 0, 128);
            RGB_MATRIX_INDICATOR_SET_COLOR(g_led_config.matrix_co[1][0], 0, 0, 128);
            RGB_MATRIX_INDICATOR_SET_COLOR(g_led_config.matrix_co[2][0], 0, 0, 128);

            break;
        case 2:
            RGB_MATRIX_INDICATOR_SET_COLOR(38, 0, 0, 128);

            RGB_MATRIX_INDICATOR_SET_COLOR(g_led_config.matrix_co[0][1], 0, 128, 0);
            RGB_MATRIX_INDICATOR_SET_COLOR(g_led_config.matrix_co[1][1], 0, 128, 0);
            RGB_MATRIX_INDICATOR_SET_COLOR(g_led_config.matrix_co[2][1], 0, 128, 0);

            break;
        case 3:
            RGB_MATRIX_INDICATOR_SET_COLOR(39, 0, 0, 128);

            RGB_MATRIX_INDICATOR_SET_COLOR(g_led_config.matrix_co[0][2], 128, 128, 0);
            RGB_MATRIX_INDICATOR_SET_COLOR(g_led_config.matrix_co[1][2], 128, 128, 0);
            RGB_MATRIX_INDICATOR_SET_COLOR(g_led_config.matrix_co[2][2], 128, 128, 0);

            break;
    }
    return false;
}
