/* Copyright 2019 Yonatan Zunger
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum custom_keycodes {
  // We provide special layer management keys:
  //    GREEK triggers the Greek (aka "Front") layer, or the SHIFTGREEK layer when shift is held.
  //          (Because we use Unicode, we need to implement shift-handling at the firmware level,
  //          rather than the OS level like we do in the QWERTY layer)
  //    CADET or GREEK+ALT triggers the Cadet (aka "Top") layer, or the SHIFTCADET layer when
  //          shift is held.
  //    LAYER_LOCK locks the "base" layer (i.e., QWERTY, GREEK, or CADET) to the value which is
  //          pressed at the moment that it is being released. When a layer lock is set, the
  //          analogous layer modifier key is reversed; e.g., if you lock the GREEK layer, then the
  //          GREEK button bounces you back to QWERTY.
  //
  // We also parse the shift, alt, and caps lock keys to provide management of those which is
  // compatible with these various layers.
  KC_GREEK = SAFE_RANGE,
  KC_CADET,
  KC_LAYER_LOCK,
};

enum layers_keymap {
  _QWERTY = 0,
  _FUNCTION,

  _GREEK,
  _SHIFTGREEK,
  _CADET,
  _SHIFTCADET,
};

// This is so that H(xxxx) has the same width as _______, which makes the grids more legible.
#define H(x) UC(0x##x)
#define MO_FN MO(_FUNCTION)
#define KC_LLCK KC_LAYER_LOCK

// TODO: To generalize this, we want some #defines that let us specify how each key on the base
// layer should map to the four special layers, and then use that plus the base layer definition to
// autogenerate the keymaps for the other layers.
// TODO: It would also be nice to be able to put the actual code points in here, rather than
// numbers.


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* The diagram below shows five rows for each key: from top to bottom, the QWERTY layer, the
   * GREEK layer, the SHIFTGREEK layer, the CADET layer, and the SHIFTCADET layer. (The single
   * diagram is to make it easier to see what goes where with this many layers!)
   *
   * ,----------------------------------------------------------------------------
   * | ` |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|HOM|END|PGU|PGD|MUT|BRK|  QWERTY
   * | ` | ¹ | ² | ³ | ⁴ | ⁵ | ⁶ | ⁷ | ⁸ | ⁹ | ⁰ | ⁻ | ⁺ | ⁽ | ⁾ |   |   |   |   |  GREEK
   * | ` | ₁ | ₂ | ₃ | ₄ | ₅ | ₆ | ₇ | ₈ | ₉ | ₀ | ₋ | ₊ | ₍ | ₎ |   |   |   |   |  SHIFTGREEK
   * | ¬ |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |  CADET
   * | ∅ |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |  SHIFTCADET
   * |---------------------------------------------------------------------------|
   * | ` | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | + | BKSPC |LCK| / | * | - |
   * | ` | ¡ |   | £ |   |   |   |   | ° |   |   | ∝ | ∼ | BKSPC |LCK| ⊘ | ⊙ | ⊖ |
   * | ` | ¿ |   | € |   |   |   |   |   |   |   |   | ≁ | BKSPC |LCK|   | ⊗ |   |
   * |   |  ̀ |  ́ |  ̂ |  ̃ |  ̈ |  ̄ |   |   |   |   |   | ± | BKSPC |LCK|   | × |   | [3]
   * |   |   |   |   |   |   |   |   |   |   |   |   | ∓ | BKSPC |LCK|   |   |   |
   * |---------------------------------------------------------------------------|
   * | TAB  | Q | W | E | R | T | Y | U | I | O | P | [ | ] |  \ | 7 | 8 | 9 |   |
   * |      | θ | ω | ε | ρ | τ | ψ | υ | ι | ο | π |   |   |    |   |   |   |   |
   * |      | Θ | Ω | Ε | Ρ | Τ | Ψ | Υ | Ι | Ο | Π |   |   |    |   |   |   |   |
   * |      | ∧ | ∨ | ∩ | ∪ | ⊂ | ⊃ | ∀ | ∞ | ∃ | ∂ | ∈ |   |    | * | * | * |   | [1]
   * |      | ℚ |   |   | ℝ | ⊆ | ⊇ |   | ℵ | ∄ |   | ∉ |   |    | * | * | * |   |
   * |-----------------------------------------------------------------------| + |
   * | CTRL   | A | S | D | F | G | H | J | K | L | ; | ' |  RET | 4 | 5 | 6 | ⊕ |
   * | CTRL   | α | σ | δ | φ | γ | η | ϑ | κ | λ | ⋯ | ⋅ |  RET |   |   |   |   |
   * | CTRL   | Α | Σ | Δ | Φ | Γ | Η |   | Κ | Λ | … | ∴ |  RET |   |   |   |   |
   * | CTRL   | ⟘ | ⊤ | ⊢ | ⊣ | ↑ | ↓ | ← | → | ↔ |   |   |  RET | * | * | * |   | [1]
   * | CTRL   | Å |   | ∇ |   | ⇑ | ⇓ | ⇐ | ⇒ | ⇔ |   |   |  RET | * | * | * |   |
   * |-----------------------------------------------------------------------|---|
   * | SHIFT   | Z | X | C | V | B | N | M | , | . | / |SHFT | ↑ | 1 | 2 | 3 |   |
   * | SHIFT   | ζ | ξ | χ | ς | β | ν | μ | ≪ | ≫ | ∫ |SHFT |   |   |   |   |   |
   * | SHIFT   | Ζ | Ξ | Χ | ✔ | Β | Ν | Μ | ≲ | ≳ |   |SHFT |   |   |   |   |   |
   * | SHIFT   |   |   | ≠ | ≈ | ≡ | ≤ | ≥ |   |   | ÷ |SHFT |   | * | * | * |   | [1]
   * | SHIFT   | ℤ |   | ℂ | ≉ | ≢ | ℕ |   |   |   |   |SHFT |   | * | * | * |   |
   * |-----------------------------------------------------------------------|ENT|
   * | CTL | ALT| CMD|         SPACE         | α | β | γ | ← | ↓ | → | 0 | . |   | [2]
   * | CTL | ALT| CMD|         SPACE         | α | β | γ |   |   |   |   |   |   |
   * | CTL | ALT| CMD|         SPACE         | α | β | γ |   |   |   |   |   |   |
   * | CTL | ALT| CMD|         SPACE         | α | β | γ |   |   |   |   |   |   |
   * | CTL | ALT| CMD|         SPACE         | α | β | γ |   |   |   |   |   |   |
   * `---------------------------------------------------------------------------'
   *
   * [1] CADET + numpad moves the mouse. SHIFT+CADET+NUMPAD moves it more quickly. CADET+5
   * clicks the mouse, and SHIFT+CADET+FIVE right-clicks.
   * [2] The Greek letters in this row are the three modifier keys (GREEK, CADET, FN),
   * not the Unicode Greek letters.
   * [3] The accent marks in this row are combining accent marks, which may be put after
   * a character to combine it. In order, they are grave, acute, circumflex, tilde,
   * diaresis (umlaut), and macron.
  */
  // NB: Using GESC for escape in the QWERTY layer as a temporary hack because I messed up the
  // switch on the KC_GRV key; change back to KC_ESC once this is fixed.
	[_QWERTY] = LAYOUT_hotswap(
    KC_GESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_HOME, KC_END,  KC_PGUP, KC_PGDN, KC_MPLY, KC_BRK,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC, KC_LLCK, KC_PSLS, KC_PAST, KC_PMNS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSLS, KC_P7,   KC_P8,   KC_P9,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                   KC_ENT,  KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_P1,   KC_P2,   KC_P3,
    KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_GREEK,KC_CADET,MO_FN,   KC_LEFT, KC_DOWN, KC_RGHT, KC_P0,   KC_PDOT, KC_PENT),
	[_GREEK] = LAYOUT_hotswap(
    KC_GRV,  H(00b9), H(00b2), H(00b3), H(2074), H(2075), H(2076), H(2077), H(2078), H(2079), H(2070), H(207b), H(207a), H(207d), H(207e), XXXXXXX, XXXXXXX, XXXXXXX, _______,
    KC_GRV,  H(00a1), _______, H(00a3), _______, _______, _______, _______, H(00b0), _______, _______, H(221d), H(223c),          _______, _______, H(2298), H(2299), H(2296),
    _______, H(03b8), H(03c9), H(03b5), H(03c1), H(03c4), H(03c8), H(03c5), H(03b9), H(03bf), H(03c0), KC_LBRC, KC_RBRC,          KC_BSLS, KC_P7,   KC_P8,   KC_P9,
    _______, H(03b1), H(03c3), H(03b4), H(03c6), H(03b3), H(03b7), H(03d1), H(03ba), H(03bb), H(22ef), H(22c5),                   _______, KC_P4,   KC_P5,   KC_P6,   H(2295),
    _______,          H(03b6), H(03be), H(03c7), H(03c2), H(03b2), H(03bd), H(03bc), H(226a), H(226b), H(222b), _______,          _______, KC_P1,   KC_P2,   KC_P3,
    _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______, KC_P0,   KC_PDOT, KC_PENT),
	[_SHIFTGREEK] = LAYOUT_hotswap(
    KC_GRV,  H(2081), H(2082), H(2083), H(2084), H(2085), H(2086), H(2087), H(2088), H(2089), H(2080), H(208b), H(208a), H(208d), H(208e), XXXXXXX, XXXXXXX, XXXXXXX, _______,
    KC_GRV,  H(00bf), _______, H(20ac), _______, _______, _______, _______, _______, _______, _______, XXXXXXX, H(2241),          _______, _______, XXXXXXX, H(2297), XXXXXXX,
    _______, H(0398), H(03a9), H(0395), H(03a1), H(03a4), H(03a8), H(03a5), H(0399), H(039f), H(03a0), KC_LBRC, KC_RBRC,          KC_BSLS, KC_P7,   KC_P8,   KC_P9,
    _______, H(0391), H(03a3), H(0394), H(03a6), H(0393), H(0397), XXXXXXX, H(039a), H(039b), H(2026), H(2234),                   _______, KC_P4,   KC_P5,   KC_P6,   H(2295),
    _______,          H(0396), H(039e), H(03a7), H(2714), H(0392), H(039d), H(039c), H(2272), H(2273), XXXXXXX, _______,          _______, KC_P1,   KC_P2,   KC_P3,
    _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______, KC_P0,   KC_PDOT, KC_PENT),
  // TODO: Add mouse keys to keypad.
	[_CADET] = LAYOUT_hotswap(
    H(00AC), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    KC_GRV,  H(0300), H(0301), H(0302), H(0303), H(0308), H(0304), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, H(00b1),          _______, _______, XXXXXXX, H(00d7), XXXXXXX,
    _______, H(2227), H(2228), H(2229), H(222a), H(2282), H(2283), H(2200), H(221e), H(2203), H(2202), H(2208), XXXXXXX,          XXXXXXX, KC_P7,   KC_P8,   KC_P9,
    _______, H(22a5), H(22a4), H(22a2), H(22a3), H(2191), H(2193), H(2190), H(2192), H(2194), XXXXXXX, XXXXXXX,                   _______, KC_P4,   KC_P5,   KC_P6,   XXXXXXX,
    _______,          XXXXXXX, XXXXXXX, H(2260), H(2248), H(2261), H(2264), H(2265), XXXXXXX, XXXXXXX, H(00f7), _______,          _______, KC_P1,   KC_P2,   KC_P3,
    _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______, KC_P0,   KC_PDOT, KC_PENT),
	[_SHIFTCADET] = LAYOUT_hotswap(
    H(2205), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    KC_GRV,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, H(2213),          _______, _______, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, H(211a), XXXXXXX, XXXXXXX, H(211d), H(2286), H(2287), XXXXXXX, H(2135), H(2204), XXXXXXX, H(2209), XXXXXXX,          XXXXXXX, KC_P7,   KC_P8,   KC_P9,
    _______, H(212b), XXXXXXX, H(2207), XXXXXXX, H(21d1), H(21d3), H(21d0), H(21d2), H(21d4), XXXXXXX, XXXXXXX,                   _______, KC_P4,   KC_P5,   KC_P6,   XXXXXXX,
    _______,          H(2124), XXXXXXX, H(2102), H(2249), H(2262), H(2115), XXXXXXX, XXXXXXX, XXXXXXX, H(00f7), _______,          _______, KC_P1,   KC_P2,   KC_P3,
    _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______, KC_P0,   KC_PDOT, KC_PENT),

  // Function layer is mostly for keyboard meta-control operations. Lots of this is just from the
  // default layout; TODO make it nicer.
	[_FUNCTION] = LAYOUT_hotswap(
    RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
    _______, RGB_TOG, _______, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______,          _______, _______, _______, _______,
    BL_TOGG, _______, _______, UC_M_OS, UC_M_LN, UC_M_WI, UC_M_BS, UC_M_WC, _______, _______, _______, _______,                   _______, _______, _______, _______, _______,
    _______,          _______, _______, BL_DEC,  BL_TOGG, BL_INC,  _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______,
    _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______, _______, _______, _______),
};

// Layer bitfields.
#define GREEK_LAYER (1UL << _GREEK)
#define SHIFTGREEK_LAYER (1UL << _SHIFTGREEK)
#define CADET_LAYER (1UL << _CADET)
#define SHIFTCADET_LAYER (1UL << _SHIFTCADET)
// The layers we don't touch.
#define LAYER_MASK ~(GREEK_LAYER|SHIFTGREEK_LAYER|CADET_LAYER|SHIFTCADET_LAYER)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // We track these persistent globals and manage them on our own, rather than trying to rely on
  // get_mods or the like, because this function is called *before* that's updated!
  static bool shift_held = false;
  static bool alt_held = false;
  static bool greek_held = false;
  static bool cadet_held = false;

  // These are where we remember the values of lock states.
  static bool shift_lock = false;
  static int layer_lock = _QWERTY;

  // Process any modifier key presses.
  if (keycode == KC_LSHIFT || keycode == KC_RSHIFT) {
    shift_held = record->event.pressed;
  } else if (keycode == KC_LALT || keycode == KC_RALT) {
    alt_held = record->event.pressed;
  } else if (keycode == KC_GREEK) {
    greek_held = record->event.pressed;
  } else if (keycode == KC_CADET) {
    cadet_held = record->event.pressed;
  }

  // Now let's transform these into the "cadet request" and "greek request."
  const bool greek_request = (greek_held && !alt_held);
  const bool cadet_request = (cadet_held || (greek_held && alt_held));

  // Now, handle the lock keys. We store next_layer_lock in a local variable so that we can
  // determine the layer to pick right now before we update layer_lock.
  int next_layer_lock = layer_lock;
  if (keycode == KC_CAPS) {
    // If we're in QWERTY mode, caps lock is already going to be managed by the host OS, but by
    // tracking it ourselves we can also usefully apply it to the GREEK and CADET layers.
    if (record->event.pressed) {
      shift_lock = !shift_lock;
    }
  } else if (keycode == KC_LAYER_LOCK) {
    if (record->event.pressed) {
      if (cadet_request) {
        next_layer_lock = _CADET;
      } else if (greek_request) {
        next_layer_lock = _GREEK;
      } else {
        next_layer_lock = _QWERTY;
      }
    }
  }

  // OK! Now we know which buttons are being held, and the current and upcoming states of the locks.
  // We can compute our new base layer. Remember that the CADET and GREEK keys act as their own
  // antonyms if they match the layer lock -- e.g., if you have CADET locked, then CADET+X generates
  // QWERTY-X.
  int base_layer;
  if (cadet_request) {
    base_layer = (layer_lock == _CADET ? _QWERTY : _CADET);
  } else if (greek_request) {
    base_layer = (layer_lock == _GREEK ? _QWERTY : _GREEK);
  } else {
    base_layer = layer_lock;
  }

  const bool shifted = (shift_held != shift_lock);
  int actual_layer;
  if (base_layer == _CADET) {
    actual_layer = (shifted ? _SHIFTCADET : _CADET);
  } else if (base_layer == _GREEK) {
    actual_layer = (shifted ? _SHIFTGREEK : _GREEK);
  } else {
    // We don't do shifting for the QWERTY layer, since for that we emit USB HID codes and shifting
    // is managed by the host OS.
    actual_layer = _QWERTY;
  }

  // And now we can update the layer lock and the actual firmware layer selector.
  layer_lock = next_layer_lock;
  layer_state_t new_layer_state = (layer_state & LAYER_MASK) | (1UL << actual_layer);
  if (new_layer_state != layer_state) {
    layer_state_set(new_layer_state);
  }

  // TODO: We can update LED states based on shift_lock (caps), layer_lock (layer lock), and
  // base_layer (base layer).

  return true;
}
