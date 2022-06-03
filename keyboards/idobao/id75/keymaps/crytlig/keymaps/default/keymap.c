#include QMK_KEYBOARD_H

#define S_NO        RSFT(KC_NO)
#define CS_TRNS     LCTL(LSFT(KC_TRNS))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,  KC_GRV,  KC_DEL,  KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, KC_BSPC, KC_PGDN,
        TG(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_SLSH, KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT,  KC_ENT,  KC_RSFT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_SCLN, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_MINS, S_NO,    KC_HOME, KC_END,
        KC_LCTL, KC_LGUI, KC_LALT, KC_LCTL, MO(1),   KC_SPC,  KC_SPC,  KC_SPC,  KC_RALT, KC_RGUI, MO(2),   KC_RCTL, TG(1),   MO(4),   KC_PSCR
    ),

    [1] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
        _______, _______, KC_UP,   _______, _______, _______, KC_RBRC, _______, _______, _______, _______, _______, _______, _______, _______,
        TO(4),   KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, KC_BSLS, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS,
        _______, _______, _______, _______, _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, BL_TOGG, BL_DEC,  BL_INC,  BL_STEP, _______, _______, _______, _______, _______,
        _______, RGB_VAI, RGB_VAD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, CS_TRNS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

};
