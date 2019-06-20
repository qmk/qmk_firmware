#pragma once
#include "brandonschlack.h"
#ifdef TAP_DANCE_ENABLE
#   include "process_keycode/process_tap_dance.h"
#endif

enum bs_dances {
    TD_LGHT_LSFT,
    TD_ESC_RGBTG,
    TD_SHLD_LGHT,
    TD_SHLD_MAGC,
    TD_DTAP_MAGC,
    TD_REDR_H
};

enum tap_dance_states {
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP = 3,
    DOUBLE_HOLD = 4,
    DOUBLE_SINGLE_TAP = 5,
    TRIPLE_TAP = 6,
    TRIPLE_HOLD = 7
};

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
#   define SFT_LGT TD(TD_LGHT_LSFT)
#   define ESC_RTG TD(TD_ESC_RGBTG)
#endif

int cur_dance (qk_tap_dance_state_t *state);
void process_tap_dance_keycode (bool reset, uint8_t toggle_layer);
