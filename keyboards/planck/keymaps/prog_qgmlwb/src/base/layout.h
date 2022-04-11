#pragma once

#include "../base.h"

// Layouts enum
enum keyboard_layouts {
    QGMLW_NO,
    QGMLW_US,
    QWERTY,
    COLEMAK,
    DVORAK,

    NORMAL_LOWER,
    NORMAL_RAISE,

    NUMPAD,

    QGMLW_NO_LOWER,
    QGMLW_US_LOWER,

    QGMLW_NO_RAISE,
    QGMLW_US_RAISE,

    ADJUST
};

// Layouts keycodes
#define lower MO(NORMAL_LOWER)
#define raise MO(NORMAL_RAISE)

#define numpad MO(NUMPAD)

#define QNLower MO(QGMLW_NO_LOWER)
#define QELower MO(QGMLW_US_LOWER)

#define QNRaise MO(QGMLW_NO_RAISE)
#define QERaise MO(QGMLW_US_RAISE)

#define adjust MO(ADJUST)
