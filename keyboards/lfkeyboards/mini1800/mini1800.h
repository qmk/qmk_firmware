#ifndef LFK87_H
#define LFK87_H

/* if the kb.h file exists (because we're running from qmkbuilder) include it */
#if __has_include("kb.h")
#include "kb.h"
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
    LFK_LED_TEST,           // cycles through switch and RGB LEDs
    LFK_PLAY_ONEUP
};

#define CLICK_HZ 500
#define CLICK_MS 2
#define CLICK_ENABLED 0

void reset_keyboard_kb(void);
void click(uint16_t freq, uint16_t duration);

#define ___ KC_NO

        // a = 10
        // b = 11
        // c = 12
        // d = 13
        // e = 14
        // f = 15
        // g = 16
        // h = 17
        // i = 18
        // j = 19

#ifndef LAYOUT
    #define LAYOUT( \
        k11,  k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,        k1f,        k1g, k1h, k1i, k1j,\
        k21,    k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      k2e,        k2g, k2h, k2i, k2j,\
        k31,     k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c,          k2f,        k3g, k3h, k3i, k3j,\
        k41,      k43, k44, k45, k46, k47, k48, k49, k4a, k4b, k4c,          k4d,   k4f,     k4g, k4h, k4i, k4j,\
        k51,   k52,   k53,                 k56,             k5b, k5c, k5d,     k5f, k5g, k5h,     k5i, k5j \
    ) \
    { \
        { k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, ___, k1f, k1g, k1h, k1i, k1j }, \
        { k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, k2h, k2i, k2j }, \
        { k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, ___, ___, ___, k3g, k3h, k3i, k3j }, \
        { k41, ___, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, k4c, k4d, ___, k4f, k4g, k4h, k4i, k4j }, \
        { k51, k52, k53, ___, ___, k56, ___, ___, ___, ___, k5b, k5c, k5d, ___, k5f, k5g, k5h, k5i, k5j }, \
    }

#endif // !LAYOUT #endif

#endif //LFK87_H
