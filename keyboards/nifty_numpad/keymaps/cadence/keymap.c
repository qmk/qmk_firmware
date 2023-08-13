// Copyright 2021 QMK / NachoxMacho
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "nifty_numpad.h"
#include "quantum.h"

// Custom String Definitions
#define STR_EDIT_GEN      "emg"
#define STR_EDIT_PLACE    "emp"
#define STR_EDIT_ETCH     "eme"
#define STR_EDIT_SHAPE    "ems"
#define STR_ROUTE         "xx"
#define STR_SLIDE         "dd"
#define STR_VIA           "vv"
#define STR_MEASURE       "me"
#define STR_SHOW          "sh"
#define STR_UPDATE_SHAPES "sup"
#define STR_ROTATE        "rr"
#define STR_MIRROR        "ff"
#define STR_PAM           "pam"
#define STR_MOVE          "mm"

// Layer Defines
#define _LAYER_BL  0
#define _LAYER_CAD 1
#define _LAYER_RGB 15

#define _LAYER_CAD_LED_INDEX 8

#define TAPPING_TERM 200

// Custom keycode declarations
enum cadence_keycodes {
    EDIT_GEN = RGB_IEF + 1,
    EDIT_PLACE,
    EDIT_ETCH,
    EDIT_SHAPE,
    ROUTE,
    SLIDE,
    VIA,
    MEASURE,
    SHOW,
    UPDATE_SHAPES,
    ROTATE,
    MIRROR,
    PAM,
    MOVE
};

// Tap Dance Declarations
enum {
    TD_NUM_TOGGLE = 0,
    TD_EDIT_GEN_TOGGLE,
    TD_M1,
    TD_M2,
    TD_M3,
    TD_M4,
    TD_M5,
    TD_M6,
    TD_M7,
    TD_M8,
    TD_M9,
    TD_M10,
    TD_M11,
    TD_M12,
};

// TD function for 1 tap, toggle layer; 2 taps, press numlock
void tap_dance_num_toggle(tap_dance_state_t *state, void *user_data){
    switch(state->count){
        case 1:
            layer_invert(_LAYER_CAD);
            break;
        case 2:
            tap_code16(KC_NUM);
            break;
    }
}

// Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_NUM_TOGGLE]  = ACTION_TAP_DANCE_FN(tap_dance_num_toggle),

    [TD_M1]  = ACTION_TAP_DANCE_DOUBLE(KC_F13, LCTL(KC_F13)),
    [TD_M2]  = ACTION_TAP_DANCE_DOUBLE(KC_F14, LCTL(KC_F14)),
    [TD_M3]  = ACTION_TAP_DANCE_DOUBLE(KC_F15, LCTL(KC_F15)),
    [TD_M4]  = ACTION_TAP_DANCE_DOUBLE(KC_F16, LCTL(KC_F16)),
    [TD_M5]  = ACTION_TAP_DANCE_DOUBLE(KC_F17, LCTL(KC_F17)),
    [TD_M6]  = ACTION_TAP_DANCE_DOUBLE(KC_F18, LCTL(KC_F18)),
    [TD_M7]  = ACTION_TAP_DANCE_DOUBLE(KC_F19, LCTL(KC_F19)),
    [TD_M8]  = ACTION_TAP_DANCE_DOUBLE(KC_F20, LCTL(KC_F20)),
    [TD_M9]  = ACTION_TAP_DANCE_DOUBLE(KC_F21, LCTL(KC_F21)),
    [TD_M10] = ACTION_TAP_DANCE_DOUBLE(KC_F22, LCTL(KC_F22)),
    [TD_M11] = ACTION_TAP_DANCE_DOUBLE(KC_F23, LCTL(KC_F23)),
    [TD_M12] = ACTION_TAP_DANCE_DOUBLE(KC_F24, LCTL(KC_F24))
};

// Setup LED map
led_config_t g_led_config = { {
    // Key Matrix to LED Index
    { 0,  1,  2,  3,      4,  5      },
    { 6,  7,  8,  9,      10, 11     },
    { 12, 13, 14, 15,     16, 17     },
    { 18, 19, 20, 21,     22, NO_LED },
    { 23, 24, 25, 26,     27, 28     },
    { 29, 30, 31, NO_LED, 32, NO_LED }
}, {
    // LED Index to Physical Position
    {  0,   0}, { 43,   0}, { 96,   0}, {139,   0}, {181,   0}, {224,   0}, 
    {  0,  17}, { 43,  17}, { 96,  17}, {139,  17}, {181,  17}, {224,  17}, 
    {  0,  29}, { 43,  29}, { 96,  29}, {139,  29}, {181,  29}, {224,  35}, 
    {  0,  41}, { 43,  41}, { 96,  41}, {139,  41}, {181,  41}, {  0,  52}, 
    { 43,  52}, { 96,  52}, {139,  52}, {181,  52}, {224,  58}, {  0,  64}, 
    { 43,  64}, {117,  64}, {181,  64}
}, {
    // LED Index to Flag
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT
} };

// Setup keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┐  ┌───┬───┬───┬───┐
     * │F13│F19│  │F1 │F2 │F3 │F4 │
     * └───┴───┘  └───┴───┴───┴───┘
     * ┌───┬───┐  ┌───┬───┬───┬───┐
     * │F14│F20│  │Num│ / │ * │ - │
     * ├───┼───┤  ├───┼───┼───┼───┤
     * │F15│F21│  │ 7 │ 8 │ 9 │   │
     * ├───┼───┤  ├───┼───┼───┤ + │
     * │F16│F22│  │ 4 │ 5 │ 6 │   │
     * ├───┼───┤  ├───┼───┼───┼───┤
     * │F17│F23│  │ 1 │ 2 │ 3 │   │
     * ├───┼───│  ├───┴───┼───┤Ent│
     * │F18│F24│  │ 0     │ . │   │
     * └───┴───┘  └───────┴───┴───┘
     */
    [_LAYER_BL] = LAYOUT_numpad_6x6(
        TD(TD_M1), TD(TD_M12),    LT(_LAYER_RGB, KC_F1), KC_F2,   KC_F3,   KC_F4,
        TD(TD_M2), TD(TD_M11),    TD(TD_NUM_TOGGLE),     KC_PSLS, KC_PAST, KC_PMNS,
        TD(TD_M3), TD(TD_M10),    KC_P7,                 KC_P8,   KC_P9,   KC_PPLS,
        TD(TD_M4), TD(TD_M9),     KC_P4,                 KC_P5,   KC_P6,   
        TD(TD_M5), TD(TD_M8),     KC_P1,                 KC_P2,   KC_P3,   KC_PENT,
        TD(TD_M6), TD(TD_M7),     KC_P0,                          KC_PDOT
    ),

    /*
     * ┌───┬───┐  ┌───┬───┬───┬───┐
     * │F13│F19│  │F1 │F2 │F3 │F4 │
     * └───┴───┘  └───┴───┴───┴───┘
     * ┌───┬───┐  ┌───┬───┬───┬───┐
     * │F14│F20│  │Num│ / │ * │ - │
     * ├───┼───┤  ├───┼───┼───┼───┤
     * │F15│F21│  │ 7 │ 8 │ 9 │   │
     * ├───┼───┤  ├───┼───┼───┤ + │
     * │F16│F22│  │ 4 │ 5 │ 6 │   │
     * ├───┼───┤  ├───┼───┼───┼───┤
     * │F17│F23│  │ 1 │ 2 │ 3 │   │
     * ├───┼───│  ├───┴───┼───┤Ent│
     * │F18│F24│  │ 0     │ . │   │
     * └───┴───┘  └───────┴───┴───┘
     */
    [_LAYER_CAD] = LAYOUT_numpad_6x6(
        _______, _______,    EDIT_GEN,                EDIT_PLACE, EDIT_ETCH,     EDIT_SHAPE,
        _______, _______,    TD(TD_NUM_TOGGLE),      _______,    _______,       _______,
        _______, _______,    ROUTE,                  SLIDE,      VIA,           KC_F8,
        _______, _______,    MEASURE,                SHOW,       UPDATE_SHAPES, 
        _______, _______,    ROTATE,                 MIRROR,     PAM,           KC_F6,
        _______, _______,    MOVE,                               KC_F9     
    ),

    /*
     * ┌───┬───┐  ┌───┬───┬───┬───┐
     * │F13│F19│  │F1 │F2 │F3 │F4 │
     * └───┴───┘  └───┴───┴───┴───┘
     * ┌───┬───┐  ┌───┬───┬───┬───┐
     * │F14│F20│  │Num│ / │ * │ - │
     * ├───┼───┤  ├───┼───┼───┼───┤
     * │F15│F21│  │ 7 │ 8 │ 9 │   │
     * ├───┼───┤  ├───┼───┼───┤ + │
     * │F16│F22│  │ 4 │ 5 │ 6 │   │
     * ├───┼───┤  ├───┼───┼───┼───┤
     * │F17│F23│  │ 1 │ 2 │ 3 │   │
     * ├───┼───│  ├───┴───┼───┤Ent│
     * │F18│F24│  │ 0     │ . │   │
     * └───┴───┘  └───────┴───┴───┘
     */
    [_LAYER_RGB] = LAYOUT_numpad_6x6(
        _______, _______,    _______, RGB_HUI, RGB_SAI, RGB_VAI,
        _______, _______,    _______, RGB_HUD, RGB_SAD, RGB_VAD,
        _______, _______,    _______, RGB_DEF, RGB_IEF, RGB_SPI,
        _______, _______,    _______, _______, _______, 
        _______, _______,    _______, _______, _______, RGB_SPD,
        _______, _______,    _______,          _______     
    )
};

// Set the layer toggle key to an indication of the active layer. This is a
// bit janky and should be done better, but I'm trying to avoid scope creep.
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (layer_state_is(_LAYER_CAD) && !rgb_matrix_idle_mode()) {
        // Get a hue that contrasts with current hue
        uint8_t hue = rgb_matrix_get_hue() + 127; 
        // Make sure saturation is high enough to distiguish between hues
        uint8_t sat = 255;
        uint8_t val = min((uint16_t) rgb_matrix_get_val() + 50, 255);
        RGB rgb = hsv_to_rgb((HSV) {hue, sat, val});
        rgb_matrix_set_color(_LAYER_CAD_LED_INDEX, rgb.r, rgb.g, rgb.b);
    }
    return false;
}

// Process custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {

    // Custom macro strings for Cadence
    case EDIT_GEN:
        if (record->event.pressed) {
            SEND_STRING(STR_EDIT_GEN);
        }
        break;
    case EDIT_PLACE:
        if (record->event.pressed) {
            SEND_STRING(STR_EDIT_PLACE);
        }
        break;
    case EDIT_ETCH:
        if (record->event.pressed) {
            SEND_STRING(STR_EDIT_ETCH);
        }
        break;
    case EDIT_SHAPE:
        if (record->event.pressed) {
            SEND_STRING(STR_EDIT_SHAPE);
        }
        break;
    case ROUTE:
        if (record->event.pressed) {
            SEND_STRING(STR_ROUTE);
        }
        break;
    case SLIDE:
        if (record->event.pressed) {
            SEND_STRING(STR_SLIDE);
        }
        break;
    case VIA:
        if (record->event.pressed) {
            SEND_STRING(STR_VIA);
        }
        break;
    case MEASURE:
        if (record->event.pressed) {
            SEND_STRING(STR_MEASURE);
        }
        break;
    case SHOW:
        if (record->event.pressed) {
            SEND_STRING(STR_SHOW);
        }
        break;
    case UPDATE_SHAPES:
        if (record->event.pressed) {
            SEND_STRING(STR_UPDATE_SHAPES);
        }
        break;
    case ROTATE:
        if (record->event.pressed) {
            SEND_STRING(STR_ROTATE);
        }
        break;
    case MIRROR:
        if (record->event.pressed) {
            SEND_STRING(STR_MIRROR);
        }
        break;
    case PAM:
        if (record->event.pressed) {
            SEND_STRING(STR_PAM);
        }
        break;
    case MOVE:
        if (record->event.pressed) {
            SEND_STRING(STR_MOVE);
        }
        break;
    }
    return true;
};
