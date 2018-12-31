#ifndef ARROW_PAD_H
#define ARROW_PAD_H

#include "quantum.h"
#include "matrix.h"
#include "keymap.h"
#ifdef BACKLIGHT_ENABLE
	#include "backlight.h"
#endif
#include <avr/io.h>
#include <stddef.h>

// This is the 21-key keypad to 4x6 element matrix mapping
#define LAYOUT( \
    KM_ESC, KM_TAB, KM_BSL, KM_ARR, \
    KM_NUM, KM_FSL, KM_AST, KM_MIN, \
    KM___7, KM___8, KM___9, KM_EQU, \
    KM___4, KM___5, KM___6, KM_PLS, \
    KM___1, KM___2, KM___3, ___ENT, \
    KM___0, _____0, KM_DOT, KM_ENT  \
) { \
    { KM_ESC, KM_TAB, KM_BSL, KM_ARR  }, \
    { KM_NUM, KM_FSL, KM_AST, KM_MIN  }, \
    { KM___7, KM___8, KM___9, KM_EQU  }, \
    { KM___4, KM___5, KM___6, KM_PLS  }, \
    { KM___1, KM___2, KM___3, KC_NO   }, \
    { KM___0, KC_NO,  KM_DOT, KM_ENT  }  \
}

// This is the 21-key keypad to 2x11 element matrix mapping
#define LAYOUT_pad21( \
    KM_ESC, KM_TAB, KM_BSL, KM_ARR, \
    KM_NUM, KM_FSL, KM_AST, KM_MIN, \
    KM___7, KM___8, KM___9,         \
    KM___4, KM___5, KM___6, KM_PLS, \
    KM___1, KM___2, KM___3,         \
    KM___0,         KM_DOT, KM_ENT  \
) { \
    { KM_ESC, KM_TAB, KM_BSL, KM_ARR, KM___7, KM___8, KM___9, KM_PLS, KM___1, KM___2, KM___3, }, \
    { KM_NUM, KM_FSL, KM_AST, KM_MIN, KM___4, KM___5, KM___6, KM_ENT, KC_NO,  KM___0, KM_DOT, }, \
}

#endif
