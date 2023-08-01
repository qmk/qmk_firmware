#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_5x15( /* Dvorak */
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_RBRC, KC_BSPC, XXXXXXX,
        KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, KC_EQL,  KC_INS,  KC_DEL,
        KC_CAPS, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, KC_ENT,  XXXXXXX, KC_PGUP,
        KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT, XXXXXXX, KC_UP,   KC_PGDN,
        KC_LCTL, MO(1),   XXXXXXX, KC_LALT, XXXXXXX, XXXXXXX, KC_SPC,  XXXXXXX, XXXXXXX, XXXXXXX, KC_LGUI, MO(2),   KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT_ortho_5x15( /* Qwerty + F keys */
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_BSPC, XXXXXXX,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_INS,  KC_DEL,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  XXXXXXX, KC_PGUP,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, XXXXXXX, KC_UP,   KC_PGDN,
        KC_LCTL, _______, XXXXXXX, KC_LALT, XXXXXXX, XXXXXXX, KC_SPC,  XXXXXXX, XXXXXXX, XXXXXXX, KC_LGUI, _______, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [2] = LAYOUT_ortho_5x15( /* Numpad + qwerty shortcut keys */
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_P7,   KC_P8,   KC_P9,   KC_0,    KC_LBRC, KC_RBRC, KC_BSPC, XXXXXXX,
        KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_P4,   KC_P5,   KC_P6,   KC_L,    KC_SLSH, KC_EQL,  KC_INS,  KC_DEL,
        KC_CAPS, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_P1,   KC_P2,   KC_P3,   KC_S,    KC_MINS, KC_ENT,  XXXXXXX, KC_PGUP,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_X,    KC_B,    KC_P0,   KC_P0,   KC_PENT, KC_Z,    KC_RSFT, XXXXXXX, KC_UP,   KC_PGDN,
        KC_LCTL, _______, XXXXXXX, KC_LALT, XXXXXXX, XXXXXXX, KC_SPC,  XXXXXXX, XXXXXXX, XXXXXXX, KC_LGUI, _______, KC_LEFT, KC_DOWN, KC_RGHT
    ),
};
