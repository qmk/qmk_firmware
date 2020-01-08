#pragma once

#include "quantum.h"
#include "matrix.h"

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

// readability
#define ___ KC_NO

#ifdef LFK_REV_B
    /* RevB Keymap */
    // This a shortcut to help you visually see your layout.
    /*
    * ,---------.  ,-----------------------------------------------------------------------.  ,---------.
    * |  0 |  1 |  |  2 |  3 |  4 |  5 |  6 |  7 | 50 | 51 | 52 | 53 | 54 | 55 | 56 |   57 |  | 94 | 95 |
    * |---------|  |-----------------------------------------------------------------------|  |---------|
    * | 10 | 11 |  | 12  | 13 | 14 | 15 | 16 |  17 | 60 | 61 | 62 | 63 | 64 | 65 | 66 | 67 |  | 96 | 97 |
    * |---------|  |-----------------------------------------------------------------------|  `---------'
    * | 20 | 21 |  | 22    | 23 | 24 | 25 | 26 | 27 | 70 | 71 | 72 | 73 | 74 | 75 |     76 |
    * |---------|  |-----------------------------------------------------------------------|  ,----.
    * | 30 | 31 |  | 32      | 33 | 34 | 35 | 36 | 37 | 80 | 81 | 82 | 83 | 84 |        85 |  | 86 |
    * |---------|  |-------------------------------------------------------------------------------------.
    * | 40 | 41 |  | 42  | 43  | 44 |               45                |  46 |  47 |  90 | | 91 | 92 | 93 |
    * `---------'  `--------------------------------------------------------------------' `--------------'
    */
    // The first section contains all of the arguements
    // The second converts the arguments into a two-dimensional array
    #define LAYOUT( \
        k00, k01,   k02, k03, k04, k05, k06, k07, k50, k51, k52, k53, k54, k55, k56, k57,   k94, k95, \
        k10, k11,   k12, k13, k14, k15, k16, k17, k60, k61, k62, k63, k64, k65, k66, k67,   k96, k97, \
        k20, k21,   k22, k23, k24, k25, k26, k27, k70, k71, k72, k73, k74, k75,      k76, \
        k30, k31,   k32,  k33, k34, k35, k36, k37, k80, k81, k82, k83, k84,          k85,   k86, \
        k40, k41,   k42, k43, k44,              k45,                  k46, k47, k90,   k91, k92, k93 \
    ) { \
        { k00, k01, k02, k03, k04, k05, k06, k07 }, \
        { k10, k11, k12, k13, k14, k15, k16, k17 }, \
        { k20, k21, k22, k23, k24, k25, k26, k27 }, \
        { k30, k31, k32, k33, k34, k35, k36, k37 }, \
        { k40, k41, k42, k43, k44, k45, k46, k47 }, \
        { k50, k51, k52, k53, k54, k55, k56, k57 }, \
        { k60, k61, k62, k63, k64, k65, k66, k67 }, \
        { k70, k71, k72, k73, k74, k75, k76, ___ }, \
        { k80, k81, k82, k83, k84, k85, k86, ___ }, \
        { k90, k91, k92, k93, k94, k95, k96, k97 }, \
    }
#else
    /* RevC+ Keymap */
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
    #define LAYOUT( \
        k11, k12,   k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G,   k1H, k1I, \
        k21, k22,   k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F, k2G,   k2H, k2I, \
        k31, k32,   k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E,      k3F, \
        k41, k42,   k43,  k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E,          k4F,   k4H, \
        k51, k52,   k53, k54, k55,              k59,                  k5D, k5E, k5F,   k5G, k5H, k5I \
    ) { \
        { k11, k12,   k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G, k1H, k1I }, \
        { k21, k22,   k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F, k2G, k2H, k2I }, \
        { k31, k32,   k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, k3F, ___, ___, ___ }, \
        { k41, k42,   k43, ___, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, k4F, ___, k4H, ___ }, \
        { k51, k52,   k53, k54, k55, ___, ___, ___, k59, ___, ___, ___, k5D, k5E, k5F, k5G, k5H, k5I } \
    }

    #define LAYOUT_split_bs( \
        k11, k12,   k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G, k3G,   k1H, k1I, \
        k21, k22,   k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F, k2G,        k2H, k2I, \
        k31, k32,   k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E,      k3F, \
        k41, k42,   k43,  k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E,          k4F,        k4H, \
        k51, k52,   k53, k54, k55,              k59,                  k5D, k5E, k5F,        k5G, k5H, k5I \
    ) { \
        { k11, k12,   k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G, k1H, k1I }, \
        { k21, k22,   k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F, k2G, k2H, k2I }, \
        { k31, k32,   k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, k3F, k3G, ___, ___ }, \
        { k41, k42,   k43, ___, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, k4F, ___, k4H, ___ }, \
        { k51, k52,   k53, k54, k55, ___, ___, ___, k59, ___, ___, ___, k5D, k5E, k5F, k5G, k5H, k5I } \
    }

    #define LAYOUT_split_rshift( \
        k11, k12,   k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G,   k1H, k1I, \
        k21, k22,   k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F, k2G,   k2H, k2I, \
        k31, k32,   k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E,      k3F, \
        k41, k42,   k43,  k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E,     k4F, k4G,   k4H, \
        k51, k52,   k53, k54, k55,              k59,                  k5D, k5E, k5F,   k5G, k5H, k5I \
    ) { \
        { k11, k12,   k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G, k1H, k1I }, \
        { k21, k22,   k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F, k2G, k2H, k2I }, \
        { k31, k32,   k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, k3F, ___, ___, ___ }, \
        { k41, k42,   k43, ___, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, k4F, k4G, k4H, ___ }, \
        { k51, k52,   k53, k54, k55, ___, ___, ___, k59, ___, ___, ___, k5D, k5E, k5F, k5G, k5H, k5I } \
    }

    #define LAYOUT_iso( \
        k11, k12,   k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G,   k1H, k1I, \
        k21, k22,   k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F, k2G,   k2H, k2I, \
        k31, k32,   k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, k3F,     \
        k41, k42,   k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E,      k4F,   k4H, \
        k51, k52,   k53, k54, k55,              k59,                  k5D, k5E, k5F,   k5G, k5H, k5I \
    ) { \
        { k11, k12,   k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G,   k1H, k1I }, \
        { k21, k22,   k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F, k2G,   k2H, k2I }, \
        { k31, k32,   k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, k3F, ___,   ___, ___ }, \
        { k41, k42,   k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, k4F, ___,   k4H, ___ }, \
        { k51, k52,   k53, k54, k55, ___, ___, ___, k59, ___, ___, ___, k5D, k5E, k5F, k5G,   k5H, k5I } \
    }

#endif //LFK_REV_B
