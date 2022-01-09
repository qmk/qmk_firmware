/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2021 Rocco Meli <@RMeli>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>

#include "rmeli.h"

// + -------------------- +
// + RGB MATRIX CALLBACKS |
// + -------------------- +

// LED numbers:
//      https://github.com/foostan/crkbd/blob/main/corne-classic/doc/buildguide_en.md

// Change LED color to red when CAPS LOCK is active
void rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(26, 255, 0, 0);
        // Only works with SPLIT_LED_STATE_ENABLE
        rgb_matrix_set_color(53, 255, 0, 0);
    }
}

// + ---- +
// + OLED |
// + ---- +

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_rocco();
    } else {
        oled_render_meli();
    }
    return false;
}


// + ---------- +
// + TAP DANCES |
// + ---------- +

// Tap dance enums
enum {
    TD_LSPO_CAPS, // Tap once for (, hold once for LSFT, tap twice for CAPS
    TD_RSPC_CAPS, // Tap once for ), hold once for RSFT, tap twice for CAPS
    TD_ESC_DEL, // Tap once for KC_ESC, twice for KC_DEL
};

// Tap dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_LSPO_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, LSPO_CAPS_finished, LSPO_CAPS_reset),
    [TD_RSPC_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, RSPC_CAPS_finished, RSPC_CAPS_reset),
    [TD_ESC_DEL] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_DEL),
};

// + --------- +
// + SHORTCUTS |
// + --------- +

// Rename tap dances for keymap with shortcuts
#define TD_LSPC TD(TD_LSPO_CAPS)
#define TD_RSPC TD(TD_RSPC_CAPS)
#define TD_ED TD(TD_ESC_DEL)

// + ------- +
// + KEY MAP |
// + ------- +

// Layer names
#define _QWERTY 0
#define _COLEMAK_DH 1
#define _DWN 2
#define _UP 3
#define _CONFIG 4

// Layer names shortcuts
#define _QWY 0
#define _CMK 1
#define _CFG 4

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        TD_ED,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TD_LSPC,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, TD_RSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,MO(_DWN),  KC_SPC,     KC_ENT,MO(_UP),  KC_RCTL
                                      //|--------------------------|  |--------------------------|
  ),

  [_COLEMAK_DH] = LAYOUT_split_3x6_3(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
       KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U, KC_SCLN,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        TD_ED,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TD_LSPC,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, TD_RSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,MO(_DWN),  KC_SPC,     KC_ENT,MO(_UP),  KC_RCTL
                                      //|--------------------------|  |--------------------------|
  ),

  [_DWN] = LAYOUT_split_3x6_3(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   A_GRV,   E_GRV,   I_GRV,   O_GRV,   U_GRV,                      XXXXXXX, XXXXXXX,   KC_UP, XXXXXXX, KC_PGUP, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX,   E_ACT, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_LEFT, KC_DOWN,KC_RIGHT, KC_PGDN, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______, _______,    _______,MO(_CFG), _______
                                      //|--------------------------|  |--------------------------|
  ),

  [_UP] = LAYOUT_split_3x6_3(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
      _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LEFT, KC_DOWN,  KC_UP, KC_RIGHT, XXXXXXX,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,MO(_CFG), _______,   _______, _______, _______
                                      //|--------------------------|  |--------------------------|
  ),

  [_CONFIG] = LAYOUT_split_3x6_3(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
        RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_ASRP, XXXXXXX, XXXXXXX, XXXXXXX,DF(_QWY),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,                       UC_MOD, KC_ASTG,   NK_ON, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,                      UC_RMOD, KC_ASDN,  NK_OFF, XXXXXXX, XXXXXXX,DF(_CMK),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,   _______, _______, _______
                                      //|--------------------------|  |--------------------------|
  )
};