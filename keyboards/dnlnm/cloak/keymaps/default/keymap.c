// Copyright (C) 2025 dnlnm
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3, KC_4,   KC_5, KC_6,   KC_7, KC_8,   KC_9,    KC_0,    KC_MINS, KC_EQL,     KC_MPLY,
        KC_TAB,  KC_Q,    KC_W,    KC_E, KC_R,   KC_T, KC_Y,   KC_U, KC_I,   KC_O,    KC_P,    KC_DEL,  KC_BSPC,    KC_VOLU,
        KC_CAPS, KC_A,    KC_S,    KC_D, KC_F,   KC_G, KC_H,   KC_J, KC_K,   KC_L,    KC_QUOT,          KC_ENT,     KC_VOLD,
        KC_LSFT,          KC_Z,    KC_X, KC_C,   KC_V, KC_B,   KC_N, KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,    KC_MUTE,
        KC_LCTL, KC_LGUI, MO(1),               KC_SPC,                              KC_RALT, KC_RGUI, KC_RCTL,    KC_PSCR),

    [1] = LAYOUT(
        QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(MS_WHLU, MS_WHLD), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] = {ENCODER_CCW_CW(UG_HUED, UG_HUEU), ENCODER_CCW_CW(UG_SATD, UG_SATU)},
};
#endif

#ifdef RGBLIGHT_ENABLE

// Light LEDs 10 & 11 in blue when caps lock is active.
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {10, 2, HSV_BLUE}       // Light 4 LEDs, starting with LED 6
);
// Light LEDs 0 & 1 in blue when keyboard layer 1 is active
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_BLUE}
);
// Light LEDs 4 & 5 in blue when keyboard layer 2 is active
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {4, 2, HSV_BLUE}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    my_layer1_layer,    // Overrides caps lock layer
    my_layer2_layer    // Overrides other layers
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    return state;
}

#endif
