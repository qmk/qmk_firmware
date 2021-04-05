#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"

#define BASE 0
#define QWRT 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_ergodox(
    KC_GRV,  KC_1,     KC_2,  KC_3,    KC_4,    KC_5,    KC_F5,
    KC_TAB,  KC_Q,     KC_W,  KC_D,    KC_F,    KC_K,    KC_BSLS,
    KC_LCTL, KC_A,     KC_S,  KC_E,    KC_T,    KC_G,
    KC_LSFT, KC_Z,     KC_X,  KC_C,    KC_V,    KC_B,    KC_LBRC,
    KC_F1,   KC_F2,    KC_F3, KC_F4,   KC_LGUI,
    /*-*/    /*-*/     /*-*/  /*-*/    /*-*/    KC_VOLD, KC_MUTE,
    /*-*/    /*-*/     /*-*/  /*-*/    /*-*/    /*-*/    KC_VOLU,
    /*-*/    /*-*/     /*-*/  /*-*/    /*-*/    KC_BSPC, CTL_T(KC_ESC), KC_LALT,
    //
    /*-*/    KC_F6,    KC_6,  KC_7,    KC_8,    KC_9,    KC_0,          KC_EQL,
    /*-*/    TG(QWRT), KC_J,  KC_U,    KC_R,    KC_L,    KC_SCLN,       KC_MINS,
    /*-*/    /*-*/     KC_Y,  KC_N,    KC_I,    KC_O,    KC_H,          KC_ENT,
    /*-*/    KC_RBRC,  KC_P,  KC_M,    KC_COMM, KC_DOT,  KC_SLSH,       KC_RSFT,
    /*-*/    /*-*/     /*-*/  KC_RGUI, KC_LEFT, KC_DOWN, KC_UP,         KC_RGHT,
    KC_MPLY, KC_MNXT,
    KC_MPRV,
    KC_RALT, KC_QUOT,  KC_SPC
  ),
  [QWRT] = LAYOUT_ergodox(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_E,    KC_R,    KC_T,    KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_D,    KC_F,    KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS, KC_TRNS,
    /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS,
    /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS, KC_TRNS, KC_TRNS,
    //
    /*-*/    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    /*-*/    KC_TRNS, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_TRNS,
    /*-*/    /*-*/    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_TRNS,
    /*-*/    KC_TRNS, KC_N,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    /*-*/    /*-*/    /*-*/    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS,
    KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS
  ),
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
    case QWRT:
      ergodox_right_led_1_on();
      break;
    default:
      break;
  }
};
