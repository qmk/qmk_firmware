/* Copyright 2021 Takeshi Nishio
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

// Defines names for use in layer keycodes and the keymap
enum layer_number {
    _BASE = 0,
    _LOW,
    _RAI,
    _ADJ,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_all(
        KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_NLCK,KC_PSLS,KC_PAST,KC_PMNS,KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL,
        KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_P7,  KC_P8,  KC_P9,  KC_PPLS,KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,       KC_BSPC,
        KC_LCTL,    KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_P4,  KC_P5,  KC_P6,  KC_PPLS,KC_H,   KC_J,   KC_K,   KC_L,   KC_MINS,    KC_ENT,
        KC_LSFT,KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_P1,  KC_P2,  KC_P3,  KC_PENT,KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_UP,
        KC_GRV, KC_BSLS,KC_LGUI,KC_LALT,KC_SPC, KC_SPC,MO(_LOW),KC_P0,  KC_P0,  KC_PDOT,MO(_RAI),KC_SPC,KC_APP, KC_ROPT,KC_LEFT,KC_DOWN,KC_RGHT
    ),
    [_LOW] = LAYOUT_all(
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
        KC_TILD,    KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,_______,_______,_______,_______,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,    KC_DEL,
        _______,    KC_PSCR,KC_SLCK,KC_PAUS,_______,_______,_______,_______,_______,_______,KC_GRV, KC_MINS,KC_EQL, KC_LBRC,KC_RBRC,    KC_BSLS,
        _______,_______,KC_MUTE,KC_VOLD,KC_VOLU,_______,_______,_______,_______,_______,_______,KC_TILD,KC_UNDS,KC_PLUS,KC_LCBR,KC_RCBR,KC_PIPE,
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_HOME,KC_PGDN,KC_PGUP,KC_END
    ),
    [_RAI] = LAYOUT_all(
        _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,_______,_______,_______,_______,KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10,   KC_F11, KC_F12,
        KC_GRV,     KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   _______,_______,_______,_______,KC_6,   KC_7,   KC_8,   KC_9,   KC_0,       KC_DEL,
        _______,    KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  _______,_______,_______,_______,KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_SCLN,    KC_QUOT,
        _______,_______,KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, _______,_______,_______,_______,KC_HOME,KC_PGDN,KC_PGUP,KC_END, KC_COLN,KC_DQUO,
        _______,_______,KC_F11, _______,KC_F12,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
    ),
    [_ADJ] = LAYOUT_all(
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,    _______,_______,_______,QK_BOOT,  _______,_______,_______,_______,_______,RGB_HUI,RGB_SAI,RGB_VAI,_______,RGB_RMOD,   _______,
        _______,    AU_TOG, CK_TOGG,MU_TOG, MU_MOD, _______,_______,_______,_______,_______,RGB_HUD,RGB_SAD,RGB_VAD,RGB_TOG,RGB_MOD,    _______,
        KC_CAPS,_______,CK_RST, CK_DOWN,CK_UP,  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
    )
};


/* ------------------------------------------------------------------------------
   RGB Lighting
------------------------------------------------------------------------------ */
#ifdef RGBLIGHT_LAYERS

// Indicator LED settings
#define INDICATOR_INDEX 0         // Where to start indicator, default:1
#define INDICATOR_COUNT 1         // How many LEDs for indicator, default:2
#define INDICATOR_CHANGE_COUNT 1  // How meny LEDs to change for temporally layer default:1
#define DIMMER_LEVEL 150          // LED brightness dimmer level, 0(brightest) - 255(perfect dark), default:150

// for Default layer (= Base layer)
const rgblight_segment_t PROGMEM my_base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX , INDICATOR_COUNT, HSV_BLACK}
);

// for Temporal layer
const rgblight_segment_t PROGMEM my_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX , INDICATOR_CHANGE_COUNT, HSV_GREEN - DIMMER_LEVEL}
);

const rgblight_segment_t PROGMEM my_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX , INDICATOR_CHANGE_COUNT, HSV_CYAN - DIMMER_LEVEL}
);

const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX , INDICATOR_CHANGE_COUNT, HSV_RED - DIMMER_LEVEL}
);

// for Lock indicator
const rgblight_segment_t PROGMEM my_caps_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX , INDICATOR_CHANGE_COUNT, HSV_MAGENTA - DIMMER_LEVEL}
);

// Define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_base_layer,
    my_caps_layer,
    my_lower_layer,
    my_raise_layer,
    my_adjust_layer
);

// Enabling and disabling lighting layers for default layer
layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _BASE));

    return state;
}

// Enabling and disabling lighting layers for lock key
bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(1, led_state.caps_lock);
    return true;
}

// Enabling and disabling lighting layers for momentary layer
layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOW, _RAI, _ADJ);

    rgblight_set_layer_state(2, layer_state_cmp(state, _LOW));
    rgblight_set_layer_state(3, layer_state_cmp(state, _RAI));
    rgblight_set_layer_state(4, layer_state_cmp(state, _ADJ));

    return state;
}
#endif


/* ------------------------------------------------------------------------------
   Post Initialize
------------------------------------------------------------------------------ */
void keyboard_post_init_user(void) {
    #ifdef RGB_DI_PIN
    // RGB Lighting: Set effect range from just after indicator.
    rgblight_set_effect_range(1, 16);
    #endif
    #ifdef RGBLIGHT_LAYERS
    // RGB Lighting Layers: Setup LED layers
    rgblight_layers = my_rgb_layers;
    #endif
}
