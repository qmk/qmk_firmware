// Copyright 2023 @miketronic -- Mike B <mxb540@gmail.com>
// SPDX-License-Identifier: GPL-2.0+

#pragma once

#    define USB_POLLING_INTERVAL_MS 1
#    undef  RGBLIGHT_HUE_STEP
#    define RGBLIGHT_HUE_STEP 1
#    undef  RGBLIGHT_SAT_STEP
#    define RGBLIGHT_SAT_STEP 1
#    undef  RGBLIGHT_VAL_STEP
#    define RGBLIGHT_VAL_STEP 1
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_LAYERS
#    define FORCE_NKRO

#    define TAPPING_TERM 160
#    define TAPPING_TERM_PER_KEY
#    define PERMISSIVE_HOLD_PER_KEY
#    define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#    define QUICK_TAP_TERM TAPPING_TERM / 2
#    define QUICK_TAP_TERM_PER_KEY
#    define IGNORE_MOD_TAP_INTERRUPT

#    define LEADER_NO_TIMEOUT
#    define LEADER_TIMEOUT 300
#    define LEADER_PER_KEY_TIMING



