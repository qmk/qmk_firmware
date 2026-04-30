#include QMK_KEYBOARD_H
#include "version.h"

enum layer_names {
    _HDGOLD,
    _SYMBOLS,
    _NUMPAD,
    _FKEYS,
    _MOUSE,
    _ARROW,
    _INTERNATIONAL,
};

enum custom_keycodes {
    ALLCAPS = SAFE_RANGE,
    CAPSWORD,
    TITLECASE,
    LAMPOON,
};

#define MO_SYM MO(_SYMBOLS)
#define MO_NUM MO(_NUMPAD)
#define MO_FK  MO(_FKEYS)
#define MO_MSE MO(_MOUSE)
#define MO_ARR MO(_ARROW)
#define MO_INTL MO(_INTERNATIONAL)

#define LT_NUM LT(_NUMPAD, KC_T)
#define LT_SYM LT(_SYMBOLS, KC_SPC)
#define TT_MSE TT(_MOUSE)
#define TT_ARR TT(_ARROW)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_HDGOLD] = LAYOUT_ergodox(
    // Left hand
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_ESC,
    KC_TAB,  KC_J,    KC_G,    KC_M,    KC_P,    KC_V,    KC_DEL,
    KC_CAPS, LCTL_T(KC_R), LGUI_T(KC_S), LALT_T(KC_N), LSFT_T(KC_D), KC_B,
    KC_LSFT, KC_X,    KC_F,    KC_L,    KC_C,    KC_W,    KC_ESC,
    KC_ESC,  KC_LBRC, KC_RBRC, KC_MINS, MO_SYM,
                                       KC_DEL,  KC_BSPC,
                                                MO_INTL,
                               LT_NUM, MO_SYM,  MO_FK,

    // Right hand
             KC_ESC,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
             KC_BSPC, KC_SCLN, KC_DOT,  KC_SLSH, KC_QUOT, KC_QUES, KC_ENT,
                      KC_COMM, RSFT_T(KC_A), RALT_T(KC_E), RGUI_T(KC_I), RCTL_T(KC_H), KC_B,
             KC_DEL,  KC_U,    KC_O,    KC_Y,    KC_K,    KC_Q,    KC_RSFT,
                               MO_NUM,  KC_MINS, KC_LBRC, KC_RBRC, KC_ESC,
             KC_BSPC, KC_DEL,
                      KC_PAUS,
             TT_ARR,  KC_BSPC, LT_SYM
),

[_SYMBOLS] = LAYOUT_ergodox(
    // Left hand
    _______, KC_CIRC, KC_HASH, KC_DLR,  KC_PERC, _______, _______,
    _______, KC_LABK, KC_MINS, KC_RABK, KC_EQL,  _______, _______,
    _______, KC_BSLS, KC_LPRN, KC_ASTR, KC_RPRN, KC_PLUS,
    _______, KC_TILD, KC_LBRC, KC_PIPE, KC_RBRC, KC_AMPR, _______,
    _______, _______, _______, _______, _______,
                                       _______, _______,
                                                _______,
                               _______, _______, _______,

    // Right hand
             _______, KC_AT,   KC_EXLM, KC_GRV,  _______, _______, _______,
             _______, KC_LCBR, KC_SCLN, KC_RCBR, KC_COLN, _______, _______,
                      KC_DLR,  KC_LBRC, KC_UNDS, KC_RBRC, KC_EXLM, _______,
             _______, KC_PERC, KC_PIPE, KC_TILD, KC_AMPR, _______, _______,
                               _______, _______, _______, _______, _______,
             _______, _______,
                      _______,
             _______, _______, _______
),

[_NUMPAD] = LAYOUT_ergodox(
    // Left hand
    _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,
                                       _______, _______,
                                                TO(0),
                               _______, _______, _______,

    // Right hand
             _______, KC_ASTR, KC_PLUS, KC_MINS, _______, _______, _______,
             _______, KC_7,    KC_8,    KC_9,    _______, _______, _______,
                      KC_0,    KC_1,    KC_2,    KC_3,    _______, _______,
             _______, KC_4,    KC_5,    KC_6,    _______, _______, _______,
                               _______, _______, _______, _______, _______,
             _______, _______,
                      _______,
             _______, _______, _______
),

[_FKEYS] = LAYOUT_ergodox(
    // Left hand
    _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, KC_CAPS,
    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, LAMPOON,
    _______, _______, _______, _______, _______,
                                       KC_MPLY, KC_VOLU,
                                                KC_VOLD,
                               TO(_NUMPAD), _______, _______,

    // Right hand
             _______, _______, _______, _______, _______, _______, _______,
             TITLECASE, KC_F7, KC_F8, KC_F9, _______, _______,
                      KC_F1, KC_F2, KC_F3, _______, _______,
             ALLCAPS, KC_F4, KC_F5, KC_F6, _______, _______,
                               _______, _______, _______, _______, _______,
             QK_BOOT, _______,
                      _______,
             _______, _______, _______
),

[_MOUSE] = LAYOUT_ergodox(
    // Left hand
    _______, _______, _______, KC_MS_BTN3, _______, _______, _______,
    _______, KC_MS_BTN4, KC_MS_BTN2, KC_MS_UP, KC_MS_BTN1, KC_MS_WH_UP, _______,
    _______, KC_MS_BTN5, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_MS_WH_DOWN,
    _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,
                                       _______, _______,
                                                KC_MS_BTN1,
                               _______, _______, _______,

    // Right hand
             _______, KC_MS_WH_UP, KC_MS_BTN1, KC_MS_UP, KC_MS_BTN2, KC_MS_BTN4, _______,
             _______, KC_MS_WH_DOWN, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_MS_BTN5, _______,
                      _______, _______, _______, _______, _______, _______,
             _______, _______, _______, _______, _______, _______, _______,
                               _______, _______, _______, _______, _______,
             _______, _______,
                      _______,
             _______, _______, KC_MS_BTN1
),

[_ARROW] = LAYOUT_ergodox(
    // Left hand
    _______, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   _______,
    _______, KC_NO,  KC_Q,   KC_W,   KC_E,   KC_R,   _______,
    _______, KC_A,   KC_NO,  KC_S,   KC_D,   _______,
    _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,
                                       _______, TO(0),
                                                _______,
                               _______, _______, _______,

    // Right hand
             _______, KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   _______,
             _______, _______, KC_PGUP, KC_UP, KC_PGDN, _______, _______,
                      KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
             _______, KC_HOME, KC_DOWN, KC_END, _______, _______,
                               _______, _______, _______, _______, _______,
             TO(0),  _______,
                      _______,
             _______, _______, _______
),

[_INTERNATIONAL] = LAYOUT_ergodox(
    // Left hand
    _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,
                                       _______, TO(0),
                                                _______,
                               _______, _______, _______,

    // Right hand
             _______, _______, _______, _______, _______, _______, _______,
             _______, _______, _______, _______, _______, _______, _______,
                      _______, _______, _______, _______, _______,
             _______, _______, _______, _______, _______, _______,
                               _______, _______, _______, _______, _______,
             TO(0),  _______,
                      _______,
             _______, _______, _______
),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ALLCAPS:
            if (record->event.pressed) {
                if (!(host_keyboard_led_state().caps_lock)) {
                    tap_code(KC_CAPS);
                }
            }
            return false;
        case TITLECASE:
            if (record->event.pressed) {
                if (!(host_keyboard_led_state().caps_lock)) {
                    tap_code(KC_CAPS);
                }
            }
            return false;
        case CAPSWORD:
            if (record->event.pressed) {
                if (!(host_keyboard_led_state().caps_lock)) {
                    tap_code(KC_CAPS);
                }
            }
            return false;
        case LAMPOON:
            if (record->event.pressed) {
            }
            return false;
    }
    return true;
}
