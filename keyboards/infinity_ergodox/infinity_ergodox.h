#ifndef KEYBOARDS_INFINITY_ERGODOX_INFINITY_ERGODOX_H_
#define KEYBOARDS_INFINITY_ERGODOX_INFINITY_ERGODOX_H_

#include "quantum.h"

#define KEYMAP( \
    A80, A70, A60, A50, A40, A30, A20,  \
    A81, A71, A61, A51, A41, A31, A21,  \
    A82, A72, A62, A52, A42, A32,       \
    A83, A73, A63, A53, A43, A33, A23,  \
    A84, A74, A64, A54, A44,            \
                                  A13, A03, \
                                       A04, \
                             A34, A24, A14, \
         B20, B30, B40, B50, B60, B70, B80, \
         B21, B31, B41, B51, B61, B71, B81, \
              B32, B42, B52, B62, B72, B82, \
         B23, B33, B43, B53, B63, B73, B83, \
                   B44, B54, B64, B74, B84, \
    B03, B13,     \
    B04,          \
    B14, B24, B34 \
) { \
    { KC_NO,    KC_NO,    KC_NO,    KC_##A03, KC_##A04 }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_##A13, KC_##A14 }, \
    { KC_##A20, KC_##A21, KC_NO,    KC_##A23, KC_##A24 }, \
    { KC_##A30, KC_##A31, KC_##A32, KC_##A33, KC_##A34 }, \
    { KC_##A40, KC_##A41, KC_##A42, KC_##A43, KC_##A44 }, \
    { KC_##A50, KC_##A51, KC_##A52, KC_##A53, KC_##A54 }, \
    { KC_##A60, KC_##A61, KC_##A62, KC_##A63, KC_##A64 }, \
    { KC_##A70, KC_##A71, KC_##A72, KC_##A73, KC_##A74 }, \
    { KC_##A80, KC_##A81, KC_##A82, KC_##A83, KC_##A84 }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_##B03, KC_##B04 }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_##B13, KC_##B14 }, \
    { KC_##B20, KC_##B21, KC_NO,    KC_##B23, KC_##B24 }, \
    { KC_##B30, KC_##B31, KC_##B32, KC_##B33, KC_##B34 }, \
    { KC_##B40, KC_##B41, KC_##B42, KC_##B43, KC_##B44 }, \
    { KC_##B50, KC_##B51, KC_##B52, KC_##B53, KC_##B54 }, \
    { KC_##B60, KC_##B61, KC_##B62, KC_##B63, KC_##B64 }, \
    { KC_##B70, KC_##B71, KC_##B72, KC_##B73, KC_##B74 }, \
    { KC_##B80, KC_##B81, KC_##B82, KC_##B83, KC_##B84 }  \
}

#endif /* KEYBOARDS_INFINITY_ERGODOX_INFINITY_ERGODOX_H_ */
