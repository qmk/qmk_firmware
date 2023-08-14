#include QMK_KEYBOARD_H

#define MODS_PRESSED(btn)  (get_mods() & (MOD_BIT(KC_L##btn)|MOD_BIT(KC_R##btn)))

enum custom_keycodes {
  SFT_ESC = SAFE_RANGE,
  ALT_F4
};

#define SET_WHETHER(mask, btn1, btn2) \
if (record->event.pressed) {          \
    if (mask) {                       \
        add_key(btn2);                \
        send_keyboard_report();       \
    } else {                          \
        add_key(btn1);                \
        send_keyboard_report();       \
    }                                 \
} else {                              \
    if (mask) {                       \
        del_key(btn2);                \
        send_keyboard_report();       \
    } else {                          \
        del_key(btn1);                \
        send_keyboard_report();       \
    }                                 \
}                                     \


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  LAYOUT( /* Base */
    SFT_ESC, KC_1,    KC_2,    KC_3,    ALT_F4,  KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
    TT(1),   KC_LCTL, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RGUI, KC_APP,  KC_RCTL
  ),
  LAYOUT( /* Cursor layer */
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
    TT(3),   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS,
    TT(2),   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME,          _______,
    _______,          _______, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_PGDN, KC_END,           KC_UP,
    _______, _______, _______,                            _______,                            _______, KC_LEFT, KC_DOWN, KC_RGHT
  ),
  LAYOUT( /* Keypad layer */
    TO(0),   KC_1,    KC_2,    KC_3,    ALT_F4,  KC_5,    KC_6,    KC_P7,   KC_P8,   KC_P9,   KC_P0,   KC_PMNS, KC_PPLS, KC_BSPC,
    _______, _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   _______, _______,          _______,
    _______,          _______, _______, _______, _______, _______, _______, KC_P0,   KC_PDOT, KC_BTN1, KC_MS_U,          KC_BTN2,
    _______, _______, _______,                            _______,                            KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN3
  ),
  LAYOUT( /* Multimedia layer */
    TO(0),   _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,
    _______, _______, KC_WAKE, _______, _______, _______, _______, _______, _______, _______, KC_MSTP, KC_MPRV, KC_MNXT, _______,
    _______, _______, KC_SLEP, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______,          _______, KC_PWR,  _______, _______, _______, _______, _______, _______, KC_BTN1, KC_WH_U,          KC_BTN2,
    _______, _______, _______,                            KC_MPLY,                            KC_WH_L, KC_WH_D, KC_WH_R, KC_BTN3
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SFT_ESC:
      SET_WHETHER(MODS_PRESSED(SFT), KC_ESC, KC_GRAVE);

      return false;

    case ALT_F4:
      SET_WHETHER(MODS_PRESSED(ALT), KC_4, KC_F4);

      return false;

    default:
      return true;
  }
}

void matrix_init_user(void) {
  setPinOutput(C7);
  writePinLow(C7);
}

layer_state_t layer_state_set_user(layer_state_t state) {
  if (get_highest_layer(state)) {
    writePinHigh(C7);
  } else {
    writePinLow(C7);
  }
  return state;
}
