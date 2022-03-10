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
#include "keymap_jp.h"

// Defines names for use in layer keycodes and the keymap
enum layer_number {
    _BASE1 = 0,
    _BASE2,
    _BASE3,
    _LOWER,
    _RAISE,
    _ADJUST,
};

// Key Macro
#define SP_LOW  LT(_LOWER, KC_SPC)
#define SP_RAI  LT(_RAISE, KC_SPC)
#define SP_ADJ  LT(_ADJUST, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE1] = LAYOUT(
        KC_ESC,   JP_1,     JP_2,     JP_3,     JP_4,     JP_5,     JP_CIRC,  JP_YEN,   JP_6,     JP_7,     JP_8,     JP_9,     JP_0,     JP_MINS,  KC_BSPC,
           KC_TAB,     JP_Q,     JP_W,     JP_E,     JP_R,     JP_T,     JP_AT,    JP_LBRC,  JP_Y,     JP_U,     JP_I,     JP_O,     JP_P,       KC_BSPC,
           KC_LCTL,    JP_A,     JP_S,     JP_D,     JP_F,     JP_G,     JP_COLN,  JP_RBRC,  JP_H,     JP_J,     JP_K,     JP_L,     JP_SCLN,    KC_ENT,
        KC_LSFT,  KC_LSFT,  JP_Z,     JP_X,     JP_C,     JP_V,     JP_B,     JP_SLSH,  JP_BSLS,  JP_N,     JP_M,     JP_COMM,  JP_DOT,   KC_DOWN,  KC_UP,
        KC_MUTE,  KC_LGUI,  KC_LALT,     JP_MHEN,       SP_LOW,        SP_RAI,   KC_BSPC,     SP_RAI,SP_RAI,       JP_HENK,     JP_KANA,  KC_LEFT,  KC_RGHT,
        KC_VOLD,  KC_VOLU,                                                                                                                KC_VOLD,  KC_VOLU
    ),
    [_BASE2] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSLS,  KC_PAST,  KC_PMNS,  _______,  _______,
           _______,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,   _______,
           _______,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_P4,    KC_P5,    KC_P6,    KC_PPLS,   _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_P1,    KC_P2,    KC_P3,    _______,  _______,
        _______,  _______,  _______,     _______,        _______,      _______,  _______,      _______,_______,    KC_P0,       KC_PDOT,  _______,  _______,
        _______,  _______,                                                                                                                _______,  _______
    ),
    [_BASE3] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
           _______,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,
           _______,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,     _______,        _______,      _______,  _______,      _______,_______,     _______,    _______,  _______,  _______,
        _______,  _______,                                                                                                                _______,  _______
    ),
    [_LOWER] = LAYOUT(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    _______,  _______,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
            _______,    JP_EXLM,  JP_DQUO,  JP_HASH,  JP_DLR,   JP_PERC,  JP_TILD,  JP_PIPE,  JP_AMPR,  JP_QUOT,  JP_LPRN,  JP_RPRN,  JP_EQL,   KC_INS,
            _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,     _______,        _______,      SP_ADJ,   _______,     SP_ADJ,SP_ADJ,       _______,     _______,  _______,  _______,
        _______,  _______,                                                                                                                _______,  _______
    ),
    [_RAISE] = LAYOUT(
        KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    _______,  _______,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
            KC_ESC,     JP_1,     JP_2,     JP_3,     JP_4,     JP_5,     JP_CIRC,  JP_YEN,   JP_6,     JP_7,     JP_8,     JP_9,     JP_0,     KC_DEL,
            _______,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    _______,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  _______,  _______,
        _______,  _______,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   _______,  _______,
        _______,  _______,  _______,     _______,        SP_ADJ,       _______,  _______,      _______,_______,     _______,    _______,  KC_DOWN,  KC_UP,
        _______,  _______,                                                                                                                _______,  _______
    ),
    [_ADJUST] = LAYOUT(
        _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,  KC_SLCK,  KC_PAUS,
            _______,    DF(_BASE1),DF(_BASE2),DF(_BASE3),_______,  _______,  _______,  _______,  RGB_HUI,  RGB_SAI,  RGB_VAI,  _______,  RGB_RMOD,  _______,
            _______,    AU_TOG,   CK_TOGG,  MU_TOG,   MU_MOD,   _______,  _______,  _______,  RGB_HUD,  RGB_SAD,  RGB_VAD,  RGB_TOG,  RGB_MOD,   _______,
        KC_CAPS,  KC_CAPS,  CK_RST,   CK_DOWN,  CK_UP,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,     _______,        _______,      _______,  _______,      _______,_______,     _______,    _______,  _______,  _______,
        _______,  _______,                                                                                                                _______,  _______
    ),
};


//------------------------------------------------------------------------------
// RGB Light settings
//------------------------------------------------------------------------------
#ifdef RGBLIGHT_LAYERS

// Indicator LED settings
#define JONES_LED_INDICATOR_INDEX 0         // where to start indicator
#define JONES_LED_INDICATOR_COUNT 4         // how many leds used for indicator
#define JONES_LED_INDICATOR_CHANGE_COUNT 1  // how meny leds to change for temporally layer
#define JONES_LED_DIMMER_LEVEL 200          // brightness dimmer

// for Default layer (= Base layer)
const rgblight_segment_t PROGMEM my_base1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {JONES_LED_INDICATOR_INDEX , JONES_LED_INDICATOR_COUNT, HSV_WHITE - JONES_LED_DIMMER_LEVEL}
);

const rgblight_segment_t PROGMEM my_base2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {JONES_LED_INDICATOR_INDEX , JONES_LED_INDICATOR_COUNT, HSV_BLUE - JONES_LED_DIMMER_LEVEL}
);

const rgblight_segment_t PROGMEM my_base3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {JONES_LED_INDICATOR_INDEX , JONES_LED_INDICATOR_COUNT, HSV_YELLOW - JONES_LED_DIMMER_LEVEL}
);

// for temporal layer
const rgblight_segment_t PROGMEM my_caps_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {JONES_LED_INDICATOR_INDEX + 1 , 1, HSV_MAGENTA - JONES_LED_DIMMER_LEVEL},
    {JONES_LED_INDICATOR_INDEX + 1 + 2 , 1, HSV_MAGENTA - JONES_LED_DIMMER_LEVEL}
);

const rgblight_segment_t PROGMEM my_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {JONES_LED_INDICATOR_INDEX , JONES_LED_INDICATOR_CHANGE_COUNT, HSV_GREEN - JONES_LED_DIMMER_LEVEL},
    {JONES_LED_INDICATOR_INDEX + 2, JONES_LED_INDICATOR_CHANGE_COUNT, HSV_GREEN - JONES_LED_DIMMER_LEVEL}
);

const rgblight_segment_t PROGMEM my_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {JONES_LED_INDICATOR_INDEX , JONES_LED_INDICATOR_CHANGE_COUNT, HSV_CYAN - JONES_LED_DIMMER_LEVEL},
    {JONES_LED_INDICATOR_INDEX + 2, JONES_LED_INDICATOR_CHANGE_COUNT, HSV_CYAN - JONES_LED_DIMMER_LEVEL}
);

const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {JONES_LED_INDICATOR_INDEX , JONES_LED_INDICATOR_CHANGE_COUNT, HSV_RED - JONES_LED_DIMMER_LEVEL},
    {JONES_LED_INDICATOR_INDEX + 2, JONES_LED_INDICATOR_CHANGE_COUNT, HSV_RED - JONES_LED_DIMMER_LEVEL}
);

// Define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_base1_layer,
    my_base2_layer,
    my_base3_layer,
    my_caps_layer,
    my_lower_layer,
    my_raise_layer,
    my_adjust_layer
);

// Enabling and disabling lighting layers
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(4, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(5, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(6, layer_state_cmp(state, _ADJUST));

    return state;
}

// Enabling and disabling lighting layers for default layer
layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _BASE1));
    rgblight_set_layer_state(1, layer_state_cmp(state, _BASE2));
    rgblight_set_layer_state(2, layer_state_cmp(state, _BASE3));

    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(3, IS_HOST_LED_ON(USB_LED_CAPS_LOCK));

    return true;
}
#endif


//------------------------------------------------------------------------------
// Rotary Encoder
//------------------------------------------------------------------------------
static uint8_t  encoder_state[ENCODERS] = {0};
static keypos_t encoder_cw[ENCODERS]    = ENCODERS_CW_KEY;
static keypos_t encoder_ccw[ENCODERS]   = ENCODERS_CCW_KEY;

void encoder_action_unregister(void) {
    for (int index = 0; index < ENCODERS; ++index) {
        if (encoder_state[index]) {
            keyevent_t encoder_event = (keyevent_t) {
                .key = encoder_state[index] >> 1 ? encoder_cw[index] : encoder_ccw[index],
                .pressed = false,
                .time = (timer_read() | 1)
            };
            encoder_state[index] = 0;
            action_exec(encoder_event);
        }
    }
}

void encoder_action_register(uint8_t index, bool clockwise) {
    keyevent_t encoder_event = (keyevent_t) {
        .key = clockwise ? encoder_cw[index] : encoder_ccw[index],
        .pressed = true,
        .time = (timer_read() | 1)
    };
    encoder_state[index] = (clockwise ^ 1) | (clockwise << 1);
    action_exec(encoder_event);
}

void matrix_scan_kb(void) {
    encoder_action_unregister();
    matrix_scan_user();
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    encoder_action_register(index, clockwise);
    return true;
};


//------------------------------------------------------------------------------
// Keyboard Initialization
//------------------------------------------------------------------------------
void keyboard_post_init_user(void) {
debug_enable=true;
#ifdef RGB_DI_PIN
  #ifdef RGBLIGHT_LAYERS
    // Enable the LED layers.
    rgblight_layers = my_rgb_layers;

    // prevent RGB light overrides layer indicator.
    layer_state_set(default_layer_state);
  #endif
#endif

}
