#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

LAYOUT_base_kit_all(
        KC_ESC,    KC_TAB,    KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_MINUS,  KC_BSPC,
        KC_PGUP,   KC_LCTL,   KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_QUOTE,  KC_ENT,
        KC_PGDN,   KC_LSFT,   KC_NUBS,   KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   MO(3),
        KC_END,    KC_DEL,    KC_LGUI,   KC_LALT,                         MO(1),                KC_SPACE,             KC_CAPS,   MO(2),     KC_MENU,   KC_RCTL
    ),

LAYOUT_base_kit_all(
        KC_GRAVE,  _______,   KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_UNDS,   _______,
        KC_TILD,   _______,   KC_EXLM,   KC_AT,     KC_HASH,   KC_DLR,    KC_PERC,   KC_CIRC,   KC_AMPR,   KC_ASTR,   KC_LPRN,   KC_RPRN,   KC_DQT,    _______,
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,                         _______,              _______,              _______,   _______,   _______,   _______
    ),

LAYOUT_base_kit_all(
        KC_BSLS,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_EQUAL,  _______,
        KC_PIPE,   KC_CAPS,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_PLUS,   _______,
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_LBRC,   KC_RBRC,   _______,
        _______,   _______,   _______,   _______,                         _______,              _______,              _______,   _______,   _______,   _______
    ),

LAYOUT_base_kit_all(
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_UP,     _______,   _______,
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_LEFT,   KC_RGHT,   _______,   _______,
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_DOWN,   _______,   _______,
        _______,   _______,   _______,   _______,                         _______,              _______,              _______,   _______,   _______,   _______
    )

};



layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case 1:
        rgblight_setrgb (RGB_CORAL);
        break;
    case 2:
        rgblight_setrgb (RGB_RED);
        break;
    case 3:
        rgblight_setrgb (RGB_BLUE);
        break;
    default: //  for any other layers, or the default layer
        rgblight_setrgb (RGB_GREEN);
        break;
    }
  return state;
}
