#include QMK_KEYBOARD_H

enum QFR_layers {
  _COLEMAK,
  _QWERTY,
  _DVORAK,
  _LOWER,
  _MOUSE
};

enum QFR_keycodes {
  COLEMAK = SAFE_RANGE,
  QWERTY,
  DVORAK,
  LOWER,
  MOUSE
};

enum custom_macros {
  R_PIPE,
  R_POINT
};

#define SPC_LW LT(_LOWER, KC_SPC)
#define MSE MO(_MOUSE)
#define PIPE M(R_PIPE)
#define POINT M(R_POINT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_COLEMAK] = LAYOUT_tkl(\
      KC_ESC,    KC_F1,     KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_PSCR,KC_SLCK,KC_PAUS, \
      KC_GRV,    KC_1,      KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS, KC_EQL, KC_BSPC,  KC_INS, KC_HOME,KC_PGUP, \
      KC_TAB,    KC_Q,      KC_W,   KC_F,   KC_P,   KC_G,   KC_J,   KC_L,   KC_U,   KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC,KC_BSLS,  KC_DEL, KC_END, KC_PGDN, \
      KC_BSPC,   KC_A,      KC_R,   KC_S,   KC_T,   KC_D,   KC_H,   KC_N,   KC_E,   KC_I,    KC_O,    KC_QUOT,         KC_ENT ,                           \
      KC_LSPO,KC_NUBS,KC_Z, KC_X,   KC_C,   KC_V,   KC_B,   KC_K,   KC_M,   KC_COMM, KC_DOT, KC_SLSH,          KC_RSPC,                   KC_UP,          \
      KC_LCTL,KC_LGUI,      KC_LALT,                SPC_LW,                                  MSE,     KC_RGUI, KC_APP, KC_RCTL,  KC_LEFT,KC_DOWN,KC_RGHT
      ),

[_QWERTY] = LAYOUT_tkl(\
       KC_ESC, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,  KC_F12,             KC_PSCR, KC_SLCK, KC_PAUS, \
       KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP, \
       KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN, \
       KC_CAPS,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,          KC_ENT, \
       KC_LSFT,KC_NUBS,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,          KC_RSFT,            KC_UP, \
       KC_LCTL,KC_LGUI,KC_LALT,                SPC_LW,                                 MSE,    KC_RGUI , KC_APP,  KC_RCTL,   KC_LEFT, KC_DOWN, KC_RGHT
       ),

[_DVORAK] = LAYOUT_tkl(\
       KC_ESC, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,  KC_F12,             KC_PSCR, KC_SLCK, KC_PAUS, \
       KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP, \
       KC_TAB, KC_QUOT,KC_COMM,KC_DOT, KC_P,   KC_Y,   KC_F,   KC_G,   KC_C,   KC_R,   KC_L,   KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN, \
       KC_BSPC,KC_A,   KC_O,   KC_E,   KC_U,   KC_I,   KC_D,   KC_H,   KC_T,   KC_N,   KC_S,   KC_QUOT,          KC_ENT, \
       KC_LSFT,KC_NUBS,KC_SCLN,KC_Q,   KC_J,   KC_K,   KC_X,   KC_B,   KC_M,   KC_W,   KC_V,   KC_Z,             KC_RSFT,            KC_UP, \
       KC_LCTL,KC_LGUI,KC_LALT,                SPC_LW,                                 MSE,    KC_RGUI, KC_APP,  KC_RCTL,   KC_LEFT, KC_DOWN, KC_RGHT
       ),

[_LOWER] = LAYOUT_tkl(\
      RESET,    _______,    _______,   _______, _______,  KC_MPLY,   KC_MSTP,   KC_MPRV,   KC_MNXT,  _______, KC_MUTE, KC_VOLD, KC_VOLU,           QWERTY, COLEMAK,DVORAK, \
      KC_TILD,  KC_EXLM,    KC_AT,     KC_HASH,  KC_DLR,  KC_PERC,   KC_CIRC,   KC_AMPR,   KC_ASTR,  KC_LBRC, KC_RBRC, KC_UNDS, KC_PLUS, KC_BSPC,  _______,_______,_______, \
      KC_TAB,   KC_PGUP,    KC_HOME,   KC_UP,    KC_END,  XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, KC_PIPE,  _______,_______,_______, \
      KC_CAPS,  KC_PGDN,    KC_LEFT,   KC_DOWN,  KC_RGHT, XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX, XXXXXXX, _______,          _______,                           \
      _______,XXXXXXX,POINT,PIPE,      KC_LCBR,  KC_LBRC, KC_GRV,    KC_PIPE,   KC_RBRC,   KC_RCBR,  _______, _______,                   _______,          _______,         \
      _______,  _______,    _______,             _______,                       KC_RALT,   _______,  _______, _______,                            _______,_______,_______  \
      ),

[_MOUSE] = LAYOUT_tkl(\
      _______,  _______,   _______,   _______,  _______, _______,   _______,   _______,   _______,  _______, _______, _______, _______,            _______,_______,_______, \
      KC_GRV,   KC_1,      KC_2,      KC_3,     KC_4,    KC_5,      KC_6,      KC_7,      KC_8,     KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_DEL,    _______,_______,_______, \
      KC_TAB,   KC_WH_U,   KC_WH_L,   KC_MS_U,  KC_WH_R, XXXXXXX,   XXXXXXX,   KC_BTN3,   KC_BTN4,  KC_BTN5, XXXXXXX, KC_LBRC, KC_RBRC, KC_BSLS,   _______,_______,_______, \
      KC_BSPC,  KC_WH_D,   KC_MS_L,   KC_MS_D,  KC_MS_R, XXXXXXX,   XXXXXXX,   KC_BTN1,   KC_BTN2,  XXXXXXX, XXXXXXX, XXXXXXX,          _______,                            \
      _______,XXXXXXX,PIPE,POINT,     XXXXXXX,  XXXXXXX, XXXXXXX,   XXXXXXX,   XXXXXXX,   _______,  _______,  _______,                  _______,           _______,         \
      _______,  _______,   _______,             KC_ACL2,                       MSE,       _______,  _______,  _______,                             _______,_______,_______  \
      )
};

// Macros to send R pointer & dplyr pipe
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch(id) {
        case R_POINT:
            if (record->event.pressed) { // pointer
                SEND_STRING("<- ");
//                return MACRO(D(LSFT), T(COMM), U(LSFT), T(MINS), END);
            }
            break;
        case R_PIPE:
            if (record->event.pressed) { // dplyr pipe
                SEND_STRING("%>% ");
//                return MACRO(D(LSFT), T(5), T(DOT), T(5), U(LSFT), END);
            }
            break;
    }
    return MACRO_NONE;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;
  }
  return true;
}
