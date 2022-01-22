#pragma once

#include <quantum_keycodes.h>

#if defined(KEYMAP_SAFE_RANGE)
#    define PLACEHOLDER_SAFE_RANGE KEYMAP_SAFE_RANGE
#else
#    define PLACEHOLDER_SAFE_RANGE SAFE_RANGE
#endif

enum custom_keycodes {
    KC_TEST = PLACEHOLDER_SAFE_RANGE,

    KC_SECRET_1,
    KC_SECRET_2,
    KC_SECRET_3,
    KC_SECRET_4,
    KC_SECRET_5,

    KC_DO_NOT_SLEEP_START,
    KC_DO_NOT_SLEEP_STOP,

    NEW_SAFE_RANGE
};
