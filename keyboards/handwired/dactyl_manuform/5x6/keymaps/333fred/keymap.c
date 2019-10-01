#include QMK_KEYBOARD_H
#include "333fred.h"

enum custom_macros {
    DLEFT,
    DRIGHT,
    PSCREEN_APP
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE] = LAYOUT_5x6(
     KC_GRV,        KC_1,        KC_2,  KC_3,  KC_4,    KC_5,                                KC_6,   KC_7,     KC_8,         KC_9,   KC_0,    KC_MINS,
     KC_TAB,        KC_Q,        KC_W,  KC_E,  KC_R,    KC_T,                                KC_Y,   KC_U,     KC_I,         KC_O,   KC_P,    KC_BSLS,
     KC_ESC,        KC_A,        KC_S,  KC_D,  KC_F,    KC_G,                                KC_H,   KC_J,     KC_K,         KC_L,   KC_SCLN, KC_QUOT,
     OSM(MOD_LSFT), CTL_T(KC_Z), KC_X,  KC_C,  KC_V,    KC_B,                                KC_N,   KC_M,     KC_COMM,      KC_DOT, KC_SLSH, OSM(MOD_RSFT),
                                 KC_F4, KC_F5,                                                                 TG(CODEFLOW), KC_EQL,
                                               KC_LALT, KC_BSPC,                             KC_SPC, OSL(VIM),
                                                        KC_TAB,  TD(TD_SYM_VIM),     KC_ENT, KC_RGUI,
                                                        KC_LCTL, KC_DEL,             KC_UP,  KC_DOWN
  ),

  [CODEFLOW] = LAYOUT_5x6(
     _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
                       KC_F7,   KC_F8,                                                             _______, _______,
                                         _______, _______,                       _______, _______,
                                                  _______, _______,     _______, _______,
                                                  _______, _______,     _______, _______
  ),

  [SYMB] = LAYOUT_5x6(
     _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                         KC_F6,   KC_F7,   KC_F8, KC_F9,  KC_F10,  KC_F11,
     _______, KC_EXLM, KC_AT,   KC_LPRN, KC_RPRN, KC_PIPE,                       _______, KC_7,    KC_8,  KC_9,   _______, KC_F12,
     _______, KC_HASH, KC_DLR,  KC_LCBR, KC_RCBR, KC_GRV,                        _______, KC_4,    KC_5,  KC_6,   _______, _______,
     _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,                       _______, KC_1,    KC_2,  KC_3,   _______, _______,
                       KC_F7,   KC_F8,                                                             KC_0,  KC_ENT,
                                         _______, _______,                       KC_MPLY, KC_MNXT,
                                                  _______, _______,     KC_MPRV, _______,
                                                  _______, _______,     KC_VOLU, KC_VOLD
  ),

  [VIM] = LAYOUT_5x6(
     _______, RESET,    _______,   _______, _______, _______,                       _______, _______, _______, _______, RESET,   _______,
     _______, _______,  _______,   _______, KC_LSFT, _______,                       _______, _______, _______, _______, _______, _______,
     _______, M(DLEFT), M(DRIGHT), KC_LCTL, KC_LGUI, _______,                       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
     _______, _______,  _______,   _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
                        _______,   _______,                                                            _______, _______,
                                           _______, _______,                       _______, _______,
                                                    _______, _______,     _______, _______,
                                                    _______, _______,     _______, _______
  ),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch(id) {
        case DLEFT:
            if (record->event.pressed) { // Windows move desktop left
                return MACRO(D(LCTL), D(LGUI), T(LEFT), U(LGUI), U(LCTL), END);
            }
            break;
        case DRIGHT:
            if (record->event.pressed) { // Windows move desktop right
                return MACRO(D(LCTL), D(LGUI), T(RIGHT), U(LGUI), U(LCTL), END);
            }
            break;
        case PSCREEN_APP: if (record->event.pressed) {
                return MACRO(D(LALT), T(PSCR), U(LALT), END);
            }
            break;
    }
    return MACRO_NONE;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_process_record(keycode);
    return true;
}
