#include QMK_KEYBOARD_H


enum td_keys {
    TD_K0,
    TD_K1,
    TD_K2,
    TD_K3
};


void td_spade_lnx (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_unicode(0x2660); // ♠
    } else {
        set_unicode_input_mode(UNICODE_MODE_LINUX);
    }
    reset_tap_dance(state);
}


void td_diamond_osx (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_unicode(0x2666); // ♦
    } else {
        set_unicode_input_mode(UNICODE_MODE_MACOS);
    }
    reset_tap_dance(state);
}


void td_club_win (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_unicode(0x2663); // ♣
    } else {
        set_unicode_input_mode(UNICODE_MODE_WINDOWS);
    }
    reset_tap_dance(state);
}


void td_heart_winc (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_unicode(0x2665); // ♥
    } else {
        set_unicode_input_mode(UNICODE_MODE_WINCOMPOSE);
    }
    reset_tap_dance(state);
}


qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_K0] = ACTION_TAP_DANCE_FN(td_spade_lnx),
    [TD_K1] = ACTION_TAP_DANCE_FN(td_diamond_osx),
    [TD_K2] = ACTION_TAP_DANCE_FN(td_club_win),
    [TD_K3] = ACTION_TAP_DANCE_FN(td_heart_winc)
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        TD(TD_K0),
        TD(TD_K1),
        TD(TD_K2),
        TD(TD_K3)
    )
};
