// Copyright 2023 *+. Audrey .+*
// SPDX-License-Identifier: GPL-3.0-or-later
#include "audreyality.h"

bool to_default_layer(void) {
    if(layer_state_is(_DFL_MACOS)) {
        layer_move(_DFL_MACOS);
    } else if(layer_state_is(_DFL_WINDOWS)) {
        layer_move(_DFL_WINDOWS);
    } else {
        layer_move(AUD_DEFAULT_LAYER);
    }

    return false;
}

inline bool flap(keyrecord_t *record, uint16_t code) {
    if (record->event.pressed) {
        register_code16(code);
    } else {
        unregister_code16(code);
    }

    return false; // Skip all further processing of this key
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_SPOT:
            return flap(record, 0x221);
        case KC_DICT:
            return flap(record, 0xCF);
        case KC_DND:
            return flap(record, 0x9B);
        case E_X_I_T:
            return to_default_layer();

    }
    return true;
}

void keyboard_post_init_user(void) {
    // setting the default layer on startup keeps the LEDs
    // in sync with the layer state
    to_default_layer();
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t highest = get_highest_layer(state);

    switch (highest) {
        case _DFL_MACOS:
        case _DFL_WINDOWS:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv_noeeprom(215, 240, 80); // fuscia
            break;
        case _XTL_FUNCTION:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_ALPHAS_MODS);
            rgb_matrix_sethsv_noeeprom(184, 237, 140);
            // speed controls offset; max 255
            rgb_matrix_set_speed_noeeprom(30);
            break;
        case _XTL_LED_MATRIX:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_CYCLE_PINWHEEL);
            rgb_matrix_sethsv_noeeprom(0, 172, 50);
            break;
        case _TTL_CONTROL:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
            rgb_matrix_set_speed_noeeprom(60);
            break;
        case _MDL_HELLDIVERS:
            // solid yellow with fast-fade from orangey-yellow
            // when the keys are pressed
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE);
            rgb_matrix_sethsv_noeeprom(43, 255, 191); // helldivers yellow
            // speed controls offset; max 255
            rgb_matrix_set_speed_noeeprom(10);
            break;
        default:
            break;
    }

    return state;
}

