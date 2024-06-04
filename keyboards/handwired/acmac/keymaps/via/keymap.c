// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define _BASE 0
#define _MACRO1 1
#define _MACRO2 2
#define _MACRO3 3

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
// entirely and just use numbers.


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT( /*Base*/
         KC_ESC, KC_A, KC_B, KC_C, KC_V, KC_W, KC_X, KC_Y,
         KC_DEL, KC_D, KC_E, KC_F, KC_Z, KC_P0, KC_PAST, KC_PSLS,
         KC_G, KC_H, KC_I, KC_J, KC_P7, KC_P8, KC_P9, KC_PMNS,
         KC_K, KC_L, KC_M, KC_N, KC_P4, KC_P5, KC_P6, KC_PPLS,
         KC_O, KC_P, KC_Q, KC_R, KC_P1, KC_P2, KC_P3,
         TO(1), KC_S, KC_T, KC_U, KC_P0, KC_PDOT, KC_COMM, KC_PENT
    ),

    [_MACRO1] = LAYOUT(
        KC_ESC, KC_P0, KC_P0, KC_P0,    KC_P0, KC_P0, KC_P0, KC_P0,
         KC_P0, KC_P0, KC_P0, KC_P0,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_P0, KC_P0, KC_P0, KC_P0,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_P0, KC_P0, KC_P0, KC_P0,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_P0, KC_P0, KC_P0, KC_P0,    KC_TRNS, KC_TRNS, KC_TRNS,
         TO(2), KC_P0, KC_P0, KC_P0,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_MACRO2] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        TO(3), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_MACRO3] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        TO(0), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};
//const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS(
   // {1, 25, HSV_PURPLE}
//);

// const rgblight_segment_t PROGMEM red_base []   = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_RED});

const rgblight_segment_t PROGMEM red_base []   = RGBLIGHT_LAYER_SEGMENTS({0, 15, HSV_RED});
const rgblight_segment_t PROGMEM blu_macro1 []   = RGBLIGHT_LAYER_SEGMENTS({0, 15, HSV_BLUE});
const rgblight_segment_t PROGMEM grn_macro2[]   = RGBLIGHT_LAYER_SEGMENTS({0, 15, HSV_GREEN});
const rgblight_segment_t PROGMEM yel_macro3[]   = RGBLIGHT_LAYER_SEGMENTS({0, 15, HSV_YELLOW});
// const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_GREEN});

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    red_base,
    blu_macro1,    // Overrides base layer
    grn_macro2,    // Overrides other layers
    yel_macro3    // Overrides other layers
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

// Acitvate the default rgb layer when the _BASE layer is enabled
layer_state_t default_layer_state_set_user(layer_state_t state) {
rgblight_set_layer_state(0, layer_state_cmp(state, _BASE));
return state;
}
/* Activate rgb layer for caps when capslock is enabled
bool led_update_user(led_t led_state) {
rgblight_set_layer_state(4, led_state.caps_lock);
return true;
}
*/

// Activate the rgb layer according to the active keyboard layer
layer_state_t layer_state_set_user(layer_state_t state) {
rgblight_set_layer_state(1, layer_state_cmp(state, _MACRO1));
rgblight_set_layer_state(2, layer_state_cmp(state, _MACRO2));
rgblight_set_layer_state(3, layer_state_cmp(state, _MACRO3));
return state;
}
