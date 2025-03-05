// Copyright 2023 Isaac Rex (@Acliad)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// NOTE: LAYER_RGB is defined in nifty_numpad.h
enum LAYERS {
    LAYER_BL = 0,
};

// Setup keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * BCK -> Backspace
     * WIN -> Task View
     * EXP -> Open Explorer
     * SCN -> Screenshot
     * ┌───┬───┐  ┌───┬───┬───┬───┐
     * │F13│F19│  │BCK│WIN│EXP│SCN│
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
        KC_F13, KC_F19,    LT(LAYER_RGB, KC_BSPC), RGUI(KC_TAB), RGUI(KC_E), RGUI(RSFT(KC_S)),
        KC_F14, KC_F20,    MT(MOD_RCTL, KC_NUM),    KC_PSLS,      KC_PAST,    KC_PMNS,
        KC_F15, KC_F21,    KC_P7,                   KC_P8,        KC_P9,      KC_PPLS,
        KC_F16, KC_F22,    KC_P4,                   KC_P5,        KC_P6,      
        KC_F17, KC_F23,    KC_P1,                   KC_P2,        KC_P3,      KC_PENT,
        KC_F18, KC_F24,    KC_P0,                                 KC_PDOT
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
     * MOD -> RGB Mode (effect cycle)
     * 
     * ___ -> Base Layer Function
     * ┌───┬───┐  ┌───┬───┬───┬───┐
     * │___│___│  │___│HUI│SAI│VAI│
     * └───┴───┘  └───┴───┴───┴───┘
     * ┌───┬───┐  ┌───┬───┬───┬───┐
     * │___│___│  │Num│HUD│SAD│VAD│
     * ├───┼───┤  ├───┼───┼───┼───┤
     * │___│___│  │___│MOD│___│   │
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
        _______, _______,    _______, RGB_MOD, _______, RGB_SPI,
        _______, _______,    _______, _______, _______, 
        _______, _______,    _______, _______, _______, RGB_SPD,
        _______, _______,    _______,          _______     
    )
};