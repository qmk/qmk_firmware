/* Copyright 2021 @ Keychron (https://www.keychron.com)
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
#include "cflye.h"
#include "print.h"
#include "features/achordion.h"

// clang-format off


#define TOG_WS MT(MOD_LGUI | MOD_LSFT, KC_PSCR)

#define LAYOUT_keychron_v1_wrapper(...) LAYOUT_iso_83(__VA_ARGS__)

#undef _________________THUMB_RIGHT_______________
#define _________________THUMB_RIGHT_______________       LT(_FUN,KC_DEL),  LT(_SYM,KC_TAB),   LT(_NUM,KC_TAB),   KC_NO,              KC_NO

#define LAYOUT_keychron_v1_base(\
     K00, K01, K02, K03, K04,                K05, K06, K07, K08, K09,\
     K10, K11, K12, K13, K14,                K15, K16, K17, K18, K19,\
     K20, K21, K22, K23, K24,                K25, K26, K27, K28, K29,\
     N30, N31, K32, K33, K34,                K35, K36, K37, N38, N39\
) \
LAYOUT_keychron_v1_wrapper(\
    KC_ESC,     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  QK_BOOT,     KC_MPLY,\
    KC_GRV,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXX,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_BSPC,     KC_DEL,\
    KC_TAB,     K00,     K01,     K02,     K03,     K04,     XXX,     K05,     K06,     K07,     K08,     K09,     XXX,                  KC_HOME,\
    KC_LSFT,    K10,     K11,     K12,     K13,     K14,     KC_AA,   K15,     K16,     K17,     K18,     K19,     KC_RSFT, KC_ENT,      KC_END,\
    KC_LCTL,    K20,     K21,     K22,     K23,     K24,     KC_AE,   KC_OE,   K25,     K26,     K27,     K28,     K29,     KC_UP,          \
    KC_LGUI,    K32,     LT(_NAV,KC_ESC),                KC_SPC,                       K36, K37, KC_LGUI,              KC_LEFT, KC_DOWN, KC_RGHT\
)

#define LAYOUT_keychron_v1_gaming(\
     K00, K01, K02, K03, K04,                K05, K06, K07, K08, K09,\
     K10, K11, K12, K13, K14,                K15, K16, K17, K18, K19,\
     K20, K21, K22, K23, K24,                K25, K26, K27, K28, K29,\
     N30, N31, K32, K33, K34,                K35, K36, K37, N38, N39\
) \
LAYOUT_keychron_v1_wrapper(\
    KC_ESC,     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  TOG_WS,      KC_MPLY,\
    KC_GRV,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXX,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_BSPC,     KC_DEL,\
    KC_TAB,     K00,     K01,     K02,     K03,     K04,     XXX,     K05,     K06,     K07,     K08,     K09,     XXX,                  KC_HOME,\
    KC_LSFT,    K10,     K11,     K12,     K13,     K14,     KC_AA,   K15,     K16,     K17,     K18,     K19,     XXX,     KC_ENT,      KC_END,\
    KC_LCTL,    K20,     K21,     K22,     K23,     K24,     KC_AE,   KC_OE,   K25,     K26,     K27,     K28,     KC_RSFT,     KC_UP,          \
    K32,        K33,     KC_LALT,                         KC_SPC,                       K36, K37, KC_LGUI,             KC_LEFT, KC_DOWN, KC_RGHT\
)


#define LAYOUT_base_wrapper(...) LAYOUT_keychron_v1_base(__VA_ARGS__)
#define LAYOUT_gaming_wrapper(...) LAYOUT_keychron_v1_gaming(__VA_ARGS__)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [_BASE] = LAYOUT_base_wrapper(
    _________________COLEMAK_L1_________________, _________________COLEMAK_R1_________________,
    _________________COLEMAK_L2_________________, _________________COLEMAK_R2_________________,
    _________________COLEMAK_L3_________________, _________________COLEMAK_R3_________________,
    _________________THUMB_LEFT________________,  _________________THUMB_RIGHT_______________
),
[_GAMING] = LAYOUT_gaming_wrapper(
    _________________GAMING_L1__________________, _________________GAMING_R1__________________,
    _________________GAMING_L2__________________, _________________GAMING_R2__________________,
    _________________GAMING_L3__________________, _________________GAMING_R3__________________,
    _________________THUMB_LEFT________________,  _________________THUMB_RIGHT_______________
),
[_SYM] = LAYOUT_base_wrapper(
    ___________________SYM_L1___________________, ___________________SYM_R1___________________,
    ___________________SYM_L2___________________, ___________________SYM_R2___________________,
    ___________________SYM_L3___________________, ___________________SYM_R3___________________,
    ___________________BLANK___________________,  ___________________BLANK___________________
),
[_NUM] = LAYOUT_base_wrapper(
    ___________________NUM_L1___________________, ___________________NUM_R1___________________,
    ___________________NUM_L2___________________, ___________________NUM_R2___________________,
    ___________________NUM_L3___________________, ___________________NUM_R3___________________,
    ___________________NUM_L4___________________,  ___________________BLANK___________________
),
[_FUN] = LAYOUT_base_wrapper(
    ___________________FUN_L1___________________, ___________________FUN_R1___________________,
    ___________________FUN_L2___________________, ___________________FUN_R2___________________,
    ___________________FUN_L3___________________, ___________________FUN_R3___________________,
    ___________________FUN_L4___________________, ___________________FUN_R4___________________
),
[_MEDIA] = LAYOUT_base_wrapper(
    __________________MEDIA_L1__________________, __________________MEDIA_R1__________________,
    __________________MEDIA_L2__________________, __________________MEDIA_R2__________________,
    __________________MEDIA_L3__________________, __________________MEDIA_R3__________________,
    __________________MEDIA_L4__________________,  __________________MEDIA_R4__________________
),
[_NAV] = LAYOUT_base_wrapper(
    ___________________NAV_L1___________________, ___________________NAV_R1___________________,
    ___________________NAV_L2___________________, ___________________NAV_R2___________________,
    ___________________NAV_L3___________________, ___________________NAV_R3___________________,
    ___________________NAV_L4___________________, ___________________NAV_R4___________________
),
[_MOUSE] = LAYOUT_base_wrapper(
    __________________MOUSE_L1__________________, __________________MOUSE_R1__________________,
    __________________MOUSE_L2__________________, __________________MOUSE_R2__________________,
    __________________MOUSE_L3__________________, __________________MOUSE_R3__________________,
    __________________MOUSE_L4__________________, __________________MOUSE_R4__________________
),

};
// clang-format on
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE]    = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_GAMING]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_NUM]     = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [_SYM]     = { ENCODER_CCW_CW(RGB_RMOD,RGB_MOD)},
    [_FUN]     = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [_MEDIA]   = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [_NAV]     = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [_MOUSE]   = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS)}
};  
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _NUM, _SYM, _FUN);
    state = update_tri_layer_state(state, _NAV, _MEDIA, _MOUSE);
    return state;
}

void keyboard_post_init_user(void) {
    uprintf("keyboard_post_init_user");
    set_single_persistent_default_layer(_BASE);
}


bool achordion_chord(uint16_t tap_hold_keycode,
                     keyrecord_t* tap_hold_record,
                     uint16_t other_keycode,
                     keyrecord_t* other_record) {
  uprintf("achordion_chord: kc: 0x%04X, col: %2u, row: %2u, kc: 0x%04X, col: %2u, row: %2u\n", other_keycode, other_record->event.key.col, other_record->event.key.row, tap_hold_keycode, tap_hold_record->event.key.col, tap_hold_record->event.key.row);
  // Exceptionally consider the following chords as holds, even though they
  // are on the same hand in Colemak.
  return true;
  switch (tap_hold_keycode) {
    case HOME_S:  // S + D and S + W.o
      if (other_keycode == KC_D || other_keycode == KC_W || other_keycode == KC_P || other_keycode == KC_LSFT) { return true; }
      break;
    case HOME_E:  // S + D and S + W.o
      if (other_keycode == KC_RSFT) { return true; }
      break; 
    case HOME_R:  // S + D and S + W.o
      if (other_keycode == KC_J || other_keycode == KC_H || other_keycode == KC_P || other_keycode == KC_LSFT) { 
        return true; }
      break;
  }
  // Also allow same-hand holds when the other key is in the rows below the
  // alphas. I need the `% (MATRIX_ROWS / 2)` because my keyboard is split.
  if (other_record->event.key.row >= 9|| tap_hold_record->event.key.row >= 9 ) { return true; }


  switch (other_keycode) {
    case KC_LEFT:
    case KC_UP:
    case KC_DOWN:
    case KC_RGHT:
      return true;
  }

  // Otherwise, follow the opposite hands rule.
  return achordion_opposite_hands(tap_hold_record, other_record);
}