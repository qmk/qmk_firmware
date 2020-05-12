#include "curry.h"
#include "leader.h"

LEADER_EXTERNS();

void matrix_scan_user(void) {
    static bool has_ran_yet;
    if (!has_ran_yet) {
        has_ran_yet = true;
        startup_user();
    }

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    matrix_scan_rgb();
#endif  // RGBLIGHT_ENABLE
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();
        SEQ_ONE_KEY(KC_F) { SEND_STRING(SS_LCTL("akf")); } // Select all and format
        SEQ_ONE_KEY(KC_P) { SEND_STRING(SS_LCTL(SS_LSFT("4"))); } // Screenshot region
        SEQ_TWO_KEYS(KC_D, KC_D) { SEND_STRING(SS_LCTL("ac")); } // Copy all
    }
    matrix_scan_keymap();
}
