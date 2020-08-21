#include QMK_KEYBOARD_H

//Define a shorter 'transparent' key code to make the keymaps more compact
#define KC_TR KC_TRNS

enum keymap_layout {
    BASE = 0,
    FUNC,
};

// #define uint16_t int
// #define uint8_t int

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = LAYOUT_ansi(
  /* Keymap VANILLA: (Base Layer) Default Layer
   * ,------------------------------------------------------------.----.
   * |Esc~| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |  0| - | = |Backspa| Ins|
   * |------------------------------------------------------------|----|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|     \| Del|
   * |------------------------------------------------------------|----|
   * |CAPS    |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgUp|
   * |------------------------------------------------------------|----|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift  |Up |PgDn|
   * |-----------------------------------------------------------------|
   * |Ctrl|Win |Alt |       Space         |Alt |Ctrl|Func|Lft| Dn |Rig |
   * `-----------------------------------------------------------------'
   */
    KC_GESC,KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL,   KC_BSPC,  KC_INS,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,  KC_DEL,
    KC_CAPS,  KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,      KC_ENT,  KC_PGUP,
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,   KC_UP,  KC_PGDN,
    KC_LCTL, KC_LGUI, KC_LALT,         KC_SPC,       KC_RALT, KC_RCTL, MO(FUNC), KC_LEFT, KC_DOWN,  KC_RGHT),

[FUNC] = LAYOUT_ansi(
   /*Keymap VANILLA: Function Layer
   * ,------------------------------------------------------------.----.
   * |Esc~| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |  0| - | = |Backspa| Ins|
   * |------------------------------------------------------------|----|
   * |MuMode | |  |  |E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|     \| Del|
   * |------------------------------------------------------------|----|
   * |AudTgl|Hz+|MS+| |  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgUp|
   * |------------------------------------------------------------|----|
   * |ClickTgl|Hz-|MS-|| C|  V|  B| N|MuTgl|  ,|  .|  /|Shift |Up |PgDn|
   * |-----------------------------------------------------------------|
   * |Ctrl|Win |Alt |       Space         |Alt |Ctrl|Func|Lft| Dn |Rig |
   * `-----------------------------------------------------------------'
   */
    KC_GRV,KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_F13,  KC_F14,
    MU_MOD, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR,     KC_TR,  RGB_TOG,
    AU_TOG,  KC_FN1,KC_FN3, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR,           RESET,  RGB_MOD,
    KC_FN5,    KC_FN2,KC_FN4, KC_TR, KC_TR, KC_TR, KC_TR, MU_TOG, RGB_VAD, RGB_VAI, KC_TR, KC_TR,        RGB_HUI,  KC_TR,
    KC_TR, KC_TR, KC_TR,         KC_TR,       KC_TR, KC_TR, KC_TR, RGB_SAD, RGB_HUD,  RGB_SAI),
};

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}
