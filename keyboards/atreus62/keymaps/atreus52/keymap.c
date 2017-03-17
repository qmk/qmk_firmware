#include "atreus62.h"

// Layers
#define QWERTY 0
#define DVORAK 1
#define RAISE 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[QWERTY] = KC_KEYMAP(
    NO, 1,    2,    3,    4,    5,                6,    7,    8,    9,    0,    NO, \
    NO, Q,    W,    E,    R,    T,                Y,    U,    I,    O,    P,    NO, \
    NO, A,    S,    D,    F,    G,                H,    J,    K,    L,    SCLN, NO, \
    NO, Z,    X,    C,    V,    B,                N,    M,    COMM, DOT,  SLSH, NO, \
    NO, ESC,  TAB,  LCTL, FN0,  FN10, BSPC, ENT,  SPC,  LALT, LGUI, LEFT, RGHT, NO  ),

[DVORAK] = KC_KEYMAP(
    NO, 1,    2,    3,    4,    5,                6,    7,    8,    9,    0,    NO, \
    NO, QUOT, COMM, DOT,  P,    Y,                F,    G,    C,    R,    L,    NO, \
    NO, A,    O,    E,    U,    I,                D,    H,    T,    N,    S,    NO, \
    NO, SCLN, Q,    J,    K,    X,                B,    M,    W,    V,    Z,    NO, \
    NO, ESC,  TAB,  LCTL, FN0,  FN10, BSPC, ENT,  SPC,  LALT, LGUI, LEFT, RGHT, NO  ),

[RAISE] = KC_KEYMAP(
    NO, ESC,  TRNS, MPRV, MPLY, MNXT,             TRNS, MUTE, VOLD, VOLU, DEL,  NO, \
    NO, TRNS, TRNS, GRV,  FN13, FN14,             BSLS, FN16, FN18, LBRC, QUOT, NO, \
    NO, FN12, MINS, FN11, EQL,  FN15,             SLSH, LEFT, DOWN, UP,   RGHT, NO, \
    NO, TRNS, TRNS, TRNS, TRNS, TRNS,             TRNS, FN17, FN19, RBRC, FN20, NO, \
    NO, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, NO  )
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(RAISE), // Raise layer

    [10] = OSM(MOD_LSFT),   // One shot shift
    [11] = LSFT(KC_EQUAL),  // +
    [12] = LSFT(KC_MINUS),  // _
    [13] = LSFT(KC_SLASH),  // ?
    [14] = LSFT(KC_BSLASH), // |
    [15] = LSFT(KC_GRAVE),  // ~
    [16] = LSFT(KC_9),      // (
    [17] = LSFT(KC_0),      // )
    [18] = LSFT(KC_LBRC),   // {
    [19] = LSFT(KC_RBRC),   // }
    [20] = LSFT(KC_QUOT)    // "
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    // MACRODOWN only works in this function
    switch (id) {
    case 0:
        if (record->event.pressed) {
            register_code(KC_RSFT);
        }
        else {
            unregister_code(KC_RSFT);
        }
        break;
    }
    return MACRO_NONE;
};

static uint8_t qw_dv_swap_state = 0;

bool process_record_user (uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_LGUI) {
        if (record->event.pressed)
            qw_dv_swap_state |= 0b00000001;
        else
            qw_dv_swap_state &= ~(0b00000001);
    }
    if (keycode == KC_LCTL) {
        if (record->event.pressed)
            qw_dv_swap_state |= 0b00000010;
        else
            qw_dv_swap_state &= ~(0b00000010);
    }

    if (qw_dv_swap_state == 0b00000011) {
        layer_invert(DVORAK);
    }
    return true;
}
