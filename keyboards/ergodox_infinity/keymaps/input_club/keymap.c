#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define L0 0 // default layer
#define L1 1
#define L2 2

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[L0] = LAYOUT_ergodox(  // layer 0 : default
/*
 * left hand
 *    +-------+-----+-----+-----+-----+-----+-----+
 *    |   =   |  0  |  2  |  3  |  4  |  5  | ESC |
 *    +-------+-----+-----+-----+-----+-----+-----+
 *    |   \   |  Q  |  W  |  E  |  R  |  T  |LCK-1|
 *    +-------+-----+-----+-----+-----+-----+     |
 *    |  TAB  |  A  |  S  |  D  |  F  |  G  +-----+
 *    +-------+-----+-----+-----+-----+-----+ f1  |
 *    | LSHIFT|  Z  |  X  |  C  |  V  |  B  |     |
 *    +-+-----+-----+-----+-----+-----+-----+-----+
 *      |LGUI |  `  |  \  |LEFT |RIGHT|
 *      +-----+-----+-----+-----+-----+   +-----+-----+
 *                                        |LCTRL| LALT|
 *                                  +-----+-----+-----+
 *                                  |     |     | HOME|
 *                                  |BKSPC| DEL +-----+
 *                                  |     |     | END |
 *                                  +-----+-----+-----+
 */
        KC_EQL,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5, KC_ESC,
        KC_BSLS, KC_Q,   KC_W,    KC_E,    KC_R,    KC_T, TG(L1),
        KC_TAB,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,
        KC_LSFT, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, MO(L1),
        KC_LGUI, KC_GRV, KC_BSLS, KC_LEFT, KC_RGHT,
                                                      KC_LCTL, KC_LALT,
                                                               KC_HOME,
                                             KC_BSPC, KC_DEL,  KC_END,
/* right hand
 *        +-----+-----+-----+-----+-----+-----+-------+
 *        |LCK-2|  6  |  7  |  8  |  9  |  0  |   -   |
 *        +-----+-----+-----+-----+-----+-----+-------+
 *        |  [  |  Y  |  U  |  I  |  O  |  P  |   ]   |
 *        |     +-----+-----+-----+-----+-----+-------+
 *        +-----+  H  |  J  |  K  |  L  |  ;  |   '   |
 *        | f1  +-----+-----+-----+-----+-----+-------+
 *        |     |  N  |  M  |  ,  |  .  |  /  | RSHIFT|
 *        +-----+-----+-----+-----+-----+-----+-----+-+
 *                    |LEFT |DOWN | UP  |RIGHT| RGUI|
 *    +-----+-----+   +-----+-----+-----+-----+-----+
 *    | RALT|RCTRL|
 *    +-----+-----+-----+
 *    | PGUP|     |     |
 *    +-----+ ENT | SPC |
 *    | PGDN|     |     |
 *    +-----+-----+-----+
 */
             TG(L2),  KC_6,   KC_7,    KC_8,    KC_9,   KC_0,     KC_MINS,
             KC_LBRC, KC_Y,   KC_U,    KC_I,    KC_O,   KC_P,     KC_RBRC,
                      KC_H,   KC_J,    KC_K,    KC_L,   KC_SCLN,  KC_QUOT,
             MO(L1),  KC_N,   KC_M,    KC_COMM, KC_DOT, KC_SLSH,  KC_RSFT,
                              KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT, KC_RGUI,
             KC_RALT, KC_RCTL,
             KC_PGUP,
             KC_PGDN, KC_ENT, KC_SPC
    ),

[L1] = LAYOUT_ergodox( // layer 1 : function layers
/* left hand
 *    +-------+-----+-----+-----+-----+-----+-----+
 *    |       | f1  | f2  | f3  | f4  | f5  | f11 |
 *    +-------+-----+-----+-----+-----+-----+-----+
 *    |       |     |     |     |     |     |     |
 *    +-------+-----+-----+-----+-----+-----+     |
 *    |       |     |     |     |     |     +-----+
 *    +-------+-----+-----+-----+-----+-----+     |
 *    |       |     |     |     |     |     |     |
 *    +-+-----+-----+-----+-----+-----+-----+-----+
 *      |     |     |     |     |     |
 *      +-----+-----+-----+-----+-----+   +-----+-----+
 *                                        |     |     |
 *                                  +-----+-----+-----+
 *                                  |     |     |     |
 *                                  |     |     +-----+
 *                                  |     |     |     |
 *                                  +-----+-----+-----+
 */
       KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                      KC_TRNS, KC_TRNS,
                                                               KC_TRNS,
                                             KC_TRNS, KC_TRNS, KC_TRNS,
/* right hand
 *        +-----+-----+-----+-----+-----+-----+-------+
 *        | f12 | f6  | f7  | f8  | f9  | f10 |       |
 *        +-----+-----+-----+-----+-----+-----+-------+
 *        |     |     |     |     |     |     |       |
 *        |     +-----+-----+-----+-----+-----+-------+
 *        +-----+     |     |     |     |     |       |
 *        |     +-----+-----+-----+-----+-----+-------+
 *        |     |     |     |     |     |     |       |
 *        +-----+-----+-----+-----+-----+-----+-----+-+
 *                    |     |     |     |     |     |
 *    +-----+-----+   +-----+-----+-----+-----+-----+
 *    |     |     |
 *    +-----+-----+-----+
 *    |     |     |     |
 *    +-----+     |     |
 *    |     |     |     |
 *    +-----+-----+-----+
 */
       KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
[L2] = LAYOUT_ergodox(
/* Left hand
 *    +-------+-----+-----+-----+-----+-----+-----+
 *    | FLASH |     |     |     |     |     |     |
 *    +-------+-----+-----+-----+-----+-----+-----+
 *    |       |     |     |     |     |     |     |
 *    +-------+-----+-----+-----+-----+-----+     |
 *    |       |     |     |     |     |     +-----+
 *    +-------+-----+-----+-----+-----+-----+     |
 *    |       |     |     |     |     |     |     |
 *    +-+-----+-----+-----+-----+-----+-----+-----+
 *      |     |     |     |     |     |
 *      +-----+-----+-----+-----+-----+   +-----+-----+
 *                                        |     |     |
 *                                  +-----+-----+-----+
 *                                  |     |     |     |
 *                                  |     |     +-----+
 *                                  |     |     |     |
 *                                  +-----+-----+-----+
 */
       RESET,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
/* right hand
 *        +-----+-----+-----+-----+-----+-----+-------+
 *        |     |     |NMLCK| P/  | P*  | P-  |       |
 *        +-----+-----+-----+-----+-----+-----+-------+
 *        |     |     | P7  | P8  | P9  | P+  |       |
 *        |     +-----+-----+-----+-----+-----+-------+
 *        +-----+     | P4  | P5  | P6  | P+  |       |
 *        |     +-----+-----+-----+-----+-----+-------+
 *        |     |     | P1  | P2  | P3  |PENT |       |
 *        +-----+-----+-----+-----+-----+-----+-----+-+
 *                    |     |     | P.  |PENT |     |
 *    +-----+-----+   +-----+-----+-----+-----+-----+
 *    |     |     |
 *    +-----+-----+-----+
 *    |     |     |     |
 *    +-----+     | P0  |
 *    |     |     |     |
 *    +-----+-----+-----+
 */
       KC_TRNS,  KC_TRNS, KC_NUMLOCK, KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_KP_7,    KC_KP_8,     KC_KP_9,        KC_KP_PLUS,  KC_TRNS,
                 KC_TRNS, KC_KP_4,    KC_KP_5,     KC_KP_6,        KC_KP_PLUS,  KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_KP_1,    KC_KP_2,     KC_KP_3,        KC_KP_ENTER, KC_TRNS,
                          KC_TRNS,    KC_TRNS,     KC_KP_DOT,      KC_KP_ENTER, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_KP_0
),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
        case 1:
        if (record->event.pressed) { // For resetting EEPROM
          eeconfig_init();
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
