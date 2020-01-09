#pragma once

#include QMK_KEYBOARD_H

enum unicode_names {
    BUL1,
    BUL2,
    LARR,
    RARR,
    ENDASH,
    EMDASH,
};

#define X_BUL (XP(BUL1, BUL2))
#define X_DASH (XP(ENDASH, EMDASH))

