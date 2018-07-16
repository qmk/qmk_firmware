#include QMK_KEYBOARD_H

#define MY_LESC LT(1, KC_ESC)
#define MY_RENT LT(1, KC_ENT)
#define MY_LCA TD(TD_LCA)
#define MY_RCA TD(TD_RCA)
#define MY_LGA TD(TD_LGA)
#define MY_RGA TD(TD_RGA)
#define MY_APP TD(TD_APP_HYPR)

enum {
    TD_LCA,
    TD_RCA,
    TD_LGA,
    TD_RGA,
    TD_APP_HYPR
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_60_ansi(
            KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
            KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
            MY_LESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          MY_RENT,
            KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,       
            MY_LGA,  KC_LALT, MY_LCA,                    KC_SPC,                             MY_RCA,  KC_RALT, MY_APP,  MY_RGA),

    LAYOUT_60_ansi(
            KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS,          KC_TRNS,
            KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};

enum {
    SINGLE_TAP        = 1,
    SINGLE_HOLD       = 2,
    DOUBLE_TAP        = 3,
    DOUBLE_HOLD       = 4,
    DOUBLE_SINGLE_TAP = 5,
    UNKNOWN_TAP       = 6
};

typedef struct {
    bool is_press_action;
    int state;
} tap;

int cur_dance(qk_tap_dance_state_t *state) {
    switch (state->count) {
        case 1:
            if (state->interrupted || state->pressed == 0) {
                return SINGLE_TAP;
            }
            return SINGLE_HOLD;
        case 2:
            if (state->interrupted) {
                return DOUBLE_SINGLE_TAP;
            }
            if (state->pressed) {
                return DOUBLE_HOLD;
            }
            return DOUBLE_TAP;
    }
    return UNKNOWN_TAP;
}

#define my_dance_combo(N, K1, K2)                                   \
static tap N ## _state = {                                          \
    .is_press_action = true,                                        \
    .state = 0                                                      \
};                                                                  \
                                                                    \
void N ## _finished(qk_tap_dance_state_t *state, void *user_data) { \
    N ## _state.state = cur_dance(state);                           \
    switch (N ## _state.state) {                                    \
        case SINGLE_TAP:                                            \
        case SINGLE_HOLD:                                           \
            register_code(K1);                                      \
            break;                                                  \
        case DOUBLE_TAP:                                            \
        case DOUBLE_SINGLE_TAP:                                     \
        case DOUBLE_HOLD:                                           \
            register_code(K1);                                      \
            register_code(K2);                                      \
            break;                                                  \
    }                                                               \
}                                                                   \
                                                                    \
void N ## _reset(qk_tap_dance_state_t *state, void *user_data) {    \
    switch (N ## _state.state) {                                    \
        case SINGLE_TAP:                                            \
        case SINGLE_HOLD:                                           \
            unregister_code(K1);                                    \
            break;                                                  \
        case DOUBLE_TAP:                                            \
        case DOUBLE_SINGLE_TAP:                                     \
        case DOUBLE_HOLD:                                           \
            unregister_code(K2);                                    \
            unregister_code(K1);                                    \
            break;                                                  \
    }                                                               \
    N ## _state.state = 0;                                          \
}

my_dance_combo(lca, KC_LCTL, KC_LALT)
my_dance_combo(rca, KC_RCTL, KC_RALT)
my_dance_combo(lga, KC_LGUI, KC_LALT)
my_dance_combo(rga, KC_RGUI, KC_RALT)

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_LCA] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lca_finished, lca_reset),
    [TD_RCA] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rca_finished, rca_reset),
    [TD_LGA] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lga_finished, lga_reset),
    [TD_RGA] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rga_finished, rga_reset),

    [TD_APP_HYPR] = ACTION_TAP_DANCE_DOUBLE(KC_APP, KC_HYPR)
};
