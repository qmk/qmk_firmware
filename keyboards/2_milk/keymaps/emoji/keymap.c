#include QMK_KEYBOARD_H

enum tapdance_keycodes {
    TD_KEY_1,
    TD_KEY_2,
};

void dance_key_one (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        send_unicode_hex_string("00AF 005C 005F 0028 30C4 0029 005F 002F 00AF"); // ¯\_(ツ)_/¯
        SEND_STRING(SS_TAP(X_ENTER));
        reset_tap_dance (state);
    } else if (state->count == 2) {
        cycle_unicode_input_mode(+1);
        reset_tap_dance (state);
    }
}

void dance_key_two (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        send_unicode_hex_string("0CA0 005F 0CA0"); // ಠ_ಠ
        SEND_STRING(SS_TAP(X_ENTER));
        reset_tap_dance (state);
    } else if (state->count == 2) {
        send_unicode_hex_string("0028 30CE 0CA0 75CA 0CA0 0029 30CE 5F61 253B 2501 253B"); // (ノಠ痊ಠ)ノ彡┻━┻
        SEND_STRING(SS_TAP(X_ENTER));
        reset_tap_dance (state);
    } else if (state->count == 3) {
        send_unicode_hex_string("256D 2229 256E 0028 002D 005F 002D 0029 256D 2229 256E"); // ╭∩╮(-_-)╭∩╮
        SEND_STRING(SS_TAP(X_ENTER));
        reset_tap_dance (state);
    } else if (state->count == 4) {
        send_unicode_hex_string("0028 3065 FFE3 0020 00B3 FFE3 0029 3065"); // (づ￣ ³￣)づ
        SEND_STRING(SS_TAP(X_ENTER));
        reset_tap_dance (state);
    } else if (state->count == 5) {
        send_unicode_hex_string("0028 FE3A FE39 FE3A 0029"); // (︺︹︺)
        SEND_STRING(SS_TAP(X_ENTER));
        reset_tap_dance (state);
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_KEY_1] = ACTION_TAP_DANCE_FN(dance_key_one),
    [TD_KEY_2] = ACTION_TAP_DANCE_FN(dance_key_two),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        TD(TD_KEY_1),
        TD(TD_KEY_2)
    ),
};
