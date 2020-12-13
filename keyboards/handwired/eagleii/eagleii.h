#pragma once

#include "quantum.h"

#define LAYOUT( \
    K47,   K27, K37, K38, K28, K39, K29, K34, K24, K31, K21, K32, K22, K33, K23,      K0A, K0B, K46,      K44, \
    K17,      K97, K18, K98, K19, K99, K14, K94, K11, K91, K12, K92, K13, K83,        K8A, K8B, K43,      K4A, \
     KA0,      K77, K88, K78, K89, K79, K84, K74, K81, K71, K82, K72, K93,            K1A, K1B, K42,      K6B, \
       K50,      K87, K08, K68, K09, K69, K04, K61, K01, K62, K02, K70,               K6A,      K41,           \
       KB5, K66, K07,                 K64,                    K76, K03                                         \
) { \
    { KC_NO, K01,   K02,   K03,   K04,   KC_NO, KC_NO, K07,   K08,   K09,   K0A,   K0B   }, \
    { KC_NO, K11,   K12,   K13,   K14,   KC_NO, KC_NO, K17,   K18,   K19,   K1A,   K1B   }, \
    { KC_NO, K21,   K22,   K23,   K24,   KC_NO, KC_NO, K27,   K28,   K29,   KC_NO, KC_NO }, \
    { KC_NO, K31,   K32,   K33,   K34,   KC_NO, KC_NO, K37,   K38,   K39,   KC_NO, KC_NO }, \
    { KC_NO, K41,   K42,   K43,   K44,   KC_NO, K46,   K47,   KC_NO, KC_NO, K4A,   KC_NO }, \
    { K50,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, K61,   K62,   KC_NO, K64,   KC_NO, K66,   KC_NO, K68,   K69,   K6A,   K6B   }, \
    { K70,   K71,   K72,   KC_NO, K74,   KC_NO, K76,   K77,   K78,   K79,   KC_NO, KC_NO }, \
    { KC_NO, K81,   K82,   K83,   K84,   KC_NO, KC_NO, K87,   K88,   K89,   K8A,   K8B   }, \
    { KC_NO, K91,   K92,   K93,   K94,   KC_NO, KC_NO, K97,   K98,   K99,   KC_NO, KC_NO }, \
    { KA0,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KB5,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
}
