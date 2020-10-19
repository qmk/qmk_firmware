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

#include "keymap_finnish.h"

enum layers {
    _BASE = 0,
    _PRPRO,
    _PRPRO2,
};

/* Tap Dance declarations */
enum {
    TD_1,
    TD_2,
    TD_3,
    TD_4,
    TD_5,
    TD_6,
    TD_COMMA,
    TD_HOME,
    TD_K,
    TD_DEL,
    TD_X,
    TD_C,
    TD_V,
    TD_Z
};

/* Tap Dance definitions */
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_1] = ACTION_TAP_DANCE_DOUBLE(LCTL(KC_1), LCTL(LSFT(KC_1))),
    [TD_2] = ACTION_TAP_DANCE_DOUBLE(LCTL(KC_2), LCTL(LSFT(KC_2))),
    [TD_3] = ACTION_TAP_DANCE_DOUBLE(LCTL(KC_3), LCTL(LSFT(KC_3))),
    [TD_4] = ACTION_TAP_DANCE_DOUBLE(LCTL(KC_4), LCTL(LSFT(KC_4))),
    [TD_5] = ACTION_TAP_DANCE_DOUBLE(LCTL(KC_5), LCTL(LSFT(KC_5))),
    [TD_6] = ACTION_TAP_DANCE_DOUBLE(LCTL(KC_6), LCTL(LSFT(KC_6))),
    [TD_COMMA] = ACTION_TAP_DANCE_DOUBLE(KC_COMMA, KC_DOT),
    [TD_HOME] = ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_END),
    [TD_K] = ACTION_TAP_DANCE_DOUBLE(LCTL(KC_K), LCTL(LSFT(KC_K))),
    [TD_DEL] = ACTION_TAP_DANCE_DOUBLE(KC_DEL, LSFT(KC_DEL)),
    [TD_X] = ACTION_TAP_DANCE_DOUBLE(LCTL(KC_X), KC_S),
    [TD_C] = ACTION_TAP_DANCE_DOUBLE(LCTL(KC_C), KC_M),
    [TD_V] = ACTION_TAP_DANCE_DOUBLE(LCTL(KC_V), LCTL(KC_L)),
    [TD_Z] = ACTION_TAP_DANCE_DOUBLE(LCTL(KC_Z), LCTL(LSFT(KC_Z)))
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        KC_ESC,  KC_0,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
        KC_Y,    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
        KC_H,    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        KC_N,    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    TG(_PRPRO),
        KC_LGUI, KC_LCTL,                                                KC_ENT,
                                               KC_LALT,  KC_SPC,  KC_ENT
    ),

    [_PRPRO] = LAYOUT(
        KC_ESC,     KC_M,        KC_V,         KC_UP,      KC_A,       KC_Y,       KC_C,
        KC_1,       KC_2,        KC_LEFT,      KC_DOWN,    KC_RIGHT,   TD(TD_Z),   TD(TD_DEL),
        FI_SECT,    TD(TD_HOME), KC_J,         KC_K,       KC_L,       TD(TD_K),   TG(_PRPRO2),
        KC_S,       KC_LSFT,     LCTL(KC_X),   LCTL(KC_C), LCTL(KC_V), LCTL(KC_S), TG(_PRPRO),
        LCTL(KC_L), KC_LCTL,                                                                   KC_ENT,
                                                                  KC_LALT,     KC_SPC,  KC_ENT
    ),

    [_PRPRO2] = LAYOUT(
        KC_TRNS, KC_TRNS, TD(TD_1), TD(TD_2), TD(TD_3),     TD(TD_4), TD(TD_5),
        KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,  KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,  KC_TRNS,
        KC_TRNS, KC_TRNS, KC_I,     KC_O,     TD(TD_COMMA), KC_TRNS,  TG(_PRPRO2),
        KC_TRNS, KC_TRNS,                                                         KC_TRNS,
                                                      KC_TRNS,   KC_TRNS, KC_TRNS
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
#define HSV_PRIMARY HUE_PRIMARY, 255, 255
#define HSV_OFF 0, 0, 0
#define HSV_CAPS HUE_PRIMARY, 255, 64
#define HSV_LAYER_BASE HUE_PRIMARY, 255, 64
#define HSV_LAYER_PRPRO 213, 255, 64
#define HSV_LAYER_PRPRO2 184, 255, 64

const rgblight_segment_t PROGMEM ug_default_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 14, HSV_PRIMARY},
    {10, 4, HSV_OFF}
);

const rgblight_segment_t PROGMEM ug_caps_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 1, HSV_CAPS}
);

const rgblight_segment_t PROGMEM ug_base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {13, 1, HSV_LAYER_BASE}
);

const rgblight_segment_t PROGMEM ug_prpro_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {13, 1, HSV_LAYER_PRPRO}
);

const rgblight_segment_t PROGMEM ug_prpro2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {13, 1, HSV_LAYER_PRPRO2}
);

/* Define layer order, later layers take precedence */
const rgblight_segment_t* const PROGMEM ug_layers[] = RGBLIGHT_LAYERS_LIST(
    ug_default_layer,
    ug_caps_layer,
    ug_base_layer,
    ug_prpro_layer,
    ug_prpro2_layer
);

void keyboard_post_init_user(void) {
    /* Enable the LED layers */
    rgblight_layers = ug_layers;
    rgblight_set_layer_state(0, true);
    rgblight_set_layer_state(2, true);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, true);
    /* Both layers will light up if both kb layers are active */
    rgblight_set_layer_state(2, layer_state_cmp(state, 0));
    rgblight_set_layer_state(3, layer_state_cmp(state, 1));
    rgblight_set_layer_state(4, layer_state_cmp(state, 2));
    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(1, led_state.caps_lock);
    return true;
}
#endif
