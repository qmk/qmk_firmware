#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
#define _BL 0 // Base Layer
#define _FN 1 // Function Layer
#define _CL 2 // Control+ Layer

// Add names for complex momentary keys, to keep the keymap matrix aligned better.
#define CTL_ESC MT(MOD_LCTL,KC_ESC)
#define GUI_ENT MT(MOD_RGUI, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BL] = LAYOUT(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_F13,   MO(_FN),  KC_DEL,
    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_DEL,   KC_BSPC,  KC_HOME,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGUP,
    CTL_ESC,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,                      KC_ENT,   KC_PGDN,
    KC_LSFT,  MO(_FN),  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,    KC_END,
    MO(_CL),  KC_LALT,  KC_LGUI,                      KC_SPC,   KC_SPC,   KC_SPC,                       GUI_ENT,  KC_RALT,  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
  ),

  [_FN] = LAYOUT(
    QK_BOOT,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  QK_BOOT,  _______,
    _______,  RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_HUD,  RGB_SAI,  RGB_SAD,  RGB_VAI,  RGB_VAD,  _______,  _______,  _______,  _______,  _______,            _______,
    _______,  KC_VOLD,  KC_VOLU,  KC_MUTE,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,
    _______,  _______,  _______,  _______,  BL_DOWN,  BL_TOGG,  BL_UP,    BL_STEP,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
    _______,  _______,  _______,                      _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______
  ),

  [_CL] = LAYOUT(
    LCTL(KC_ESC),   LCTL(KC_F1),    LCTL(KC_F2),    LCTL(KC_F3),  LCTL(KC_F4),  LCTL(KC_F5),  LCTL(KC_F6),  LCTL(KC_F7),  LCTL(KC_F8), LCTL(KC_F9),    LCTL(KC_F10),   LCTL(KC_F11),   LCTL(KC_F12),   LCTL(KC_PSCR),  _______,        LCTL(KC_DEL),
    KC_ESC,         LCTL(KC_1),     LCTL(KC_2),     LCTL(KC_3),   LCTL(KC_4),   LCTL(KC_5),   LCTL(KC_6),   LCTL(KC_7),   LCTL(KC_8),  LCTL(KC_9),     LCTL(KC_0),     LCTL(KC_MINS),  LCTL(KC_EQL),   LCTL(KC_DEL),   KC_DEL,         LCTL(KC_HOME),
    LCTL(KC_TAB),   LCTL(KC_Q),     LCTL(KC_W),     LCTL(KC_E),   LCTL(KC_R),   LCTL(KC_T),   LCTL(KC_Y),   LCTL(KC_U),   LCTL(KC_I),  LCTL(KC_O),     KC_PGUP,        LCTL(KC_LBRC),  LCTL(KC_RBRC),  LCTL(KC_BSLS),                  LCTL(KC_PGUP),
    CTL_ESC,        LCTL(KC_A),     LCTL(KC_S),     LCTL(KC_D),   LCTL(KC_F),   LCTL(KC_G),   KC_LEFT,      KC_DOWN,      KC_UP,       KC_RGHT,        LCTL(KC_SCLN),  LCTL(KC_QUOT),                                  LCTL(KC_ENT),   LCTL(KC_PGDN),
    LCTL(KC_LSFT),  _______,        LCTL(KC_Z),     LCTL(KC_X),   LCTL(KC_C),   LCTL(KC_V),   LCTL(KC_B),   KC_PGDN,      LCTL(KC_M),  LCTL(KC_COMM),  LCTL(KC_DOT),   LCTL(KC_SLSH),  LCTL(KC_RSFT),                  LCTL(KC_UP),    LCTL(KC_END),
    _______,        LCTL(KC_LALT),  LCTL(KC_LGUI),                              LCTL(KC_SPC), LCTL(KC_SPC), LCTL(KC_SPC),                              LCTL(KC_RGUI),  LCTL(KC_RALT),  LCTL(KC_RCTL),  LCTL(KC_LEFT),  LCTL(KC_DOWN),  LCTL(KC_RGHT)
  ),

};
