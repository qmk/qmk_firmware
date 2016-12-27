#include "lfk78.h"
#include "issi.h"
#include "action_layer.h"

//Define a shorter 'transparent' key code to make the keymaps more compact
#define KC_TR KC_TRNS

enum keymap_layout {
    BASE = 0,
    FUNC,
    SETTINGS,
};

  /* Keymap BASE: (Base Layer) Default Layer
   * ,---------.  ,------------------------------------------------------------.  ,---------.
   * | F1 | F2 |  |Esc~| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |  0| - | = |Backspa|  | Ins|PgUp|
   * |---------|  |------------------------------------------------------------|  |---------|
   * | F3 | F4 |  |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|     \|  | Del|PgDn|
   * |---------|  |------------------------------------------------------------|  `---------'
   * | F5 | F6 |  |CapsLock|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
   * |---------|  |------------------------------------------------------------|  ,----.
   * | F7 | F8 |  |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift      |  | Up |
   * |---------|  |--------------------------------------------------------------------------.
   * | F9 | F10|  |Ctrl|   |Alt |      Space          |MO(FUNC)|Alt |Ctrl|     |Lft| Dn |Rig |
   * `---------'  `-------------------------------------------------------'    `-------------'
   */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = KEYMAP(
  KC_F1, KC_F2,   KC_FN11,KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL,  KC_BSPC,  KC_INS, KC_PGUP,
  KC_F3, KC_F4,   KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,  KC_DEL, KC_PGDN,
  KC_F5, KC_F6,   MO(FUNC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,      KC_ENT,
  KC_F7, KC_F8,   KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,          KC_LSFT,  KC_UP,
  KC_F9, KC_F10,  KC_LCTL, KC_TR,   KC_LALT,            KC_SPC,            MO(FUNC), KC_RALT, KC_RCTL,  KC_LEFT, KC_DOWN, KC_RGHT),

  /* Keymap FUNCTION: Function Layer
   * ,---------.  ,-------------------------------------------------------------.  ,---------.
   * | V- | V+ |  | ` |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Backspace|  | Ins|Home|
   * |---------|  |-------------------------------------------------------------|  |---------|
   * | F3 | F4 |  |Tab  |  Q| Up|  E|PgU|  T|  Y|  U|  I|  O|  P|  [|  ]|    \  |  | Del|End |
   * |---------|  |-------------------------------------------------------------|  `---------'
   * | F5 | F6 |  |CapsLock|Lft|Dn |Rig|PgD|  G|  H|  J|  K|  L|  ;|  '|Return  |
   * |---------|  |-------------------------------------------------------------|  ,----.
   * | F7 | F8 |  |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|TG(SETTINGS)|  | Up |
   * |---------|  |--------------------------------------------------------------------------.
   * | F9 | F10|  |Ctrl|Gui |Alt |      Space          |MO(FUNC)|Alt |ctrl|     |Lft| Dn |Rig |
   * `---------'  `-------------------------------------------------------'     `-------------'
   */
[FUNC] = KEYMAP(
  KC_VOLD, KC_VOLU,  KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,  KC_TR, KC_HOME,
  KC_TR,   KC_TR,    KC_TR,  KC_TR, KC_UP, KC_TR, KC_PGUP, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR,   KC_TR,  KC_TR, KC_END,
  KC_TR,   KC_TR,    KC_TR,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR,    KC_TR,
  KC_TR,   KC_TR,    KC_TR,    KC_TR,  KC_TR,  KC_TR,  KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR,       TG(SETTINGS),  KC_TR,
  KC_TR,   KC_TR,    KC_TR, KC_TR, KC_TR,                  KC_TR,                             MO(FUNC), KC_TR, KC_TR,   KC_TR,  KC_TR, KC_TR),

  /* Keymap SETTINGS: Settings Layer
   * ,---------.  ,-----------------------------------------------------------.  ,---------.
   * |LEDT|    |  |   |   |   |   |   |   |   |   |   |   |   |   |   |Tgl Aud|  |Hz+ |Sec+|
   * |---------|  |-----------------------------------------------------------|  |---------|
   * |    |    |  |     |   |   |   |Red|   |   |   |   |   |   |   |   |Debug|  |Hz- |Sec-|
   * |---------|  |-----------------------------------------------------------|  `---------'
   * |    |    |  |       |   |   |   |   |Grn|   |   |   |   |   |   |Tgl LED|
   * |---------|  |-----------------------------------------------------------|  ,----.
   * |    |    |  |        |   |   |   |   |Blu|   |   |   |   |   |Layer Clr |  |LED+|
   * |---------|  |------------------------------------------------------------------------.
   * | RST| DBG|  |    |    |    |                       |lyrClr|    |   |   |LED-|    |
   * `---------'  `------------------------------------------------------'   `-------------'
   */
[SETTINGS] = KEYMAP(
  KC_FN10, KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    KC_FN8,    KC_FN4, KC_FN6,
  KC_NO,   KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, KC_LCTL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_FN9,    KC_FN5, KC_FN7,
  KC_NO,   KC_NO,    KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_LALT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,       KC_FN3,
  KC_NO,   KC_NO,    KC_NO,     KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_LGUI, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,         KC_FN0,    KC_FN1,
  RESET,   DEBUG,    KC_NO, KC_NO, KC_NO,                  KC_NO,                              KC_FN0, KC_NO, KC_NO,    KC_NO, KC_FN2, KC_NO),
};

const uint16_t PROGMEM fn_actions[] = {
    ACTION_FUNCTION(LFK_CLEAR),        // FN0 - reset layers
    ACTION_FUNCTION(LFK_LED_UP),   // FN1 - increase LED brightness (R/G/B set via ctl/alt/gui modifiers, defaults to backlight)
    ACTION_FUNCTION(LFK_LED_DOWN),  // FN2 - decrease LED brightness (R/G/B set via ctl/alt/gui modifiers, defaults to backlight)
    ACTION_FUNCTION(LFK_LED_TOGGLE),   // FN3 - toggle all LEDs
    ACTION_FUNCTION(LFK_CLICK_FREQ_HIGHER),   // FN4 - Increase Freq of audio click
    ACTION_FUNCTION(LFK_CLICK_FREQ_LOWER),  // FN5 - Decrease Freq of audio click
    ACTION_FUNCTION(LFK_CLICK_TIME_LONGER),   // FN6 - Increase length of audio click
    ACTION_FUNCTION(LFK_CLICK_TIME_SHORTER),  // FN7 - Decrease length of audio click
    ACTION_FUNCTION(LFK_CLICK_TOGGLE),  // FN8 - Toggle audio click
    ACTION_FUNCTION(LFK_DEBUG_SETTINGS),  // FN9 - xprintf() current LED and Audio settings
    ACTION_FUNCTION(LFK_LED_TEST),  // FN10 cycle through LEDs for testing
    ACTION_FUNCTION(LFK_ESC_TILDE), // FN11 esc+shift = ~, else escape
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
