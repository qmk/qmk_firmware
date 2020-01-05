#include "tapDance.h"

#include "quantum.h"

void left(qk_tap_dance_state_t* state, void* user_data) {
    switch (state->count) {
        case 1:
            if (state->pressed)
                tap_code16(S(KC_LBRACKET));
            else
                tap_code16(S(KC_9));
            break;
        case 2:
            if (state->pressed)
                tap_code16(S(KC_COMM));
            else
                tap_code(KC_LBRACKET);
            break;
        default:
            reset_tap_dance(state);
    }
}

void right(qk_tap_dance_state_t* state, void* user_data) {
    switch (state->count) {
        case 1:
            if (state->pressed)
                tap_code16(S(KC_RBRACKET));
            else
                tap_code16(S(KC_0));
            break;
        case 2:
            if (state->pressed)
                tap_code16(S(KC_DOT));
            else
                tap_code(KC_RBRACKET);
            break;
        default:
            reset_tap_dance(state);
    }
}

enum { REST, HOLD1, HOLD2, HOLD3 };

static int Alt = REST;
void       altFinish(qk_tap_dance_state_t* state, void* user_data) {
    switch (state->count) {
        case 1:
            if (state->pressed) {
                register_code(KC_LALT);
                Alt = HOLD1;
            } else {
                tap_code(KC_TAB);
            }
            break;
        case 2:
            if (state->pressed) {
                register_code(KC_RALT);
                Alt = HOLD2;
            }
            break;
        case 3:
            if (state->pressed) {
                register_code(KC_RALT);
                register_code(KC_RSHIFT);
                Alt = HOLD3;
            }
            break;
        default:
            reset_tap_dance(state);
    }
}

void altReset(qk_tap_dance_state_t* state, void* user_data) {
    switch (Alt) {
        case HOLD1:
            unregister_code(KC_LALT);
            break;
        case HOLD2:
            unregister_code(KC_RALT);
            break;
        case HOLD3:
            unregister_code(KC_RSHIFT);
            unregister_code(KC_RALT);
            break;
    }
    Alt = REST;
}

static int Ctrl = REST;
void       ctrlFinish(qk_tap_dance_state_t* state, void* user_data) {
    switch (state->count) {
        case 1:
            if (state->pressed) {
                register_code(KC_LCTL);
                Ctrl = HOLD1;
            } else {
                tap_code(KC_ESC);
            }
            break;
        case 2:
            if (state->pressed) {
                register_code(KC_LGUI);
                Ctrl = HOLD2;
            }
            break;
        default:
            reset_tap_dance(state);
    }
}

void ctrlReset(qk_tap_dance_state_t* state, void* user_data) {
    switch (Ctrl) {
        case HOLD1:
            unregister_code(KC_LCTL);
            break;
        case HOLD2:
            unregister_code(KC_LGUI);
            break;
    }
    Ctrl = REST;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [ALT]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, altFinish, altReset),
    [CTRL]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctrlFinish, ctrlReset),
    [LEFT]  = ACTION_TAP_DANCE_FN(left),
    [RIGHT] = ACTION_TAP_DANCE_FN(right),
};
