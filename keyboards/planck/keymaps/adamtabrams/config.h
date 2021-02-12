#pragma once


// General Configs

#define NO_ACTION_ONESHOT
#define FORCE_NKRO
#define TAPPING_TOGGLE 2


// Mouse Configs

#define MK_COMBINED


// Tap-Hold Configs

#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
#define TAPPING_FORCE_HOLD

#define TAPPING_FORCE_HOLD_PER_KEY
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CTL_T(KC_TAB):
            return true;
        case GUI_T(KC_GESC):
            return true;
        case SFT_T(KC_MINS):
            return true;
        default:
            return false;
    }
}
