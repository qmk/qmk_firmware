#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

// Define layer names
#define BASE  0
#define FUNCT 1

// Macros
enum macos_keycodes {
  KC_LHPD = SAFE_RANGE,
};

// Useful Defines
#define FN_CAPS   LT(FUNCT, KC_CAPS)
// MacOS
#define MC_SLPD   LCTL(LSFT(KC_POWER))

#endif
