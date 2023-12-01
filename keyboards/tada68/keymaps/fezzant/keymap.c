#include QMK_KEYBOARD_H

// Layers

#define _BL 0
#define _FL 1
#define _NUM 2
#define _BSPC 3

// Macros
// name macros here for keymap reference
enum {
  EMAIL_ADD = SAFE_RANGE,
  OTHER_MACRO
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if(record->event.pressed){
    switch(keycode) {
      // copy these lines to define new macro
      case EMAIL_ADD:
        SEND_STRING("email@example.com");
        return false; break;
      // copy to here
      case OTHER_MACRO:
        SEND_STRING("The Other Macro");
        return false; break;
    }
  }
  return true;
};

// Keymaps

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * .----------------------------------------------------------------.
   * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |~ ` |
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Del |
   * |----------------------------------------------------------------|
   * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |Home|
   * |----------------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Up |End |
   * |----------------------------------------------------------------|
   * |Ctrl|Win |Alt |        Space          |Alt| FN|Ctrl|Lft|Dwn|Rig |
   * '----------------------------------------------------------------'
   */
[_BL] = LAYOUT_ansi(
  KC_ESC,    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL, KC_BSPC, KC_GRAVE,
  KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,KC_BSLS,KC_DELETE,
  LT(_BSPC,KC_CAPS), KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,         KC_ENT,KC_HOME,
  KC_LSFT,         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,   KC_RSFT,KC_UP,KC_END,
  KC_LCTL, KC_LGUI,KC_LALT,                KC_SPC,                        KC_RALT,MO(_FL),KC_RCTL, KC_LEFT,KC_DOWN,KC_RGHT),


  /* Keymap _FL: Function Layer
   * .-----------------------------------------------------------------.
   * |   | F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Del    |Paus |
   * |-----------------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |BLB|BL-|BL |BL+|Foobr|ToNUM|
   * |-----------------------------------------------------------------|
   * |KC_NO |   |   |   |   |   |   |   |   |   |   |Mnu|        |PgUp |
   * |-----------------------------------------------------------------|
   * |        |   |   |   |   |   |   |   |   |   |   |      |   |PgDn |
   * |-----------------------------------------------------------------|
   * |WinUl|WinLk|   |                      |   |   |    |Nxt|Stp|Prev |
   * '-----------------------------------------------------------------'
   */
[_FL] = LAYOUT_ansi(
  _______, KC_F1 ,KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_PAUSE ,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,BL_BRTG,BL_DOWN,BL_TOGG, BL_UP,  KC_MAIL,TG(_NUM),
  XXXXXXX,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_APPLICATION,        _______,KC_PGUP,
  _______,_______,_______,_______,_______,_______, _______,_______,_______,_______,_______,KC_BTN1, KC_MS_U, KC_PGDN,
  MAGIC_UNNO_GUI,MAGIC_NO_GUI,_______,                 _______,               _______,_______,_______,KC_MPRV,KC_MSTP, KC_MNXT),


  /* Keymap _NUM: Numpad Layer
   * .----------------------------------------------------------------.
   * |Esc| 1 | 2 | 3 | 4 | 5 | 6 |NP7|Np8|Np9|   | - | + |Backspc|CALC| 15
   * |----------------------------------------------------------------|
   * |Tab |NumL| up|   |   |   |Np4|Np5|Np6|   |   | / | * |     |    | 15
   * |----------------------------------------------------------------|
   * |To__BL|lft|dwn|rit|   |   |Np1|Np2|Np3|   |   |   |Enter   |Prsc| 14
   * |----------------------------------------------------------------|
   * |Shift   | Z | X | C | V |   |Np.|Np.|Np.|   |   |      |msU|Rclk| 14
   * |----------------------------------------------------------------|
   * |Ctrl|Win |Alt |            Np0       |Emal|   |Lclk|msL|msD|msR | 10
   * '----------------------------------------------------------------'
   */
[_NUM] = LAYOUT_ansi(
  KC_ESC,    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_P7,   KC_P8,   KC_P9,XXXXXXX,   KC_KP_MINUS, KC_KP_PLUS, KC_BSPC,KC_CALC,
  KC_TAB,KC_NUM, KC_UP,XXXXXXX,XXXXXXX, XXXXXXX,KC_P4,KC_P5,KC_P6,XXXXXXX,XXXXXXX,KC_PSLS,KC_PAST, XXXXXXX,_______,
  TG(_NUM), KC_LEFT, KC_DOWN, KC_RIGHT,XXXXXXX,XXXXXXX,KC_P1,KC_P2,KC_P3,XXXXXXX,XXXXXXX,XXXXXXX, KC_KP_ENTER,KC_PSCR,
  KC_LSFT, KC_Z, KC_X, KC_C, KC_V,XXXXXXX, KC_PDOT, KC_PDOT, KC_PDOT,XXXXXXX,XXXXXXX,XXXXXXX, KC_MS_U, KC_BTN2,
  KC_LCTL, KC_LGUI, KC_LALT,KC_P0,EMAIL_ADD,_______,KC_BTN1,KC_MS_L,KC_MS_D, KC_MS_R),


  /* Keymap _BSPC: back_SPACE Layer
   * .----------------------------------------------------------------.
   * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |
   * |----------------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |Up |   |   |   |   |     |    |
   * |----------------------------------------------------------------|
   * |      |   |   |   |   |   |   |Lft|Dwn|Rig|End|   |        |    |
   * |----------------------------------------------------------------|
   * |        |   |   |   |   |   |   |   |   |   |   |      |   |    |
   * |----------------------------------------------------------------|
   * |    |    |    |       Backspace         |   |NO |   |   |   |   |
   * '----------------------------------------------------------------'
   */
[_BSPC] = LAYOUT_ansi(
  _______, _______ ,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______,_______,_______,_______,_______,_______,_______,_______,KC_UP,_______,_______,_______, _______, _______,_______,
  _______,_______,_______,_______,_______,_______,_______,KC_LEFT,KC_DOWN,KC_RIGHT,KC_END,_______,        _______,_______,
  _______,_______,_______,_______,_______,_______, _______,_______,_______,_______,_______,_______, _______, _______,
  _______,_______,_______,                 KC_BSPC,                 _______,XXXXXXX,_______,_______,_______, _______)


};
