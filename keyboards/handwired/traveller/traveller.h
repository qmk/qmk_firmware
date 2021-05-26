#ifndef TRAVELLER_H
#define TRAVELLER_H

#include "quantum.h"
#include "led.h"

#ifdef RGBLIGHT_ENABLE
  #include "rgblight.h"
#endif
#ifdef BACKLIGHT_ENABLE
        #include "backlight.h"
#endif



// This a shortcut to help you visually see your layout.
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
        k00, k01, k02, k03, k04, k05,       k07, k08, k09, k0a, k0b, k0c, \
        k10, k11, k12, k13, k14, k15,       k17, k18, k19, k1a, k1b, k1c, \
        k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, \
        k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c  \
) \
{ \
        { k00, k01, k02, k03, k04, k05, KC_NO, k07, k08, k09, k0a, k0b, k0c }, \
        { k10, k11, k12, k13, k14, k15, KC_NO, k17, k18, k19, k1a, k1b, k1c }, \
        { k20, k21, k22, k23, k24, k25, k26,   k27, k28, k29, k2a, k2b, k2c }, \
        { k30, k31, k32, k33, k34, k35, k36,   k37, k38, k39, k3a, k3b, k3c } \
}

#endif
