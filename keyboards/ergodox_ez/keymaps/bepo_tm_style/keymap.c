// An Ergodox EZ keymap meant to be used with a bépo layout (FR ergonomic
// layout, dvorak style). The overall design is slightly inspired by the
// TypeMatrix keyboard. Switching between a TypeMatrix and an Ergodox with this
// layout should be relatively easy.
//
// See the README.md file for an image of this keymap.

#include QMK_KEYBOARD_H
#include "keymap_bepo.h"

// The layers that we are defining for this keyboards.
#define BASE 0
#define FN 1
#define MOUSE 2
#define NUMS 3
#define SWAP 4
#define SYSLEDS 5

// A 'transparent' key code (that fallsback to the layers below it).
#define ___ KC_TRANSPARENT

// A 'blocking' key code. Does nothing but prevent falling back to another layer.
#define XXX KC_NO

// Some combined keys (one normal keycode when tapped and one modifier or layer
// toggle when held).
#define ESC_FN    LT(FN, KC_ESC)        // ESC key and FN layer toggle.
#define M_RSFT    MT(MOD_RSFT, BP_M)    // 'M' key and right shift modifier.
#define W_RCTL    MT(MOD_RCTL, BP_W)    // 'W' key and right control modifier.
#define PERC_FN   LT(FN, BP_PERC)       // '%' key and FN layer toggle.
#define SPC_RALT  MT(MOD_RALT, KC_SPC)  // SPACE key and right alt modifier.

// The most portable copy/paste keys (windows, linux, and some terminal emulators).
#define MK_CUT    LSFT(KC_DEL)  // shift + delete
#define MK_COPY   LCTL(KC_INS)  // ctrl + insert
#define MK_PASTE  LSFT(KC_INS)  // shift + insert

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Layer 0: basic keys.
  [BASE] = KEYMAP(  
    /* left hand */
    BP_DLR,   BP_DQOT, BP_LGIL, BP_RGIL, BP_LPRN, BP_RPRN, KC_DEL,
    KC_TAB,   BP_B,    BP_ECUT, BP_P,    BP_O,    BP_EGRV, KC_BSPC,
    KC_LSFT,  BP_A,    BP_U,    BP_I,    BP_E,    BP_COMM,
    KC_LCTRL, BP_AGRV, BP_Y,    BP_X,    BP_DOT,  BP_K,    KC_ENT,
    ESC_FN,   BP_ECRC, KC_LGUI, KC_LALT, SPC_RALT,
                                                          TT(SWAP), KC_MNXT,
                                                                    KC_MPLY,
                                                  TT(FN), TT(NUMS), KC_MPRV,
    /* right hand */
        KC_DEL,  BP_AT,   BP_PLUS, BP_MINS, BP_SLSH,     BP_ASTR, BP_EQL,
        KC_BSPC, BP_DCRC, BP_V,    BP_D,    BP_L,        BP_J,    BP_Z,
                 BP_C,    BP_T,    BP_S,    BP_R,        BP_N,    M_RSFT,
        KC_ENT,  BP_APOS, BP_Q,    BP_G,    BP_H,        BP_F,    W_RCTL,
                          SPC_RALT,  KC_LALT, TT(SYSLEDS), BP_CCED, PERC_FN,
    KC_LEFT, KC_RIGHT,
    KC_UP,
    KC_DOWN, TT(FN), TT(MOUSE)),

  // Layer 1: function and media keys.
  [FN] = KEYMAP(  
    /* left hand */
    KC_SLEP, KC_F1, KC_F2,  KC_F3,   KC_F4,    KC_F5, ___,
    ___,     ___,   ___,    ___,     ___,      ___,   ___,
    ___,     ___,   ___,    ___,     ___,      ___,
    ___,     ___,   MK_CUT, MK_COPY, MK_PASTE, ___,   ___,
    ___,     ___,   ___,    ___,     ___,
                                                 KC_HOME, KC_VOLU,
                                                          KC_VOLD,
                                             ___,    ___, KC_MUTE,
    /* right hand */
        ___, KC_F6, KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,
        ___, ___,   KC_HOME, KC_UP,   KC_END,   KC_PGUP, KC_F12,
             ___,   KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN, ___,
        ___, ___,   ___,     ___,     ___,      ___,     ___,
                    ___,     ___,     ___,      ___,     ___,
    KC_HOME, KC_END,
    KC_PGUP,
    KC_PGDN, ___,    ___),

  // Layer 2: Mouse control.
  [MOUSE] = KEYMAP(  
    /* left hand */
    ___, XXX, XXX,     KC_BTN3, XXX,      XXX,     ___,
    ___, XXX, KC_BTN1, KC_MS_U, KC_BTN2,  KC_BTN4, ___,
    ___, XXX, KC_MS_L, KC_MS_D, KC_MS_R,  KC_BTN5,
    ___, XXX, MK_CUT,  MK_COPY, MK_PASTE, XXX,     ___,
    ___, XXX, ___,     ___,     ___,
                                                  ___, ___,
                                                       ___,
                                             ___, ___, ___,
    /* right hand */
         ___, XXX, XXX,     XXX,     XXX,     XXX, ___,
         ___, XXX, XXX,     KC_WH_U, XXX,     XXX, ___,
              XXX, KC_WH_L, KC_WH_D, KC_WH_R, XXX, ___,
         ___, XXX, KC_ACL0, KC_ACL1, KC_ACL2, XXX, ___,
                   KC_BTN1, KC_BTN2, KC_BTN3, XXX, ___,
    ___, ___,
    ___,
    ___, ___, ___),

  // Layer 3: Numeric keypad and system keys.
  [NUMS] = KEYMAP(  
    /* left hand */
    KC_PSCR, KC_INS, KC_PAUS,    ___,     ___,      ___, ___,
    ___,     ___,    ___,        ___,     ___,      ___, ___,
    ___,     ___,    ___,        ___,     ___,      ___,
    ___,     ___,    MK_CUT,     MK_COPY, MK_PASTE, ___, ___,
    ___,     ___,    ___,        ___,     ___,
                                              ___, ___,
                                                   ___,
                                         ___, ___, ___,
    /* right hand */
         ___,     ___,     ___,   ___,   ___,     ___,     KC_NLCK,
         ___,     KC_PEQL, KC_P7, KC_P8, KC_P9,   KC_PMNS, KC_SLCK,
                  KC_PCMM, KC_P4, KC_P5, KC_P6,   KC_PPLS, ___,
         KC_PENT, KC_P0,   KC_P1, KC_P2, KC_P3,   KC_PAST, ___,
                           ___,   ___,   ___,     KC_PSLS, ___,
    ___, ___,
    ___,
    ___, ___, ___),

  // Layer 4: hand swap, all keys are mirrored to the other side of the keyboard
  // except for the layer toggle itself (so there is no right arrow when this
  // layer is activated).
  [SWAP] = KEYMAP(  
    /* left hand */
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___,
                             TT(SWAP), ___,
                                       ___,
                             ___, ___, ___,
    /* right hand */
         ___, ___, ___, ___, ___, ___, ___,
         ___, ___, ___, ___, ___, ___, ___,
              ___, ___, ___, ___, ___, ___,
         ___, ___, ___, ___, ___, ___, ___,
                   ___, ___, ___, ___, ___,
    ___, TT(SWAP),
    ___,
    ___, ___,      ___),
 
  // Layer 5: The LEDs are showing the "standard" caps/num/scroll lock indicator
  // instead of their default which shows the currently active layers (FN, NUMS,
  // and MOUSE in that order).
  [SYSLEDS] = KEYMAP(  
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
         ___, ___, ___, ___, ___,         ___, ___,
         ___, ___, ___, ___, ___,         ___, ___,
              ___, ___, ___, ___,         ___, ___,
         ___, ___, ___, ___, ___,         ___, ___,
                   ___, ___, TT(SYSLEDS), ___, ___,
    ___, ___,
    ___,
    ___, ___, ___),
};

// Runs for each key down or up event.
// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   switch (keycode) {
//     case SWAP_HAND:
//       swap_hands = record->event.pressed;
//       return false;  // Skip all further processing of this key
//   }
//   return true; // Let QMK send the enter press/release events
// }

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

};

// The state of the LEDs requested by the system, as a bitmask.
static uint8_t sys_led_state = 0;

// Use these masks to read the system LEDs state.
static const uint8_t sys_led_mask_num_lock = 1 << USB_LED_NUM_LOCK;
static const uint8_t sys_led_mask_caps_lock = 1 << USB_LED_CAPS_LOCK;
static const uint8_t sys_led_mask_scroll_lock = 1 << USB_LED_SCROLL_LOCK;

// Value to use to switch LEDs on. The default value of 255 is far too bright.
static const uint8_t max_led_value = 20;

// The current set of active layers (as a bitmask).
// There is a global 'layer_state' variable but it is set after the call
// to layer_state_set_user().
static uint32_t current_layer_state = 0;

// Whether the given layer (one of the constant defined at the top) is active.
#define LAYER_ON(layer) (current_layer_state & (1<<layer))

void led_1_on(void) {
  ergodox_right_led_1_on();
  ergodox_right_led_1_set(max_led_value);
}

void led_2_on(void) {
  ergodox_right_led_2_on();
  ergodox_right_led_2_set(max_led_value);
}

void led_3_on(void) {
  ergodox_right_led_3_on();
  ergodox_right_led_3_set(max_led_value);
}

void led_1_off(void) {
  ergodox_right_led_1_off();
}

void led_2_off(void) {
  ergodox_right_led_2_off();
}

void led_3_off(void) {
  ergodox_right_led_3_off();
}

// Called by the system to set the state of the keyboard led.
// Use led_sed_kb if this is not called.
void led_set_user(uint8_t usb_led) {
    sys_led_state = usb_led;
  if (LAYER_ON(SYSLEDS)) {
    if (sys_led_state & sys_led_mask_caps_lock) {
      led_1_on();
    } else {
      led_1_off();
    }
    if (sys_led_state & sys_led_mask_num_lock) {
      led_2_on();
    } else {
      led_2_off();
    }
    if (sys_led_state & sys_led_mask_scroll_lock) {
      led_3_on();
    } else {
      led_3_off();
    }
  }
}

uint32_t layer_state_set_user(uint32_t state) {
  current_layer_state = state;
  swap_hands = LAYER_ON(SWAP);

  if (LAYER_ON(SYSLEDS)) {
    led_set_user(sys_led_state);
    return state;
  }

  if (LAYER_ON(FN)) {
    led_1_on();
  } else {
    led_1_off();
  }

  if (LAYER_ON(NUMS)) {
    led_2_on();
  } else {
    led_2_off();
  }

  if (LAYER_ON(MOUSE)) {
    led_3_on();
  } else {
    led_3_off();
  }

  return state;
};
