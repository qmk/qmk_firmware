/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
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

enum charybdis_keymap_layers {
    _MAIN,
    _FUN,
    _NUM,
    _MEDIA,
    _NAV,
    _MOUSE
};

//COMBOS (TOTAL 12)
enum combos {
  PB_LPAR,
  TG_CAP,
  DV_GESC,
  FP_MINS,
  LTH_DEL,

  JL_RPAR,
  MN_SCLN,
  KH_EMAIL,
  LU_PLUS,
  RTH_ESC,

  QQT_PSCR,
  CD_NUM
};

//DEFINE THE COMBO SET UPS (TOTAL 12)
const uint16_t PROGMEM pb_combo[] = {KC_P, KC_B, COMBO_END};
const uint16_t PROGMEM tg_combo[] = {MT(MOD_LSFT,KC_T), KC_G, COMBO_END};
const uint16_t PROGMEM dv_combo[] = {KC_D, KC_V, COMBO_END};
const uint16_t PROGMEM fp_combo[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM lth_combo[] = {LT(_FUN,KC_TAB),  LT(_NUM,KC_BSPC), COMBO_END};

const uint16_t PROGMEM jl_combo[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM mn_combo[] = {KC_M, MT(MOD_RSFT,KC_N), COMBO_END};
const uint16_t PROGMEM kh_combo[] = {KC_K, KC_H, COMBO_END};
const uint16_t PROGMEM lu_combo[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM rth_combo[] = {LT(_MOUSE,KC_SPC), LT(_NAV,KC_ENT), COMBO_END};

const uint16_t PROGMEM qqt_combo[] = {KC_Q, KC_QUOT, COMBO_END};
const uint16_t PROGMEM cd_combo[] = {KC_C, KC_D, COMBO_END};

//DEFINE THE COMBO OUTPUTS (TOTAL 12)
combo_t key_combos[COMBO_COUNT] = {
  [PB_LPAR]  = COMBO(pb_combo, S(KC_9)),
  [TG_CAP]   = COMBO(tg_combo, CAPS_WORD),
  [DV_GESC]  = COMBO(dv_combo,  QK_GESC),
  [FP_MINS]  = COMBO(fp_combo, KC_MINS),
  [LTH_DEL]  = COMBO(lth_combo, KC_DEL),  

  [JL_RPAR]  = COMBO(jl_combo, S(KC_0)),
  [MN_SCLN]  = COMBO(mn_combo, KC_SCLN),
  [KH_EMAIL] = COMBO_ACTION(kh_combo),
  [LU_PLUS]  = COMBO(lu_combo, KC_EQL),
  [RTH_ESC]  = COMBO(rth_combo, QK_GESC),

  [QQT_PSCR] = COMBO(qqt_combo, KC_PSCR),
  [CD_NUM]  = COMBO(cd_combo, KC_NUM)

};

//Macro to send email
void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case KH_EMAIL:
      if (pressed) {
        SEND_STRING("cheung.eden.law@gmail.com");
      }
      break;

  }
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_LGUI,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,       KC_J,    KC_L,    KC_U,    KC_Y,    KC_Y, KC_RGUI,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LCTL,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,       KC_M,    KC_N,    KC_E,    KC_I,     KC_O, KC_RCTL,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,       KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                   KC_TAB, KC_BKSP,  KC_ESC,     KC_ENT,  KC_SPC
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_LOWER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX, RGB_TOG, KC_MNXT, KC_MPLY, KC_MPRV, XXXXXXX,    KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    KC_PPLS,    KC_4,    KC_5,    KC_6, KC_PMNS, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR,  QK_BOOT,    KC_PAST,    KC_1,    KC_2,    KC_3, KC_PSLS, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  XXXXXXX, XXXXXXX, _______,    XXXXXXX, _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_RAISE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_VOLU, KC_MUTE, KC_VOLD, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LEFT,   KC_UP, KC_DOWN, KC_RGHT, XXXXXXX,    XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_HOME, KC_PGUP, KC_PGDN,  KC_END, XXXXXXX,    QK_BOOT, EE_CLR,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, XXXXXXX,    _______, XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
};
// clang-format on
