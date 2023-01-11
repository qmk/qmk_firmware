#include QMK_KEYBOARD_H

#define MY_ESC LT(1, KC_ESC)
#define MY_ENT LT(1, KC_ENT)
#define MY_APP LT(2, KC_APP)

#define MY_LCA TD(TD_LCTL_ALT)
#define MY_RCA TD(TD_RCTL_ALT)
#define MY_LGA TD(TD_LGUI_ALT)
#define MY_RGA TD(TD_RGUI_ALT)
#define MY_LCG TD(TD_LCTL_GUI)
#define MY_RCG TD(TD_RCTL_GUI)
#define MY_LSH TD(TD_LSFT_HPR)
#define MY_RSH TD(TD_RSFT_HPR)

enum {
    TD_LCTL_ALT,
    TD_RCTL_ALT,
    TD_LGUI_ALT,
    TD_RGUI_ALT,
    TD_LCTL_GUI,
    TD_RCTL_GUI,
    TD_LSFT_HPR,
    TD_RSFT_HPR
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_60_ansi(
            KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
            KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
            MY_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          MY_ENT,
            MY_LSH,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          MY_RSH,
            MY_LGA,  MY_LCG,  MY_LCA,                    KC_SPC,                             MY_RCA,  MY_RCG,  MY_APP, MY_RGA),

    LAYOUT_60_ansi(
            KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS,          KC_TRNS,
            KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    LAYOUT_60_ansi(
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS, DB_TOGG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
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

#define my_dance_combo(N, K0, REGFN, UNREGFN) my_dance_combo_expanded(N, K0, REGFN, UNREGFN)
#define my_dance_combo_expanded(N, K0, REGFN, UNREGFN)              \
static tap N ## _state = {                                          \
    .is_press_action = true,                                        \
    .state = 0                                                      \
};                                                                  \
                                                                    \
void N ## _finished(qk_tap_dance_state_t *state, void *user_data) { \
    N ## _state.state = cur_dance(state);                           \
    switch (N ## _state.state) {                                    \
        case SINGLE_TAP: case SINGLE_HOLD:                          \
            register_code(K0);                                      \
            break;                                                  \
        case DOUBLE_TAP: case DOUBLE_SINGLE_TAP: case DOUBLE_HOLD:  \
            register_code(K0);                                      \
            REGFN;                                                  \
            break;                                                  \
    }                                                               \
}                                                                   \
                                                                    \
void N ## _reset(qk_tap_dance_state_t *state, void *user_data) {    \
    switch (N ## _state.state) {                                    \
        case SINGLE_TAP: case SINGLE_HOLD:                          \
            unregister_code(K0);                                    \
            break;                                                  \
        case DOUBLE_TAP: case DOUBLE_SINGLE_TAP: case DOUBLE_HOLD:  \
            UNREGFN;                                                \
            unregister_code(K0);                                    \
            break;                                                  \
    }                                                               \
    N ## _state.state = 0;                                          \
}

#define my_dance_reg_code_1(K1) register_code(K1)
#define my_dance_unreg_code_1(K1) unregister_code(K1)
#define my_dance_combo_1(N, K0, K1) \
    my_dance_combo(N, K0, my_dance_reg_code_1(K1), my_dance_unreg_code_1(K1))

#define my_dance_reg_code_3(K1, K2, K3) \
    do { register_code(K1); register_code(K2); register_code(K3); } while (0)
#define my_dance_unreg_code_3(K1, K2, K3) \
    do { unregister_code(K3); unregister_code(K2); unregister_code(K1); } while (0)
#define my_dance_combo_3(N, K0, K1, K2, K3) \
    my_dance_combo(N, K0, my_dance_reg_code_3(K1, K2, K3), my_dance_unreg_code_3(K1, K2, K3))

my_dance_combo_1(lca, KC_LCTL, KC_LALT)
my_dance_combo_1(rca, KC_RCTL, KC_RALT)
my_dance_combo_1(lga, KC_LGUI, KC_LALT)
my_dance_combo_1(rga, KC_RGUI, KC_RALT)
my_dance_combo_1(lcg, KC_LCTL, KC_LGUI)
my_dance_combo_1(rcg, KC_RCTL, KC_RGUI)
my_dance_combo_3(lsh, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI)
my_dance_combo_3(rsh, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI)

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_LCTL_ALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lca_finished, lca_reset),
    [TD_RCTL_ALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rca_finished, rca_reset),
    [TD_LGUI_ALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lga_finished, lga_reset),
    [TD_RGUI_ALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rga_finished, rga_reset),
    [TD_LCTL_GUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lcg_finished, lcg_reset),
    [TD_RCTL_GUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rcg_finished, rcg_reset),
    [TD_LSFT_HPR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lsh_finished, lsh_reset),
    [TD_RSFT_HPR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rsh_finished, rsh_reset)
};
