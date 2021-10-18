#pragma once

#include "quantum.h"
#include "matrix.h"
#include <avr/sfr_defs.h>

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

#ifndef LAYOUT
#    define LAYOUT( \
    k00,  k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C,        k0E,        k0F, k0G, k0H, k0I, \
    k10,    k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C,      k1D,        k1F, k1G, k1H, k1I, \
    k20,     k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B,          k1E,        k2F, k2G, k2H, k2I, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,          k3C,   k3E,     k3F, k3G, k3H, k3I, \
    k40,   k41,   k42,                 k45,             k4A, k4B, k4C,     k4E, k4F, k4G,     k4H, k4I \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, ___, k0E, k0F, k0G, k0H, k0I }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G, k1H, k1I }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, ___, ___, ___, k2F, k2G, k2H, k2I }, \
    { k30, ___, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, ___, k3E, k3F, k3G, k3H, k3I }, \
    { k40, k41, k42, ___, ___, k45, ___, ___, ___, ___, k4A, k4B, k4C, ___, k4E, k4F, k4G, k4H, k4I } \
}
#endif // !LAYOUT #endif
