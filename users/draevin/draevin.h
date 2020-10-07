#pragma once

#include QMK_KEYBOARD_H
#include "wrappers.h"

#define TAPPING_TOGGLE 2
#define TAPPING_TERM 150

#define _CM 0
#define _QW 1
#define _FN 2

enum custom_keys {
  CM_QW = SAFE_RANGE, // Switch between Colemak and QWERTY
};

enum taps {
  TD_CAPS = 0
};
