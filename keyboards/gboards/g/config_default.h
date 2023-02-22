#include "engine.h"

// Configuration options for the engine

#define C_SIZE uint64_t  // type for chord
#define COMBO_MAX 4      // Longest Combo

// Key Aliases, must fit within C_SIZE!
// These are for Ginni + Asetniop
#define GQ STN(0)
#define GW STN(1)
#define GE STN(2)
#define GR STN(3)
#define GT STN(4)
#define GY STN(5)
#define GU STN(6)
#define GI STN(7)
#define GO STN(8)
#define GP STN(9)

#define GA STN(10)
#define GS STN(11)
#define GD STN(12)
#define GF STN(13)
#define GG STN(14)
#define GH STN(15)
#define GJ STN(16)
#define GK STN(17)
#define GL STN(18)
#define GCL STN(19)

#define GZ STN(20)
#define GX STN(21)
#define GC STN(22)
#define GV STN(23)
#define GB STN(24)
#define GN STN(25)
#define GM STN(26)
#define GLT STN(27)
#define GGT STN(28)
#define GQU STN(29)

#define GL1 STN(30)
#define GL2 STN(31)
#define GL3 STN(32)
#define GR3 STN(33)
#define GR2 STN(34)
#define GR1 STN(35)

// Chord to start buffering strokes
#define COMMAND_MODE (GL1 | GR1)

// Mapping of QMK Keycodes to chord positions
#define ENGINE_CONFIG         \
    ENGINE_HOOK(KC_Q, GQ)     \
    ENGINE_HOOK(KC_W, GW)     \
    ENGINE_HOOK(KC_E, GE)     \
    ENGINE_HOOK(KC_R, GR)     \
    ENGINE_HOOK(KC_T, GT)     \
    ENGINE_HOOK(KC_Y, GY)     \
    ENGINE_HOOK(KC_U, GU)     \
    ENGINE_HOOK(KC_I, GI)     \
    ENGINE_HOOK(KC_O, GO)     \
    ENGINE_HOOK(KC_P, GP)     \
    ENGINE_HOOK(KC_A, GA)     \
    ENGINE_HOOK(KC_S, GS)     \
    ENGINE_HOOK(KC_D, GD)     \
    ENGINE_HOOK(KC_F, GF)     \
    ENGINE_HOOK(KC_G, GG)     \
    ENGINE_HOOK(KC_H, GH)     \
    ENGINE_HOOK(KC_J, GJ)     \
    ENGINE_HOOK(KC_K, GK)     \
    ENGINE_HOOK(KC_L, GL)     \
    ENGINE_HOOK(KC_SCLN, GCL) \
    ENGINE_HOOK(KC_Z, GZ)     \
    ENGINE_HOOK(KC_X, GX)     \
    ENGINE_HOOK(KC_C, GC)     \
    ENGINE_HOOK(KC_V, GV)     \
    ENGINE_HOOK(KC_B, GB)     \
    ENGINE_HOOK(KC_N, GN)     \
    ENGINE_HOOK(KC_M, GM)     \
    ENGINE_HOOK(KC_COMM, GLT) \
    ENGINE_HOOK(KC_DOT, GGT)  \
    ENGINE_HOOK(KC_SLSH, GQU) \
    ENGINE_HOOK(KC_F1, GL1)   \
    ENGINE_HOOK(KC_F2, GL2)   \
    ENGINE_HOOK(KC_F3, GL3)   \
    ENGINE_HOOK(KC_F4, GR3)   \
    ENGINE_HOOK(KC_F5, GR2)   \
    ENGINE_HOOK(KC_F6, GR1)
