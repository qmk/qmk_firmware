/* Copyright 2020 Mika Kuitunen
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

/* Each layer gets a name for readability, which is then used in the keymap matrix below.
 * The underscores don't mean anything - you can have a layer called STUFF or any other name.
 */
enum layers {
    _BASE = 0,
    _RGB,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        KC_ESC,  KC_0,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
        KC_Y,    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
        KC_H,    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        KC_N,    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    TG(_RGB),
        KC_LGUI, KC_LCTL,                                                 KC_ENT,
                                               KC_LALT,  KC_SPC,  KC_ENT
    ),

    [_RGB] = LAYOUT(
        RGB_RMOD, RGB_MOD, RGB_TOG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        RGB_HUD,  RGB_HUI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        RGB_SAD,  RGB_SAI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        RGB_VAD,  RGB_VAI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TG(_RGB),
        KC_TRNS,  KC_TRNS,                                                 KC_TRNS,
                                               KC_TRNS,  KC_TRNS,  KC_TRNS
    ),
};

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_MS_WH_DOWN);
        } else {
            tap_code(KC_MS_WH_UP);
        }
    }
}
#endif


#ifdef RGBLIGHT_LAYERS
#define HUE_PRIMARY 10
#define HSV_CAPS HUE_PRIMARY, 255, 64
#define HSV_LAYER_BASE HUE_PRIMARY, 255, 64
#define HSV_LAYER_RGB 213, 255, 64

const rgblight_segment_t PROGMEM ug_default_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {10, 4, HSV_OFF}
);

const rgblight_segment_t PROGMEM ug_caps_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 1, HSV_CAPS}
);

const rgblight_segment_t PROGMEM ug_base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {13, 1, HSV_LAYER_BASE}
);

const rgblight_segment_t PROGMEM ug_rgb_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {13, 1, HSV_LAYER_RGB}
);

/* Define layer order, later layers take precedence */
const rgblight_segment_t* const PROGMEM ug_layers[] = RGBLIGHT_LAYERS_LIST(
    ug_default_layer,
    ug_caps_layer,
    ug_base_layer,
    ug_rgb_layer
);

void keyboard_post_init_user(void) {
    /* Enable the LED layers and set the initial state */
    rgblight_layers = ug_layers;
    rgblight_set_layer_state(0, true);
    rgblight_set_layer_state(2, true);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    /* Both layers will light up if both kb layers are active, latter overrides */
    rgblight_set_layer_state(2, layer_state_cmp(state, 0));
    rgblight_set_layer_state(3, layer_state_cmp(state, 1));
    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(1, led_state.caps_lock);
    return true;
}
#endif
