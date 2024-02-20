/* Copyright 2022 durken (https://github.com/durken1/)
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
#include "keymap_swedish.h"

enum layers {
    BASE,
    MBO,
    SYM,
    NUM,
    FN
};

enum combos {
    WF_ARNG,
    EI_ADIA,
    UK_ODIA
};

#if defined PS2_MOUSE_ENABLE
#include "ps2_mouse.h"
#endif

#if defined AUTO_BUTTONS && defined PS2_MOUSE_ENABLE

static uint16_t auto_buttons_timer;
extern int tp_buttons; // mousekey button state set in action.c and used in ps2_mouse.c

void ps2_mouse_moved_user(report_mouse_t *mouse_report) {
    if (auto_buttons_timer) {
        auto_buttons_timer = timer_read();
    } else {
        if (!tp_buttons) {
            layer_on(MBO);
            auto_buttons_timer = timer_read();
        }
    }
}

void matrix_scan_user(void) {
    if (auto_buttons_timer && (timer_elapsed(auto_buttons_timer) > AUTO_BUTTONS_TIMEOUT)) {
        if (!tp_buttons) {
            layer_off(MBO);
            auto_buttons_timer = 0;
        }
    }
}

#endif // defined AUTO_BUTTONS && defined PS2_MOUSE_ENABLE

// Left-hand home row mods
#define GUI_A LGUI_T(KC_A)
#define ALT_R LALT_T(KC_R)
#define SFT_S LSFT_T(KC_S)
#define CTRL_T LCTL_T(KC_T)

// Right-hand home row mods
#define CTL_N RCTL_T(KC_N)
#define SFT_E RSFT_T(KC_E)
#define ALT_I LALT_T(KC_I)
#define GUI_O LGUI_T(KC_O)

#define NUM_SPC LT(NUM, KC_SPC)
#define FN_ENT LT(FN, KC_ENT)
#define SYM_BSP LT(SYM, KC_BSPC)

const uint16_t PROGMEM arng_combo[] = {ALT_R, SFT_S, COMBO_END};
const uint16_t PROGMEM adia_combo[] = {SFT_E, ALT_I, COMBO_END};
const uint16_t PROGMEM odia_combo[] = {SE_U, SE_K, COMBO_END};

combo_t key_combos[] = {
	[WF_ARNG] = COMBO(arng_combo, SE_ARNG),
	[EI_ADIA] = COMBO(adia_combo, SE_ADIA),
	[UK_ODIA] = COMBO(odia_combo, SE_ODIA)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_split_3x5_3(
 // BASE
  //,--------------------------------------------,                    ,--------------------------------------------.
         SE_Q,    SE_W,    SE_F,    SE_P,    SE_B,                         SE_Y,    SE_L,    SE_U,    SE_K, SE_QUOT,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
        GUI_A,   ALT_R,   SFT_S,  CTRL_T,    SE_G,                         SE_M,   CTL_N,   SFT_E,   ALT_I,   GUI_O,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
         SE_Z,    SE_X,    SE_C,    SE_D,    SE_V,                         SE_J,    SE_H, SE_COMM,  SE_DOT, SE_MINS,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                  KC_ESC, NUM_SPC,  KC_TAB,     FN_ENT, SYM_BSP,  KC_DEL
                             //`--------------------------'  '--------------------------'

  ),


  [MBO] = LAYOUT_split_3x5_3(
  // Mouse
  //,--------------------------------------------,                    ,--------------------------------------------.
      _______, _______, _______, _______, _______,                      KC_BTN1, KC_BTN2, _______, _______, _______,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______,                      KC_BTN3, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 _______, _______, _______,    _______, KC_BSPC, _______
                             //`--------------------------'  '--------------------------'

  ),

  [SYM] = LAYOUT_split_3x5_3(
  // Symbols
  //,--------------------------------------------,                    ,--------------------------------------------.
      SE_SECT, SE_ACUT, SE_SLSH, SE_TILD, _______,                      _______, SE_PIPE, SE_BSLS, SE_DIAE, SE_CIRC,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      SE_EXLM,  SE_DLR, SE_LPRN, SE_LBRC, _______,                      _______, SE_RBRC, SE_RPRN, SE_HASH, SE_QUES,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      _______, SE_PERC, SE_LCBR, SE_LABK, _______,                      _______, SE_RABK, SE_RCBR, SE_AMPR, _______,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                   SE_AT,  SE_EQL, SE_DQUO,    _______, _______, _______
                             //`--------------------------'  '--------------------------'
  ),

  [NUM] = LAYOUT_split_3x5_3(
  // Numbers
  //,--------------------------------------------,                    ,--------------------------------------------.
      _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,                      _______,    SE_7,    SE_8,    SE_9, SE_QUOT,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      SE_PLUS, SE_MINS, SE_ASTR, SE_SLSH, SE_CIRC,                      _______,    SE_4,    SE_5,    SE_6, _______,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      _______, _______, KC_VOLD, KC_VOLU, _______,                       KC_SPC,    SE_1,    SE_2,    SE_3, _______,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 _______, _______, _______,    SE_COMM,   SE_0,  SE_DOT
                             //`--------------------------'  '--------------------------'
  ),

  [FN] = LAYOUT_split_3x5_3(
  // FN
  //,--------------------------------------------,                    ,--------------------------------------------.
      _______, _______, _______, _______, _______,                      _______,   KC_F7,   KC_F8,   KC_F9,  KC_F10,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, _______,                      _______,   KC_F4,   KC_F5,   KC_F6,  KC_F11,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______,                      _______,   KC_F1,   KC_F2,   KC_F3,  KC_F12,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 KC_PSCR, KC_CAPS, _______,    _______, _______, _______
                             //`--------------------------'  '--------------------------'
  )
};
