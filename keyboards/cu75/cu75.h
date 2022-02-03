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
    LFK_LED_TEST            // cycles through switch and RGB LEDs
};

#define CLICK_HZ 500
#define CLICK_MS 2
#define CLICK_ENABLED 0

void reset_keyboard_kb(void);
void click(uint16_t freq, uint16_t duration);

#define XXX KC_NO

/* Vanilla Keymap */
// This a shortcut to help you visually see your layout.
/*
* ,-------------------------------------------------------------------------------.
* | 00 | 01 | 02 | 03 | 04 | 05 | 06 | 07 | 08 | 09 | 0A | 0B | 0C | 0D | 0E | 0F |
* |-------------------------------------------------------------------------------|
* | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 1A | 1B | 1C |   1D    | 1F |
* |-------------------------------------------------------------------------------|
* | 20   | 21 |22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 2A | 2B | 2C |   2D   | 2E |
* |-------------------------------------------------------------------------------|
* | 30    | 31 |32 | 33 | 34 | 35 | 36 | 37 | 38 | 39 | 3A | 3B |      3C    | 3E |
* |-------------------------------------------------------------------------------|
* | 40      | 42 |43 | 44 | 45 | 46 | 47 | 48 | 49 | 4A | 4B |    4C    | 4D | 4E |
* |-------------------------------------------------------------------------------|
* | 50  |  51  | 52  | 53 |         56        | 58 | 59 | 5A | 5B |  5C | 5D | 5E |
* `-------------------------------------------------------------------------------'
*/
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D,      k1F, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C,      k3E, \
    k40,      k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, \
    k50, k51, k52, k53,           k56,      k58, k59, k5A, k5B, k5C, k5D, k5E \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, XXX, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, XXX }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, XXX, k3E, XXX }, \
    { k40, XXX, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, XXX }, \
    { k50, k51, k52, k53, XXX, XXX, k56, XXX, k58, k59, k5A, k5B, k5C, k5D, k5E, XXX } \
}

#define LAYOUT_all( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, \
    k50, k51, k52, k53,           k56,      k58, k59, k5A, k5B, k5C, k5D, k5E \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, XXX }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, XXX }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, XXX }, \
    { k50, k51, k52, k53, XXX, XXX, k56, XXX, k58, k59, k5A, k5B, k5C, k5D, k5E, XXX } \
}

#define LAYOUT_iso( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D,      k1F, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C,      k3E, \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, \
    k50, k51, k52,       k53,  k56,  k58,        k59, k5A, k5B, k5C, k5D, k5E \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, XXX, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, XXX }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, XXX, k3E, XXX }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, XXX }, \
    { k50, k51, k52, k53, XXX, XXX, k56, XXX, k58, k59, k5A, k5B, k5C, k5D, k5E, XXX } \
}
