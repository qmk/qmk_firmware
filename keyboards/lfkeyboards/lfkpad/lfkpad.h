#ifndef LFKPAD_H
#define LFKPAD_H

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
    LFK_LED_TEST            // cycles through switch and RGB LEDs
};

#define CLICK_HZ 500
#define CLICK_MS 2
#define CLICK_ENABLED 0

void reset_keyboard_kb(void);
void click(uint16_t freq, uint16_t duration);

#define KEYMAP( \
    k00, k01, k02, k03,\
    k10, k11, k12, k13,\
    k20, k21, k22, k23,\
    k30, k31, k32,\
    k40, k41, k42, k43,\
    k50,      k52\
) { \
    { k00, k01,   k02, k03 }, \
    { k10, k11,   k12, k13 }, \
    { k20, k21,   k22, k23 }, \
    { k30, k31,   k32, KC_NO }, \
    { k40, k41,   k42, k43 }, \
    { k50, KC_NO, k52, KC_NO } \
}

#endif //LFKPAD_H