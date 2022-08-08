// Copyright 2022 Markus Knutsson (@TweetyDaBird)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _RGB
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        TO(_RGB),	KC_MSEL,	KC_MPRV,	KC_MNXT,	KC_MPLY
    ),
    [_RGB] = LAYOUT(
        TO(_BASE),	RGB_VAI,	RGB_TOG,	RGB_VAD, 	RGB_TOG
    )
};

#ifdef ENCODER_ENABLE

// switch(biton32(layer_state)) will get you the number of the current layer

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        switch(biton32(layer_state)){
            case _RGB:
                // rgb brightness up/down
                if(clockwise){
                    // tap_code(RGB_VAI);
                    //rgblight_increase_val();
					tap_code(KC_UP);
                } else {
                    // tap_code(RGB_VAD);
                    //rgblight_decrease_val();
					tap_code(KC_DOWN);
                }
                break;
            default:
                //volume up/down
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
        }
    } 
	return true;
};

#endif