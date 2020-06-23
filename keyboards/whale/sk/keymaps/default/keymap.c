#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
        KC_ESC, KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_HOME,      KC_END, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_PGUP,               KC_PGDOWN, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLASH,
        KC_LCTRL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_DEL,               KC_BSPC, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_ENT,
        KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_LEFT,              KC_RIGHT, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLSH, KC_RSHIFT,
        MO(1), KC_LALT, KC_LWIN, KC_APP, KC_HENK, KC_MENU,              KC_MENU, KC_MHEN, KC_APP, KC_RWIN, KC_RALT, MO(1),
                                            KC_F1, KC_F2,       KC_F7, KC_F8,
                                    KC_SPC, KC_F3, KC_F4,       KC_F9, KC_F10, KC_SPC,
                                            KC_F5, KC_F6,       KC_F11, KC_F12
    ),
    [1] = LAYOUT_all(
        _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                         _______, _______, _______, _______, _______, _______,
                                                              _______, _______,     _______, _______,
                                                     _______, _______, _______,     _______, _______, _______,
                                                              _______, _______,     _______, _______
    )
};
