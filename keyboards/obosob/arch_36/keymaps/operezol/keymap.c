#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names { _QWERTY, _LAYER1, _LAYER2, _LAYER3 };

// tab esc tap dance
enum { TD_TAB_ESC = 0 };

void tab_esc(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) {
            register_code(KC_ESC);
        } else {
            register_code(KC_TAB);
        }
    }
    reset_tap_dance(state);
}
qk_tap_dance_action_t tap_dance_actions[] = {[TD_TAB_ESC] = ACTION_TAP_DANCE_FN(tab_esc)};

#define TD_RS TD(TD_TAB_ESC);

#define LT_1L LT(1, KC_F);
#define LT_2L LT(2, KC_D);
#define LT_3L LT(3, KC_S);
#define LT_4L LT(4, KC_A);

#define LT_1R LT(1, KC_J);
#define LT_2R LT(2, KC_K);
#define LT_3R LT(3, KC_L);
#define LT_4R LT(4, KC_SCLN);

#define MT_WCL LGUI_T(KC_CAPS);
#define MT_GRE RALT_T(KC_ENTER);
#define MT_CBS LCTL_T(KC_BSPC);
#define MT_SSP LSFT_T(KC_SPC);
#define MT_ADL LALT_T(KC_DEL);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_split_3x5_3(
        KC_Q,  KC_W,  KC_E,   KC_R,   KC_T,    KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,
        LT_4L, LT_3L, LT_2L,  LT_1L,  KC_G,    KC_H,   LT_1R,  LT_2R,   LT_3R,   LT_4R,
        KC_Z,  KC_X,  KC_C,   KC_V,   KC_B,    KC_N,   KC_M,   KC_LBRC, KC_QUOT, KC_NUHS,
                      MT_WCL, MT_GRE, TD_RS,   MT_CBS, MT_SSP, MT_ADL),
    [_LAYER1] = LAYOUT_split_3x5_3(
        KC_Q, KC_W, KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,
        KC_A, KC_S, KC_D,    KC_F,    KC_G,      KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN,
        KC_Z, KC_X, KC_C,    KC_V,    KC_B,      KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH,
                    KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS),
    [_LAYER2] = LAYOUT_split_3x5_3(
        KC_Q, KC_W, KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,
        KC_A, KC_S, KC_D,    KC_F,    KC_G,      KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN,
        KC_Z, KC_X, KC_C,    KC_V,    KC_B,      KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH,
                    KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS),
    [_LAYER3] = LAYOUT_split_3x5_3(
        KC_Q, KC_W, KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,
        KC_A, KC_S, KC_D,    KC_F,    KC_G,      KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN,
        KC_Z, KC_X, KC_C,    KC_V,    KC_B,      KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH,
                    KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS),
}
