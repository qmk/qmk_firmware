#include QMK_KEYBOARD_H

// Layer names. We stick to 3 letters if possible so MO(NAME) fits in 7
// characters and doesn't mess with the grid.
#define _QW 0
#define _L1 1
#define _L2 2
#define _L3 3

// Curly braces have their own keys. These are defined so they don't mess up the
// grid in layer 2.
#define L_CURBR LSFT(KC_LBRC)
#define R_CURBR LSFT(KC_RBRC)

#define L1_TAB  LT(_L1, KC_TAB)
#define L2_ESC  LT(_L2, KC_ESC)
#define L2_SLSH LT(_L2, KC_SLSH)
#define L3_QUOT LT(_L3, KC_QUOT)

// Tap dance magic
#define TD_LGUI TD(BE_TD_GUI)
#define TD_LCTL TD(BE_TD_CTL)
#define TD_LALT TD(BE_TD_ALT)

enum belak_td {
    BE_TD_GUI = 0,
    BE_TD_CTL,
    BE_TD_ALT,
};

void mod_tap_fn(qk_tap_dance_state_t *state, void *user_data);
void mod_reset_fn(qk_tap_dance_state_t *state, void *user_data);

qk_tap_dance_action_t tap_dance_actions[] = {
    [BE_TD_GUI] = ACTION_TAP_DANCE_FN_ADVANCED(mod_tap_fn, NULL, mod_reset_fn),
    [BE_TD_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(mod_tap_fn, NULL, mod_reset_fn),
    [BE_TD_ALT] = ACTION_TAP_DANCE_FN_ADVANCED(mod_tap_fn, NULL, mod_reset_fn),
};

uint16_t tap_dance_keys[] = {
    [BE_TD_GUI] = KC_LGUI,
    [BE_TD_CTL] = KC_LCTL,
    [BE_TD_ALT] = KC_LALT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QW] = LAYOUT_arrow_command( /* Qwerty */
        L2_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        L1_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   L2_SLSH,
        TD_LCTL, MO(_L3), TD_LALT, TD_LGUI,          KC_SPC,  KC_SPC,           MO(_L1), KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_L1] = LAYOUT_arrow_command( /* LAYER 1 */
        KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
        _______, KC_BSLS, KC_QUOT, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_DOWN, KC_UP,   KC_LEFT, KC_RGHT, KC_QUOT,
        _______, KC_ESC,  _______, KC_PSCR, _______, _______, _______, KC_MSTP, KC_MPLY, KC_MPRV, KC_MNXT, KC_RSFT,
        _______, KC_LGUI, _______, _______,          _______, _______,          _______, _______, _______, _______
    ),
    [_L2] = LAYOUT_arrow_command( /* LAYER 2 */
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        KC_ESC,  KC_PIPE, KC_DQUO, KC_UNDS, KC_PLUS, L_CURBR, R_CURBR, KC_4,    KC_5,    KC_6,    KC_VOLU, _______,
        _______, _______, _______, _______, _______, _______, KC_0,    KC_1,    KC_2,    KC_3,    KC_VOLD, _______,
        _______, _______, _______, _______,          _______, _______,          KC_RALT, _______, _______, _______
    ),
    [_L3] = LAYOUT_arrow_command( /* LAYER 3 */
        _______, _______, _______, _______, _______, _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______,
        KC_ESC,  _______, _______, _______, _______, _______, _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______,
        _______, _______, _______, _______, _______, _______, _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_RSFT,
        _______, _______, _______, _______,          _______, _______,          KC_RALT, _______, _______, _______
    )
};

// Tap dance functions
void mod_tap_fn(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            register_mods(MOD_BIT(tap_dance_keys[state->keycode - QK_TAP_DANCE]));
            send_keyboard_report();
            break;
        case 2:
            layer_on(_L2);
            break;
        case 3:
            layer_off(_L2);
            layer_on(_L1);
            break;
        default:
            reset_tap_dance(state);
    }
}

void mod_reset_fn(qk_tap_dance_state_t *state, void *user_data) {
    layer_off(_L1);
    layer_off(_L2);
    unregister_mods(MOD_BIT(tap_dance_keys[state->keycode - QK_TAP_DANCE]));
    send_keyboard_report();
}
