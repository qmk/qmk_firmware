#include "lfk78_revc.h"
#include "issi.h"
#include "lighting.h"
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
   * | F5 | F6 |  |MO(FUNC)|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
   * |---------|  |------------------------------------------------------------|  ,----.
   * | F7 | F8 |  |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|           |  | Up |
   * |---------|  |-------------------------------------------------------------------------.
   * | F9 | F10|  |Ctrl|Alt |Cmd |      Space            |Cmd |Alt |CTRL |    |Lft| Dn |Rig |
   * `---------'  `------------------------------------------------------'    `-------------'
   */


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = KEYMAP(
  KC_VOLD, KC_VOLU,   KC_FN5,KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL,   KC_BSPC,  KC_INS, KC_PGUP,
  KC_F3, KC_F4,       KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,  KC_DEL, KC_PGDN,
  KC_F5, KC_F6,       MO(FUNC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,      KC_ENT,
  KC_F7, KC_F8,       KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,          KC_RSFT,   KC_UP,
  KC_F9, KC_F10,      KC_LCTL, KC_LALT, KC_LGUI,              KC_SPC,           KC_LGUI, KC_LALT, MO(FUNC), KC_LEFT, KC_DOWN, KC_RGHT),
  /* Keymap FUNCTION: Function Layer
   * ,---------.  ,-------------------------------------------------------------.  ,---------.
   * | V- | V+ |  | ` |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Delete   |  | Ins|Home|
   * |---------|  |-------------------------------------------------------------|  |---------|
   * |    |    |  |Tab  |Hom| Up|End|PgU|   |   |   |   |   |   |   |   |       |  | Del|End |
   * |---------|  |-------------------------------------------------------------|  `---------'
   * |    |    |  |MO(FUNC)|Lft|Dn |Rig|PgD|   |Lft|Dwn| Up|Rgt|   |   |        |
   * |---------|  |-------------------------------------------------------------|  ,----.
   * |    |    |  |Shift   |   |   |   |   |   |   |   |   |   |   |shift       |  | Up |
   * |---------|  |--------------------------------------------------------------------------.
   * |    | F10|  |Ctrl|Alt |Cmd |        PgD            |Cmd |Alt |CTRL |     |Lft| Dn |Rig |
   * `---------'  `------------------------------------------------------'     `-------------'
   */
[FUNC] = KEYMAP(
  KC_TR,   KC_TR,    KC_GRV,  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,       KC_DEL,  KC_TR, KC_HOME,
  KC_TR,   KC_TR,    KC_NO,KC_HOME, KC_UP, KC_END, KC_PGUP, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,         KC_NO,  KC_TR, KC_END,
  KC_TR,   KC_TR,    KC_TR,   KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_NO,    KC_NO,
  KC_TR,   KC_TR,    KC_TR,     KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,             TG(SETTINGS),  KC_TR,
  KC_TR,   KC_TR,    KC_TR,  KC_TR, KC_TR,                  KC_PGDN,                           KC_TR, KC_TR, KC_TR,         KC_TR,  KC_TR, KC_TR),

  /* Keymap SETTINGS: Settings Layer
   * ,---------.  ,-----------------------------------------------------------.  ,---------.
   * |LEDT|    |  |   |   |   |   |   |   |   |   |   |   |   |   |   |Tgl Aud|  |Hz+ |Sec+|
   * |---------|  |-----------------------------------------------------------|  |---------|
   * |    |    |  |     |   |   |   |Red|   |   |   |   |   |   |   |   |Debug|  |Hz- |Sec-|
   * |---------|  |-----------------------------------------------------------|  `---------'
   * |    |    |  |LayrClr|   |   |   |   |Grn|   |   |   |   |   |   |Tgl LED|
   * |---------|  |-----------------------------------------------------------|  ,----.
   * |    |    |  |        |   |   |   |   |Blu|   |   |   |   |   |Layer Clr |  |LED+|
   * |---------|  |------------------------------------------------------------------------.
   * | RST| DBG|  |    |    |    |                       |    |    |     |   |   |LED-|    |
   * `---------'  `------------------------------------------------------'   `-------------'
   */
[SETTINGS] = KEYMAP(
  KC_FN4, KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO,    KC_NO, KC_NO,
  KC_NO,   KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, KC_LCTL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,    KC_NO, KC_NO,
  KC_NO,   KC_NO,    KC_FN0,  KC_NO, KC_NO, KC_NO, KC_NO, KC_LALT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,       KC_FN3,
  KC_NO,   KC_NO,    KC_NO,     KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_LGUI, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,         KC_FN0,    KC_FN1,
  RESET,   DEBUG,    KC_NO, KC_NO, KC_NO,                  KC_NO,                              KC_NO, KC_NO, KC_NO,    KC_NO, KC_FN2, KC_NO),
};


const uint16_t PROGMEM fn_actions[] = {
    ACTION_FUNCTION(LFK_CLEAR),               // FN0 - reset layers
    ACTION_FUNCTION(LFK_LED_UP),              // FN1 - increase LED brightness (R/G/B set via ctl/alt/gui modifiers, defaults to backlight)
    ACTION_FUNCTION(LFK_LED_DOWN),            // FN2 - decrease LED brightness (R/G/B set via ctl/alt/gui modifiers, defaults to backlight)
    ACTION_FUNCTION(LFK_LED_TOGGLE),          // FN3 - toggle all LEDs
    ACTION_FUNCTION(LFK_LED_TEST),            // FN4 cycle through LEDs for testing
    ACTION_FUNCTION(LFK_ESC_TILDE),           // FN5 esc+shift = ~, else escape
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
