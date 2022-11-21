// Copyright 2022 Joshua Diamond josh@windowoffire.com (@spidey3)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include QMK_KEYBOARD_H

#ifdef UNICODEMAP_ENABLE

enum unicode_names {
    BUL1,
    BUL2,
    LARR,
    RARR,
    ENDASH,
    EMDASH,
    SPIDER,
    SAD,
    MEH,
    HAPPY,
    ANGRY,
    THUMBUP,
    THUMBDN,
    LOL,
    SURPRISE,
};

#    define X_BUL (XP(BUL1, BUL2))
#    define X_DASH (XP(EMDASH, ENDASH))

#endif
