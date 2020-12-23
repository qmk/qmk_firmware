#include QMK_KEYBOARD_H
#include "keymap_italian.h"

enum layers {
  _QWERTY,
  _SHIFT,
  _NUMBER,
  _SYMBOL,
  _ACCENT,
  _SERVICE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_65_ansi(
        KC_GESC,        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    IT_MINS, IT_EQL,  KC_BSPC, KC_HOME,
        KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    IT_LBRC, IT_RBRC, IT_LESS, KC_PGUP,
        SFT_T(KC_CAPS), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    IT_SCLN, IT_QUOT,          KC_ENT,  KC_PGDN,
        MO(_SHIFT),     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  IT_SLSH, MO(_SHIFT), KC_UP,   KC_END,
        KC_LCTL,        KC_LGUI, KC_LALT,                        LT(_ACCENT, KC_SPC),                    KC_RALT, MO(_SERVICE),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_SHIFT] = LAYOUT_65_ansi(
        S(KC_GESC), IT_EXLM,    IT_AT,   IT_SHRP, IT_DLR,  IT_PERC, IT_CIRC, IT_AMPR, IT_ASTR,    IT_LPRN,   IT_RPRN,    IT_UNDS,    IT_PLUS,    KC_DEL,     S(KC_HOME),
        S(KC_TAB),  S(KC_Q),    S(KC_W), S(KC_E), S(KC_R), S(KC_T), S(KC_Y), S(KC_U), S(KC_I),    S(KC_O),   S(KC_P),    IT_LCBR,    IT_RCBR,    IT_MORE,    S(KC_PGUP),
        KC_LSFT,    S(KC_A),    S(KC_S), S(KC_D), S(KC_F), S(KC_G), S(KC_H), S(KC_J), S(KC_K),    S(KC_L),   IT_COLN,    IT_DQUO,                S(KC_ENT),  S(KC_PGDN),
        KC_LSFT,    S(KC_Z),    S(KC_X), S(KC_C), S(KC_V), S(KC_B), S(KC_N), S(KC_M), IT_BSLS,    IT_PIPE,   IT_QST,     KC_RSFT,                S(KC_UP),   S(KC_END),
        S(KC_LCTL), S(KC_LGUI), S(KC_LALT),                      S(KC_SPC),                    S(KC_RALT), MO(_SERVICE), S(KC_RCTL), S(KC_LEFT), S(KC_DOWN), S(KC_RGHT)
    ),
    [_ACCENT] = LAYOUT_65_ansi(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, IT_EURO, XXXXXXX, IT_EGRV, XXXXXXX, XXXXXXX, XXXXXXX, IT_UGRV, IT_IGRV, IT_OGRV, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, IT_AGRV, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT, XXXXXXX, XXXXXXX,
        KC_LCTL, KC_LGUI, KC_LALT,                      KC_SPC,                    KC_RALT, MO(_SERVICE),  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_SERVICE] = LAYOUT_65_ansi(
        RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_HOME,
        XXXXXXX, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, XXXXXXX, KC_PSCR, KC_SLCK, KC_PAUS, RESET,   KC_PGUP,
        _______, RGB_SPI, RGB_SPD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, KC_PGDN,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          KC_VOLU, KC_MUTE,
        _______, _______, _______,                            _______,                   _______, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT
    )
};
