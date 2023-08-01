#include QMK_KEYBOARD_H

#define DVORAK_MAC_MODE 0 // Base Dvorak in Kinesis's Mac Mode with (Cmd, Option, Ctrl, Cmd) thumbkeys

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[DVORAK_MAC_MODE] = LAYOUT(
        // left hand
        KC_CAPS,  KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5, KC_F6, KC_F7, KC_F8,
        KC_EQL,   KC_1,    KC_2,    KC_3,    KC_4,   KC_5,
        KC_TAB,   KC_QUOT, KC_COMM, KC_DOT,  KC_P,   KC_Y,
        KC_ESC,   KC_A,    KC_O,    KC_E,    KC_U,   KC_I,
        KC_LSFT,  KC_SCLN, KC_Q,    KC_J,    KC_K,   KC_X,
                  KC_GRV,  KC_INS,  KC_LEFT, KC_RIGHT,
        // left thumb
                            KC_LGUI, KC_LALT,
                                     KC_HOME,
                   KC_BSPC, KC_DEL,  KC_END,
        // right hand
        KC_F9,  KC_F10,   KC_F11,   KC_F12,   KC_PSCR, KC_SCRL, KC_PAUS, KC_NUM, KC_PWR,
        KC_6,   KC_7,     KC_8,     KC_9,     KC_0,    KC_MINS,
        KC_F,   KC_G,     KC_C,     KC_R,     KC_L,    KC_SLSH,
        KC_D,   KC_H,     KC_T,     KC_N,     KC_S,    KC_BSLS,
        KC_B,   KC_M,     KC_W,     KC_V,     KC_Z,    KC_RSFT,
                          KC_UP,  KC_DOWN, KC_LBRC,    KC_RBRC,
        // right thumb
        KC_RCTL,    KC_RGUI,
        KC_PGUP,
        KC_PGDN, KC_ENT, KC_SPC
    )
};
