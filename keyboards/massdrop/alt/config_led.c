#ifdef RGB_MATRIX_ENABLE
#include "alt.h"

#include "md_rgb_matrix.h"
#include "rgb_matrix.h"
#include "config_led.h"

// This table can be almost-automatically derived from ISSI3733_LED_MAP that is
// defined in config_led.h

// You can calculate the (0-244, 0-64) x/y values from the x/y values defined in
// ISSI3733_LED_MAP with the following formula:
//   uint8_t rgb_x = ((ISSI3733_LED_MAP[i].x - MIN_X) / (MAX_X - MIN_X)) * 224;
//   uint8_t rgb_y = ((ISSI3733_LED_MAP[i].y - MIN_Y) / (MAX_Y - MIN_Y)) * 64;
// Where the min/max vars are the minimum and maximum "bounds" of x/y values
// present in ISSI3733_LED_MAP
//
// The row/col values need to be manually tweaked though, compensating for the
// "empty" cells that are a product of larger keys
//
// There is a quick-and-dirty implementation of this under ledvis.html

led_config_t g_led_config = { {
    {   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14 },
    {  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29 },
    {  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41, NO_LED,  42,  43 },
    {  44, NO_LED,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57 },
    {  58,  59,  60, NO_LED, NO_LED, NO_LED,  61, NO_LED, NO_LED, NO_LED,  62,  63,  64,  65,  66 }
}, {
    {   8,  56 }, {  22,  56 }, {  35,  56 }, {  49,  56 }, {  63,  56 }, {  77,  56 }, {  91,  56 }, { 105,  56 }, { 118,  56 }, { 132,  56 }, { 146,  56 }, { 160,  56 }, { 174,  56 }, { 195,  56 }, { 215,  56 },
    {  11,  44 }, {  28,  44 }, {  42,  44 }, {  56,  44 }, {  70,  44 }, {  84,  44 }, {  98,  44 }, { 112,  44 }, { 125,  44 }, { 139,  44 }, { 153,  44 }, { 167,  44 }, { 181,  44 }, { 198,  44 }, { 215,  44 },
    {  13,  32 }, {  32,  32 }, {  46,  32 }, {  60,  32 }, {  73,  32 }, {  87,  32 }, { 101,  32 }, { 115,  32 }, { 129,  32 }, { 143,  32 }, { 156,  32 }, { 170,  32 }, { 193,  32 }, { 215,  32 }, {  16,  19 },
    {  39,  19 }, {  53,  19 }, {  67,  19 }, {  80,  19 }, {  94,  19 }, { 108,  19 }, { 122,  19 }, { 136,  19 }, { 150,  19 }, { 163,  19 }, { 182,  19 }, { 201,  19 }, { 215,  19 }, {   9,   7 }, {  27,   7 },
    {  44,   7 }, {  96,   7 }, { 148,   7 }, { 165,   7 }, { 188,   7 }, { 201,   7 }, { 215,   7 },
  // Underglow LEDs
    {   1,   1 }, {  15,   0 }, {  31,   0 }, {  47,   0 }, {  63,   0 }, {  79,   0 }, {  95,   0 }, { 112,   0 }, { 128,   0 }, { 144,   0 }, { 160,   0 }, { 176,   0 }, { 192,   0 }, { 208,   0 }, { 222,   1 },
    { 224,  13 }, { 224,  25 }, { 224,  38 }, { 224,  50 }, { 222,  62 }, { 191,  64 }, { 179,  64 }, { 167,  64 }, { 153,  64 }, { 139,  64 }, { 125,  64 }, { 112,  64 }, {  98,  64 }, {  84,  64 }, {  70,  64 },
    {  56,  64 }, {  42,  64 }, {  28,  64 }, {   1,  62 }, {   0,  50 }, {   0,  38 }, {   0,  25 }, {   0,  13 }
}, {
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    9, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1,
    1, 1, 1, 4, 1, 1, 1, 1, 1,
  // Underglow LEDs
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2
} };


#ifdef USB_LED_INDICATOR_ENABLE
bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    md_rgb_matrix_indicators_advanced(led_min, led_max);
    return true;
}
#endif // USB_LED_INDICATOR_ENABLE

#endif
