#include QMK_KEYBOARD_H

#define ____ KC_TRNS
// Tab on tap or Function layer 1 on hold
#define FN_TAB LT(1, KC_TAB)
#define KC_SLP KC_SYSTEM_SLEEP

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // BASE LAYER
    [0] = LAYOUT_all(
        KC_ESC,    KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_LBRC,   KC_RBRC,
        FN_TAB,    KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,              KC_ENT,
        KC_LSFT,   KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,              MO(2),
                   KC_LCTL,   KC_LALT,   KC_LGUI,   KC_BSPC,   KC_BSPC,              KC_SPC,               MO(3),     MO(1)
    ),
    // BASE LAYER TWO (Fn1)
    [1] = LAYOUT_all(
        KC_GRV,    KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_MINS,    KC_EQL,
        ____,      ____,      ____,      ____,      ____,      ____,      ____,      ____,      ____,      KC_UP,     KC_QUOT,               KC_BSLS,
        ____,      ____,      ____,      ____,      ____,      ____,      ____,      ____,      KC_LEFT,   KC_DOWN,   KC_RGHT,               KC_RSFT,
                   ____,      ____,      ____,      KC_DEL,    KC_DEL,               ____,                 KC_RGUI,   ____
    ),
    // FROW LAYER AND ARROWS (Fn2)
    [2] = LAYOUT_all(
        KC_ESC,    KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,     KC_F12,
        ____,      ____,      ____,      ____,      ____,      ____,      ____,      ____,      ____,      KC_PGUP,   ____,                  ____,
        ____,      ____,      ____,      ____,      ____,      ____,      ____,      ____,      KC_HOME,   KC_PGDN,   KC_END,                ____,
                   MO(4),     ____,      ____,      ____,      ____,                 ____,                 ____,      ____
    ),
    // MEDIA AND RGB (Fn3)
    [3] = LAYOUT_all(
        ____,      RGB_M_P,   RGB_M_B,   RGB_M_R,   RGB_M_SW,  RGB_M_SN,  RGB_M_K,   RGB_M_X,   RGB_M_G,   KC_MPRV,   KC_MPLY,   KC_MNXT,    KC_DEL,
        ____,      ____,      ____,      RGB_HUI,   RGB_SAI,   RGB_VAI,   ____,      ____,      ____,      ____,      ____,                  ____,
        ____,      RGB_MOD,   RGB_TOG,   RGB_HUD,   RGB_SAD,   RGB_VAD,   BL_TOGG,   BL_STEP,   ____,      ____,      ____,                  ____,
                   ____,      ____,      ____,      ____,      ____,                 ____,                 ____,      ____
    ),
    // UTIL (Fn1+Fn3)
    [4] = LAYOUT_all(
        KC_SLP,    ____,      ____,      ____,      ____,      ____,      ____,      ____,      ____,      ____,      ____,      KC_PSCR,    RESET,
        ____,      ____,      ____,      ____,      ____,      ____,      ____,      ____,      ____,      ____,      ____,                  ____,
        ____,      ____,      ____,      ____,      ____,      ____,      ____,      ____,      ____,      ____,      ____,                  ____,
                   ____,      ____,      ____,      ____,      ____,                 ____,                 ____,      ____
    ),
};

/**
 * Status LED layer indicators courtesy of jetpacktuxedo's firmware
 */
layer_state_t layer_state_set_kb(layer_state_t state)
{
  if (state & (1<<1)) { // if we are on layer 1
    PORTD |= (1 << PD0); // light num lock led
  } else if (state & (1<<2)) { // if we are on layer 2

    if (state & (1<<4)) {
      PORTD |= (1 << PD0); // light all indicator leds
      PORTD |= (1 << PD1);
      PORTD |= (1 << PD6);
    } else {
      PORTD &= ~(1 << PD0);
      PORTD |= (1 << PD1); // light caps lock led
      PORTD &= ~(1 << PD6);
    }
  } else if (state & (1<<3)) { // if we are on layer 3
    PORTD |= (1 << PD6); // light scroll lock led
  } else if (state & (1<<4)) { // if we are stuck on layer 4
    PORTD |= (1 << PD0); // light all indicator leds
    PORTD |= (1 << PD1);
    PORTD |= (1 << PD6);
  } else {
    PORTD &= ~(1 << PD0);
    PORTD &= ~(1 << PD1);
    PORTD &= ~(1 << PD6);
  }

  return state;
}
