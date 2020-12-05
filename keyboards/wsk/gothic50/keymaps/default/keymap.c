#include QMK_KEYBOARD_H

// Tap Dance Declarations
enum {
    TD_SCAPS = 0
};

#define SCAPS_LG TD(TD_SCAPS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_GESC,        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,      KC_PSCR, \
    LCTL_T(KC_TAB), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,            KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT,                  KC_INS, \
    SCAPS_LG,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,            MO(2),   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,      KC_UP,       KC_DEL, \
    KC_APP,         KC_LGUI,          KC_LALT, MO(1),   LT(1,KC_SPC),    KC_BSPC, KC_RALT, KC_RCTL,                        KC_LEFT, KC_DOWN, KC_RGHT \
  ),

  [1] = LAYOUT(
    KC_TILD,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,          KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS, KC_EQL,             KC_PAUS, \
    _______, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______,       _______, _______, _______, _______, KC_SCLN, KC_BSLS,                       KC_MUTE, \
    _______, RGB_TOG, RGB_HUD, RGB_SAD, RGB_VAD, _______,       _______, _______, _______, _______, _______, _______,          KC_PGUP,       KC_MPLY, \
    _______, _______,          _______, _______, _______,       _______, _______, _______,                            KC_HOME, KC_PGDN, KC_END \
  ),

  [2] = LAYOUT(
    _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,   KC_F12,         RESET, \
    _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,                   _______, \
    _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,           KC_VOLU,   _______,\
    _______, _______,          _______, _______, _______,      _______, _______, _______,                             KC_MPRV, KC_VOLD, KC_MNXT \
  )
};

void matrix_init_user(void) {
  // set CapsLock LED to output and low
  setPinOutput(F6);
  writePinLow(F6);
  // set NumLock LED to output and low
  setPinOutput(F5);
  writePinLow(F5);
  // set ScrollLock LED to output and low
  setPinOutput(F4);
  writePinLow(F4);
}

layer_state_t layer_state_set_user(layer_state_t state)
{
    writePin(F4, (state & 0x1));
    writePin(F5, (state & 0x2));
    writePin(F6, (state & 0x4));
    return state;
}

// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // double tap for caps
    [TD_SCAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS)
};
