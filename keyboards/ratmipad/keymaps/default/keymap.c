/* Copyright 2022 Sandipratama <https://github.com/nendezkombet>
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


#define SELECT      LCTL(KC_A)
#define SAVE        LCTL(KC_S)
#define COPY        LCTL(KC_C)
#define PASTE       LCTL(KC_V)


enum my_encoder {
  _LEFT,
  _RIGHT,
};

enum my_layer {
    _FIRST = 0,
    _SECOND,
    _THIRD,
    _FOURTH
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    
    [_FIRST] = LAYOUT(
        	KC_TRNS, TO(_SECOND), KC_TRNS,
        	KC_MPLY, SAVE, KC_MYCM,
        	SELECT, COPY, PASTE
    ),
    
    [_SECOND] = LAYOUT(
        	KC_TRNS, TO(_THIRD), KC_TRNS, 
		RGB_TOG, RGB_MOD, RGB_RMOD, 
		RGB_M_B, RGB_M_R, RGB_M_SW
    ),
    
    [_THIRD] = LAYOUT(
		KC_TRNS, TO(_FOURTH), KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS

    ),
    
    [_FOURTH] = LAYOUT(
		KC_TRNS, TO(_FIRST), KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS

    ),
};


const rgblight_segment_t PROGMEM _first_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {0, RGBLED_NUM, HSV_GOLDENROD}
        );
const rgblight_segment_t PROGMEM _second_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {0, RGBLED_NUM, HSV_CYAN}
        );
const rgblight_segment_t PROGMEM _third_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {0, RGBLED_NUM, HSV_RED}
        );
const rgblight_segment_t PROGMEM _fourth_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {0, RGBLED_NUM, HSV_GREEN}
        );


const rgblight_segment_t* const PROGMEM _rgb_layers[] =
RGBLIGHT_LAYERS_LIST(
        _first_layer,
        _second_layer,
        _third_layer,
	_fourth_layer
        );

void keyboard_post_init_user(void) {
    rgblight_layers = _rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {

    switch (get_highest_layer(state)) {
        case 0:
            rgblight_blink_layer(0, 500);
            break;
        case 1:
            rgblight_blink_layer(1, 500);
            break;
        case 2:
            rgblight_blink_layer(2, 500);
            break;
	case 3:
            rgblight_blink_layer(3, 500);
            break;
    }
    return state;
}

//uint8_t selected_layer = 0;
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _LEFT) {
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        }
     else if (index == _RIGHT) {
            if (clockwise) {
                tap_code(KC_PGDN);
            } else {
            tap_code(KC_PGUP);
            }
       }
  return true;
}

// qmk compile -kb ratmipad -km default