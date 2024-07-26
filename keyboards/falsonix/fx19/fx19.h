// Written by Falsonix
// Original on 7/11/2024

#pragma once

#include "quantum.h" // include firmware dependencies

#define WS2812_DI_PIN F7 // Define pin for RGB lighting
#define RGBLIGHT_DEFAULT_ON // Set RGB lighting on by default
#define RGB_MATRIX_LED_COUNT 6 // 6 LEDs onboard

#define LAYOUT_numpad_4x5( \
    k00, k01, k02, k03, \
    k04, k05, k06, \
    k07, k08, k09, k16, \
    k10, k11, k12, \
    k13, k14, k15, k17 \
) { \
    { k00, k01, k02, k03 }, \
    { k04, k05, k06, KC_NO }, \
    { k07, k08, k09, k16 }, \
    { k10, k11, k12, KC_NO }, \
    { k13, k14, k15, k17 } \
}