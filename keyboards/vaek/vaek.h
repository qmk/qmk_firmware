#ifndef vaek_H
#define vaek_H

#include "keymap.h"
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
    LFK_LED_TEST            // cycles through switch and RGB LEDs
};


void reset_keyboard_kb(void);
void click(uint16_t freq, uint16_t duration);

// This a shortcut to help you visually see your layout.
/*
* ,---------.  ,-----------------------------------------------------------------------.  ,---------.
* | 11 | 12 |  | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 1A | 1B | 1C | 1D | 1E | 1F |   1G |  | 1H | 1I |
* |---------|  |-----------------------------------------------------------------------|  |---------|
* | 21 | 22 |  | 23  | 24 | 25 | 26 | 27 | 28 | 29 | 2A | 2B | 2C | 2D | 2E | 2F |  2G |  | 2H | 2I |
* |---------|  |-----------------------------------------------------------------------|  `---------'
* | 31 | 32 |  | 33    | 34 | 35 | 36 | 37 | 38 | 39 | 3A | 3B | 3C | 3D | 3E |     3F |
* |---------|  |-----------------------------------------------------------------------|  ,----.
* | 41 | 42 |  | 43      | 45 | 46 | 47 | 48 | 49 | 4A | 4B | 4C | 4D | 4E |        4F |  | 4H |
* |---------|  |-------------------------------------------------------------------------------------.
* | 51 | 52 |  | 53  | 54  | 55 |               59                |  5D |  5E |  5F | | 5G | 5H | 5I |
* `---------'  `--------------------------------------------------------------------' `--------------'
*/
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define KEYMAP( \
    k11, k12,   k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G,   k1H, k1I, \
    k21, k22,   k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F, k2G,   k2H, k2I, \
    k31, k32,   k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E,      k3F, \
    k41, k42,   k43,  k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E,          k4F,   k4H, \
    k51, k52,   k53, k54, k55,              k59,                  k5D, k5E, k5F,   k5G, k5H, k5I \
) { \
    {k11, k12,   k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G,   k1H, k1I}, \
    {k21, k22,   k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F, k2G,   k2H, k2I}, \
    {k31, k32,   k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, k3F, KC_NO,   KC_NO, KC_NO}, \
    {k41, k42,   k43, KC_NO, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, k4F, KC_NO,   k4H, KC_NO}, \
    {k51, k52,   k53, k54, k55, KC_NO, KC_NO, KC_NO, k59, KC_NO, KC_NO, KC_NO, k5D, k5E, k5F, k5G,   k5H, k5I} \
}

#endif //vaek_H
