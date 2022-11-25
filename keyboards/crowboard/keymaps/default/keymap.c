#include QMK_KEYBOARD_H

#define CTLA LCTL(KC_A)
#define CAE LCTL(LALT(KC_END))
#define CAD LCTL(LALT(KC_DEL))
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

enum custom_keycodes {
    PASS = SAFE_RANGE,
};

enum crow_layers {
_QWERTY,
_LOWER,
_RAISE,
_ADJUST,
};




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT (
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        LCTL_T(KC_A),    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT,
        LSFT_T(KC_Z),    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,    KC_DOT, RSFT_T(KC_SLSH),
                          KC_LCTL,    LOWER,    KC_SPACE,    KC_BSPC,    RAISE,    KC_RALT
    ),

    [_LOWER] = LAYOUT_ortho_4x10(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_TAB,    KC_LEFT,    KC_DOWN,    KC_UP,    KC_RIGHT,    KC_TRNS,    KC_MINUS,    KC_EQUAL,    KC_LBRC,    KC_RBRC,
        KC_LCTL,    KC_GRAVE,    KC_LGUI,    KC_LALT,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_BSLS,    KC_SCLN,
                          KC_TRNS,    LOWER,    KC_TRNS,    KC_ENTER,    RAISE,    KC_TRNS
    ),
    [_RAISE] = LAYOUT_ortho_4x10(
        KC_EXLM,    KC_AT,    KC_HASH,    KC_DLR,    KC_PERC,    KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RPRN,
        KC_ESC,    KC_DEL,    CTLA,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_UNDS,    KC_PLUS,    KC_LCBR,    KC_RCBR,
        KC_CAPS,    KC_TILDE,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_PIPE,    KC_COLN,
                          KC_TRNS,    LOWER,    KC_TRNS,    KC_TRNS,    RAISE,    KC_TRNS
    ),
    [_ADJUST] = LAYOUT_ortho_4x10(
        KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,
        KC_F11,    KC_F12,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    PASS,    CAE,    CAD,    CAD,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                          KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
};


bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_A):
            // Do not force the mod-tap key press to be handled as a modifier
            // if any other key was pressed while the mod-tap key is held down.
            return true;
        default:
            // Force the mod-tap key press to be handled as a modifier if any
            // other key was pressed while the mod-tap key is held down.
            return false;
    }
}



layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}



