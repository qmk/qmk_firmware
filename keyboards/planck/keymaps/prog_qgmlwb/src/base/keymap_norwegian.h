#pragma once

#include "keymap_extras/keymap_norwegian.h"
#include "../base.h"

// WRONG: |, ^, ", ~, `
// Norwegian layout fix
// #undef NO_QUOT
// #define NO_QUOT KC_BSLS  // '
// #undef NO_TILD
// #define NO_TILD RALT(KC_RBRC)  // ~

// Better norwegian defines
#undef NO_LESS
#define NO_LESS KC_NUBS // <
#undef NO_GRTR
#define NO_GRTR S(NO_LESS) // >
#undef NO_AE
#define NO_AE KC_QUOT // Æ
#undef NO_OE
#define NO_OE KC_SCLN // Ø
#undef NO_AA
#define NO_AA KC_LBRC // Å

// Shift layout fix
// #undef NO_SQUOT
// #define NO_SQUOT KC_AT  // "
// #undef NO_SBSLS
// #define NO_SBSLS KC_GRAVE  // |
