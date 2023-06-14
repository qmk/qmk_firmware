#include "curry.h"
#include "leader_user.h"

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_F)) {
        // Select all and format
        SEND_STRING(SS_LCTL("akf"));
    }
    if (leader_sequence_one_key(KC_P)) {
        // Screenshot region
        SEND_STRING(SS_LCTL(SS_LSFT("4")));
    }
    if (leader_sequence_two_keys(KC_D, KC_D)) {
        // Copy all
        SEND_STRING(SS_LCTL("ac"));
    }
}

void matrix_scan_user(void) {
    static bool has_ran_yet;
    if (!has_ran_yet) {
        has_ran_yet = true;
        startup_user();
    }

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    matrix_scan_rgb();
#endif  // RGBLIGHT_ENABLE

    matrix_scan_keymap();
}
