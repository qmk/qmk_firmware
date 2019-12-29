#pragma once

#include "kunai16.h"
#define LAYOUT(   \
        L01, L02, L03, L04, L05, R01, R02, R03, R04, R05, \
        L06, L07, L08, L09, L10, R06, R07, R08, R09, R10, \
        L11, L12, L13, L14, L15, R11, R12, R13, R14, R15, \
                  L18, L19, L20, R16, R17, R18  \
        ) \
        { \
                { KC_NO, KC_NO, L02, L03, L18, L08, L13, L07, KC_NO, L12, KC_NO, L11, L06, L01, KC_NO, KC_NO }, \
                { L04, L05, L10, L15, L20, L14, L09, L19, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
                { KC_NO, KC_NO, R02, R03, R18, R08, R13, R07, R17, R12, R16, R11, R06, R01, KC_NO, KC_NO }, \
                { R04, R05, R10, R15, KC_NO, R14, R09, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
        }
