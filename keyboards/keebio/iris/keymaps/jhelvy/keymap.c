#include QMK_KEYBOARD_H

enum layers {
    QWERTY = 0,
    HOTKEYS,
    TEXT,
    SELECT,
    MOUSE,
};

enum custom_keycodes {
    SIG_PROF = SAFE_RANGE,
    SIG_JOHN,
    R_PIPE,
    R_ASSIGN,
    R_COLS,
    R_IN,
    TEX,
    E_GMAIL,
    E_GWU,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


[QWERTY] = LAYOUT(LALT(KC_A), KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL, KC_EQL, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_MINS, KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_QUOT, KC_ENT, SC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_NO, KC_NO, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, SC_RSPC, MO(4), KC_LGUI, MO(2), KC_SPC, MO(1), TG(1)),

[HOTKEYS] = LAYOUT(KC_F5, LGUI(LALT(KC_1)), LGUI(LALT(KC_2)), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_F14, KC_F6, KC_NO, KC_NO, LCTL(KC_U), SGUI(KC_R), KC_F2, SGUI(KC_K), LCTL(KC_9), LCTL(KC_0), KC_NO, KC_F11, KC_F15, KC_F7, LGUI(LCTL(KC_A)), KC_F10, KC_LBRC, KC_RBRC, KC_F9, SIG_JOHN, LSFT(KC_TAB), KC_TAB, E_GMAIL, KC_F12, KC_F16, KC_F8, KC_ASTG, KC_NO, KC_LCBR, KC_RCBR, KC_NO, KC_NO, KC_NO, SIG_PROF, KC_F3, KC_F4, E_GWU, KC_F13, KC_F17, LALT(KC_SPC), KC_LGUI, KC_LCTL, KC_SPC, KC_TRNS, KC_TRNS),

[TEXT] = LAYOUT(KC_ESC, LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4), LGUI(KC_5), KC_SCLN, KC_PIPE, KC_COLN, KC_NO, KC_UNDS, KC_PLUS, LGUI(KC_BSPC), LGUI(KC_Q), LGUI(KC_W), KC_ESC, LGUI(KC_R), LGUI(KC_T), LCTL(KC_Y), LGUI(KC_LEFT), KC_UP, LGUI(KC_RGHT), KC_TILD, R_PIPE, KC_BSPC, MO(3), LGUI(KC_S), LGUI(KC_C), LGUI(KC_V), LGUI(KC_X), KC_DEL, KC_LEFT, KC_DOWN, KC_RGHT, KC_GRV, KC_ENT, KC_F18, LGUI(KC_A), LGUI(KC_D), KC_F1, LGUI(KC_Z), LGUI(KC_Y), KC_NO, KC_NO, KC_BSPC, LGUI(KC_F), SGUI(KC_G), LGUI(KC_G), KC_BSLS, R_ASSIGN, KC_LALT, KC_LGUI, KC_TRNS, KC_SPC, KC_RGUI, KC_NO),

[SELECT] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, SGUI(KC_LEFT), LSFT(KC_UP), SGUI(KC_RGHT), KC_NO, R_COLS, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LSFT(KC_LEFT), LSFT(KC_DOWN), LSFT(KC_RGHT), KC_NO, R_IN, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LALT(LSFT(KC_LEFT)), LALT(LSFT(KC_RIGHT)), KC_NO, TEX, KC_NO, KC_NO, KC_NO, KC_SPC, KC_TRNS, KC_TRNS),

[MOUSE] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LGUI, KC_NO, KC_NO, LGUI(KC_LBRC), KC_MS_U, LGUI(KC_RBRC), KC_NO, KC_NO, LCTL(KC_TAB), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_BTN1, KC_BTN2, KC_NO)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case SIG_PROF:
        if (record->event.pressed) {
            SEND_STRING("Cheers,\nProfessor Helveston");
        } else {
        }
        break;

    case SIG_JOHN:
        if (record->event.pressed) {
            SEND_STRING("Cheers,\nJohn");
        } else {
        }
        break;

    case R_PIPE:
        if (record->event.pressed) {
            SEND_STRING(" %>% ");
        } else {
        }
        break;

    case R_ASSIGN:
        if (record->event.pressed) {
            SEND_STRING(" <- ");
        } else {
        }
        break;

    case R_COLS:
        if (record->event.pressed) {
            SEND_STRING(".leftcol[\n]\n.rightcol[\n]\n");
        } else {
        }
        break;

    case R_IN:
        if (record->event.pressed) {
            SEND_STRING(" %in% ");
        } else {
        }
        break;

    case TEX:
        if (record->event.pressed) {
            SEND_STRING("\\text{}");
        } else {
        }
        break;

    case E_GMAIL:
        if (record->event.pressed) {
            SEND_STRING("john.helveston@gmail.com");
        } else {
        }
        break;

    case E_GWU:
        if (record->event.pressed) {
            SEND_STRING("jph@gwu.edu");
        } else {
        }
        break;

    }

    return true;
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (IS_LAYER_ON(HOTKEYS)) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (IS_LAYER_ON(TEXT)) {
        if (clockwise) {
            tap_code(KC_MS_WH_RIGHT);
        } else {
            tap_code(KC_MS_WH_LEFT);
        }
    } else if (IS_LAYER_ON(MOUSE)) {
        if (clockwise) {
            tap_code16(G(KC_EQL));
        } else {
            tap_code16(G(KC_MINS));
        }
    } else {
        if (clockwise) {
            tap_code(KC_MS_WH_DOWN);
        } else {
            tap_code(KC_MS_WH_UP);
        }
    }
    return true;
}
