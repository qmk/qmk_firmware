#ifndef KEYBOARDS_MODULO_REV2_H_
#define KEYBOARDS_MODULO_REV2_H_

#include "quantum.h"

#define LAYOUT(   \
        L00, L01, L02, L03, L04, R00, R01, R02, R03, R04, \
        L05, L06, L07, L08, L09, R05, R06, R07, R08, R09, \
        L10, L11, L12, L13, L14, R10, R11, R12, R13, R14, \
                  L17, L18, L19, R15, R16, R17  \
        ) \
        { \
                { KC_NO, KC_NO, L06, L01, L07, L02, L12, L17, L11, KC_NO, KC_NO, L10, L05, L00, KC_NO, KC_NO }, \
                { L03, L08, L04, L09, L14, L19, L18, L13, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
                { KC_NO, KC_NO, R06, R01, R07, R02, R12, R17, R11, R16, R15, R10, R05, R00, KC_NO, KC_NO }, \
                { R03, R08, R04, R09, R14, KC_NO, KC_NO, R13, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
        }

#endif /* KEYBOARDS_MODULO_REV2_H_ */
