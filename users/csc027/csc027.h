#pragma once

#include "quantum.h"
#include "defines.h"

enum custom_keycodes {
    // Layer Keycodes
    LOWER = SAFE_RANGE,
    RAISE,

    // Git Keycodes
    GIT_MACROS(GIT_ENUM, DROP, DROP, COMMA_DELIM),

    // Remote Desktop
    MC_MRD7, // Minimize Remote Desktop on Windows 7
    MC_MRD8, // Minimize Remote Desktop on Windows 8+
    MC_ATRD  // Switch windows on local machine from Remote Desktop on Windows
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
