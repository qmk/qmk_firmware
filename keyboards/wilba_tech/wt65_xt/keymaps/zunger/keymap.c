/* Copyright 2021 Yonatan Zunger
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
// generate mathematical symbols (à la Space Cadet), without relying on the host OS to do
// key mappings or handle accents. Why? Because different OS's do this in radically different
// ways, and don't support all of the features one often needs.
//
// LAYER MAGIC (aka, typing in many alphabets)
// 
//   This keyboard has three sets of "polyglot" layers: GREEK, CADET, and YIDDISH. Each of these
// is actually a pair of layers, FOO and SHIFTFOO, which are full of Unicode points that let you
// type in them. (The Greek and Yiddish keymaps selected here are very canted towards use on a
// QWERTY layout, rather than the "standard" layouts often used for those languages in monolingual
// environments. This is useful if your keyboard doesn't have legends for all of them, which in
// most cases it won't. Of course, you could easily add more.)
//
//   These each have their own layer select key, which can act as a held modifier key (GREEK+s to
// produce sigma, etc). There's also a "layer lock" key; layer lock + modifier switches you into
// that layer until you hit "layer lock" again to bounce back to QWERTY.
//
// ACCENT MAGIC
//
//   We want to support easy typing of diacriticals, again without relying on the host OS. (On
// MacOS, if you want Unicode to work you have to lose all the normal accent combining keys, and
// if you're in a multi-OS world, each OS has a totally different input method)
//
//   The real nuance comes from the three different ways Unicode represents these. Many common
// accent + letter combinations like é have their own dedicated code points (the combined
// normal form). One can also place a "combining accent mark" after the letter's code point to
// form the decomposed normal form (NFKD); this often renders the same as the combined form, but
// many less-sophisticated apps won't realize it's the same thing as the combined form (thus messing
// up string matching), and if you backspace you need to backspace *twice* to remove the character,
// because it's literally two characters. Finally, if you want to render just the accent mark as a
// symbol of its own, that's a *third* code point. If you're simply typing, you don't want to think
// about any of this!
//
//   We thus have a bunch of special keycodes for "accent requests," which live on the FUNCTION
// layer. Accent requests don't do anything immediate, but when the *next* non-modifier key is hit,
// we generate a combined code point (if possible), two uncombined points (in cases where combined
// points don't exist), or the isolated accent followed by the next character typed (in cases where
// what you typed next isn't a letterform at all, e.g. you hit the space bar). You can also hit
// shift-<accent request> to just generate the uncombined accent on its own.
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
//   - Add accent support for Hebrew accents.
//   - Factor the code below so that the data layers are more clearly separated from the code logic,
//     so that other users of this keymap can easily add whichever alphabets they need without
//     having to deeply understand the implementation. Probably something similar to
//     users/drashna/keyrecords/unicode.c, but I want to see if I can do some preprocessor magic
//     so that we can actually have the rendered *character* sitting in the code instead of just the
//     hex code point!
//
// PLATFORM MAGIC (aka, working well on both Mac and Windows)
//
//   Finally, this keyboard can switch between Mac and Windows modes, changing various macro
// combinations, the Unicode mode, and the position of the ALT and GUI keys.


enum custom_keycodes {
  // We provide special layer management keys:
  //    GREEK triggers the Greek (aka "Front") layer, or the SHIFTGREEK layer when shift is held.
  //          (Because we use Unicode, we need to implement shift-handling at the firmware level,
  //          rather than the OS level like we do in the QWERTY layer)
  //    CADET or GREEK+ALT triggers the Cadet (aka "Top") layer, or the SHIFTCADET layer when
  //          shift is held.
  //    YIDDISH triggers a keymap designed for easy Hebrew and Yiddish, based loosely on QWERTY
  //          layouts.
  //    LAYER_LOCK locks the "base" layer (i.e., QWERTY, GREEK, or CADET) to the value which is
  //          pressed at the moment that it is being released. When a layer lock is set, the
  //          analogous layer modifier key is reversed; e.g., if you lock the GREEK layer, then the
  //          GREEK button bounces you back to QWERTY.
  //
  // We also parse the shift, alt, and caps lock keys to provide management of those which is
  // compatible with these various layers.
  KC_GREEK = SAFE_RANGE,
  KC_CADET,
  KC_YIDDISH,
  KC_LAYER_LOCK,
  KC_PLATFORM,  // Platform select

  // OS-dependent macros
  KC_VC_MUTE,  // Video conference mute
  KC_VC_HAND,  // Video conference hand-raise
  KC_SCRNSHT,  // Screenshot (gui-shift-S on Windows, gui-shift-4 on Mac)

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

  _FIRST_LANGUAGE_LAYER,
  _YIDDISH = _FIRST_LANGUAGE_LAYER,
  _SHIFTYIDDISH,
  _GREEK,
  _SHIFTGREEK,
  _CADET,
  _SHIFTCADET,
  _LAST_LANGUAGE_LAYER,

  // Function goes last.
  _FUNCTION = _LAST_LANGUAGE_LAYER,
};

// We manage our OS mode internally, and store it in a static, rather than EEPROM, bit. That's
// because it changes as we flip machines, and there's no good reason to wear out the memory.
enum os_modes {
  _WINDOWS = 0,
  _MAC = 1,
  _OS_MODES_MAX = 2,
};
static uint8_t os_mode = _MAC;

// Key types matter for accent handling. If there's a pending accent request and another key is
// pressed:
// - If it's a normal key, we trigger all our magic accent handling.
// - If it's a modifier key, we do nothing and let the accent request hold until the next keypress.
// - If it's a special key, we drop the accent request but don't handle it.
enum key_types {
  _NORMAL_KEY,
  _MODIFIER_KEY,
  _SPECIAL_KEY,
};

// msec to hold the platform key to trigger a switch
#define PLATFORM_HOLD_DURATION 750

// This is so that H(xxxx) has the same width as _______, which makes the grids more legible.
#define H(x) UC(0x##x)
#define MO_FN MO(_FUNCTION)
#define KC_LLCK KC_LAYER_LOCK

// Values for our OS-dependent keys, as arrays keyed by OS mode. Use Meet shortcuts on Mac, Teams on Windows
const char *VC_MUTE_VALUES[_OS_MODES_MAX] = {SS_LCTL(SS_LSFT("m")), SS_LCMD("d")};
const char *VC_HAND_VALUES[_OS_MODES_MAX] = {SS_LCTL(SS_LSFT("k")), SS_LCTL(SS_LCMD("h"))};
const char *SCRNSHT_VALUES[_OS_MODES_MAX] = {SS_LGUI(SS_LSFT("s")), SS_LCMD(SS_LSFT("4"))};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = LAYOUT_all(
		KC_ESC,      KC_LLCK,    KC_GRAVE,KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_HOME,
		KC_PLATFORM, KC_MPLY,    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
		KC_SCRNSHT,  KC_YIDDISH, KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                    KC_PGDN,
		KC_GREEK,    KC_CADET,   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                   KC_UP,   KC_END,
		KC_VC_HAND,  KC_VC_MUTE, KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                                      MO_FN,            KC_LEFT, KC_DOWN, KC_RGHT),

  /* The Greek and Cadet layers. Tab, backspace, the nav and modifier keys, and the control block
   * are always transparent.
   *
   * QWERTY GREEK   SGREEK  CADET   SCADET  YID      SYID
   *   `                                    ׳ 05f3   ״ 05f4
   *   1    ₁ 2081  ¹ 00b9  ¡ 00a1  ¿ 00bf  [transparent]
   *   2    ₂ 2082  ² 00b2  « 00ab  » 00bb  [transparent]
   *   3    ₃ 2083  ³ 00b3  £ 00a3  € 20ac  [transparent]
   *   4    ₄ 2084  ⁴ 2074                  [transparent]
   *   5    ₅ 2085  ⁵ 2075                  [transparent]
   *   6    ₆ 2086  ⁶ 2076                  [transparent]
   *   7    ₇ 2087  ⁷ 2077                  [transparent]
   *   8    ₈ 2088  ⁸ 2078  ° 00b0  ⊗ 2297  [transparent]
   *   9    ₉ 2089  ⁹ 2079                  [transparent]
   *   0    ₀ 2080  ⁰ 2070  ∅ 2205          [transparent]
   *   -    ₋ 208b  ⁻ 207b  ¬ 00ac  ⊖ 2296  [transparent]
   *   =    ₊ 208a  ₋ 208b  ≠ 2260  ⊕ 2295  [transparent]
   *   q    θ 03b8  Θ 0398  ℚ 211a          ק 05e7
   *   w    ω 03c9  Ω 03a9                  ש 05e9
   *   e    ε 03b5  Ε 0395  ∃ 2203  ∄ 2204  ע 05e2
   *   r    ρ 03c1  Ρ 03a1  ℝ 211d          ר 05e8
   *   t    τ 03c4  Τ 03a4                  ט 05d8  תּ fb4a
   *   y    ψ 03c8  Ψ 03a8  ∨ 2228  ∧ 2227  ײ 05f2  ײַ fb1f
   *   u    υ 03c5  Υ 03a5  ∪ 222a  ∩ 2229  ו 05d5  ױ 05f1
   *   i    ι 03b9  Ι 0399  ∞ 221e  ℵ 2135  י 05d9
   *   o    ο 03bf  Ο 039f                  ו 05d5  אָ fb2f
   *   p    π 03c0  Π 03a0  ≡ 2261  ≢ 2262  פ 05e4  ף 05e3
   *   [                    ± 00b1  ∓ 2213
   *   ]                    ≈ 2248  ≉ 2249
   *   \                    ∼ 223c  ≁ 2241
   *   a    α 03b1  Α 0391  ∀ 2200  Å 212b  א 05d0  אַ fb2e
   *   s    σ 03c3  Σ 03a3  ∈ 2208  ∉ 2209   ס 05e1 ת 05ea
   *   d    δ 03b4  Δ 0394  ⊂ 2282  ⊄ 2284   ד 05d3
   *   f    φ 03c6  Φ 03a6  ⊆ 2286  ⊈ 2288   פֿ fb4e
   *   g    γ 03b3  Γ 0393  ⊇ 2287  ⊉ 2289   ג 05d2
   *   h    η 03b7  Η 0397  ← 2190  ⇐ 21d0   ה 05d4
   *   j            ϑ 03d1  ↓ 2193  ⇓ 21d3   ח 05d7  כֿ fb4d
   *   k    κ 03ba  Κ 039a  ↑ 2191  ⇑ 21d1   כ 05db  ך 05da
   *   l    λ 03bb  Λ 039b  → 2192  ⇒ 21d2   ל 05dc
   *   ;    … 2026  ⋯ 22ef  ↔ 2194  ⇔ 21d4
   *   '    · 00b7  • 2022  ∴ 2234  ⊙ 2299
   *   z    ζ 03b6  Ζ 0396  ℤ 2124           ז 05d6
   *   x    ξ 03be  Ξ 039e  ✘ 2718            צ 05e6  ץ 05e5
   *   c    χ 03c7  Χ 03a7  ℂ 2102            כ 05db  ך 05da
   *   v            ς 03c2  ✔ 2714  √ 221a    װ 05f0  בֿ fb4c
   *   b    β 03b2  Β 0392                    ב 05d1
   *   n    ν 03bd  Ν 039d  ℕ 2115            נ 05e0  ן 05df
   *   m    μ 03bc  Μ 039c                    מ 05de  ם 05dd
   *   ,    ≪ 226a  ≫ 226b  ∂ 2202  ∫ 222b
   *   .    ≲ 2272  ≳ 2273  ≰ 2270  ≱ 2271
   *   /                            ⊘ 2298
   */
	[_YIDDISH] = LAYOUT_all(
		KC_TRNS,  KC_TRNS,    H(05f3), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
    KC_TRNS,  KC_TRNS,    KC_TRNS, H(05e7), H(05e9), H(05e2), H(05e8), H(05d8), H(05f2), H(05d5), H(05d9), H(05d5), H(05e4), KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
		KC_TRNS,  KC_TRNS,    KC_TRNS, H(05d0), H(05e1), H(05d3), H(fb4e), H(05d2), H(05d4), H(05d7), H(05db), H(05dc), KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,
		KC_TRNS,  KC_TRNS,    KC_TRNS, H(05d6), H(05e6), H(05db), H(05f0), H(05d1), H(05e0), H(05de), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS,
		KC_TRNS,  KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                                     KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS),
	[_SHIFTYIDDISH] = LAYOUT_all(
		KC_TRNS,  KC_TRNS,    H(05f4), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
		KC_TRNS,  KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, H(fb4a), H(fb1f), H(05f1), KC_TRNS, H(fb2f), H(05e3), KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
    KC_TRNS,  KC_TRNS,    KC_TRNS, H(fb2e), H(05ea), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, H(fb4d), H(05da), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,
		KC_TRNS,  KC_TRNS,    KC_TRNS, KC_TRNS, H(05e5), H(05da), H(fb4c), KC_TRNS, H(05df), H(05dd), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS,
		KC_TRNS,  KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                                     KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS),
	[_GREEK] = LAYOUT_all(
		KC_TRNS,  KC_TRNS,    XXXXXXX, H(2081), H(2082), H(2083), H(2084), H(2085), H(2086), H(2087), H(2088), H(2089), H(2080), H(208b), H(208a), KC_TRNS,          KC_TRNS,
		KC_TRNS,  KC_TRNS,    KC_TRNS, H(03b8), H(03c9), H(03b5), H(03c1), H(03c4), H(03c8), H(03c5), H(03b9), H(03bf), H(03c0), XXXXXXX, XXXXXXX, XXXXXXX,          KC_TRNS,
		KC_TRNS,  KC_TRNS,    KC_TRNS, H(03b1), H(03c3), H(03b4), H(03c6), H(03b3), H(03b7), XXXXXXX, H(03ba), H(03bb), H(2026), H(00b7), KC_TRNS,                   KC_TRNS,
		KC_TRNS,  KC_TRNS,    KC_TRNS, H(03b6), H(03be), H(03c7), XXXXXXX, H(03b2), H(03bd), H(03bc), H(226a), H(2272), XXXXXXX, KC_TRNS,                   KC_TRNS, KC_TRNS,
		KC_TRNS,  KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                                     KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS),
	[_SHIFTGREEK] = LAYOUT_all(
		KC_TRNS,  KC_TRNS,    XXXXXXX, H(00b9), H(00b2), H(00b3), H(2074), H(2075), H(2076), H(2077), H(2078), H(2079), H(2070), H(207b), H(208b), KC_TRNS,          KC_TRNS,
		KC_TRNS,  KC_TRNS,    KC_TRNS, H(0398), H(03a9), H(0395), H(03a1), H(03a4), H(03a8), H(03a5), H(0399), H(039f), H(03a0), XXXXXXX, XXXXXXX, XXXXXXX,          KC_TRNS,
		KC_TRNS,  KC_TRNS,    KC_TRNS, H(0391), H(03a3), H(0394), H(03a6), H(0393), H(0397), H(03d1), H(039a), H(039b), H(22ef), H(2022), KC_TRNS,                   KC_TRNS,
		KC_TRNS,  KC_TRNS,    KC_TRNS, H(0396), H(039e), H(03a7), H(03c2), H(0392), H(039d), H(039c), H(226b), H(2273), XXXXXXX, KC_TRNS,                   KC_TRNS, KC_TRNS,
		KC_TRNS,  KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                                     KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS),
	[_CADET] = LAYOUT_all(
		KC_TRNS,  KC_TRNS,    XXXXXXX, H(00a1), H(00ab), H(00a3), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, H(00b0), XXXXXXX, H(2205), H(00ac), H(2260), KC_TRNS,          KC_TRNS,
		KC_TRNS,  KC_TRNS,    KC_TRNS, H(211a), XXXXXXX, H(2203), H(211d), XXXXXXX, H(2228), H(222a), H(221e), XXXXXXX, H(2261), H(00b1), H(2248), H(223c),          KC_TRNS,
		KC_TRNS,  KC_TRNS,    KC_TRNS, H(2200), H(2208), H(2282), H(2286), H(2287), H(2190), H(2193), H(2191), H(2192), H(2194), H(2234), KC_TRNS,                   KC_TRNS,
		KC_TRNS,  KC_TRNS,    KC_TRNS, H(2124), H(2718), H(2102), H(2714), XXXXXXX, H(2115), XXXXXXX, H(2202), H(2270), XXXXXXX, KC_TRNS,                   KC_TRNS, KC_TRNS,
		KC_TRNS,  KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                                     KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS),
	[_SHIFTCADET] = LAYOUT_all(
		KC_TRNS,  KC_TRNS,    XXXXXXX, H(00bf), H(00bb), H(20ac), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, H(2297), XXXXXXX, XXXXXXX, H(2296), H(2295), KC_TRNS,          KC_TRNS,
		KC_TRNS,  KC_TRNS,    KC_TRNS, XXXXXXX, XXXXXXX, H(2204), XXXXXXX, XXXXXXX, H(2227), H(2229), H(2135), XXXXXXX, H(2262), H(2213), H(2249), H(2241),          KC_TRNS,
		KC_TRNS,  KC_TRNS,    KC_TRNS, H(212b), H(2209), H(2284), H(2288), H(2289), H(21d0), H(21d3), H(21d1), H(21d2), H(21d4), H(2299), KC_TRNS,                   KC_TRNS,
		KC_TRNS,  KC_TRNS,    KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX, H(221a), XXXXXXX, XXXXXXX, XXXXXXX, H(222b), H(2271), H(2298), KC_TRNS,                   KC_TRNS, KC_TRNS,
		KC_TRNS,  KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                                     KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS),
  // The function layer mostly contains the accent marks, but also has a few meta-control
  // operations. The accent marks are placed by analogy with Mac OS.
	[_FUNCTION] = LAYOUT_all(
		QK_BOOT,  KC_TRNS,    KC_CGRV, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX,          XXXXXXX,
		KC_TRNS,  KC_TRNS,    KC_TRNS, XXXXXXX, XXXXXXX, KC_CAGU, XXXXXXX, XXXXXXX, XXXXXXX, KC_CDIA, KC_CCIR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
		KC_TRNS,  KC_TRNS,    KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX,
		KC_TRNS,  KC_TRNS,    KC_TRNS, XXXXXXX, XXXXXXX, KC_CCED, XXXXXXX, XXXXXXX, KC_CTIL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS,                   XXXXXXX, XXXXXXX,
		KC_TRNS,  KC_TRNS,    KC_RCTL, KC_RGUI, KC_RALT,                            KC_TRNS,                                     KC_TRNS,          XXXXXXX, XXXXXXX, XXXXXXX),
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
//
// Returns true if the keycode has been completely handled by this function (and so should not be
// processed further by process_record_user) or false otherwise.
bool process_key_after_accent(
    uint16_t accent_key,
    uint16_t keycode,
    bool is_shifted
) {
  assert(accent_key >= KC_ACCENT_START);
  assert(accent_key < KC_ACCENT_END);
  const int accent_index = accent_key - KC_ACCENT_START;

  // If the keycode is outside A..Z, we know we shouldn't even bother with a table lookup.
  if (keycode <= KC_Z) {
    // Pick the correct array. Because this is progmem, we're going to need to do the
    // two-dimensional array indexing by hand, and so we just cast it to a single-dimensional array.
    const uint16_t *points = (const uint16_t*)(is_shifted ? shifted_accents : unshifted_accents);
    const uint16_t code_point = pgm_read_word(points + KC_NUM_ACCENTS * keycode + accent_index);
    if (code_point) {
      register_unicode(code_point);
      return true;
    }
  }

  // If we get here, there was no accent match. Emit the accent as its own character (i.e. a
  // Unicode combining accent mark) and return false so that process_record_user also registers
  // whatever is appropriate for the keycode after that. The host can figure out what to do with
  // combining Unicode.
  register_unicode(pgm_read_word(uncombined_accents + accent_index));
  return false;
}

// This is a bitmask which selects the activation bits for layers *other* than our language
// selectors.
#define NON_LANGUAGE_LAYERS ~(((1UL << _LAST_LANGUAGE_LAYER) - 1) - ((1UL << _FIRST_LANGUAGE_LAYER) - 1))

// Update the current layer state and return the layer we're in.
uint8_t update_layer(
  uint8_t layer_lock,
  uint8_t layer_select_held,
  bool shifted
) {
  uint8_t current_layer = layer_lock;
  layer_state_t language_layers = 0;

  // If there's a layer select being held right now, then it updates the current layer.
  // (If it's the layer select for the currently locked layer, then instead it's a toggle
  // back to _QWERTY!)
  if (layer_select_held != _QWERTY) {
    current_layer = (layer_lock == layer_select_held ? _QWERTY : layer_select_held);
  }

  language_layers |= (1UL << current_layer);

  // If we're shifted (with either shift or caps lock), and we're in one of our special
  // layers, bump up to the SHIFTED version of that layer. We don't do this for QWERTY;
  // there we just emit USB HID codes and let the host deal with shift.
  if (shifted && current_layer != _QWERTY) {
    ++current_layer;
    language_layers |= (1UL << current_layer);
  }

  // Update the QMK layer state by stomping just the language layer bits.
  const layer_state_t new_layer_state = (layer_state & NON_LANGUAGE_LAYERS) | language_layers;
  if (new_layer_state != layer_state) {
    layer_state_set(new_layer_state);
  }

  return current_layer;
}

void set_os_mode(uint8_t new_mode) {
  os_mode = new_mode;
  // NB: We set unicode_config.input_mode directly, rather than calling
  // set_unicode_input_mode, because we don't want to persist this and so we shouldn't put
  // extra load on the EEPROMs.
  unicode_config.input_mode = (os_mode == _MAC ? UNICODE_MODE_MACOS : UNICODE_MODE_WINCOMPOSE);
  // Swap LALT and LGUI depending on Mac/Windows.
  keymap_config.swap_lalt_lgui = (os_mode == _MAC);
  // This would be a great moment for some auditory or visual feedback, but this keyboard
  // doesn't support it. :(
}

void toggle_os_mode(void) {
  set_os_mode((os_mode + 1) % _OS_MODES_MAX);
}

void keyboard_post_init_user() {
  set_os_mode(_WINDOWS);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // We track these persistent globals and manage them on our own, rather than trying to rely on
  // get_mods or the like, because this function is called *before* that's updated!
  static bool shift_held = false;
  static bool alt_held = false;
  static bool ctrl_held = false;
  static bool super_held = false;

  // These are where we remember the values of lock states.
  static bool shift_lock = false;
  static uint8_t layer_lock = _QWERTY;  // The currently locked layer
  static uint8_t next_layer_lock = _QWERTY;  // Used when layer_lock is held
  // Which layer select key is currently being held down. _QWERTY is equivalent to "none."
  static uint8_t layer_select_held = _QWERTY; 

  // When the hold on the platform key started
  static uint16_t platform_hold_start = 0;

  // The accent request, or zero if there isn't one.
  static uint16_t accent_request = 0;

  // What kind of key we're striking right now, so that we know what to do if any accent requests
  // are hanging around.
  uint8_t key_type = _NORMAL_KEY;

  // The layer selection and locking logic is:
  // * By default, the current layer is given by saved value layer_lock.
  // * If a layer select key is held down, we update the current layer to that value.
  //   (But special thing: If the current layer lock is <layer> and you hit the select key
  //   for <layer>, it instead toggles the current layer back to _QWERTY! That way you can
  //   insert some QWERTY keys in the midst of other-layer text.)
  // * If the KC_LAYER_LOCK key is held down and a layer select key gets pressed, we update
  //   next_layer_lock to that selected layer. When KC_LAYER_LOCK is released, we update
  //   layer_lock to next_layer_lock. Note that that simply tapping KC_LAYER_LOCK resets 
  //   layer_lock to _QWERTY.
  // * After all of this is done, we check if shift is held (via either shift or caps lock);
  //   if it is, and our current layer isn't _QWERTY, then we bump the current layer ID by 1
  //   to get the shifted layer.

  // Step 1: Process various interesting keycodes, especially ones that update our running
  // state variables.
  switch (keycode) {
    // Monitoring the modifier keys, because we'll need them for our logic!
    case KC_LSFT:
    case KC_RSFT:
      shift_held = record->event.pressed;
      key_type = _MODIFIER_KEY;
      break;
    case KC_CAPS:
      // If we're in QWERTY mode, caps lock is already going to be managed by the host OS, but by
      // tracking it ourselves we can also usefully apply it to the GREEK and CADET layers.
      shift_lock = !shift_lock;
      key_type = _MODIFIER_KEY;
      break;
    case KC_LALT:
    case KC_RALT:
      alt_held = record->event.pressed;
      key_type = _MODIFIER_KEY;
      break;
    case KC_LCTL:
    case KC_RCTL:
      ctrl_held = record->event.pressed;
      key_type = _MODIFIER_KEY;
      break;
    case KC_LGUI:
    case KC_RGUI:
      super_held = record->event.pressed;
      key_type = _MODIFIER_KEY;
      break;

    case KC_LAYER_LOCK:
      if (record->event.pressed) {
        // On press, get ready for a layer selection.
        next_layer_lock = _QWERTY;
      } else {
        // On release, propagate next_layer_lock to layer_lock.
        layer_lock = next_layer_lock;
      }
      key_type = _MODIFIER_KEY;
      break;

    // Layer selectors
    case KC_GREEK:
      if (record->event.pressed) {
        layer_select_held = _GREEK;
        next_layer_lock = _GREEK;
      } else {
        layer_select_held = _QWERTY;
      }
      key_type = _MODIFIER_KEY;
      break;
    case KC_CADET:
      if (record->event.pressed) {
        layer_select_held = _CADET;
        next_layer_lock = _CADET;
      } else {
        layer_select_held = _QWERTY;
      }
      key_type = _MODIFIER_KEY;
      break;
    case KC_YIDDISH:
      if (record->event.pressed) {
        layer_select_held = _YIDDISH;
        next_layer_lock = _YIDDISH;
      } else {
        layer_select_held = _QWERTY;
      }
      key_type = _MODIFIER_KEY;
      break;

    // Accent selectors
    case KC_CGRV:
    case KC_CAGU:
    case KC_CDIA:
    case KC_CCIR:
    case KC_CCED:
    case KC_CTIL:
      // The accent request keys normally update accent_request (whose effect will trigger the next
      // time we see a "normal" key pressed). However, shift+accent request will instead immediately
      // generate the Unicode combining accent symbol instead.
      if (shift_held) {
        register_unicode(pgm_read_word(combined_accents + keycode - KC_ACCENT_START));
        return false;
      } else {
        accent_request = keycode;
      }
      key_type = _MODIFIER_KEY;
      break;

    // Our special keycodes
    case KC_PLATFORM:
      if (record->event.pressed) {
        platform_hold_start = record->event.time;
      } else if (platform_hold_start != 0 && record->event.time - platform_hold_start > PLATFORM_HOLD_DURATION) {
        toggle_os_mode();
      }
      key_type = _SPECIAL_KEY;
      return true;

    case KC_VC_MUTE:
      if (record->event.pressed) {
        send_string(VC_MUTE_VALUES[os_mode]);
        return true;
      }
      key_type = _SPECIAL_KEY;
      break;

    case KC_VC_HAND:
      if (record->event.pressed) {
        send_string(VC_HAND_VALUES[os_mode]);
        return true;
      }
      key_type = _SPECIAL_KEY;
      break;

    case KC_SCRNSHT:
      if (record->event.pressed) {
        send_string(SCRNSHT_VALUES[os_mode]);
        return true;
      }
      key_type = _SPECIAL_KEY;
      break;

    case QK_BOOT:
      key_type = _SPECIAL_KEY;
      break;
  }

  // Step 2: Finalize current_layer and update the QMK layer state.
  const bool shifted = (shift_held != shift_lock);
  const uint8_t current_layer = update_layer(layer_lock, layer_select_held, shifted);

  // Step 3: Handle accents.
  bool handled = false;
  if (accent_request && record->event.pressed) {
    // If we're in any layer other than _QWERTY, or a modifier key is being held down,
    // then we're actually generating a special key, not a normal one.
    if (key_type == _NORMAL_KEY &&
        (current_layer != _QWERTY || ctrl_held || super_held || alt_held)) {
      key_type = _SPECIAL_KEY;
    }

    switch (key_type) {
      case _NORMAL_KEY:
        handled = process_key_after_accent(accent_request, keycode, shifted);
        accent_request = 0;
        break;

      case _SPECIAL_KEY:
        accent_request = 0;
        break;

      case _MODIFIER_KEY:
        break;
    }
  }

  return !handled;
}
