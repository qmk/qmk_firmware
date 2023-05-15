#include "danielo515.h"

bool onMac = true;

//**************** LEADER *********************//
#ifdef LEADER_ENABLE
void leader_start_user(vodi) {
#    ifdef RGBLIGHT_ENABLE
    rgblight_setrgb_range(5, 100, 199, 10, 15);
#    endif
}

void leader_end_user() {
    if (leader_sequence_one_key(KC_T)) {
        SEND_STRING("``" SS_TAP(X_LEFT));
    }
    // Triple ticks
    if (leader_sequence_two_keys(KC_T, KC_T)) {
        SEND_STRING("```" SS_TAP(X_ENTER) SS_TAP(X_ENTER) "```" SS_TAP(X_UP));
    }
    // ==== International spanish accent vowels ====
    if (leader_sequence_one_key(KC_A)) {
        SEND_STRING(SS_LALT("e") "a");
    }
    if (leader_sequence_one_key(KC_E)) {
        SEND_STRING(SS_LALT("e") "e");
    }
    if (leader_sequence_one_key(KC_I)) {
        SEND_STRING(SS_LALT("e") "i");
    }
    if (leader_sequence_one_key(KC_O)) {
        SEND_STRING(SS_LALT("e") "o");
    }
    if (leader_sequence_one_key(KC_U)) {
        SEND_STRING(SS_LALT("e") "u");
    }
    if (leader_sequence_one_key(KC_N)) {
        SEND_STRING(SS_LALT("n") "n");
    }
    // ==== MACROS ===
    if (leader_sequence_one_key(KC_G)) {
        SEND_STRING(" | grep ");
    }
    if (leader_sequence_one_key(KC_K)) {
        onMac ? SEND_STRING(SS_LCTL(" ")) : SEND_STRING(SS_LCTL("f"));
    }
    // vim delete all
    if (leader_sequence_two_keys(KC_D, KC_G)) {
        if (onMac) {
            SEND_STRING(SS_LGUI("a") SS_TAP(X_D));
        } else {
            SEND_STRING(SS_LCTL("a") SS_TAP(X_D));
        }
    }
    // tripe delete!
    if (leader_sequence_one_key(KC_BACKSPACE)) {
        SEND_STRING(SS_TAP(X_BACKSPACE) SS_TAP(X_BACKSPACE) SS_TAP(X_BACKSPACE));
    }
    if (leader_sequence_two_keys(KC_P, KC_G)) {
        SEND_STRING("ps -ef | grep ");
    }
    if (leader_sequence_two_keys(KC_J, KC_A)) {
        SEND_STRING("() => {}" SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT));
    }
    // this is a pain to type
    if (leader_sequence_two_keys(KC_S, KC_S)) {
        SEND_STRING("~/.ssh/ ");
    }
    if (leader_sequence_two_keys(KC_F, KC_T)) {
        SEND_STRING("feat():" SS_TAP(X_LEFT) SS_TAP(X_LEFT));
    }
    // ### LAYER CHANGE
    if (leader_sequence_one_key(KC_1)) {
        layer_on(1);
    }
    // control enter, because yes
    if (leader_sequence_one_key(KC_H)) {
        SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_ENTER) SS_UP(X_LCTL));
    }
    // paste all
    if (leader_sequence_one_key(KC_P)) {
        if (onMac) {
            SEND_STRING(SS_LGUI("a") SS_LGUI("v"));
        } else {
            SEND_STRING(SS_LCTL("a") SS_LCTL("v"));
        }
    }
    if (leader_sequence_three_keys(KC_M, KC_A, KC_C)) {
        onMac = true;
#    ifdef RGBLIGHT_ENABLE
        rgblight_setrgb(255, 255, 255);
#    endif
    }
    if (leader_sequence_three_keys(KC_W, KC_I, KC_N)) {
        onMac = false;
#    ifdef RGBLIGHT_ENABLE
        rgblight_setrgb(255, 255, 0);
#    endif
    }
    /*  Copy all */
    if (leader_sequence_one_key(KC_Y)) {
        if (onMac) {
            SEND_STRING(SS_LGUI("a") SS_LGUI("c"));
        } else {
            SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
        }
    }
    // emoji bar
    if (leader_sequence_two_keys(KC_E, KC_E)) {
        SEND_STRING(SS_DOWN(X_LGUI) SS_LCTL(" ") SS_UP(X_LGUI));
    }

    if (leader_sequence_two_keys(KC_F, KC_F)) {
        SEND_STRING("ps -ef | grep ");
    }
    if (leader_sequence_two_keys(KC_H, KC_T)) {
        SEND_STRING("https://");
    }

#    ifdef RGBLIGHT_ENABLE
    rgblight_setrgb_range(200, 200, 255, 10, 15);
#    endif
}
#endif  // LEADER
