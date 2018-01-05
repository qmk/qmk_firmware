// XD60 Rev 2.0

#include "xd60.h"
#include "action_layer.h"
//#include "action_tapping.h"
#include "backlight.h"

// Define tapping term
#define TAPPING_TERM    150

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
// Layer definitions~
#define _BL 0
#define _FL 1
#define _LK 2

// RShift TapHold
#define RSTT MT(MOD_RSFT, KC_SLSH)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* (Base Layer) Default Layer
   * ,-----------------------------------------------------------.
   * |Esc~| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
   * |-----------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |
   * |-----------------------------------------------------------|
   * | Caps |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '| Return |
   * |-----------------------------------------------------------|
   * |Shift  |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|Shift| Up |Del |
   * |-----------------------------------------------------------|
   * |Ctrl|Gui |Alt |      Space           |Ctrl|Fn| LT| DN | RT |
   * `-----------------------------------------------------------'
   */
  // 0: Base Layer
  [_BL] = KEYMAP(
      KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC,  \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,            \
      KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, XXXXXXX, KC_ENT,             \
      KC_LSFT, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  XXXXXXX, RSTT,    KC_UP,   KC_DEL,    \
      KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RCTL, MO(_FL), KC_LEFT, KC_DOWN, KC_RIGHT),

  // 1: Function Layer
  [_FL] = KEYMAP(
      KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_DEL,   \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, XXXXXXX, XXXXXXX, XXXXXXX,           \
      XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           \
      XXXXXXX, XXXXXXX, KC_VOLD, KC_VOLU, KC_MUTE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______,  \
      XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX,                            TG(_LK), _______, KC_HOME, _______, KC_END),

 // 2: Lighting Keys
  [_LK] = KEYMAP(
      TO(_BL), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   RESET,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_DEL,   \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, XXXXXXX, XXXXXXX, XXXXXXX,           \
      RESET  , KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           \
      XXXXXXX, XXXXXXX, KC_VOLD, KC_VOLU, KC_MUTE, XXXXXXX, XXXXXXX, RGB_SAD, RGB_SAI, RGB_HUD, RGB_HUI, XXXXXXX, XXXXXXX, RGB_VAI, BL_STEP,  \
      XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX,                            TO(_BL), XXXXXXX, RGB_TOG, RGB_VAD, RGB_MOD),

};

// Macros
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {

  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        backlight_step();
      }
      else { unregister_code(KC_RSFT); }
      break;
  }

  return MACRO_NONE;
};

// Loop
void matrix_scan_user(void) {
  // Empty
};