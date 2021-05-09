/* Copyright 2020 Duckle
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "analog.h"
#include "qmk_midi.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN,
    _MEDIA
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    UR_GAY = SAFE_RANGE,
    QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        TO(_FN),
        C(KC_T),    KC_LBRC,    KC_RBRC,
        C(S(KC_N)), C(S(KC_E)), C(KC_J), C(KC_S)
    ),
    [_FN] = LAYOUT(
        TO(_MEDIA),
        RGB_TOG, RGB_MOD,  RGB_VAI,
        QMKURL,  RGB_RMOD, RGB_VAD, UR_GAY
    ),
    [_MEDIA] = LAYOUT(
        TO(_BASE),
        KC_VOLD, KC_VOLU, KC_F24,
        KC_MRWD, KC_MFFD, KC_F23, RESET
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case UR_GAY:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("You're super gay and I love you a lot!!!");
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case QMKURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://qmk.fm/\n");
            } else {
                // when keycode QMKURL is released
            }
            break;
    }
    return true;
}

uint8_t divisor = 0;

void slider(void) {
    if (divisor++) { // only run the slider function 1/256 times it's called
        return;
    }

    midi_send_cc(&midi_device, 2, 0x3E, 0x7F - (analogReadPin(SLIDER_PIN) >> 3));
}

void matrix_scan_user(void) {
    slider();
}

// Light LEDs in cyan when base layer is active
const rgblight_segment_t PROGMEM _base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 4, HSV_PURPLE}
);

// Light LEDs 6 to 9 and 12 to 15 red when in media layer. Hard to ignore!
const rgblight_segment_t PROGMEM _media_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 4, HSV_RED}
);

// Light LEDs 11 & 12 in purple when keyboard layer 2 is active
const rgblight_segment_t PROGMEM _fn_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_PURPLE}
);

const rgblight_segment_t* const PROGMEM _rgb_layers[] =
    RGBLIGHT_LAYERS_LIST(_base_layer, _media_layer, _fn_layer);

void keyboard_post_init_user(void) {
    rgblight_layers = _rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _FN));
    rgblight_set_layer_state(1, layer_state_cmp(state, _MEDIA));
    return state;
}

/*
// Note we user post_process_record_user because we want the state
// after the flag has been flipped...
void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case 0:
            rgblight_blink_layer(0, 500);
            break;

        case 1:
            rgblight_blink_layer(1, 500);
            break;

        case 2:
            rgblight_blink_layer(2, 500);
            break;
    }
}
*/

