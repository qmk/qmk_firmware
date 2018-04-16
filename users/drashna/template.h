#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

// Define layer names 
#define BASE 0

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  KC_MAKE,
  KC_RESET,
  NEWPLACEHOLDER  //use "NEWPLACEHOLDER for keymap specific codes
};

#endif
