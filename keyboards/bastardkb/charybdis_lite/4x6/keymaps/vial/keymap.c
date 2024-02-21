/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#ifdef CONSOLE_ENABLE
#include "print.h"
#endif  // CONSOLE_ENABLE


#include "features/caps_word.h"

/**
 * The default keymap is a simplified version of the Miryoku layout using
 * a QWERTY alpha base layer.
 */
enum charybdis_vial_keymap_layers {
  LAYER_FIRST = 0,
  LAYER_BASE = LAYER_FIRST,
  LAYER_LOWER,
  LAYER_RAISE,
  LAYER_POINTER,
  LAYER_LAST = LAYER_POINTER,
};

enum charybdis_vial_keymap_keycodes {
#ifdef VIA_ENABLE
  USER_RESET = USER00,
#else
  USER_RESET = SAFE_RANGE,
#endif  // VIA_ENABLE
  POINTER_DEFAULT_DPI_FORWARD,
  POINTER_DEFAULT_DPI_REVERSE,
  POINTER_SNIPING_DPI_FORWARD,
  POINTER_SNIPING_DPI_REVERSE,
  SNIPING_MODE,
  SNIPING_MODE_TOGGLE,
  DRAGSCROLL_MODE,
  DRAGSCROLL_MODE_TOGGLE,
  KEYMAP_SAFE_RANGE,
};

#define USR_RST USER_RESET
#define DPI_MOD POINTER_DEFAULT_DPI_FORWARD
#define DPI_RMOD POINTER_DEFAULT_DPI_REVERSE
#define S_D_MOD POINTER_SNIPING_DPI_FORWARD
#define S_D_RMOD POINTER_SNIPING_DPI_REVERSE
#define SNIPING SNIPING_MODE
#define SNP_TOG SNIPING_MODE_TOGGLE
#define DRGSCRL DRAGSCROLL_MODE
#define DRG_TOG DRAGSCROLL_MODE_TOGGLE

#define LOWER MO(LAYER_LOWER)
#define RAISE MO(LAYER_RAISE)
#define _L_PTR(KC) LT(LAYER_POINTER, KC)

/** Automatically enable sniping-mode on the pointer layer. */
#define AUTO_SNIPING_MODE_ON_LAYER LAYER_POINTER

// clang-format off
#define LAYOUT_charybdis_4x6(...) LAYOUT_split_4x6_5(__VA_ARGS__)

/**
 * Add pointer layer keys to a layout.
 *
 * Expects a 12-key per row layout.  The layout passed in parameter must contain
 * at least 30 keycodes.
 */
#define _POINTER_MOD(                                                        \
    L00, L01, L02, L03, L04, L05, R06, R07, R08, R09, R0A, R0B,              \
    L10, L11, L12, L13, L14, L15, R16, R17, R18, R19, R1A, R1B,              \
    L20, L21, L22, L23, L24, L25, R26, R27, R28, R29, R2A, R2B,              \
    L30, L31, L32, L33, L34, L35, R36, R37, R38, R39, R3A, R3B,              \
    ...)                                                                     \
            L00,        L01,        L02,        L03,        L04,        L05, \
            R06,        R07,        R08,        R09,        R0A,        R0B, \
            L10,        L11,        L12,        L13,        L14,        L15, \
            R16,        R17,        R18,        R19,        R1A,        R1B, \
            L20,        L21,        L22,        L23,        L24,        L25, \
            R26,        R27,        R28,        R29,        R2A,        R2B, \
            L30, _L_PTR(L31),       L32,        L33,        L34,        L35, \
            R36,        R37,        R38,        R39, _L_PTR(R3A),       R3B, \
      __VA_ARGS__
#define POINTER_MOD(...) _POINTER_MOD(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_charybdis_4x6(POINTER_MOD(
  // ╭─────────────────────────────────────────────────────╮ ╭─────────────────────────────────────────────────────╮
        KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,      KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
  // ├─────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────┤
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,   KC_SCLN, KC_BSLS,
  // ├─────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────┤
       MT(MOD_MEH,KC_ESC),    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,      KC_H,    KC_J,    KC_K,    KC_L,   KC_P, KC_QUOT,
  // ├─────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────┤
       KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,      KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  // ╰─────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────╯
  	                                  
                          MO(RAISE),CMD_T(KC_BSPC), KC_BSPC,	  LT(RAISE, KC_ENT), LT(RAISE, KC_ENT),KC_SPC,	
                   MT(MOD_LALT,KC_TAB),  MT(MOD_LCTL,KC_DEL),    LT(RAISE, KC_ENT), LT(RAISE, KC_ENT)
  //                            ╰──────────────────────────╯ ╰──────────────────────────╯
  )),

  [LAYER_LOWER] = LAYOUT_charybdis_4x6(
  // ╭─────────────────────────────────────────────────────╮ ╭─────────────────────────────────────────────────────╮
       KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
  // ├─────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────┤
       RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   KC_LBRC,   KC_P7,   KC_P8,   KC_P9, KC_RBRC, XXXXXXX,
  // ├─────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────┤
       RGB_TOG, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,   KC_PPLS,   KC_P4,   KC_P5,   KC_P6, KC_PMNS, KC_PEQL,
  // ├─────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────┤
      RGB_RMOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   KC_PAST,   KC_P1,   KC_P2,   KC_P3, KC_PSLS, KC_PDOT,
  // ╰─────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────╯
                                  XXXXXXX, XXXXXXX, _______,   XXXXXXX, _______, _______,
                                           XXXXXXX, XXXXXXX,     KC_P0, KC_P0
  //                            ╰──────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_RAISE] = LAYOUT_charybdis_4x6(
  // ╭─────────────────────────────────────────────────────╮ ╭─────────────────────────────────────────────────────╮
        KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  // ├─────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────┤
       KC_MNXT, A(KC_BSPC), KC_BSPC, KC_UP, KC_DEL, A(KC_DEL),      KC_LBRC,   KC_P7,   KC_P8,   KC_P9, KC_RBRC, XXXXXXX,
  // ├─────────────────────────────────────────────────────┤ ├───────────────────────────────────────────────────────────┤
       KC_MPLY, G(KC_LEFT), KC_LEFT, KC_DOWN, KC_RGHT, G(KC_RIGHT),  KC_PPLS,   KC_P4,   KC_P5,   KC_P6, KC_PMNS, KC_PEQL,
  // ├─────────────────────────────────────────────────────┤ ├───────────────────────────────────────────────────────────┤
       KC_LSFT, KC_HOME, KC_PGUP, KC_ENT, KC_PGDN,  KC_END,          KC_PAST,   KC_P1,   KC_P2,   KC_P3, KC_PSLS, KC_LSFT,
  // ╰─────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────╯
                                  _______, _______, XXXXXXX,   _______, KC_PDOT, KC_PDOT,
                                           _______, _______,    KC_P0, KC_P0
  //                            ╰──────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_POINTER] = LAYOUT_charybdis_4x6(
  // ╭─────────────────────────────────────────────────────╮ ╭─────────────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├─────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, KC_WH_L, KC_WH_U, KC_WH_R, S_D_MOD,   S_D_MOD,KC_WH_L, KC_WH_U, KC_WH_R,  XXXXXXX, XXXXXXX,
  // ├─────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────┤
       XXXXXXX, KC_LGUI, KC_BTN2, KC_WH_D, KC_BTN1, XXXXXXX,   XXXXXXX, KC_BTN1, KC_WH_D, KC_BTN2, KC_RGUI, XXXXXXX,
  // ├─────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────┤
       XXXXXXX, _______, DRGSCRL, SNIPING, EEP_RST, USR_RST,   USR_RST, EEP_RST, SNIPING, DRGSCRL, _______, XXXXXXX,
  // ╰─────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────╯
                                  XXXXXXX, KC_BTN1, KC_BTN3,   KC_BTN3, KC_BTN1, KC_BTN1,
                                           XXXXXXX, KC_BTN2,   KC_BTN2, KC_BTN2
  //                            ╰──────────────────────────╯ ╰──────────────────────────╯
  ),
};
// clang-format on

/** Whether SHIFT mod is enabled. */
static bool _has_shift_mod(void) {
#ifdef NO_ACTION_ONESHOT
  return mod_config(get_mods()) & MOD_MASK_SHIFT;
#else
  return mod_config(get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT;
#endif  // NO_ACTION_ONESHOT
}

#ifdef POINTING_DEVICE_ENABLE
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (!process_caps_word(keycode, record)) { return false; }

  switch (keycode) {
    case USER_RESET:
      if (record->event.pressed) {
#ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_RED);
#endif  // RGB_MATRIX_ENABLE
      } else {
        reset_keyboard();
      }
      break;
    case POINTER_DEFAULT_DPI_FORWARD:
      if (record->event.pressed) {
        // Step backward if shifted, forward otherwise.
        charybdis_cycle_pointer_default_dpi(/* forward= */ !_has_shift_mod());
      }
      break;
    case POINTER_DEFAULT_DPI_REVERSE:
      if (record->event.pressed) {
        // Step forward if shifted, backward otherwise.
        charybdis_cycle_pointer_default_dpi(/* forward= */ _has_shift_mod());
      }
      break;
    case POINTER_SNIPING_DPI_FORWARD:
      if (record->event.pressed) {
        // Step backward if shifted, forward otherwise.
        charybdis_cycle_pointer_sniping_dpi(/* forward= */ !_has_shift_mod());
      }
      break;
    case POINTER_SNIPING_DPI_REVERSE:
      if (record->event.pressed) {
        // Step forward if shifted, backward otherwise.
        charybdis_cycle_pointer_sniping_dpi(/* forward= */ _has_shift_mod());
      }
      break;
    case SNIPING_MODE:
      charybdis_set_pointer_sniping_enabled(record->event.pressed);
      break;
    case SNIPING_MODE_TOGGLE:
      if (record->event.pressed) {
        charybdis_set_pointer_sniping_enabled(
            !charybdis_get_pointer_sniping_enabled());
      }
      break;
    case DRAGSCROLL_MODE:
      charybdis_set_pointer_dragscroll_enabled(record->event.pressed);
      break;
    case DRAGSCROLL_MODE_TOGGLE:
      if (record->event.pressed) {
        charybdis_set_pointer_dragscroll_enabled(
            !charybdis_get_pointer_dragscroll_enabled());
      }
      break;
  }
  return true;
}

#ifdef AUTO_SNIPING_MODE_ON_LAYER
layer_state_t layer_state_set_kb(layer_state_t state) {
  state = layer_state_set_user(state);
  charybdis_set_pointer_sniping_enabled(
      layer_state_cmp(state, AUTO_SNIPING_MODE_ON_LAYER));
  return state;
}
#endif  // AUTO_SNIPING_MODE_ON_LAYER
#endif  // POINTING_DEVICE_ENABLE

#ifdef CONSOLE_ENABLE
void keyboard_post_init_user(void) { debug_enable = true; }
#endif  // CONSOLE_ENABLE
