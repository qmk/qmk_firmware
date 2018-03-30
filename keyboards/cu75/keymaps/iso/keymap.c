#include "cu75.h"
#include "action_layer.h"

//Define a shorter 'transparent' key code to make the keymaps more compact
#define KC_TR KC_TRNS

enum keymap_layout {
    VANILLA = 0,
    FUNC,
    SETTINGS,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[VANILLA] = ISO_KEYMAP(
  /* Keymap VANILLA: (Base Layer) Default Layer
   * ,------------------------------------------------------------.----.
   * |Esc | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|F13|F14| F15|
   * |------------------------------------------------------------|----|
   * |  ~ | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |  0| - | = |Backspa| Ins|
   * |------------------------------------------------------------|----|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  Ret | Del|
   * |--------------------------------------------------------.   |----|
   * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  # |   |PgUp|
   * |------------------------------------------------------------|----|
   * |Shft| \ |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up |PgDn|
   * |-----------------------------------------------------------------|
   * |Ctrl|Win |Alt |       Space         |Alt |Ctrl|Func|Lft| Dn |Rig |
   * `-----------------------------------------------------------------'
   */
    KC_ESC,KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_F13,  KC_F14, KC_F15,
    KC_GRV,KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL,  KC_BSPC,  KC_INS,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_ENT,   KC_DEL,
    KC_CAPS,  KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,     KC_NUHS,  KC_PGUP,
    KC_LSFT, KC_NUBS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,   KC_UP,  KC_PGDN,
    KC_LCTL, KC_LGUI, KC_LALT,KC_SPC, KC_SPC, KC_SPC,KC_RALT, KC_RCTL, MO(FUNC), KC_LEFT, KC_DOWN,  KC_RGHT),

[FUNC] = KEYMAP(
  /* Keymap VANILLA: Function Layer
   * ,-------------------------------------------------------------------.
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |   |    |    |
   * |-------------------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |       |     |
   * |-------------------------------------------------------------------|
   * |    |   |   |   |   |   |   |   |   |   |   |   |   |     | RGB_TOG|
   * |-------------------------------------------------------------------|
   * |       |   |   |   |   |   |   |   |   |   |   |   |RESET |RGB_MODE|
   * |-------------------------------------------------------------------|
   * |       |   |   |   |   |   |   |   |   |   |   |      |RGB_HUI|    |
   * |-------------------------------------------------------------------|
   * |    |    |    |               |    |   |   |RGB_SAD|RGB_HUD|RGB_SAI|
   * `-------------------------------------------------------------------'
   */
    KC_TR,KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR,
    KC_TR,KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR,  KC_TR,
    KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR,KC_TR,  RGB_TOG,
    KC_TR,  KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR,      RESET,  RGB_MOD,
    KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, RGB_VAD, RGB_VAI, KC_TR, KC_TR, RGB_HUI,  KC_TR,
    KC_TR, KC_TR, KC_TR,   KC_TR,      KC_TR,          KC_TR, KC_TR, KC_TR, KC_TR, RGB_SAD, RGB_HUD,  RGB_SAI),
};

const uint16_t PROGMEM fn_actions[] = {
    ACTION_FUNCTION(LFK_CLEAR),                               // FN0 - reset layers
    ACTION_FUNCTION(LFK_ESC_TILDE),                           // FN1 - esc+shift = ~, else escape
  };


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
      }
    return MACRO_NONE;
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
