//#include "g/engine.h"

// Configuration options for the engine
#define C_SIZE uint32_t  // type for chord
#define COMBO_MAX 4      // Longest Combo

// Key Aliases, must fit within C_SIZE!
// These are for Ginni + Asetniop
#define FN STN(0)
#define PWR STN(1)
#define LSU STN(2)
#define LSD STN(3)
#define LFT STN(4)
#define LK STN(5)
#define LP STN(6)
#define LW STN(7)
#define LH STN(8)
#define LR STN(9)
#define ST1 STN(10)
#define ST2 STN(11)
#define ST3 STN(12)
#define ST4 STN(13)
#define RF STN(14)
#define RR STN(15)
#define RP STN(16)
#define RB STN(17)
#define RL STN(18)
#define RG STN(19)
#define RT STN(20)
#define RS STN(21)
#define RD STN(22)
#define RZ STN(23)

#define LNO STN(24)
#define LA STN(25)
#define LO STN(26)  // Rightmost Thumbs
#define RE STN(27)
#define RU STN(28)
#define RNO STN(29)

#define SYMB STN(30)  // Symbol Layer

// Chord to start buffering strokes
#define COMMAND_MODE (PWR | FN | RD | RZ)
//#define IN_CHORD_MASK (0xFFFF & ~(AL))      // Special keys that are used for mods

// Mapping of QMK Keycodes to chord positions
#define ENGINE_CONFIG         \
    ENGINE_HOOK(KC_LSFT, FN)  \
    ENGINE_HOOK(KC_Q, LSU)    \
    ENGINE_HOOK(KC_W, LFT)    \
    ENGINE_HOOK(KC_E, LP)     \
    ENGINE_HOOK(KC_R, LH)     \
    ENGINE_HOOK(KC_T, ST1)    \
    ENGINE_HOOK(KC_Y, ST3)    \
    ENGINE_HOOK(KC_U, RF)     \
    ENGINE_HOOK(KC_I, RP)     \
    ENGINE_HOOK(KC_O, RL)     \
    ENGINE_HOOK(KC_P, RT)     \
    ENGINE_HOOK(KC_BSPC, RD)  \
                              \
    ENGINE_HOOK(KC_CAPS, PWR) \
    ENGINE_HOOK(KC_A, LSD)    \
    ENGINE_HOOK(KC_S, LK)     \
    ENGINE_HOOK(KC_D, LW)     \
    ENGINE_HOOK(KC_F, LR)     \
    ENGINE_HOOK(KC_G, ST2)    \
    ENGINE_HOOK(KC_H, ST4)    \
    ENGINE_HOOK(KC_J, RR)     \
    ENGINE_HOOK(KC_K, RB)     \
    ENGINE_HOOK(KC_L, RG)     \
    ENGINE_HOOK(KC_SCLN, RS)  \
    ENGINE_HOOK(KC_ENT, RZ)   \
                              \
    ENGINE_HOOK(KC_X, LNO)    \
    ENGINE_HOOK(KC_C, LA)     \
    ENGINE_HOOK(KC_V, LO)     \
    ENGINE_HOOK(KC_B, RE)     \
    ENGINE_HOOK(KC_N, RU)     \
    ENGINE_HOOK(KC_M, RNO)
