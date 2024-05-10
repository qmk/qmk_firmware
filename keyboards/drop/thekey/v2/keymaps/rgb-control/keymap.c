/* Copyright 2022 Jason Wihardja
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

enum custom_keycodes {
    LAYER_SWITCH = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Default */
    [0] = LAYOUT(LAYER_SWITCH, C(KC_C), C(KC_V)),

    /* RGB Toggle + Mode Change */
    [1] = LAYOUT(LAYER_SWITCH, UG_TOGG, UG_NEXT),

    /* RGB Brightness */
    [2] = LAYOUT(LAYER_SWITCH, UG_VALD, UG_VALU),

    /* RGB Hue */
    [3] = LAYOUT(LAYER_SWITCH, UG_HUED, UG_HUEU),

    /* RGB Saturation */
    [4] = LAYOUT(LAYER_SWITCH, UG_SATD, UG_SATU),

};

/* Lighting layers */

const rgblight_segment_t PROGMEM layer_indicator_0[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_WHITE},
    {1, 4, HSV_OFF}
);

const rgblight_segment_t PROGMEM layer_indicator_1[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_OFF},
    {1, 1, HSV_WHITE},
    {2, 3, HSV_OFF}
);

const rgblight_segment_t PROGMEM layer_indicator_2[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_OFF},
    {2, 1, HSV_WHITE},
    {3, 2, HSV_OFF}
);

const rgblight_segment_t PROGMEM layer_indicator_3[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_OFF},
    {3, 1, HSV_WHITE},
    {4, 1, HSV_OFF}
);

const rgblight_segment_t PROGMEM layer_indicator_4[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 4, HSV_OFF},
    {4, 1, HSV_WHITE}
);

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_indicator_0,
    layer_indicator_1,
    layer_indicator_2,
    layer_indicator_3,
    layer_indicator_4
);

void keyboard_post_init_user(void) {
    /* Enable the LED layers */
    rgblight_layers = rgb_layers;
}

/* Layer handler */

uint16_t layer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LAYER_SWITCH:
            if (record->event.pressed) {
                if (layer > 0) {
                    layer_off(layer);
                }

                rgblight_unblink_layer(layer);
                layer = (layer + 1) % 5;
                rgblight_blink_layer_repeat(layer, 1000, 1);

                if (layer > 0) {
                    layer_on(layer);
                }
            }
            return false;
        default:
            return true;
    }
}
