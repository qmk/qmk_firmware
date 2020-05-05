//#include "g/engine.h"

// Configuration options for the engine

#define C_SIZE uint32_t  // type for chord
#define COMBO_MAX 4      // Longest Combo

// Key Aliases, must fit within C_SIZE!
// These are for Ginni + Asetniop
#define FP01 STN(0)
#define FP02 STN(1)
#define FP03 STN(2)
#define FP04 STN(3)
#define FP11 STN(4)
#define FP12 STN(5)
#define FP13 STN(6)
#define FP14 STN(7)

// Mapping of QMK Keycodes to chord positions
#define ENGINE_CONFIG       \
    ENGINE_HOOK(KC_1, FP01) \
    ENGINE_HOOK(KC_2, FP02) \
    ENGINE_HOOK(KC_3, FP03) \
    ENGINE_HOOK(KC_4, FP04) \
    ENGINE_HOOK(KC_5, FP11) \
    ENGINE_HOOK(KC_6, FP12) \
    ENGINE_HOOK(KC_7, FP13) \
    ENGINE_HOOK(KC_8, FP14)
