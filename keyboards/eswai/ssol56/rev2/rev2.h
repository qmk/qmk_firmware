#ifndef KEYBOARDS_MODULO_REV2_H_
#define KEYBOARDS_MODULO_REV2_H_

#include "quantum.h"

#define LAYOUT(   \
        L00, L01, L02, L03, L04, L05, L06, R00, R01, R02, R03, R04, R05, R06, \
        L07, L08, L09, L10, L11, L12, L13, R07, R08, R09, R10, R11, R12, R13, \
        L14, L15, L16, L17, L18, L19, L20, R14, R15, R16, R17, R18, R19, R20, \
        L21, L22, L23, L24, L25, L26, L27, R21, R22, R23, R24, R25, R26, R27 \
        ) \
        { \
                { L22,   L21,   L15, L14, L08, L07, L00, L01, KC_NO, L03, L10, L23, L16, L09, L02, KC_NO }, \
                { KC_NO, KC_NO, L11, L04, L18, L25, L24, L17,   L06, L13, L20, L27, L05, L12, L19, L26   }, \
                { R22,   R21,   R15, R14, R08, R07, R00, R01, KC_NO, R03, R10, R23, R16, R09, R02, KC_NO }, \
                { KC_NO, KC_NO, R11, R04, R18, R25, R24, R17,   R06, R13, R20, R27, R05, R12, R19, R26 } \
        }

#endif /* KEYBOARDS_MODULO_REV2_H_ */
