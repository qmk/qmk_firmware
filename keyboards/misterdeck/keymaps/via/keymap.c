#include QMK_KEYBOARD_H
#include "quantum.h"

#define _______ KC_TRNS
#define NUMPAD  TO(_NUMPAD)
enum layers {
    _NUMPAD = 0,
    _FUNC2,
    _MOUSE,
    _CTRL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_NUMPAD] = LAYOUT(
        KC_P7, KC_P8, KC_P9, LT(_CTRL,KC_P0),
        KC_P4, KC_P5, KC_P6, TT(_MOUSE),
        KC_P1, KC_P2, KC_P3, TT(_FUNC2)
    ),

    [_FUNC2] = LAYOUT(
        KC_F17, KC_F18, KC_F19,  NUMPAD,
        KC_F14, KC_F15, KC_F16, _______,
        KC_F11, KC_F12, KC_F13, _______
    ),

    [_MOUSE] = LAYOUT(
        _______, _______, KC_WH_D,  NUMPAD,
        _______, _______, KC_BTN1, _______,
        _______, _______, KC_WH_U, _______
    ),

    [_CTRL] = LAYOUT(
        KC_MUTE,  RGB_TOG, _______, _______,
        KC_VOLU, RGB_RMOD, _______, _______,
        KC_VOLD,  RGB_MOD, _______, _______
    ),

};

static const rgblight_segment_t PROGMEM mrd_numpad_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 4, HSV_GREEN}
);
static const rgblight_segment_t PROGMEM mrd_mouse_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {4, 4, HSV_YELLOW}
);
static const rgblight_segment_t PROGMEM mrd_ctrl_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 4, HSV_PURPLE}
);
static const rgblight_segment_t PROGMEM mrd_func2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {12, 4, HSV_BLUE}
);

// Now define the array of layers. Later layers take precedence
static const rgblight_segment_t* const PROGMEM mrd_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    mrd_numpad_layer,
    mrd_func2_layer,
    mrd_mouse_layer,
    mrd_ctrl_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = mrd_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _FUNC2));
    rgblight_set_layer_state(2, layer_state_cmp(state, _MOUSE));
    rgblight_set_layer_state(3, layer_state_cmp(state, _CTRL));
    return state;
}
