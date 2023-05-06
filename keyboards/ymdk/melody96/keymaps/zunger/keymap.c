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
#include <assert.h>

// This keymap is designed to make it easy to type in a wide variety of languages, as well as
// generate mathematical symbols (à la Space Cadet).
//
// LAYER MAGIC (aka, typing in many alphabets)
//   This keyboard has three "base" layers: QWERTY, GREEK, and CADET. The GREEK and CADET layers
// are actually full of Unicode points, and so which point they generate depends on things like
// whether the shift key is down. To handle this, each of those layers is actually *two* layers, one
// with and one without shift. In our main loop, we manage modifier state detection, as well as
// layer switch detection, and pick the right layer on the fly.
//   Layers are selected with a combination of three keys. The "Greek" and "Cadet" keys act like
// modifiers: When held down, they transiently select the indicated base layer. The "Layer Lock" key
// locks the value of the base layer at whatever is currently held; so e.g., if you hold Greek +
// Layer Lock, you'll stay in Greek mode until you hit Layer Lock again without any of the mods
// held.
//   TODO: This system of layer selection is nice for math, but it's not very nice for actually
// typing in multiple languages. It seems like a better plan will be to reserve one key for each
// base layer -- maybe fn + F(n) -- which can either be held as a modifier or tapped to switch
// layers. That will open up adding some more languages, like Yiddish, but to do this effectively
// we'll need to find a good UI with which to show the currently selected layer. Need to check what
// the melody96 has in the way of outputs (LEDs, sound, etc).
//
// ACCENT MAGIC (aka, typing conveniently in Romance languages)
//   We want to support easy typing of diacritical marks. We can't rely on the host OS for this,
// because (e.g.) on MacOS, to make any of the other stuff work, we need to be using the Unicode
// input method at the OS level, which breaks all the normal accent stuff on that end. So we do it
// ourselves. Accents can actually be invoked in two different ways: one fast and very compatible,
// one very versatile but with occasional compatibility problems.
//
//   THE MAIN WAY: You can hit one of the "accent request" key patterns immediately *before* typing
//   a letter to be accented. It will emit the corresponding accented Unicode. For example, you can
//   hit fn-e to request an acute accent, followed by i, and it will output í, U+00ED LATIN SMALL
//   LETTER I WITH ACUTE. These "combined characters" are in Unicode normal form C (NFKC), which is
//   important because many European websites and apps, in particular, tend to behave very badly
//   (misunderstanding and/or crashing) when presented with characters in other forms! The catch is
//   that this only works for the various combinations of letters and accents found in the Latin-1
//   supplement block of Unicode -- basically, things you need for Western European languages.
//
//   (NB: If you make an accent request followed by a letter which can't take the corresponding
//   accent, it will output the uncombined form of the accent followed by whatever you typed; so
//   e.g., if you hit fn-e followed by f, it will output ´f, U+00B4 ACUTE ACCENT followed by an
//   ordinary f. This is very similar to the default behavior of MacOS.)
//
//   THE FLEXIBLE WAY: If you hit the accent request with a shift -- e.g., fn-shift-e -- it will
//   instead immediately output the corresponding *combining* Unicode accent mark, which will modify
//   the *previous* character you typed. For example, if you type i followed by fn-shift-e, it will
//   generate í. But don't be fooled by visual similarity: unlike the previous example, this one is
//   an ordinary i followed by U+0301 COMBINING ACUTE ACCENT. It's actually *two symbols*, and this
//   is Unicode normal form D (NFKD). Unlike NFKC, there are NFKD representations of far more
//   combinations of letters and accents, and it's easy to add more of these if you need. (The NFKC
//   representation of such combinations is identical to their NFKD representation)
//
//   Programs that try to compare Unicode strings *should* first normalize them by converting them
//   all into one normal form or another, and there are functions in every programming language to
//   do this -- e.g., JavaScript's string.normalize() -- but lots of programmers fail to understand
//   this, and so write code that massively freaks out when it encounters the wrong form.
//
// The current accent request codes are modeled on the ones in MacOS.
//
//    fn+`    Grave accent (`)
//    fn+e    Acute accent (´)
//    fn+i    Circumflex (^)
//    fn+u    Diaresis / umlaut / trema (¨)
//    fn+c    Cedilla (¸)
//    fn+n    Tilde (˜)
//
// Together, these functions make for a nice "polyglot" keyboard: one that can easily type in a wide
// variety of languages, which is very useful for people who, well, need to type in a bunch of
// languages.
//
// The major TODOs are:
//   - Update the layer selection logic (and add visible layer cues);
//   - Factor the code below so that the data layers are more clearly separated from the code logic,
//     so that other users of this keymap can easily add whichever alphabets they need without
//     having to deeply understand the implementation.


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

  // These are the keycodes generated by the various "accent request" keystrokes.
  KC_ACCENT_START,
  KC_CGRV = KC_ACCENT_START,  // Grave accent
  KC_CAGU,  // Acute accent
  KC_CDIA,  // Diaresis / umlaut / trema
  KC_CCIR,  // Circumflex
  KC_CCED,  // Cedilla
  KC_CTIL,  // Tilde
  KC_ACCENT_END,
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


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // NB: Using GESC for escape in the QWERTY layer as a temporary hack because I messed up the
  // switch on the KC_GRV key; change back to KC_ESC once this is fixed.
	[_QWERTY] = LAYOUT_hotswap(
    QK_GESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_HOME, KC_END,  KC_PGUP, KC_PGDN, KC_MPLY, KC_BRK,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC, KC_LLCK, KC_PSLS, KC_PAST, KC_PMNS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSLS, KC_P7,   KC_P8,   KC_P9,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                   KC_ENT,  KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_P1,   KC_P2,   KC_P3,
    KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             MO_FN,   KC_GREEK,KC_CADET,KC_LEFT, KC_DOWN, KC_RGHT, KC_P0,   KC_PDOT, KC_PENT),
  /* The Greek layers. Shown here are the QWERTY layer (for visual reference) and the two Greek
   * layers.
   * ,----------------------------------------------------------------------------
   * | ` |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|HOM|END|PGU|PGD|MUT|BRK|  QWERTY
   * | ` | ₁ | ₂ | ₃ | ₄ | ₅ | ₆ | ₇ | ₈ | ₉ | ₀ | ₋ | ₊ | ₍ | ₎ |   |   |   |   |  SHIFTGREEK
   * | ` | ¹ | ² | ³ | ⁴ | ⁵ | ⁶ | ⁷ | ⁸ | ⁹ | ⁰ | ⁻ | ⁺ | ⁽ | ⁾ |   |   |   |   |  GREEK
   * |---------------------------------------------------------------------------|
   * | ` | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | + | BKSPC |LCK| / | * | - |
   * | ` | ¿ |   | € |   |   |   |   |   |   |   |   | ≁ | BKSPC |LCK|   | ⊗ |   |
   * |   |   |   |   |   |   |   |   |   |   |   | ∝ | ∼ | BKSPC |LCK| ⊘ | ⊙ | ⊖ |
   * |---------------------------------------------------------------------------|
   * | TAB  | Q | W | E | R | T | Y | U | I | O | P | [ | ] |  \ | 7 | 8 | 9 |   |
   * |      | Θ | Ω | Ε | Ρ | Τ | Ψ | Υ | Ι | Ο | Π |   |   |    |   |   |   |   |
   * |      | θ | ω | ε | ρ | τ | ψ | υ | ι | ο | π |   |   |    |   |   |   |   |
   * |-----------------------------------------------------------------------| + |
   * | CTRL   | A | S | D | F | G | H | J | K | L | ; | ' |  RET | 4 | 5 | 6 | ⊕ |
   * | CTRL   | Α | Σ | Δ | Φ | Γ | Η |   | Κ | Λ | … | ∴ |  RET |   |   |   |   |
   * | CTRL   | α | σ | δ | φ | γ | η | ϑ | κ | λ | ⋯ | ⋅ |  RET |   |   |   |   |
   * |-----------------------------------------------------------------------|---|
   * | SHIFT   | Z | X | C | V | B | N | M | , | . | / |SHFT | ↑ | 1 | 2 | 3 |   |
   * | SHIFT   | Ζ | Ξ | Χ | ✔ | Β | Ν | Μ | ≲ | ≳ |   |SHFT |   |   |   |   |   |
   * | SHIFT   | ζ | ξ | χ | ς | β | ν | μ | ≪ | ≫ | ∫ |SHFT |   |   |   |   |   |
   * |-----------------------------------------------------------------------|ENT|
   * | CTL | ALT| CMD|         SPACE         | α | β | γ | ← | ↓ | → | 0 | . |   |
   * | CTL | ALT| CMD|         SPACE         | α | β | γ |   |   |   |   |   |   |
   * | CTL | ALT| CMD|         SPACE         | α | β | γ |   |   |   |   |   |   |
   * `---------------------------------------------------------------------------'
   */
	[_GREEK] = LAYOUT_hotswap(
    KC_GRV,  H(00b9), H(00b2), H(00b3), H(2074), H(2075), H(2076), H(2077), H(2078), H(2079), H(2070), H(207b), H(207a), H(207d), H(207e), XXXXXXX, XXXXXXX, XXXXXXX, _______,
    KC_GRV,  _______, _______, _______, _______, _______, _______, _______, H(00b0), _______, _______, H(221d), H(223c),          _______, _______, H(2298), H(2299), H(2296),
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
  /* The Cadet layers. Again, we show the QWERTY layer and the two cadet layers.
   * ,----------------------------------------------------------------------------
   * | ` |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|HOM|END|PGU|PGD|MUT|BRK|  QWERTY
   * | ∅ |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |  SHIFTCADET
   * | ¬ |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |  CADET
   * |---------------------------------------------------------------------------|
   * | ` | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | + | BKSPC |LCK| / | * | - |
   * | ` | ¡ |   | £ |   |   |   |   | ° |   |   | * | ∓ | BKSPC |LCK|   |   |   |
   * |   |   |   |   |   |   |   |   |   |   |   |   | ± | BKSPC |LCK|   | × |   |
   * |---------------------------------------------------------------------------|
   * | TAB  | Q | W | E | R | T | Y | U | I | O | P | [ | ] |  \ | 7 | 8 | 9 |   |
   * |      | ℚ |   |   | ℝ | ⊆ | ⊇ |   | ℵ | ∄ |   | ∉ |   |    | * | * | * |   |
   * |      | ∧ | ∨ | ∩ | ∪ | ⊂ | ⊃ | ∀ | ∞ | ∃ | ∂ | ∈ |   |    | * | * | * |   | [1]
   * |-----------------------------------------------------------------------| + |
   * | CTRL   | A | S | D | F | G | H | J | K | L | ; | ' |  RET | 4 | 5 | 6 | ⊕ |
   * | CTRL   | Å |   | ∇ |   | ⇑ | ⇓ | ⇐ | ⇒ | ⇔ |   |   |  RET | * | * | * |   |
   * | CTRL   | ⟘ | ⊤ | ⊢ | ⊣ | ↑ | ↓ | ← | → | ↔ |   |   |  RET | * | * | * |   | [1]
   * |-----------------------------------------------------------------------|---|
   * | SHIFT   | Z | X | C | V | B | N | M | , | . | / |SHFT | ↑ | 1 | 2 | 3 |   |
   * | SHIFT   | ℤ | ℂ |   | ≉ | ≢ | ℕ |   |   |   |   |SHFT |   | * | * | * |   |
   * | SHIFT   |   | ≠ |   | ≈ | ≡ | ≤ | ≥ |   |   | ÷ |SHFT |   | * | * | * |   | [1]
   * |-----------------------------------------------------------------------|ENT|
   * | CTL | ALT| CMD|         SPACE         | α | β | γ | ← | ↓ | → | 0 | . |   |
   * | CTL | ALT| CMD|         SPACE         | α | β | γ |   |   |   |   |   |   |
   * | CTL | ALT| CMD|         SPACE         | α | β | γ |   |   |   |   |   |   |
   * `---------------------------------------------------------------------------'
   * [1] CADET + numpad moves the mouse. SHIFT+CADET+NUMPAD moves it more quickly. CADET+5
   * clicks the mouse, and SHIFT+CADET+FIVE right-clicks.
   */
	[_CADET] = LAYOUT_hotswap(
    H(00AC), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    KC_GRV,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, H(00b1),          _______, _______, XXXXXXX, H(00d7), XXXXXXX,
    _______, H(2227), H(2228), H(2229), H(222a), H(2282), H(2283), H(2200), H(221e), H(2203), H(2202), H(2208), XXXXXXX,          XXXXXXX, KC_P7,   KC_P8,   KC_P9,
    _______, H(22a5), H(22a4), H(22a2), H(22a3), H(2191), H(2193), H(2190), H(2192), H(2194), XXXXXXX, XXXXXXX,                   _______, KC_P4,   KC_P5,   KC_P6,   XXXXXXX,
    _______,          XXXXXXX, H(2260), XXXXXXX, H(2248), H(2261), H(2264), H(2265), XXXXXXX, XXXXXXX, H(00f7), _______,          _______, KC_P1,   KC_P2,   KC_P3,
    _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______, KC_P0,   KC_PDOT, KC_PENT),
	[_SHIFTCADET] = LAYOUT_hotswap(
    H(2205), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    KC_GRV,  H(00a1), XXXXXXX, H(00a3), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, H(2213),          _______, _______, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, H(211a), XXXXXXX, XXXXXXX, H(211d), H(2286), H(2287), XXXXXXX, H(2135), H(2204), XXXXXXX, H(2209), XXXXXXX,          XXXXXXX, KC_P7,   KC_P8,   KC_P9,
    _______, H(212b), XXXXXXX, H(2207), XXXXXXX, H(21d1), H(21d3), H(21d0), H(21d2), H(21d4), XXXXXXX, XXXXXXX,                   _______, KC_P4,   KC_P5,   KC_P6,   XXXXXXX,
    _______,          H(2124), H(2102), XXXXXXX, H(2249), H(2262), H(2115), XXXXXXX, XXXXXXX, XXXXXXX, H(00f7), _______,          _______, KC_P1,   KC_P2,   KC_P3,
    _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______, KC_P0,   KC_PDOT, KC_PENT),

  // Function layer is mostly for keyboard meta-control operations, but also contains the combining
  // accent marks. These are deliberately placed to match where the analogous controls go on Mac OS.
	[_FUNCTION] = LAYOUT_hotswap(
    KC_CGRV, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, QK_BOOT,
    KC_CGRV, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
    _______, _______, _______, KC_CAGU, _______, _______, _______, KC_CDIA, KC_CCIR, _______, _______, _______, _______,          _______, _______, _______, _______,
    _______, _______, _______, UC_MAC,  UC_LINX, UC_WIN,  UC_BSD,  UC_WINC, _______, _______, _______, _______,                   _______, _______, _______, _______, _______,
    _______,          _______, _______, KC_CCED, _______, _______, KC_CTIL, _______, _______, _______, _______, _______,          _______, _______, _______, _______,
    _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______, _______, _______, _______),
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Accent implementation
//
// In the body of process_record_user, we store an "accent_request", which is the accent keycode if
// one was just selected, or zero otherwise. When the *next* key is hit, we look up whether the
// accent request plus that next keycode (plus the state of the shift key) together amount to an
// interesting combined (NFKC) character, and if so, emit it; otherwise, we emit the accent as a
// separate character and then process the next key normally. The resulting UI behavior is similar
// to that of the combining accent keys in MacOS.
//
// We store two arrays, depending on whether shift is or isn't held. Each is two-dimensional, with
// its outer key by the next keycode struck, and the inner key by the accent requested. The outer
// array has KC_Z + 1 as its upper bound, so that we can save memory by only coding alphabetic keys.
// The contents are either Unicode code points, or zero to indicate that we don't have a point for
// this combination.

#define KC_NUM_ACCENTS (KC_ACCENT_END - KC_ACCENT_START)
#define KC_NUM_SLOTS (KC_Z + 1)

const uint16_t PROGMEM unshifted_accents[KC_NUM_SLOTS][KC_NUM_ACCENTS] = {
  //         KC_CGRV, KC_CAGU, KC_CDIA, KC_CCIR, KC_CCED, KC_CTIL
  [KC_A] = { 0x00e0,  0x00e1,  0x00e4,  0x00e2,  0,       0x00e3 },
  [KC_E] = { 0x00e8,  0x00e9,  0x00eb,  0x00ea,  0,       0      },
  [KC_I] = { 0x00ec,  0x00ed,  0x00ef,  0x00ee,  0,       0      },
  [KC_O] = { 0x00f2,  0x00f3,  0x00f6,  0x00f4,  0,       0x00f5 },
  [KC_U] = { 0x00f9,  0x00fa,  0x00fc,  0x00fb,  0,       0      },
  [KC_Y] = { 0,       0,       0x00ff,  0,       0,       0      },
  [KC_N] = { 0,       0,       0,       0,       0,       0x00f1 },
  [KC_C] = { 0,       0,       0,       0,       0x00e7,  0      },
};

const uint16_t PROGMEM shifted_accents[KC_NUM_SLOTS][KC_NUM_ACCENTS] = {
  //         KC_CGRV, KC_CAGU, KC_CDIA, KC_CCIR, KC_CCED, KC_CTIL
  [KC_A] = { 0x00c0,  0x00c1,  0x00c4,  0x00c2,  0,       0x00c3 },
  [KC_E] = { 0x00c8,  0x00c9,  0x00cb,  0x00ca,  0,       0      },
  [KC_I] = { 0x00cc,  0x00cd,  0x00cf,  0x00ce,  0,       0      },
  [KC_O] = { 0x00d2,  0x00d3,  0x00d6,  0x00d4,  0,       0x00d5 },
  [KC_U] = { 0x00d9,  0x00da,  0x00dc,  0x00db,  0,       0      },
  [KC_Y] = { 0,       0,       0x00df,  0,       0,       0      },
  [KC_N] = { 0,       0,       0,       0,       0,       0x00d1 },
  [KC_C] = { 0,       0,       0,       0,       0x00c7,  0      },
};

// The uncombined and combined forms of the accents, for when we want to emit them as single
// characters.
const uint16_t PROGMEM uncombined_accents[KC_NUM_ACCENTS] = {
  [KC_CGRV - KC_ACCENT_START] = 0x0060,
  [KC_CAGU - KC_ACCENT_START] = 0x00b4,
  [KC_CDIA - KC_ACCENT_START] = 0x00a8,
  [KC_CCIR - KC_ACCENT_START] = 0x005e,
  [KC_CCED - KC_ACCENT_START] = 0x00b8,
  [KC_CTIL - KC_ACCENT_START] = 0x02dc,
};

const uint16_t PROGMEM combined_accents[KC_NUM_ACCENTS] = {
  [KC_CGRV - KC_ACCENT_START] = 0x0300,
  [KC_CAGU - KC_ACCENT_START] = 0x0301,
  [KC_CDIA - KC_ACCENT_START] = 0x0308,
  [KC_CCIR - KC_ACCENT_START] = 0x0302,
  [KC_CCED - KC_ACCENT_START] = 0x0327,
  [KC_CTIL - KC_ACCENT_START] = 0x0303,
};

// This function manages keypresses that happen after an accent has been selected by an earlier
// keypress.
// Args:
//   accent_key: The accent key which was earlier selected. This must be in the range
//     [KC_ACCENT_START, KC_ACCENT_END).
//   keycode: The keycode which was just pressed.
//   is_shifted: The current shift state (as set by a combination of shift and caps lock)
//   force_no_accent: If true, we're in a situation where we want to force there to be no
//     accent combination -- if e.g. we're in a non-QWERTY layer, or if other modifier keys
//     are held.
//
// Returns true if the keycode has been completely handled by this function (and so should not be
// processed further by process_record_user) or false otherwise.
bool process_key_after_accent(
    uint16_t accent_key,
    uint16_t keycode,
    bool is_shifted,
    bool force_no_accent
) {
  assert(accent_key >= KC_ACCENT_START);
  assert(accent_key < KC_ACCENT_END);
  const int accent_index = accent_key - KC_ACCENT_START;

  // If the keycode is outside A..Z, or force_no_accent is set, we know we shouldn't even bother
  // with a table lookup.
  if (keycode <= KC_Z && !force_no_accent) {
    // Pick the correct array. Because this is progmem, we're going to need to do the
    // two-dimensional array indexing by hand, and so we just cast it to a single-dimensional array.
    const uint16_t *points = (const uint16_t*)(is_shifted ? shifted_accents : unshifted_accents);
    const uint16_t code_point = pgm_read_word_near(points + KC_NUM_ACCENTS * keycode + accent_index);
    if (code_point) {
      register_unicode(code_point);
      return true;
    }
  }

  // If we get here, there was no accent match. Emit the accent as its own character, and then let
  // the caller figure out what to do next.
  register_unicode(pgm_read_word_near(uncombined_accents + accent_index));
  return false;
}

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
  static bool ctrl_held = false;
  static bool super_held = false;
  static bool greek_held = false;
  static bool cadet_held = false;

  // These are where we remember the values of lock states.
  static bool shift_lock = false;
  static int layer_lock = _QWERTY;

  // The accent request, or zero if there isn't one.
  static uint16_t accent_request = 0;

  // If this is set to true, don't trigger any handling of pending accent requests. That's what we
  // want to do if e.g. the user just hit the shift key or something.
  bool ignore_accent_change = !record->event.pressed;

  // Step 1: Process any modifier key state changes, so we can maintain that state.
  if (keycode == KC_LSFT || keycode == KC_RSFT) {
    shift_held = record->event.pressed;
    ignore_accent_change = true;
  } else if (keycode == KC_LALT || keycode == KC_RALT) {
    alt_held = record->event.pressed;
    ignore_accent_change = true;
  } else if (keycode == KC_LCTL || keycode == KC_RCTL) {
    ctrl_held = record->event.pressed;
    ignore_accent_change = true;
  } else if (keycode == KC_LGUI || keycode == KC_RGUI) {
    super_held = record->event.pressed;
    ignore_accent_change = true;
  } else if (keycode == KC_GREEK) {
    greek_held = record->event.pressed;
    ignore_accent_change = true;
  } else if (keycode == KC_CADET) {
    cadet_held = record->event.pressed;
    ignore_accent_change = true;
  }

  // Step 2: Figure out which layer we're supposed to be in, by transforming all the prior stuff
  // into layer requests.
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

  // Step 3: Handle accents. If there's a pending accent request, process it. If what the user just
  // hit creates a new accent request, update the pending state for the next keypress.
  if (!ignore_accent_change && accent_request && record->event.pressed) {
    // Only do the accent stuff if we're in the QWERTY layer and we aren't modifying something.
    const bool force_no_accent = (
        actual_layer != _QWERTY ||
        ctrl_held ||
        super_held ||
        alt_held
    );
    const uint16_t old_accent = accent_request;
    accent_request = 0;
    if (process_key_after_accent(old_accent, keycode, shifted, force_no_accent)) {
      return false;
    }
  }

  // And if a new accent request just arrived, update accent_request.
  if (keycode >= KC_ACCENT_START && keycode < KC_ACCENT_END && record->event.pressed) {
    if (shifted) {
      // Shift + accent request generates the combining accent key, and leaves accent_request alone.
      register_unicode(pgm_read_word_near(combined_accents + keycode - KC_ACCENT_START));
      return false;
    } else {
      accent_request = keycode;
    }
  }

  return true;
}
