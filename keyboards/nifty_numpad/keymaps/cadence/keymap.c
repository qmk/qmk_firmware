// Copyright 2023 Isaac Rex (@Acliad)
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
#define STR_MEASURE       "~m"
#define STR_SHOW          "sh"
#define STR_UPDATE_SHAPES "sup"
#define STR_ROTATE        "r"
#define STR_MIRROR        "f"
#define STR_PAM           "pam"
#define STR_MOVE          "m"

// Layers 
enum LAYERS {
    LAYER_BL,
    LAYER_CAD,
    LAYER_RGB
};

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
            layer_invert(LAYER_CAD);
            break;
        case 2:
            tap_code16(KC_NUM);
            break;
    }
}

// Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_NUM_TOGGLE]  = ACTION_TAP_DANCE_FN(tap_dance_num_toggle),

    [TD_M1]  = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_1),  LCTL(KC_1)),
    [TD_M2]  = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_2),  LCTL(KC_2)),
    [TD_M3]  = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_3),  LCTL(KC_3)),
    [TD_M4]  = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_4),  LCTL(KC_4)),
    [TD_M5]  = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_5),  LCTL(KC_5)),
    [TD_M6]  = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_F5), LCTL(KC_F5)),
    [TD_M7]  = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_F6), LCTL(KC_F6)),
    [TD_M8]  = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_6),  LCTL(KC_6)),
    [TD_M9]  = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_7),  LCTL(KC_7)),
    [TD_M10] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_8),  LCTL(KC_8)),
    [TD_M11] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_9),  LCTL(KC_9)),
    [TD_M12] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_0),  LCTL(KC_0))
};

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
    [LAYER_BL] = LAYOUT_numpad_6x6(
        TD(TD_M1), TD(TD_M12),    LT(LAYER_RGB, (KC_F1)), LALT(LWIN(KC_F)),   KC_F3,   KC_BACKSPACE,
        TD(TD_M2), TD(TD_M11),    TD(TD_NUM_TOGGLE),      KC_PSLS,            KC_PAST, KC_PMNS,
        TD(TD_M3), TD(TD_M10),    KC_P7,                  KC_P8,              KC_P9,   KC_PPLS,
        TD(TD_M4), TD(TD_M9),     KC_P4,                  KC_P5,              KC_P6,   
        TD(TD_M5), TD(TD_M8),     KC_P1,                  KC_P2,              KC_P3,   KC_PENT,
        TD(TD_M6), TD(TD_M7),     KC_P0,                                      KC_PDOT
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
    [LAYER_CAD] = LAYOUT_numpad_6x6(
        _______, _______,    EDIT_GEN,                EDIT_PLACE, EDIT_ETCH,     EDIT_SHAPE,
        _______, _______,    TD(TD_NUM_TOGGLE),      _______,    _______,       _______,
        _______, _______,    ROUTE,                  SLIDE,      VIA,           KC_F8,
        _______, _______,    MEASURE,                SHOW,       UPDATE_SHAPES, 
        _______, _______,    ROTATE,                 MIRROR,     PAM,           KC_ESC,
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
    [LAYER_RGB] = LAYOUT_numpad_6x6(
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
    if (layer_state_is(LAYER_CAD) && !rgb_matrix_idle_mode()) {
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
