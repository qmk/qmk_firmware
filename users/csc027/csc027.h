#pragma once

#include "quantum.h"
#include "defines.h"

enum custom_keycodes {
    // Layer Keycodes
    LOWER = SAFE_RANGE,
    RAISE,


    MC_first,

    // Macro Keycodes
    CUSTOM_MACROS(CUSTOM_ENUM, DROP, COMMA_DELIM),

    MC_last
};

enum custom_layers {
    _QW = 0, // Qwerty
    _RS,     // Raise
    _LW,     // Lower
    _MS,     // Mouse
    _GT,     // Git
    _CN,     // Convenience
    _GG,     // General Gaming
    _CS      // Counter-Strike: Global Offensive
};
