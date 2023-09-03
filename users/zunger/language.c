#include QMK_KEYBOARD_H
#include "users/zunger/base.h"
#include "users/zunger/language.h"

// The current language that is "locked", if any
static Language *language_lock = NULL;
// The current language select key being held down, if any
static Language *language_select_held = NULL;

Language *current_language(void) {
  if (language_select_held == NULL) {
    // No selector key currently held; pick the locked language.
    return language_lock;
  } else if (language_select_held == language_lock) {
    // The currently locked language's key is held; toggle back to DEFAULT.
    return NULL;
  } else {
    // A selector key is held; use that.
    return language_select_held;
  }
}

void lang_tap_dance_finished(tap_dance_state_t *state, Language *user_data) {
    if (state->pressed) {
        language_select_held = language;
    } else if (state->count == 2) {  // Double-tap
        language_lock = (language_lock == language ? NULL : language);
    }
}

void lang_tap_dance_reset(tap_dance_state_t *state, Language *user_data) {
    language_select_held = NULL;
}

// Given the language we're in, if we need to generate some Unicode, actually do it! Returns
// 'true' if we've done so and fully handled the keystroke, 'false' if this isn't Unicode and
// we need to pass it on.
bool process_language_key(uint16_t keycode, keyrecord_t *record) {
  // Fast paths: For keys outside the language-mapped set, or anything but keypresses, nothing
  // to do here.
  if (keycode < KC_A || keycode >= MAX_MAPPABLE_CHAR || !record->event.pressed) return FALLTHROUGH;

  Language *language = current_language();
  if (language == NULL) return FALLTHROUGH;

  const uint16_t code_point = pgm_read_word(
    (const uint16_t*)language +   // Translation table
    keycode * LANGUAGE_COLUMNS +  // Outer index is the keycode
    (IS_SHIFTED ? 1 : 0)          // unshifted, then shifted.
  );

  switch (code_point) {
    case ______:
      return FALLTHROUGH;
    case XXXXXX:
      return STOP;
    default:
      register_unicode(code_point);
      return STOP;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Language tables

Language greek = {
  [KC_A] = {0x03b1, 0x0391},  // α Α
  [KC_B] = {0x03b2, 0x0392},  // β Β
  [KC_C] = {0x03c7, 0x03a7},  // χ Χ
  [KC_D] = {0x03b4, 0x0394},  // δ Δ
  [KC_E] = {0x03b5, 0x0395},  // ε Ε
  [KC_F] = {0x03c6, 0x03a6},  // φ Φ
  [KC_G] = {0x03b3, 0x0393},  // γ Γ
  [KC_H] = {0x03b7, 0x0397},  // η Η
  [KC_I] = {0x03b9, 0x0399},  // ι Ι
  [KC_J] = {XXXXXX, 0x03d1},  //   ϑ
  [KC_K] = {0x03ba, 0x039a},  // κ Κ
  [KC_L] = {0x03bb, 0x039b},  // λ Λ
  [KC_M] = {0x03bc, 0x039c},  // μ Μ
  [KC_N] = {0x03bd, 0x039d},  // ν Ν
  [KC_O] = {0x03bf, 0x039f},  // ο Ο
  [KC_P] = {0x03c0, 0x03a0},  // π Π
  [KC_Q] = {0x03b8, 0x0398},  // θ Θ
  [KC_R] = {0x03c1, 0x03a1},  // ρ Ρ
  [KC_S] = {0x03c3, 0x03a3},  // σ Σ
  [KC_T] = {0x03c4, 0x03a4},  // τ Τ
  [KC_U] = {0x03c5, 0x03a5},  // υ Υ
  [KC_V] = {XXXXXX, 0x03c2},  //   ς
  [KC_W] = {0x03c9, 0x03a9},  // ω Ω
  [KC_X] = {0x03be, 0x039e},  // ξ Ξ
  [KC_Y] = {0x03c8, 0x03a8},  // ψ Ψ
  [KC_Z] = {0x03b6, 0x0396},  // ζ Ζ
  [KC_1] = {0x2081, 0x00b9},  // ₁ ¹
  [KC_2] = {0x2082, 0x00b2},  // ₂ ²
  [KC_3] = {0x2083, 0x00b3},  // ₃ ³
  [KC_4] = {0x2084, 0x2074},  // ₄ ⁴
  [KC_5] = {0x2085, 0x2075},  // ₅ ⁵
  [KC_6] = {0x2086, 0x2076},  // ₆ ⁶
  [KC_7] = {0x2087, 0x2077},  // ₇ ⁷
  [KC_8] = {0x2088, 0x2078},  // ₈ ⁸
  [KC_9] = {0x2089, 0x2079},  // ₉ ⁹
  [KC_0] = {0x2080, 0x2070},  // ₀ ⁰
  [KC_MINS] = {0x208b, 0x207b},  // ₋ ⁻
  [KC_EQL]  = {0x208a, 0x208b},  // ₊ ₋
  [KC_SCLN] = {0x2026, 0x22ef},  // … ⋯
  [KC_QUOT] = {0x00b7, 0x2022},  // · •
  [KC_COMM] = {0x2264, 0x2272},  // ≤ ≲
  [KC_DOT] =  {0x2265, 0x2273},  // ≥ ≳
};

Language symbol = {
  [KC_A] = {0x2200, 0x212b},  // ∀ Å
  [KC_C] = {0x2102, 0x221d},  // ℂ ∝
  [KC_D] = {0x2282, 0x2284},  // ⊂ ⊄
  [KC_E] = {0x2203, 0x2204},  // ∃ ∄
  [KC_F] = {0x2286, 0x2288},  // ⊆ ⊈
  [KC_G] = {0x2287, 0x2289},  // ⊇ ⊉
  [KC_H] = {0x2190, 0x21d0},  // ← ⇐
  [KC_I] = {0x221e, 0x2135},  // ∞ ℵ
  [KC_J] = {0x2193, 0x21d3},  // ↓ ⇓
  [KC_K] = {0x2191, 0x21d1},  // ↑ ⇑
  [KC_L] = {0x2192, 0x21d2},  // → ⇒
  [KC_N] = {0x2115, XXXXXX},  // ℕ
  [KC_P] = {0x2261, 0x2262},  // ≡ ≢
  [KC_Q] = {0x211a, XXXXXX},  // ℚ
  [KC_R] = {0x211d, XXXXXX},  // ℝ
  [KC_S] = {0x2208, 0x2209},  // ∈ ∉
  [KC_U] = {0x222a, 0x2229},  // ∪ ∩
  [KC_V] = {0x2714, 0x221a},  // ✔ √
  [KC_X] = {0x2718, XXXXXX},  // ✘
  [KC_Y] = {0x2228, 0x2227},  // ∨ ∧
  [KC_Z] = {0x2124, XXXXXX},  // ℤ
  [KC_1] = {0x00a1, 0x00bf},  // ¡ ¿
  [KC_2] = {0x00ab, 0x00bb},  // « »
  [KC_3] = {0x00a3, 0x20ac},  // £ €
  [KC_8] = {0x00b0, 0x2297},  // ° ⊗
  [KC_0] = {0x2205, XXXXXX},  // ∅
  [KC_MINS] = {0x00ac, 0x2296},  // ¬ ⊖
  [KC_EQL]  = {0x2260, 0x2295},  // ≠ ⊕
  [KC_LBRC] = {0x00b1, 0x2213},  // ± ∓
  [KC_RBRC] = {0x2248, 0x2249},  // ≈ ≉
  [KC_BSLS] = {0x223c, 0x2241},  // ∼ ≁
  [KC_SCLN] = {0x2194, 0x21d4},  // ↔ ⇔
  [KC_QUOT] = {0x2234, 0x2299},  // ∴ ⊙
  [KC_COMM] = {0x226a, 0x2202},  // ≪ ∂
  [KC_DOT]  = {0x226b, 0x222b},  // ≫ ∫
  [KC_SLSH] = {0x2298, XXXXXX},  // ⊘
};

Language yiddish = {
  [KC_A] = {0x05d0, 0xfb2e},  // א ‎ אַ
  [KC_B] = {0x05d1, XXXXXX},  // ב
  [KC_C] = {0x05db, 0x05da},  // כ ‎ ך
  [KC_D] = {0x05d3, XXXXXX},  // ד
  [KC_E] = {0x05e2, XXXXXX},  // ע
  [KC_F] = {0xfb4e, XXXXXX},  // פֿ
  [KC_G] = {0x05d2, XXXXXX},  // ג
  [KC_H] = {0x05d4, XXXXXX},  // ה
  [KC_I] = {0x05d9, XXXXXX},  // י
  [KC_J] = {0x05d7, 0xfb4d},  // ח ‎ כֿ
  [KC_K] = {0x05db, 0x05da},  // כ ‎ ך
  [KC_L] = {0x05dc, XXXXXX},  // ל
  [KC_M] = {0x05de, 0x05dd},  // מ ‎ ם
  [KC_N] = {0x05e0, 0x05df},  // נ ‎ ן
  [KC_O] = {0x05d5, 0xfb2f},  // ו ‎ אָ
  [KC_P] = {0x05e4, 0x05e3},  // פ ‎ ף
  [KC_Q] = {0x05e7, XXXXXX},  // ק
  [KC_R] = {0x05e8, XXXXXX},  // ר
  [KC_S] = {0x05e1, 0x05ea},  // ס ‎ ת
  [KC_T] = {0x05d8, 0xfb4a},  // ט ‎ תּ
  [KC_U] = {0x05d5, 0x05f1},  // ו ‎ ױ
  [KC_V] = {0x05f0, 0xfb4c},  // װ ‎ בֿ
  [KC_W] = {0x05e9, 0xfb2b},  // ש ‎ שׂ
  [KC_X] = {0x05e6, 0x05e5},  // צ ‎ ץ
  [KC_Y] = {0x05f2, 0xfb1f},  // ײ ‎ ײַ
  [KC_Z] = {0x05d6, XXXXXX},  // ז
};
