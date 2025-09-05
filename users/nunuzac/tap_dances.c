#include "tap_dances.h"
#include "nunuzac.h"

#define ACTION_TAP_AND_HOLD_DANCE(kc1, kc2)                   \
    {                                                         \
        .fn        = {NULL, tap_and_hold_dance_end, NULL},    \
        .user_data = (void *)&((tap_dance_pair_t){kc1, kc2}), \
    }

#define ACTION_TILDE_DANCE(kc1, kc2)                          \
    {                                                         \
        .fn        = {NULL, tilde_dance_end, NULL},           \
        .user_data = (void *)&((tap_dance_pair_t){kc1, kc2}), \
    }

#define ACTION_SHORTCUT_DANCE(sc1, sc2)                      \
    {                                                        \
        .fn        = {NULL, shortcut_dance_end, NULL},       \
        .user_data = (void *)&((shortcut_pair_t){sc1, sc2}), \
    }


typedef struct shortcut_pair {
    shortcut_t sc1;
    shortcut_t sc2;
} shortcut_pair_t;

void tilde_dance_end(tap_dance_state_t *state, void *user_data) {
    tap_dance_pair_t *pair = (tap_dance_pair_t *)user_data;
    switch (state->count) {
        case 1:
            if(state->pressed)
                tap_code16(S(pair->kc1));
            else
                tap_code16(pair->kc1);
        break;
        case 2:
            if(state->pressed) {
                tap_code16(pair->kc2);
                tap_code16(pair->kc1);
            } else {
                tap_code16(pair->kc1);
                tap_code16(pair->kc1);
            }
        break;
        case 3:
            if(state->pressed) {
                tap_code16(pair->kc2);
                tap_code16(S(pair->kc1));
            } else {
                tap_code16(pair->kc1);
                tap_code16(pair->kc1);
                tap_code16(pair->kc1);
            }
        break;
        default:
            for(int i = 0; i < state->count; i++)
                tap_code16(pair->kc1);
        break;
    }
}

void tap_and_hold_dance_end(tap_dance_state_t *state, void *user_data) {
    tap_dance_pair_t *pair = (tap_dance_pair_t *)user_data;
    uint16_t to_press = state->pressed ? pair->kc2 : pair->kc1;
    for(int i = 0; i < state->count; i++)
        tap_code16(to_press);
}

void shortcut_dance_end(tap_dance_state_t *state, void *user_data) {
    shortcut_pair_t *scs = (shortcut_pair_t *)user_data;
    shortcut_t sc = state->pressed ? scs->sc2 : scs->sc1;
    tap_code16(get_os_shortcut(sc));
}

tap_dance_action_t tap_dance_actions[] = {
    [X_AT]        = ACTION_TILDE_DANCE(KC_A, KC_QUOT),
    [X_ET]        = ACTION_TILDE_DANCE(KC_E, KC_QUOT),
    [X_IT]        = ACTION_TILDE_DANCE(KC_I, KC_QUOT),
    [X_OT]        = ACTION_TILDE_DANCE(KC_O, KC_QUOT),
    [X_UT]        = ACTION_TILDE_DANCE(KC_U, KC_QUOT),
    [X_NT]        = ACTION_TILDE_DANCE(KC_N, KC_QUOT),
    [X_N1]        = ACTION_TAP_AND_HOLD_DANCE(KC_TILD, KC_1),
    [X_N2]        = ACTION_TAP_AND_HOLD_DANCE(KC_AT, KC_2),
    [X_N3]        = ACTION_TAP_AND_HOLD_DANCE(KC_HASH, KC_3),
    [X_N4]        = ACTION_TAP_AND_HOLD_DANCE(KC_DLR, KC_4),
    [X_N5]        = ACTION_TAP_AND_HOLD_DANCE(KC_PERC, KC_5),
    [X_N6]        = ACTION_TAP_AND_HOLD_DANCE(KC_CIRC, KC_6),
    [X_N7]        = ACTION_TAP_AND_HOLD_DANCE(KC_GRV, KC_7),
    [X_N8]        = ACTION_TAP_AND_HOLD_DANCE(KC_ASTR, KC_8),
    [X_N9]        = ACTION_TAP_AND_HOLD_DANCE(KC_EXLM, KC_9),
    [X_N0]        = ACTION_TAP_AND_HOLD_DANCE(KC_QUES, KC_0),
    [X_1N]        = ACTION_TAP_AND_HOLD_DANCE(KC_1, KC_TILD),
    [X_2N]        = ACTION_TAP_AND_HOLD_DANCE(KC_2, KC_AT),
    [X_3N]        = ACTION_TAP_AND_HOLD_DANCE(KC_3, KC_HASH),
    [X_4N]        = ACTION_TAP_AND_HOLD_DANCE(KC_4, KC_DLR),
    [X_5N]        = ACTION_TAP_AND_HOLD_DANCE(KC_5, KC_PERC),
    [X_6N]        = ACTION_TAP_AND_HOLD_DANCE(KC_6, KC_CIRC),
    [X_7N]        = ACTION_TAP_AND_HOLD_DANCE(KC_7, KC_GRV),
    [X_8N]        = ACTION_TAP_AND_HOLD_DANCE(KC_8, KC_ASTR),
    [X_9N]        = ACTION_TAP_AND_HOLD_DANCE(KC_9, KC_EXLM),
    [X_0N]        = ACTION_TAP_AND_HOLD_DANCE(KC_0, KC_QUES),
    [X_QUOTES]    = ACTION_TAP_AND_HOLD_DANCE(KC_DQT, KC_QUOT),
    [X_SLASHES]   = ACTION_TAP_AND_HOLD_DANCE(KC_SLSH, KC_BSLS),
    [X_LOGIC]     = ACTION_TAP_AND_HOLD_DANCE(KC_PIPE, KC_AMPR),
    [X_EQ_PL]     = ACTION_TAP_AND_HOLD_DANCE(KC_EQL, KC_PLUS),
    [X_LINES]     = ACTION_TAP_AND_HOLD_DANCE(KC_MINS, KC_UNDS),
    [X_COLONS]    = ACTION_TAP_AND_HOLD_DANCE(KC_SCLN, KC_COLN),
    [X_DOT_GE]    = ACTION_TAP_AND_HOLD_DANCE(KC_DOT, KC_GT),
    [X_COM_LE]    = ACTION_TAP_AND_HOLD_DANCE(KC_COMM, KC_LT),
    [X_PGUP_HOME] = ACTION_TAP_AND_HOLD_DANCE(KC_PGUP, KC_HOME),
    [X_PGDN_END]  = ACTION_TAP_AND_HOLD_DANCE(KC_PGDN, KC_END),
    [X_CURLY_BR]  = ACTION_TAP_AND_HOLD_DANCE(KC_LCBR, KC_RCBR),
    [X_ROUND_BR]  = ACTION_TAP_AND_HOLD_DANCE(KC_LPRN, KC_RPRN),
    [X_SQUARE_BR] = ACTION_TAP_AND_HOLD_DANCE(KC_LBRC, KC_RBRC),
    [X_ESC_CAPSL] = ACTION_TAP_AND_HOLD_DANCE(KC_ESC, KC_CAPS),
    [X_COPY_CUT]  = ACTION_SHORTCUT_DANCE(COPY, CUT),
    [X_PST_SV]    = ACTION_SHORTCUT_DANCE(PASTE, SAVE),
    [X_FIND_REPL] = ACTION_SHORTCUT_DANCE(FIND, REPLACE),
};

