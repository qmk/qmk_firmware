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
    NO, UP,   DOWN, LCTL, LALT, FN1,  BSPC, ENT,  SPC,  FN0,  LGUI, LEFT, RGHT, NO  ),

[DVORAK] = KC_KEYMAP(
    NO, 1,    2,    3,    4,    5,                6,    7,    8,    9,    0,    NO, \
    NO, QUOT, COMM, DOT,  P,    Y,                F,    G,    C,    R,    L,    NO, \
    NO, A,    O,    E,    U,    I,                D,    H,    T,    N,    S,    NO, \
    NO, SCLN, Q,    J,    K,    X,                B,    M,    W,    V,    Z,    NO, \
    NO, UP,   DOWN, LCTL, LALT, FN1,  BSPC, ENT,  SPC,  FN0,  LGUI, LEFT, RGHT, NO  ),

[RAISE] = KC_KEYMAP(
    NO, MRWD, MPRV, MPLY, MNXT, MFFD,             TRNS, MUTE, VOLD, VOLU, DEL,  NO, \
    NO, TAB,  ESC,  GRV,  QUES, PIPE,             BSLS, LPRN, LCBR, LBRC, QUOT, NO, \
    NO, UNDS, MINS, PLUS, EQL,  TILD,             SLSH, LEFT, DOWN, UP,   RGHT, NO, \
    NO, TRNS, TRNS, TRNS, TRNS, TRNS,             FN2,  RPRN, RCBR, RBRC, DQUO, NO, \
    NO, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, NO  )
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(RAISE), // Raise layer
    [1] = OSM(MOD_LSFT), // One shot shift
    [2] = LALT(KC_TAB) // Alt Tab key
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
