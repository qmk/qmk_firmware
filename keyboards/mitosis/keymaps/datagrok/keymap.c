#include "mitosis.h"

enum mitosis_layers
{
    _xW, // workman
    _xQ, // qwerty
    _xS, // symbols
    _xN, // numbers
    _xF  // functions
};

// Fillers to make layering more clear
#define XXXXXXX KC_NO   // No-op (no key in this location on Mitosis' fake matrix)
#define _______ KC_TRNS // Transparent, because I haven't decided a mapping yet
#define ___M___ KC_TRNS // Transparent, as required by modifier key on another layer
#define KC_LMTA KC_LALT // For fun, name the mods like the space cadet keyboard does
#define KC_RMTA KC_RALT // META
#define KC_LSUP KC_LGUI // SUPER
#define KC_RSUP KC_RGUI //
#define KC_RHYP KC_INT4 // HYPER (actually muhenkan 無変換 and henkan 変換)
#define KC_LHYP KC_INT5 // or NFER/XFER.

// Momentary tri-state layers. Mitosis default keymap does this too but employs
// new keymappings and a bunch of conditional code. This simpler keymap
// accomplishes it, but with a small quirk: triggering both layers then
// releasing one out-of-order will leave the tri-state triggered until the
// other is released. Which doesn't bother me.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_xW] = {
    {KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,    KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN},
    {KC_A,    KC_S,    KC_H,    KC_T,    KC_G,    KC_Y,    KC_N,    KC_E,    KC_O,    KC_I},
    {KC_Z,    KC_X,    KC_M,    KC_C,    KC_V,    KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_QUOT},
    {XXXXXXX, KC_LSUP, KC_LCTL, MO(_xN), KC_LSFT, KC_RSFT, MO(_xN), KC_RCTL, KC_RSUP, XXXXXXX},
    {XXXXXXX, KC_LHYP, KC_LMTA, MO(_xS), KC_BSPC, KC_SPC,  MO(_xS), KC_RMTA, KC_RHYP, XXXXXXX}
  },
  [_xQ] = {
    {KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P},
    {KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN},
    {KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_QUOT},
    {XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX},
    {XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX}
  },
  [_xS] = {
    {KC_ESC,  _______, KC_UP,   _______, _______, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_TILD},
    {KC_TAB,  KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_CIRC, KC_AMPR, KC_PIPE, KC_GRV,  KC_UNDS},
    {KC_BSLS, KC_RPRN, KC_RCBR, KC_RBRC, KC_RABK, KC_LABK, KC_LBRC, KC_LCBR, KC_LPRN, KC_SLSH},
    {XXXXXXX, _______, _______, MO(_xF), _______, _______, MO(_xF), _______, _______, XXXXXXX},
    {XXXXXXX, _______, _______, ___M___, KC_DEL,  KC_ENT,  ___M___, _______, _______, XXXXXXX},
  },
  [_xN] = {
    {_______, _______, _______, _______, _______, KC_PSLS, KC_P7,   KC_P8,   KC_P9,   KC_P0},
    {_______, _______, _______, _______, _______, KC_PAST, KC_P4,   KC_P5,   KC_P6,   KC_PPLS},
    {_______, _______, _______, _______, _______, KC_PMNS, KC_P1,   KC_P2,   KC_P3,   KC_PEQL},
    {XXXXXXX, _______, _______, ___M___, _______, _______, ___M___, _______, _______, XXXXXXX},
    {XXXXXXX, _______, _______, MO(_xF), _______, KC_PENT, MO(_xF), _______, _______, XXXXXXX},
  },
  [_xF] = {
    {_______, _______, KC_PGUP, _______, KC_VOLU, KC_F13,  KC_F7,   KC_F8,   KC_F9,   KC_F10},
    {_______, KC_HOME, KC_PGDN, KC_END,  KC_VOLD, KC_F14,  KC_F4,   KC_F5,   KC_F6,   KC_F11},
    {TG(_xQ), KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_F15,  KC_F1,   KC_F2,   KC_F3,   KC_F12},
    {XXXXXXX, _______, _______, ___M___, _______, _______, ___M___, _______, _______, XXXXXXX},
    {XXXXXXX, _______, _______, _______, ___M___, ___M___, _______, _______, _______, XXXXXXX},
  },
};

// This is a hack to place <question mark> on <shift-comma> and <exclaimation
// mark> on <shift-period>, when using an operating system configured for a
// US/qwerty layout.
bool comm_shifted = false;
bool ques_shifted = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint8_t shifted;
  uint16_t s_keycode;
  bool *k_shifted;

  switch (keycode) {
    case KC_COMM:
      s_keycode = KC_SLSH;
      k_shifted = &comm_shifted;
      break;
    case KC_DOT:
      s_keycode = KC_1;
      k_shifted = &ques_shifted;
      break;
    default:
      return true;
  }

  shifted = get_mods() & (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT));

  // Keydown. If shift is currently pressed, register its alternate keycode.
  if (record->event.pressed && shifted) {
    *k_shifted = true;
    register_code(s_keycode);
    return false;
    // Keyup. If shift was pressed back when the key was pressed, unregister
    // its alternate keycode.
  } else if (!(record->event.pressed) && *k_shifted) {
    *k_shifted = false;
    unregister_code(s_keycode);
    return false;
    // Otherwise, behave as normal.
  } else {
    return true;
  }
}

// Set the bits of A selected by MASK to the corresponding bits of B
#define setbits(A, B, MASK) A = (A & (B | ~MASK)) | (B & MASK)
void matrix_scan_user(void) {
  //
  // Bit #            7     6     5     4     3     2     1     0
  // layer_state: [     |     |     | _xF | _xN | _xS | _xQ | _xW ]
  // usb_led      [     |     |     |kana |cmps |scrl |caps | num ]
  // PORTB:       [  NC |  10 |   9 |   8 |  14 |  16 |  15 |rxled]
  // PORTC:       [  NC |   5 |     |     |     |     |     |     ]
  // PORTD:       [   6 |  NC |txled|   4 | tx* | rx* | grn | p29 ]
  // PORTE:       [     |   7 |     |     |     |     |     |     ]
  // PORTF:       [  a0 |  a1 | red | blu |     |     |  NC |  NC ]
  //
  // PD0 is connected to the pairing switch and p29 on the wireless module.
  // PF0,PF1,PB7,PC7,PD6 are not broken out by the pro micro board. I don't understand why.
  // PB1-PB6,PD4,PD5,PD6,PF6,PF7 are not connected to the Mitosis receiver
  // board. Each may be connected to an LED by way of a resistor (4.7k to
  // match the others) for a total of 14 additional indicators.

  // A simple (but technically inaccurate) model of the momentary layer state:
  // Fn1 key makes _xS active; indicator = red
  // Fn2 key makes _xN active; indicator = blue
  // Both keys make _xF active; indicator = purple
  // Toggling QWERTY mode makes indicator include green, so (red/blue/purple becomes yellow/cyan/white)

  // negated because for ports 0=LED on.
  uint32_t portf_bits = ~(layer_state|layer_state<<1|(layer_state&0b100)<<3);
  setbits(PORTF, portf_bits, 0b00110000);
  setbits(PORTD, ~layer_state, 0b00000010);
}

// vim: set sw=2 et:
