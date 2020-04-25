#include "g/engine.h"

// Configuration options for the engine

#define C_SIZE uint16_t             // type for chord
#define COMBO_MAX 4                     // Longest Combo

// Key Aliases, must fit within C_SIZE!
// These are for Ginni + Asetniop
#define AA      STN(0)
#define AS      STN(1)
#define AE      STN(2)
#define AT      STN(3)
#define AN      STN(4)
#define AI      STN(5)
#define AO      STN(6)
#define AP      STN(7)
#define AL      STN(8)                  // Left/Right thumbs
#define AR      STN(9)
#define NUM     STN(10)                 // Sticky Layer 1
#define USR     STN(11)                 // Sticky Layer 2
#define CMD     STN(12)                 // Sticky Layer 3
#define RGT     STN(13)                 // Right Hand chord

// Chord to start buffering strokes
#define COMMAND_MODE    (AI | AN | AT | AE)
#define IN_CHORD_MASK (0xFFFF & ~(AL))      // Special keys that are used for mods

// Mapping of QMK Keycodes to chord positions
#define ENGINE_CONFIG               \
        ENGINE_HOOK(KC_A, AA)       \
        ENGINE_HOOK(KC_S, AS)       \
        ENGINE_HOOK(KC_E, AE)       \
        ENGINE_HOOK(KC_T, AT)       \
        ENGINE_HOOK(KC_N, AN)       \
        ENGINE_HOOK(KC_I, AI)       \
        ENGINE_HOOK(KC_O, AO)       \
        ENGINE_HOOK(KC_P, AP)       \
        ENGINE_HOOK(KC_L, AL)       \
        ENGINE_HOOK(KC_R, AR)       

