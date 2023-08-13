#include QMK_KEYBOARD_H
#include "nifty_numpad.h"
#include "quantum.h"

// Layer Defines
#define _LAYER_BL  0
#define _LAYER_RGB 3

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
     * SCN -> Screenshot
     * WIN -> Task View
     * EXP -> Open Explorer
     * BCK -> Backspace
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
    [_LAYER_BL] = LAYOUT_numpad_6x6(
        KC_F13, KC_F19,    LT(_LAYER_RGB, KC_BSPC), RGUI(KC_TAB), RGUI(KC_E), RGUI(RSFT(KC_S)),
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
    [_LAYER_RGB] = LAYOUT_numpad_6x6(
        _______, _______,    _______, RGB_HUI, RGB_SAI, RGB_VAI,
        _______, _______,    _______, RGB_HUD, RGB_SAD, RGB_VAD,
        _______, _______,    _______, RGB_MOD, _______, RGB_SPI,
        _______, _______,    _______, _______, _______, 
        _______, _______,    _______, _______, _______, RGB_SPD,
        _______, _______,    _______,          _______     
    )
};