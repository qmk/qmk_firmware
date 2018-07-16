/*
 * Let's Split - Dvorak turkish
 * Keymap by @bbaserdem
 * Dvorak layout with multiple features
 * Most of the code is in the "user" directory.
 * Check qmk_firmware/users/bbaserdem for the main part of the code
 */

#include "lets_split.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /*      Navigation All Supered)                        Numpad
   * ,-----------------------. ,-----------------------.
   * | F4| ` | Q |Alt| L | > | | ) | - | + | = |Ent|Bkp|
   * |---+---+---+---+---+---| |---+---+---+---+---+---|
   * | F3| M |Ent|Ctl| K | ^ | | ( | * | 9 | 6 | 3 | . |
   * |---+---+---+---+---+---| |---+---+---+---+---+---|
   * | F2| T |Spc|Shf| J | v | | % | / | 8 | 5 | 2 | , |
   * |---+---+---+---+---+---| |---+---+---+---+---+---|
   * | F1| F | P |Tab| H | < | |Nlc|Tab| 7 | 4 | 1 | 0 |
   * `-----------------------' `-----------------------'
   */
  // Main Dvorak layer
  [0] = LAYOUT(
    LCTL(LALT(KC_DEL)), LGUI(KC_GRV), LGUI(KC_Q),   LGUI(KC_LALT), LGUI(KC_L), LGUI(KC_RGHT), KC_RPRN, KC_PMNS, KC_PPLS, KC_PEQL, KC_PENT, KC_BSPC,
    LGUI(KC_F3),        LGUI(KC_M),   LGUI(KC_ENT), LGUI(KC_LCTL), LGUI(KC_K), LGUI(KC_UP),   KC_LPRN, KC_PAST, KC_P9,   KC_P6,   KC_P3,   KC_PDOT,
    LGUI(KC_F2),        LGUI(KC_T),   LGUI(KC_SPC), LGUI(KC_LSFT), LGUI(KC_J), LGUI(KC_DOWN), KC_PERC, KC_PSLS, KC_P8,   KC_P5,   KC_P2,   KC_PCMM,
    LGUI(KC_F1),        LGUI(KC_F),   LGUI(KC_P),   LGUI(KC_TAB),  LGUI(KC_H), LGUI(KC_LEFT), KC_NLCK, KC_TAB,  KC_P7,   KC_P4,   KC_P1,   KC_P0
  )
};
