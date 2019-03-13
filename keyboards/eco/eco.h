#ifndef ECO_H
#define ECO_H

#ifdef KEYBOARD_eco_rev1
    #include "rev1.h"
#endif
#ifdef KEYBOARD_eco_rev2
    #include "rev2.h"
#endif

#include "quantum.h"

// Used to create a keymap using only KC_ prefixed keys
#define LAYOUT_kc( \
    k01, k02, k03, k04, k05, k06, k07, k08, k09, k010, k011, k012, k013, k014, \
    k11, k12, k13, k14, k15, k16, k17, k18, k19, k110, k111, k112, k113, k114, \
    k21, k22, k23, k24, k25, k26, k27, k28, k29, k210, k211, k212, k213, k214, \
    k31, k32, k33, k34, k35, k36, k37, k38, k39, k310, k311, k312, k313, k314  \
    ) \
    { \
        { KC_##k01, KC_##k02, KC_##k03, KC_##k04, KC_##k05, KC_##k06, KC_##k07, KC_##k08, KC_##k09, KC_##k010, KC_##k011, KC_##k012, KC_##k013, KC_##k014 }, \
        { KC_##k11, KC_##k12, KC_##k13, KC_##k14, KC_##k15, KC_##k16, KC_##k17, KC_##k18, KC_##k19, KC_##k110, KC_##k111, KC_##k112, KC_##k113, KC_##k114 }, \
        { KC_##k21, KC_##k22, KC_##k23, KC_##k24, KC_##k25, KC_##k26, KC_##k27, KC_##k28, KC_##k29, KC_##k210, KC_##k211, KC_##k212, KC_##k213, KC_##k214 }, \
        { KC_##k31, KC_##k32, KC_##k33, KC_##k34, KC_##k35, KC_##k36, KC_##k37, KC_##k38, KC_##k39, KC_##k310, KC_##k311, KC_##k312, KC_##k313, KC_##k314 }  \
    }

#endif
