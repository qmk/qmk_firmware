
#include QMK_KEYBOARD_H
#include "led.h"

// This is the 21-key keypad to 2x11 element matrix mapping
#define LAYOUT_pad21( \
    k00, k01, k02, k03, \
    k10, k11, k12, k13, \
    k04, k05, k06, \
    k14, k15, k16, k07, \
    k08, k09, k0A, \
    k19,      k1A, k17 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, KC_NO, k19, k1A } \
}

enum layers {
  LAYER_BASE,
  LAYER_EDIT,
  LAYER_FUNCTION
};

enum custom_keycodes {
  M_COPY = SAFE_RANGE,  // KC_FN5: MACRO_COPY_CUT
  M_SHFCT,              // KC_FN6: MACRO_SHIFT_CONTROL
  M_CTALT               // KC_FN7: MACRO_CONTROL_ALT
};

#define SC_UNDO             LCTL(KC_Z)
#define SC_REDO             LCTL(KC_Y)
#define SC_CUT              LCTL(KC_X)
#define SC_COPY             LCTL(KC_C)
#define SC_PSTE             LCTL(KC_V)
#define SC_SELA             LCTL(KC_A)
#define SC_SAVE             LCTL(KC_S)
#define SC_OPEN             LCTL(KC_O)
#define SC_ACLS             LALT(KC_F4)
#define SC_CCLS             LCTL(KC_F4)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[LAYER_BASE] = LAYOUT_pad21(
  KC_ESC,  KC_TAB,  KC_BSLS, MO(2),
  KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
  KC_P7,   KC_P8,   KC_P9,
  KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
  KC_P1,   KC_P2,   KC_P3,
  KC_P0,            KC_PDOT, KC_PENT  ),

[LAYER_EDIT] = LAYOUT_pad21(
  KC_ESC,  KC_TAB,  KC_SPC,  _______,
  TG(1),   SC_PSTE, SC_REDO, SC_UNDO,
  KC_HOME, KC_UP,   KC_PGUP,
  KC_LEFT, M_COPY,  KC_RGHT, M_CTALT,
  KC_END,  KC_DOWN, KC_PGDN,
  KC_BSPC,          KC_DEL,  M_SHFCT),

[LAYER_FUNCTION] = LAYOUT_pad21(
  BL_TOGG, BL_UP,   BL_DOWN, _______,
  TG(1),   _______, _______, _______,
  _______, _______, _______,
  _______, _______, _______, _______,
  _______, _______, _______,
  QK_BOOT,          _______, _______  ),

};


bool process_record_user(uint16_t keycode, keyrecord_t * record) {
  // MACRODOWN only works in this function
  switch (keycode) {

  case M_COPY:
    if (record->event.pressed) {
      register_code(KC_LCTL);
      if (record->tap.count == 1) {
        register_code(KC_C);
        unregister_code(KC_C);
      } else if (record->tap.count == 2) {
        register_code(KC_X);
        unregister_code(KC_X);
      }
      unregister_code(KC_LCTL);
    }
    break;

  case M_SHFCT:
    if (record->event.pressed) {
      if (record->tap.count <= 2) register_mods(MOD_BIT(KC_LSFT));
      if (record->tap.count == 2) register_mods(MOD_BIT(KC_LCTL));
      if (record->tap.count == 3) register_code(KC_PENT);;
    } else {
      unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_LCTL));
      unregister_code(KC_PENT);
    }
    break;

  case M_CTALT:
    if (record->event.pressed) {
      if (record->tap.count < 2) register_mods(MOD_BIT(KC_LCTL));
      if (record->tap.count >= 2) register_mods(MOD_BIT(KC_LALT));
    } else {
      unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT));
    }
    break;
  }

  return true;
}

bool led_update_user(led_t led_state)
{
    if (led_state.caps_lock) {
        // output high
        gpio_set_pin_output(D6);
        gpio_write_pin_high(D6);
    } else {
        // Hi-Z
        gpio_set_pin_input(D6);
    }
    if (led_state.num_lock) {
        // output low
        gpio_set_pin_output(C7);
        gpio_write_pin_low(C7);
    } else {
        // Hi-Z
        gpio_set_pin_input(C7);
    }
    return false;
}
