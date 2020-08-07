#include "boboysdadda.h"
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
        SEQ_TWO_KEYS(KC_W, KC_1) {
        SEND_STRING("https://www.google.com\n");
        }
        SEQ_TWO_KEYS(KC_T, KC_1) {
        SEND_STRING("!roll all\n");
        }
        SEQ_TWO_KEYS(KC_T, KC_2) {
        SEND_STRING("!slots 5000\n");
        }
        SEQ_TWO_KEYS(KC_T, KC_3) {
        SEND_STRING("!slots 10000\n");
        }
    }
    matrix_scan_keymap();
}