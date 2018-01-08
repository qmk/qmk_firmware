#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

// Layer names
#define _BASE     0
#define _LOWER    1
#define _RAISE    2
#define _BOTH     3
#define _FUNCTION 4

enum custom_keycodes {
  USER_SAFE_RANGE = SAFE_RANGE,
  BASE,
  LOWER,
  RAISE,
  BOTH,
  FUNCTION,
  KEYMAP_SAFE_RANGE
};

// Layer keycodes
#define LOWER    M(_LOWER)
#define RAISE    M(_RAISE)
#define FUNCTION M(_FUNCTION)

// Function macro keycodes
#define ESC_CTL FUNC(0) // Tap for Esc, hold for Ctrl
#define SFT_ENT FUNC(1) // Tap for Enter, hold for Shift

#endif
