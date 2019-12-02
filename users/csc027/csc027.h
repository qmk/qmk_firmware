#pragma once

#include "quantum.h"
#include "defines.h"

enum custom_keycodes {
    // Layer Keycodes
    LOWER = SAFE_RANGE,
    RAISE,

    // Macro Keycodes
    GIT_MACROS(GIT_ENUM, DROP, COMMA_DELIM),
    CUSTOM_MACROS(CUSTOM_ENUM, COMMA_DELIM)
};

enum custom_layers {
    _QW = 0, // Qwerty
    _RS,     // Raise
    _LW,     // Lower
    _MS,     // Mouse
    _GT,     // Git
    _CN,     // Convenience
    _GW,     // Guild Wars 2
    _CS      // Counter-Strike: Global Offensive
};
