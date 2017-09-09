#ifndef SMK65_H
#define SMK65_H

/* if the kb.h file exists (because we're running from qmkbuilder) include it */
#ifdef __has_include
#if __has_include("kb.h")
#include "kb.h"
#endif
#endif

#include "quantum.h"
#include "matrix.h"
#include <avr/sfr_defs.h>

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif


typedef struct RGB_Color {
    uint16_t red;
    uint16_t green;
    uint16_t blue;
} RGB_Color;

typedef struct Layer_Info {
    uint32_t layer;
    uint32_t mask;
    RGB_Color color;
} Layer_Info;

extern const uint32_t layer_count;
extern const Layer_Info layer_info[];

enum action_functions {
    LFK_CLEAR = 0,          // Resets all layers
    LFK_ESC_TILDE,          // esc+lshift = ~
    LFK_SET_DEFAULT_LAYER,  // changes and saves current base layer to eeprom
    LFK_CLICK_TOGGLE,       // Adjusts click duration
    LFK_CLICK_FREQ_HIGHER,  // Adjusts click frequency
    LFK_CLICK_FREQ_LOWER,   // Adjusts click frequency
    LFK_CLICK_TIME_LONGER,  // Adjusts click duration
    LFK_CLICK_TIME_SHORTER, // Adjusts click duration
    LFK_DEBUG_SETTINGS,     // prints LED and click settings to HID
    LFK_LED_TEST            // cycles through switch and RGB LEDs
};

#define CLICK_HZ 500
#define CLICK_MS 2
#define CLICK_ENABLED 0

void reset_keyboard_kb(void);
void click(uint16_t freq, uint16_t duration);

/* Vanilla Keymap */
// This a shortcut to help you visually see your layout.
/*
* ,-------------------------------------------------------------------------------.
* | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 1A | 1B | 1C | 1D |   1E    | 1G |
* |-------------------------------------------------------------------------------|
* | 21   | 22 |23 | 24 | 25 | 26 | 27 | 28 | 29 | 2A | 2B | 2C | 2D |   2F   | 2G |
* |-------------------------------------------------------------------------------|
* | 31    | 32 |33 | 34 | 35 | 36 | 37 | 38 | 39 | 3A | 3B | 3C |      3F    | 3G |
* |-------------------------------------------------------------------------------|
* | 41      | 42 |43 | 45 | 46 | 47 | 48 | 49 | 4A | 4B | 4C |    4D    | 4F | 4G |
* |-------------------------------------------------------------------------------|
* | 51  |  52  | 53  |              57        | 5A | 5B | 5C | 5D |  5E | 3E | 4E |
* `-------------------------------------------------------------------------------'
*/
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define KEYMAP( \
    k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D,         k1E, k1G, \
    k21,   k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D,       k2F, k2G, \
    k31,    k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C,           k3F, k3G, \
    k41,     k43, k44,  k45, k46, k47, k48, k49, k4A, k4B, k4C,         k4D, k4F, k4G, \
    k51, k52, k53,              k57,                      k5B, k5C, k5D, k5E, k3E, k4E \
) { \
    {k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, KC_NO, k1G}, \
    {k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, KC_NO, k2F, k2G}, \
    {k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, KC_NO, k3E, k3F, k3G}, \
    {k41, KC_NO, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, k4F, k4G}, \
    {k51, k52, k53, KC_NO, KC_NO, KC_NO, k57, KC_NO, KC_NO, KC_NO, k5B, k5C, k5D, k5E, KC_NO, KC_NO}, \
}

#endif //SMK65_H
