#pragma once

#include "quantum.h"
#include "defines.h"

enum custom_keycodes {
    // Layer Keycodes
    LOWER = SAFE_RANGE,
    RAISE,

    // Git Keycodes
    GIT_ADD, // Add
    GIT_BRC, // Branch
    GIT_CHK, // Checkout
    GIT_CHR, // Cherry-Pick
    GIT_CMT, // Commit
    GIT_DIF, // Diff
    GIT_FTC, // Fetch
    GIT_GRP, // Grep
    GIT_LOG, // Log
    GIT_INT, // Init
    GIT_MRG, // Merge
    GIT_MOV, // Move (mv)
    GIT_PSH, // Push
    GIT_PUL, // Pull
    GIT_RBS, // Rebase
    GIT_RMT, // Remote
    GIT_RST, // Reset
    GIT_SHW, // Show
    GIT_STH, // Stash
    GIT_STS, // Status
    GIT_TAG, // Tag

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
