#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"

#define BASE 0
#define SYMB 1
#define PLVR 2
#define ARRW 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = KEYMAP(
    KC_GRV,        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_F14,
    KC_TAB,        KC_Q,    KC_W,    KC_D,    KC_F,    KC_K,    TG(PLVR),
    CTL_T(KC_ESC), KC_A,    KC_S,    KC_E,    KC_T,    KC_G,
    KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC,
    KC_F1,         KC_F2,   KC_F3,   KC_LALT, KC_LGUI,
    /*-*/          /*-*/    /*-*/    /*-*/    /*-*/    KC_VOLD, KC_MUTE,
    /*-*/          /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    KC_VOLU,
    /*-*/          /*-*/    /*-*/    /*-*/    /*-*/    KC_BSPC, CTL_T(KC_ESC), KC_FN1,
    //
    /*-*/          KC_F15,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,          KC_EQL,
    /*-*/          KC_BSLS, KC_J,    KC_U,    KC_R,    KC_L,    KC_SCLN,       KC_MINS,
    /*-*/          /*-*/    KC_Y,    KC_N,    KC_I,    KC_O,    KC_H,          KC_ENT,
    /*-*/          KC_RBRC, KC_P,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,       KC_RSFT,
    /*-*/          /*-*/    /*-*/    KC_RGUI, KC_RALT, KC_F4,   KC_F5,         KC_F6,
    KC_MPLY,       KC_MNXT,
    KC_MPRV,
    KC_FN3,        KC_QUOT, KC_SPC
  ),
  [SYMB] = KEYMAP(
    KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,       KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_TRNS,
    KC_TRNS,       KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,
    KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    /*-*/          /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS, KC_TRNS,
    /*-*/          /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS,
    /*-*/          /*-*/    /*-*/    /*-*/    KC_TRNS, KC_TRNS, KC_TRNS,
    //
    /*-*/          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,
    /*-*/          KC_TRNS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,          KC_TRNS,
    /*-*/          /*-*/    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,       KC_TRNS,
    /*-*/          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,
    /*-*/          /*-*/    /*-*/    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,
    KC_TRNS,       KC_TRNS,
    KC_TRNS,
    KC_TRNS,       KC_TRNS, KC_TRNS
  ),
  [PLVR] = KEYMAP(
    KC_NO,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS,
    KC_NO,         KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_TRNS,
    KC_NO,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
    KC_NO,         KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_NO,
    KC_TRNS,       KC_TRNS, KC_TRNS, KC_NO,   KC_NO,
    /*-*/          /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS, KC_TRNS,
    /*-*/          /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS,
    /*-*/          /*-*/    /*-*/    /*-*/    KC_C,    KC_V,    KC_NO,
    //
    /*-*/          KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_NO,
    /*-*/          KC_NO,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,          KC_NO,
    /*-*/          /*-*/    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,          KC_LBRC,
    /*-*/          KC_NO,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,       KC_QUOT,
    /*-*/          /*-*/    /*-*/    KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_NO,
    KC_TRNS,       KC_TRNS,
    KC_TRNS,
    KC_NO,         KC_N,    KC_M
  ),
  [ARRW] = KEYMAP(
    KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,       KC_TRNS, KC_MS_L, KC_MS_U, KC_MS_D, KC_MS_R,
    KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2, KC_TRNS,
    KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    /*-*/          /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS, KC_TRNS,
    /*-*/          /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS,
    /*-*/          /*-*/    /*-*/    /*-*/    KC_TRNS, KC_TRNS, KC_TRNS,
    //
    /*-*/          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,
    /*-*/          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,
    /*-*/          /*-*/    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS,       KC_TRNS,
    /*-*/          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,
    /*-*/          /*-*/    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,       KC_TRNS,
    KC_TRNS,
    KC_TRNS,       KC_TRNS, KC_TRNS
  ),
};

const uint16_t PROGMEM fn_actions[] = {
  [SYMB] = ACTION_LAYER_TAP_TOGGLE(SYMB), // FN1 - Momentary Symbols Layer
  [PLVR] = ACTION_LAYER_TAP_TOGGLE(PLVR), // FN2 - Momentary Plover Layer
  [ARRW] = ACTION_LAYER_TAP_TOGGLE(ARRW), // FN3 - Momentary Arrows Layer
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) {
        register_code(KC_RSFT);
      } else {
        unregister_code(KC_RSFT);
      }
      break;
  }
  return MACRO_NONE;
};

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
    case SYMB:
      ergodox_right_led_1_on();
      break;
    case PLVR:
      ergodox_right_led_2_on();
      break;
    case ARRW:
      ergodox_right_led_3_on();
      break;
    default:
      break;
  }
};
