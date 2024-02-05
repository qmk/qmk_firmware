// Copyright 2023 Isaac Rex (@Acliad)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Layers 
// NOTE: LAYER_RGB is defined in nifty_numpad.h
enum LAYERS {
    LAYER_BL = 0,
    LAYER_MOD,
};

// Layer Indicator LED index
#define _NUM_LED_INDEX 8

#define TAPPING_TERM 200

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
            layer_invert(LAYER_MOD);
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

// Setup keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * SCN -> Screenshot
     * WIN -> Task View
     * EXP -> Open Explorer
     * BCK -> Backspace
     * ┌───┬───┐  ┌───┬───┬───┬───┐
     * │F13│F19│  │SCN│WIN│EXP│BCK│
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
        TD(TD_M1), TD(TD_M7) ,    LT(LAYER_RGB, KC_BSPC), RGUI(KC_TAB), RGUI(KC_E), RGUI(RSFT(KC_S)),
        TD(TD_M2), TD(TD_M8) ,    TD(TD_NUM_TOGGLE),      KC_PSLS,      KC_PAST,    KC_PMNS,
        TD(TD_M3), TD(TD_M9) ,    KC_P7,                  KC_P8,        KC_P9,      KC_PPLS,
        TD(TD_M4), TD(TD_M10),    KC_P4,                  KC_P5,        KC_P6,      
        TD(TD_M5), TD(TD_M11),    KC_P1,                  KC_P2,        KC_P3,      KC_PENT,
        TD(TD_M6), TD(TD_M12),    KC_P0,                                KC_PDOT
    ),

    /*
     * ┌───┬───┐  ┌───┬───┬───┬───┐
     * │F13│F19│  │F9 │F10│F11│F12│
     * └───┴───┘  └───┴───┴───┴───┘
     * ┌───┬───┐  ┌───┬───┬───┬───┐
     * │___│___│  │___│~/ │~* │___│
     * ├───┼───┤  ├───┼───┼───┼───┤
     * │___│___│  │~7 │~8 │~9 │   │
     * ├───┼───┤  ├───┼───┼───┤___│
     * │___│___│  │~4 │~5 │~6 │   │
     * ├───┼───┤  ├───┼───┼───┼───┤
     * │___│___│  │~1 │~2 │~3 │   │
     * ├───┼───│  ├───┴───┼───┤___│
     * │___│___│  │~0     │~. │   │
     * └───┴───┘  └───────┴───┴───┘
     */
    [LAYER_MOD] = LAYOUT_numpad_6x6(
        _______, _______,    KC_F9,             KC_F10,         KC_F11,        KC_F12,
        _______, _______,    TD(TD_NUM_TOGGLE), RCTL(KC_PSLS), RCTL(KC_PAST), _______,
        _______, _______,    RCTL(KC_P7),       RCTL(KC_P8),   RCTL(KC_P9),   _______,
        _______, _______,    RCTL(KC_P4),       RCTL(KC_P5),   RCTL(KC_P6), 
        _______, _______,    RCTL(KC_P1),       RCTL(KC_P2),   RCTL(KC_P3),   _______,
        _______, _______,    RCTL(KC_P0),                      RCTL(KC_PDOT)     
    ),

    /*
     * HUI -> Hue Increase
     * HUD -> Hue Decrease
     * 
     * SAI -> Saturation Increase
     * SAD -> Saturation Decrease
     * 
     * VAI -> Value Increase
     * VAD -> Value Decrease
     * 
     * SPI -> Speed Increase
     * SPD -> Speed Decrease
     * 
     * DEF -> Set default effect mode
     * IEF -> Set idle effect mode
     * 
     * ___ -> Base Layer Function
     * ┌───┬───┐  ┌───┬───┬───┬───┐
     * │___│___│  │___│HUI│SAI│VAI│
     * └───┴───┘  └───┴───┴───┴───┘
     * ┌───┬───┐  ┌───┬───┬───┬───┐
     * │___│___│  │Num│HUD│SAD│VAD│
     * ├───┼───┤  ├───┼───┼───┼───┤
     * │___│___│  │___│DEF│IEF│   │
     * ├───┼───┤  ├───┼───┼───┤SPI│
     * │___│___│  │___│___│___│   │
     * ├───┼───┤  ├───┼───┼───┼───┤
     * │___│___│  │___│___│___│   │
     * ├───┼───│  ├───┴───┼───┤SPD│
     * │___│___│  │___    │___│   │
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
    if (layer_state_is(LAYER_MOD) && !rgb_matrix_idle_mode()) {
        // Get a hue that contrasts with current hue
        uint8_t hue = rgb_matrix_get_hue() + 127; 
        // Make sure saturation is high enough to distiguish between hues
        uint8_t sat = 255;
        uint8_t val = MIN((uint16_t) rgb_matrix_get_val() + 50, 255);
        RGB rgb = hsv_to_rgb((HSV) {hue, sat, val});
        rgb_matrix_set_color(_NUM_LED_INDEX, rgb.r, rgb.g, rgb.b);
    }
    return false;
}
