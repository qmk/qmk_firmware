#pragma once

#include <quantum_keycodes.h>

#if defined(KEYMAP_SAFE_RANGE)
#define PLACEHOLDER_SAFE_RANGE KEYMAP_SAFE_RANGE
#else
#define PLACEHOLDER_SAFE_RANGE SAFE_RANGE
#endif

enum custom_keycodes {
  KC_TEST = PLACEHOLDER_SAFE_RANGE,

  KC_DO_NOT_SLEEP_START,
  KC_DO_NOT_SLEEP_STOP,

  KC_CAPS_WORD,

  NEW_SAFE_RANGE
};
