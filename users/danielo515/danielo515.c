#include "danielo515.h"

bool onMac = true;

//**************** LEADER *********************//
#ifdef LEADER_ENABLE
LEADER_EXTERNS();
#    ifdef RGBLIGHT_ENABLE

void leader_start_user() { rgblight_setrgb_range(5, 100, 199, 10, 15); };

void leader_end_user() { rgblight_setrgb_range(200, 200, 255, 10, 15); };
#    endif

void matrix_scan_user(void) {
    if (leading && leader_sequence_size > 0 && timer_elapsed(leader_time) > LEADER_TIMEOUT) {
        leading = false;
        SEQ_ONE_KEY(KC_T) { SEND_STRING("``" SS_TAP(X_LEFT)); }
        // Triple ticks
        SEQ_TWO_KEYS(KC_T, KC_T) { SEND_STRING("```" SS_TAP(X_ENTER) SS_TAP(X_ENTER) "```" SS_TAP(X_UP)); }
        // ==== International spanish accent vowels ====
        SEQ_ONE_KEY(KC_A) { SEND_STRING(SS_LALT("e") "a"); }
        SEQ_ONE_KEY(KC_E) { SEND_STRING(SS_LALT("e") "e"); }
        SEQ_ONE_KEY(KC_I) { SEND_STRING(SS_LALT("e") "i"); }
        SEQ_ONE_KEY(KC_O) { SEND_STRING(SS_LALT("e") "o"); }
        SEQ_ONE_KEY(KC_U) { SEND_STRING(SS_LALT("e") "u"); }
        SEQ_ONE_KEY(KC_N) { SEND_STRING(SS_LALT("n") "n"); }
        // ==== MACROS ===
        SEQ_ONE_KEY(KC_G) { SEND_STRING(" | grep "); }
        SEQ_ONE_KEY(KC_K) { onMac ? SEND_STRING(SS_LCTL(" ")) : SEND_STRING(SS_LCTL("f")); }
        // vim delete all
        SEQ_TWO_KEYS(KC_D, KC_G) {
            if (onMac) {
                SEND_STRING(SS_LGUI("a") SS_TAP(X_D));
            } else {
                SEND_STRING(SS_LCTL("a") SS_TAP(X_D));
            }
        }
        // tripe delete!
        SEQ_ONE_KEY(KC_BACKSPACE) { SEND_STRING(SS_TAP(X_BACKSPACE) SS_TAP(X_BACKSPACE) SS_TAP(X_BACKSPACE)); }
        SEQ_TWO_KEYS(KC_P, KC_G) { SEND_STRING("ps -ef | grep "); }
        SEQ_TWO_KEYS(KC_J, KC_A) { SEND_STRING("() => {}" SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT)); }
        // this is a pain to type
        SEQ_TWO_KEYS(KC_S, KC_S) { SEND_STRING("~/.ssh/ "); }
        SEQ_TWO_KEYS(KC_F, KC_T) { SEND_STRING("feat():" SS_TAP(X_LEFT) SS_TAP(X_LEFT)); }
        // ### LAYER CHANGE
        SEQ_ONE_KEY(KC_1) { layer_on(1); }
        // control enter, because yes
        SEQ_ONE_KEY(KC_H) { SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_ENTER) SS_UP(X_LCTL)); }
        // paste all
        SEQ_ONE_KEY(KC_P) {
            if (onMac) {
                SEND_STRING(SS_LGUI("a") SS_LGUI("v"));
            } else {
                SEND_STRING(SS_LCTL("a") SS_LCTL("v"));
            }
        }
        SEQ_THREE_KEYS(KC_M, KC_A, KC_C) {
            onMac = true;
#    ifdef RGBLIGHT_ENABLE
            rgblight_setrgb(255, 255, 255);
#    endif
        }
        SEQ_THREE_KEYS(KC_W, KC_I, KC_N) {
            onMac = false;
#    ifdef RGBLIGHT_ENABLE
            rgblight_setrgb(255, 255, 0);
#    endif
        }
        /*  Copy all */
        SEQ_ONE_KEY(KC_Y) {
            if (onMac) {
                SEND_STRING(SS_LGUI("a") SS_LGUI("c"));
            } else {
                SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
            }
        }
        // emoji bar
        SEQ_TWO_KEYS(KC_E, KC_E) { SEND_STRING(SS_DOWN(X_LGUI) SS_LCTL(" ") SS_UP(X_LGUI)); }

        SEQ_TWO_KEYS(KC_F, KC_F) { SEND_STRING("ps -ef | grep "); }
        SEQ_TWO_KEYS(KC_H, KC_T) { SEND_STRING("https://"); }

        leader_end();
    }
}
#endif  // LEADER
