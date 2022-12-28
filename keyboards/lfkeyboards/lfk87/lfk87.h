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

#define CLICK_HZ 500
#define CLICK_MS 2
#define CLICK_ENABLED 0

void reset_keyboard_kb(void);
void click(uint16_t freq, uint16_t duration);

#define ___ KC_NO

#ifdef LFK_TKL_REV_A
#    ifndef LAYOUT_tkl_ansi
#        define LAYOUT_tkl_ansi( \
    k00,       k02, k03, k04, k05,    k06, k07, k08, k09,    k0A, k0B, k0C, k0D,   k0E, k0F, k0G, \
    k10,  k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C,       k1D,   k1E, k1F, k1G, \
    k20,    k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C,     k2D,   k2E, k2F, k2G, \
    k30,     k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,         k3C, \
    k40,      k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B,             k4C,        k4F, \
    k50,   k51,   k52,                 k56,            k5A,   k5B,   k5C,   k5D,   k5E, k5F, k5G \
) { \
    { k00, ___, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, k0G }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F, k2G }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, ___, ___, ___, ___ }, \
    { k40, ___, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, ___, ___, k4F, ___ }, \
    { k50, k51, k52, ___, ___, ___, k56, ___, ___, ___, k5A, k5B, k5C, k5D, k5E, k5F, k5G } \
}
    #endif // !LAYOUT_tkl_ansi
#    ifndef LAYOUT_tkl_iso
#        define LAYOUT_tkl_iso( \
    k00,       k02, k03, k04, k05,    k06, k07, k08, k09,    k0A, k0B, k0C, k0D,   k0E, k0F, k0G, \
    k10,  k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C,       k1D,   k1E, k1F, k1G, \
    k20,    k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C,            k2E, k2F, k2G, \
    k30,     k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C,    k2D, \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B,             k4C,        k4F, \
    k50,   k51,   k52,                 k56,            k5A,   k5B,   k5C,   k5D,   k5E, k5F, k5G \
) { \
    { k00, ___, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, k0G }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F, k2G }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, ___, ___, ___, ___ }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, ___, ___, k4F, ___ }, \
    { k50, k51, k52, ___, ___, ___, k56, ___, ___, ___, k5A, k5B, k5C, k5D, k5E, k5F, k5G } \
}
#    endif // !LAYOUT_tkl_iso
#else  // RevC+ keymaps
#    ifndef LAYOUT_tkl_ansi
#        define LAYOUT_tkl_ansi( \
    k60,       k00, k01, k02, k03,    k04, k05, k06, k07,    k08, k09, k0A, k0B,   k0D, k0E, k0F, \
    k61,  k62, k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A,       k1B,   k1D, k1E, k1F, \
    k63,    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B,     k2C,   k2D, k2E, k2F, \
    k50,     k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A,         k3B, \
    k51,      k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A,             k4B,        k4E, \
    k52,   k53,   k54,                 k56,            k59,   k5A,   k5B,   k5C,   k5D, k5E, k5F \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, ___, k0D, k0E, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, ___, k1D, k1E, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, ___, ___, ___, ___ }, \
    { ___, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, ___, ___, k4E, ___ }, \
    { k50, k51, k52, k53, k54, ___, k56, ___, ___, k59, k5A, k5B, k5C, k5D, k5E, k5F }, \
    { k60, k61, k62, k63, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___ } \
}
#    endif // !LAYOUT_tkl_ansi
#    ifndef LAYOUT_tkl_iso
#        define LAYOUT_tkl_iso( \
    k60,       k00, k01, k02, k03,    k04, k05, k06, k07,    k08, k09, k0A, k0B,   k0D, k0E, k0F, \
    k61,  k62, k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A,       k1B,   k1D, k1E, k1F, \
    k63,    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B,            k2D, k2E, k2F, \
    k50,     k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,    k2C, \
    k51, k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A,             k4B,        k4E, \
    k52,   k53,   k54,                 k56,            k59,   k5A,   k5B,   k5C,   k5D, k5E, k5F \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, ___, k0D, k0E, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, ___, k1D, k1E, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, ___, ___, ___, ___ }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, ___, ___, k4E, ___ }, \
    { k50, k51, k52, k53, k54, ___, k56, ___, ___, k59, k5A, k5B, k5C, k5D, k5E, k5F }, \
    { k60, k61, k62, k63, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___ } \
}
#    endif // !LAYOUT_tkl_iso
#endif //Rev
