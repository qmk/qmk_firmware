#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"


#include "keymap_bepo.h"

#define VERSION M(0)


// Define layer names 
#define BASE 0
#define FN 1
#define MOUSE 2
#define ARROWS 3

enum custom_keycodes {
  SWAP_HAND = SAFE_RANGE, // make this a layer so that it can have the TT mode?
};

#define ___ KC_TRANSPARENT
#define XXX KC_NOP

#define ESC_FN    LT(FN, KC_ESC)
#define M_RSFT    MT(MOD_RSFT, BP_M)
#define CCED_RCTL MT(MOD_RCTL, BP_CCED)
#define PERC_FN   LT(FN, BP_PERC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = KEYMAP(  
    /* left hand */
    BP_DLR,   BP_DQOT, BP_LGIL, BP_RGIL, BP_LPRN, BP_RPRN, KC_DEL,
    KC_TAB,   BP_B,    BP_ECUT, BP_P,    BP_O,    BP_EGRV, KC_BSPC,
    KC_LSFT,  BP_A,    BP_U,    BP_I,    BP_E,    BP_COMM,
    KC_LCTRL, BP_AGRV, BP_Y,    BP_X,    BP_DOT,  BP_K,    KC_ENT,
    ESC_FN,   BP_ECRC, KC_LOCK, KC_LGUI, KC_LALT,
                                                          KC_LEFT,    KC_DOWN,
                                                                    SWAP_HAND,
                                                  KC_SPC,  TT(FN), TT(ARROWS),
    /* right hand */
        KC_DEL,  BP_AT,   BP_PLUS, BP_MINS, BP_SLSH, BP_ASTR, BP_EQL,
        KC_BSPC, BP_DCRC, BP_V,    BP_D,    BP_L,    BP_J,    BP_Z,
                 BP_C,    BP_T,    BP_S,    BP_R,    BP_N,    M_RSFT,
        KC_ENT,  BP_APOS, BP_Q,    BP_G,    BP_H,    BP_F,    CCED_RCTL,
                          KC_MPRV, KC_MPLY, KC_MNXT, BP_W,    PERC_FN,
    KC_UP,     KC_RIGHT,
    SWAP_HAND,
    TT(MOUSE), KC_RALT, KC_SPC),

  [FN] = KEYMAP(  
    /* left hand */
    KC_SLEP, KC_F1, KC_F2,  KC_F3,   KC_F4,    KC_F5, KC_INS,
    ___,     ___,   ___,    ___,     ___,      ___,   KC_SLCK,
    ___,     ___,   ___,    ___,     ___,      ___,
    ___,     ___,   KC_CUT, KC_COPY, KC_PASTE, ___,   KC_NLCK,
    ___,     ___,   ___,    ___,     ___,
                                                      KC_HOME, KC_PGDN,
                                                                   ___,
                                                  ___,    ___,     ___,
    /* right hand */
        KC_PSCR, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_PAUS, KC_PEQL, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, KC_F12,
                 KC_PCMM, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, ___,
        KC_PENT, KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_PAST, ___,
                          KC_MUTE, KC_VOLD, KC_VOLU, KC_PSLS, ___,
    KC_PGUP, KC_END,
    ___,
    ___,     ___,    ___),

  [MOUSE] = KEYMAP(  
    /* left hand */
    ___,     ___, ___,     KC_BTN3, ___,     ___,     ___,
    KC_ACL2, ___, KC_BTN1, KC_MS_U, KC_BTN2, KC_BTN4, ___,
    KC_ACL1, ___, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN5,
    KC_ACL0, ___, ___,     ___,     ___,     ___,     ___,
    ___,     ___, ___,     ___,     ___,
                                                      ___, ___,
                                                           ___,
                                                 ___, ___, ___,
    /* right hand */
         ___, ___, ___,     ___,     ___,     ___, ___,
         ___, ___, ___,     KC_WH_U, ___,     ___, ___,
              ___, KC_WH_L, KC_WH_D, KC_WH_R, ___, ___,
         ___, ___, ___,     ___,     ___,     ___, ___,
                   ___,     ___,     ___,     ___, ___,
    ___, ___,
    ___,
    ___, ___, ___),

  [ARROWS] = KEYMAP(  
    /* left hand */
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___,
                                  ___, ___,
                                       ___,
                             ___, ___, ___,
    /* right hand */
         ___, ___, ___,     ___,     ___,     ___, ___,
         ___, ___, KC_HOME,     KC_UP, KC_END,     KC_PGUP, ___,
              ___, KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN, ___,
         ___, ___, ___,     ___,     ___,     ___, ___,
                   ___,     ___,     ___,     ___, ___,
    ___, ___,
    ___,
    ___, ___, ___),
};

// Run for each key down or up event.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SWAP_HAND:
      swap_hands = record->event.pressed;
      return false;  // Skip all further processing of this key
  }
  return true; // Let QMK send the enter press/release events
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

};

// The state of the LEDs, as requested by the system.
uint8_t sys_led_state = 0;
// Use these masks to read the led state.
const uint8_t sys_led_mask_num_lock = 1 << USB_LED_NUM_LOCK;
const uint8_t sys_led_mask_caps_lock = 1 << USB_LED_CAPS_LOCK;
const uint8_t sys_led_mask_scroll_lock = 1 << USB_LED_SCROLL_LOCK;

// Called by the system to set the state of the keyboard led.
// Use led_sed_kb if this is not called.
void led_set_user(uint8_t usb_led) {
    sys_led_state = usb_led;
    if (sys_led_state & sys_led_mask_caps_lock) {
      ergodox_right_led_1_on();
    } else {
      ergodox_right_led_1_off();
    }
    if (sys_led_state & sys_led_mask_num_lock) {
      ergodox_right_led_2_on();
    } else {
      ergodox_right_led_2_off();
    }
}
// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
  uint8_t layer = biton32(state);
  // Light the third led for all layer except the default one.
  switch (layer) {
    case 0:
      ergodox_right_led_3_off();
      break;
    default:
      ergodox_right_led_3_on();
      break;
  }

  return state;
};
