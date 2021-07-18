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
    {   8,  7 }, {  22,  7 }, {  35,  7 }, {  49,  7 }, {  63,  7 }, {  77,  7 }, {  91,  7 }, { 105,  7 }, { 118,  7 }, { 132,  7 }, { 146,  7 }, { 160,  7 }, { 174,  7 }, { 195,  7 }, { 215,  7 },
    {  11,  19 }, {  28,  19 }, {  42,  19 }, {  56,  19 }, {  70,  19 }, {  84,  19 }, {  98,  19 }, { 112,  19 }, { 125,  19 }, { 139,  19 }, { 153,  19 }, { 167,  19 }, { 181,  19 }, { 198,  19 }, { 215,  19 },
    {  13,  32 }, {  32,  32 }, {  46,  32 }, {  60,  32 }, {  73,  32 }, {  87,  32 }, { 101,  32 }, { 115,  32 }, { 129,  32 }, { 143,  32 }, { 156,  32 }, { 170,  32 }, { 193,  32 }, { 215,  32 }, {  16,  44 },
    {  39,  44 }, {  53,  44 }, {  67,  44 }, {  80,  44 }, {  94,  44 }, { 108,  44 }, { 122,  44 }, { 136,  44 }, { 150,  44 }, { 163,  44 }, { 182,  44 }, { 201,  44 }, { 215,  44 }, {   9,   56 }, {  27,   56 },
    {  44,   56 }, {  96,   56 }, { 148,   56 }, { 165,   56 }, { 188,   56 }, { 201,   56 }, { 215,   56 },
  // Underglow LEDs
    {   1,   62 }, {  15,   64 }, {  31,   64 }, {  47,   64 }, {  63,   64 }, {  79,   64 }, {  95,   64 }, { 112,   64 }, { 128,   64 }, { 144,   64 }, { 160,   64 }, { 176,   64 }, { 192,   64 }, { 208,   64 }, { 222,   62 },
    { 224,  50 }, { 224,  38 }, { 224,  25 }, { 224,  13 }, { 222,  1 }, { 191,  0 }, { 179,  0 }, { 167,  0 }, { 153,  0 }, { 139,  0 }, { 125,  0 }, { 112,  0 }, {  98,  0 }, {  84,  0 }, {  70,  0 },
    {  56,  0 }, {  42,  0 }, {  28,  0 }, {   1,  1 }, {   0,  13 }, {   0,  25 }, {   0,  38 }, {   0,  50 }
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
void rgb_matrix_indicators_kb(void)
{
  md_rgb_matrix_indicators();
}
#endif // USB_LED_INDICATOR_ENABLE

#endif
