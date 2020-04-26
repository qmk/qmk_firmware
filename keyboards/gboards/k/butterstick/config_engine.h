//#include "g/engine.h"

// Configuration options for the engine

#define C_SIZE uint32_t             // type for chord
#define COMBO_MAX 4                 // Longest Combo

// Key Aliases, must fit within C_SIZE!
// These are for Ginni + Asetniop
#define KQ       STN(0)
#define KW       STN(1)
#define KE       STN(2)
#define KR       STN(3)
#define KT       STN(4)
#define KY       STN(5)
#define KU       STN(6)
#define KI       STN(7)
#define KO       STN(8)
#define KP       STN(9)

#define KA       STN(10)
#define KS       STN(11)
#define KD       STN(12)
#define KF       STN(13)
#define KG       STN(14)
#define KH       STN(15)
#define KJ       STN(16)
#define KK       STN(17)
#define KL       STN(18)
#define KC       STN(19)

#define COMMAND_MODE (KQ | KA | KP | KC)

// Mapping of QMK Keycodes to chord positions
#define ENGINE_CONFIG                    \
        ENGINE_HOOK(KC_Q,      KQ)       \
        ENGINE_HOOK(KC_W,      KW)       \
        ENGINE_HOOK(KC_E,      KE)       \
        ENGINE_HOOK(KC_R,      KR)       \
        ENGINE_HOOK(KC_T,      KT)       \
        ENGINE_HOOK(KC_Y,      KY)       \
        ENGINE_HOOK(KC_U,      KU)       \
        ENGINE_HOOK(KC_I,      KI)       \
        ENGINE_HOOK(KC_O,      KO)       \
        ENGINE_HOOK(KC_P,      KP)       \
                                         \
        ENGINE_HOOK(KC_A,      KA)       \
        ENGINE_HOOK(KC_S,      KS)       \
        ENGINE_HOOK(KC_D,      KD)       \
        ENGINE_HOOK(KC_F,      KF)       \
        ENGINE_HOOK(KC_G,      KG)       \
        ENGINE_HOOK(KC_H,      KH)       \
        ENGINE_HOOK(KC_J,      KJ)       \
        ENGINE_HOOK(KC_K,      KK)       \
        ENGINE_HOOK(KC_L,      KL)       \
        ENGINE_HOOK(KC_C,      KC)   
