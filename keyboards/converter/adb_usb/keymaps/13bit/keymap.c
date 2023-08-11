#include QMK_KEYBOARD_H

#define MCTL LCTL(KC_UP)
#define SCST LSFT(LGUI(KC_4))
#define SLP  LALT(LGUI(KC_EJCT))

#define APP1 LSFT(LALT(LCTL(LGUI(KC_1))))
#define APP2 LSFT(LALT(LCTL(LGUI(KC_2))))
#define APP3 LSFT(LALT(LCTL(LGUI(KC_3))))
#define APP4 LSFT(LALT(LCTL(LGUI(KC_4))))
#define APP5 LSFT(LALT(LCTL(LGUI(KC_5))))
#define APP6 LSFT(LALT(LCTL(LGUI(KC_6))))
#define APP7 LSFT(LALT(LCTL(LGUI(KC_7))))
#define APP8 LSFT(LALT(LCTL(LGUI(KC_8))))


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ext_ansi(
    KC_ESC,  APP1,    APP2,   APP3,   APP4,   APP5,   APP6,   APP7,   APP8,    MCTL,   KC_MUTE, KC_VOLD, KC_VOLU,                SCST,   KC_SCRL, KC_PAUS,                               SLP,
    KC_GRV,  KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSPC,       KC_INS, KC_HOME, KC_PGUP,     KC_NUM,  KC_EQL, KC_PSLS, KC_PAST,
    KC_TAB,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,       KC_DEL, KC_END,  KC_PGDN,     KC_P7,   KC_P8,  KC_P9,   KC_PMNS,
    KC_LCAP, KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOT,          KC_ENT,                                      KC_P4,   KC_P5,  KC_P6,   KC_PPLS,
    KC_LSFT, KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH,                   KC_RSFT,                KC_UP,               KC_P1,   KC_P2,  KC_P3,
    KC_LCTL, KC_LALT, KC_LGUI,                KC_SPC,                                  KC_RALT, KC_RCTL,                         KC_LEFT, KC_DOWN, KC_RGHT,    KC_P0,           KC_PDOT, KC_PENT
    ),
};
