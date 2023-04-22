// Copyright 2023 @miketronic -- Mike B <mxb540@gmail.com>
// SPDX-License-Identifier: GPL-2.0+

#pragma once

// specific defines example
// #if defined(TAP_DANCE_ENABLE) && defined(KEYBOARD_lets_split_rev2) || defined(KEYBOARD_keebio_iris_rev2)

// Common QMK settings
#define DEBOUNCE 10
#if defined(TAP_DANCE_ENABLE)
#    define TAP_CODE_DELAY 5
#    define TAP_HOLD_CAPS_DELAY 25
#endif
#define ENCODER_RESOLUTION 4
#define MACRO_TIMER 5

//////////////
// For Pi40 //
//////////////
#if defined(KEYBOARD_1upkeyboards_pi40_mit_v1_0)

// Tapping Config
// https://docs.qmk.fm/#/tap_hold?id=tapping_term
// https://docs.qmk.fm/#/ChangeLog/20230226?id=quick-tap-term

// Tap-hold settings
#    if defined(TAP_DANCE_ENABLE)
#        define TAPPING_TERM 170
#        define TAPPING_TERM_PER_KEY
#        define QUICK_TAP_TERM TAPPING_TERM / 2
#        define QUICK_TAP_TERM_PER_KEY
#    endif

#    define PERMISSIVE_HOLD_PER_KEY
#    define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

#endif

////////////////
// For SATPAD //
////////////////
#if defined(KEYBOARD_hazel_satpad)

// Tap-hold settings
#    if defined(TAP_DANCE_ENABLE)
#        define TAPPING_TERM 170
#        define TAPPING_TERM_PER_KEY
#        define QUICK_TAP_TERM TAPPING_TERM / 2
#        define QUICK_TAP_TERM_PER_KEY
#    endif

#    define PERMISSIVE_HOLD_PER_KEY
#    define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

#endif
