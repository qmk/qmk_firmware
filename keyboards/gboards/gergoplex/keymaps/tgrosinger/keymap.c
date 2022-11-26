/* Copyright 2022 Tony Grosinger
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
#include "g/keymap_combo.h"

enum {
  _ALPHA,  // Default
  _SYMB,   // Symbols
  _NUMB,   // Numbers
  _ARROWS, // Arrows and OS
  _TMUX,   // TMUX Nav layer
  _POPOS,  // Gnome Shell, aka PopOS
};


// Macros
enum custom_keycodes {
  TMUX_NEW = SAFE_RANGE,
  TMUX_ZOOM,
  TMUX_SCROLL,
  TMUX_PN_LT,
  TMUX_PN_UP,
  TMUX_PN_DN,
  TMUX_PN_RT,
  TMUX_WN_LT,
  TMUX_WN_RT,
  TMUX_SP_VT,
  TMUX_SP_HZ,
  VIM_CLIP_CP,
  VIM_CLIP_PST,
  VIM_MACRO,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case TMUX_NEW:
      if (record->event.pressed) {
        tap_code16(C(KC_B));
        SEND_STRING("c");
      }
      break;
    case TMUX_ZOOM:
      if (record->event.pressed) {
        tap_code16(C(KC_B));
        SEND_STRING("z");
      }
      break;
    case TMUX_SCROLL:
      if (record->event.pressed) {
        tap_code16(C(KC_B));
        SEND_STRING("[");
      }
      break;
    case TMUX_PN_LT:
      if (record->event.pressed) {
        tap_code16(C(KC_B));
        tap_code(KC_LEFT);
      }
      break;
    case TMUX_PN_DN:
      if (record->event.pressed) {
        tap_code16(C(KC_B));
        tap_code(KC_DOWN);
      }
      break;
    case TMUX_PN_UP:
      if (record->event.pressed) {
        tap_code16(C(KC_B));
        tap_code(KC_UP);
      }
      break;
    case TMUX_PN_RT:
      if (record->event.pressed) {
        tap_code16(C(KC_B));
        tap_code(KC_RIGHT);
      }
      break;
    case TMUX_WN_LT:
      if (record->event.pressed) {
        tap_code16(C(KC_B));
        SEND_STRING("p");
      }
      break;
    case TMUX_WN_RT:
      if (record->event.pressed) {
        tap_code16(C(KC_B));
        SEND_STRING("n");
      }
      break;
    case TMUX_SP_VT:
      if (record->event.pressed) {
        tap_code16(C(KC_B));
        SEND_STRING("%");
      }
      break;
    case TMUX_SP_HZ:
      if (record->event.pressed) {
        tap_code16(C(KC_B));
        SEND_STRING("\"");
      }
      break;
    case VIM_CLIP_CP:
      if (record->event.pressed) {
        tap_code16(S(KC_QUOTE));
        tap_code16(S(KC_EQUAL));
        tap_code(KC_Y);
      }
      break;
    case VIM_CLIP_PST:
      if (record->event.pressed) {
        tap_code16(S(KC_QUOTE));
        tap_code16(S(KC_EQUAL));
        tap_code(KC_P);
      }
      break;
    case VIM_MACRO:
      if (record->event.pressed) {
        tap_code16(S(KC_2));
        tap_code(KC_Q);
      }
      break;
    /*
    case LAYRMOD:
      // Act as a mod key if held, or toggle a layer if tapped
      // replace KC_LCTL with desired mod, and _TARGET with desired layer name / number
      if (record->event.pressed) {
        uint8_t key_timer = timer_read();
        register_mods(MOD_BIT(KC_LCTL));
      } else {
        unregister_mods(MOD_BIT(KC_LCTL));
        if (timer_elapsed(key_timer) < 200) {
          layer_invert(_TARGET);
        }
      }
      return false;
      break;
    */
  }
  return true;
}

/* Combos
 *
 * ,-----------------------------.      ,-----------------------------.
 * |     `     |     |     |     |      |     |    MINS   |    BSLH   |
 * |-----+----ESC----+-----+-----|      |-----+-----+-----+-----------|
 * |     |   BSPC   TAB    |     |      |    LES   COLN  GRT    |     |
 * |-----+-----+-----+--RMB+-LMB-|      |-----+-----+-----+-----------|
 * |     |     |    ENT    |     |      |    QUO   UNDR   |     |     |
 * `-----+-----+-----+-----+-----'      `-----------------------------'
 *     .-------------------------.           .-------------------.
 *     |        |       |        |           |        |    |     |
 *     '-------------------------'           '-------------------'
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap 0: Default layer
  * ,------------------------------.      ,----------------------------------.
  * |  Q   |  W  |  E  |  R  |  T  |      |  Y  |  U  |  I  |   O   |    P   |
  * |------+-----+-----+-----+-----|      |-----+-----+-----+-------+--------|
  * |CTRL/A|  S  |  D  |  F  |  G  |      |  H  |  J  |  K  |   L   | CTRL/; |
  * |------+-----+-----+-----+-----|      |-----+-----+-----+-------+--------|
  * |SHFT/Z|ALT/X|  C  |  V  |  B  |      |  N  |  M  |  <  | ALT/> | SHFT/? |
  * `------+-----+-----+------+----'      `----------------------------------'
  *           .-----------------.             .----------------------.
  *           |   |GUI |SPC(NUM)|             |SPC(SYM)|TMUX | PopOS |
  *           '-----------------'             '----------------------'
  */
  [_ALPHA] = LAYOUT_split_3x5_3(
      KC_Q,              KC_W,               KC_E, KC_R, KC_T,    KC_Y, KC_U, KC_I,    KC_O,   KC_P, 
      MT(MOD_LCTL, KC_A),KC_S,               KC_D, KC_F, KC_G,    KC_H, KC_J, KC_K,    KC_L,   MT(MOD_LCTL, KC_SCLN),
      MT(MOD_LSFT, KC_Z),MT(MOD_LALT, KC_X), KC_C, KC_V, KC_B,    KC_N, KC_M, KC_COMM, MT(MOD_LALT, KC_DOT), MT(MOD_RSFT, KC_SLSH),
              
      KC_NO,   KC_LGUI, LT(_NUMB, KC_SPC),       // Left
      LT(_SYMB, KC_SPC), MO(_TMUX), MO(_POPOS)   // Right
      ),

  /* Keymap 1: Symbols layer
  * ,------------------------------.      ,-------------------------------.
  * |  !   |  @  |  #  |  $  |  %  |      |  ^  |  &  |  *  |  +  |   =   |
  * |------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
  * |  F1  | F2  | F3  | F4  | F5  |      | F6  | F7  | F8  | F9  |  F10  |
  * |------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
  * |      |     |     |     |     |      |     |     |     | F11 |  F12  |
  * `------+-----+-----+-----+-----'      `-------------------------------'
  *        .-----------------.                  .-----------------.
  *        |     | DEL | MO3 |                  | HLD | SPC |     |
  *        '-----------------'                  '-----------------'
  */
  [_SYMB] = LAYOUT_split_3x5_3(
      KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,   KC_CIRC, KC_AMPR, KC_ASTR, KC_PLUS, KC_EQL,
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_F11,  KC_F12,
                KC_NO, KC_DEL, MO(_ARROWS),                 KC_TRNS,  KC_SPC, KC_NO
      ),

  /* Keymap 2: Number layer
  * ,------------------------------.      ,-------------------------------.
  * |  1   |  2  |  3  |  4  |  5  |      |  6  |  7  |  8  |  9  |   0   |
  * |------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
  * | CTRL |     |  (  |  )  |     |      |     |  4  |  7  |  6  |       |
  * |------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
  * | SHFT |     |  [  |  ]  |     |      |     |  1  |  2  |  3  |   .   |
  * `------+-----+-----+-----+-----'      `-------------------------------'
  *        .-----------------.                  .-----------------.
  *        |     |     | HLD |                  | MO3 |  0  |     |
  *        '-----------------'                  '-----------------'
  */
  [_NUMB] = LAYOUT_split_3x5_3(
      KC_1,    KC_2,  KC_3,    KC_4,    KC_5,       KC_6,  KC_7, KC_8, KC_9,  KC_0,
      KC_LCTL, KC_NO, KC_LPRN, KC_RPRN, KC_NO,      KC_NO, KC_4, KC_5, KC_6,  KC_NO,
      KC_LSFT, KC_NO, KC_LBRC, KC_RBRC, KC_NO,      KC_NO, KC_1, KC_2, KC_3,  KC_DOT,
                  KC_NO,KC_NO,KC_TRNS,                   MO(_ARROWS),KC_0,KC_NO
      ),

  /* Keymap 3: Arrows and OS
  * ,------------------------------.      ,------------------------------------.
  * |      |     |     |     |     |      |       |       |      |       |     |
  * |------+-----+-----+-----+-----|      |-------+-------+------+-------+-----|
  * | CTRL |HOME | PUP |     |     |      | LEFT  | DOWN  |  UP  | RIGHT |     |
  * |------+-----+-----+-----+-----|      |-------+-------+------+-------+-----|
  * | SHFT |END  | PDN |     |     |      |       |       |      |       |     |
  * `------+-----+-----+-----+-----'      `------------------------------------'
  *        .-----------------.                   .-----------------.
  *        |     |     | HLD |                   | HLD |     |     |
  *        '-----------------'                   '-----------------'
  */
  [_ARROWS] = LAYOUT_split_3x5_3(
      KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,     KC_NO,        KC_NO,         KC_NO,         KC_NO,         KC_NO,
      KC_LCTL, KC_HOME, KC_PGUP, KC_NO, KC_NO,     KC_LEFT,      KC_DOWN,       KC_UP,         KC_RGHT,       KC_NO,
      KC_LSFT, KC_END,  KC_PGDN, KC_NO, KC_NO,     KC_NO,        KC_NO,         KC_NO,         KC_NO,         KC_NO,
                  KC_NO,KC_NO,KC_TRNS,                   KC_TRNS,KC_NO,KC_NO
      ),
      
  /* Keymap 4: Tmux navigation layer
  * ,----------------------------------.      ,---------------------------------------.
  * | Vi Mcr |     |     |     | SP VT |      | Vi Ynk|       |       |       | Vi PT |
  * |--------+-----+-----+-----+-------|      |-------+-------+-------+-------+-------|
  * |        | SCRL|     |     |       |      | PN LT | PN DN | PN UP | PN RT | SP HZ |
  * |--------+-----+-----+-----+-------|      |-------+-------+-------+-------+-------|
  * |  ZOOM  | KILL| NEW |     |       |      | W LT  |       |       | W RT  |       |
  * `--------+-----+-----+-----+-------'      `---------------------------------------'
  *          .-----------------.                   .-----------------.
  *          |     |     |     |                   |     | HLD |     |
  *          '-----------------'                   '-----------------'
  */
  [_TMUX] = LAYOUT_split_3x5_3(
      VIM_MACRO, KC_NO,       KC_NO,    KC_NO, TMUX_SP_VT,      VIM_CLIP_CP, KC_NO,      KC_NO,      KC_NO,      VIM_CLIP_PST,
      KC_NO,     TMUX_SCROLL, KC_NO,    KC_NO, KC_NO,           TMUX_PN_LT,  TMUX_PN_DN, TMUX_PN_UP, TMUX_PN_RT, TMUX_SP_HZ,
      TMUX_ZOOM, KC_NO,       TMUX_NEW, KC_NO, KC_NO,           TMUX_WN_LT,  KC_NO,      KC_NO,      TMUX_WN_RT, KC_NO,
                  KC_NO,KC_NO,KC_NO,                              KC_NO,KC_TRNS,KC_NO
      ),

  /* Keymap 5: Gnome Shell (PopOS)
  * ,------------------------------.      ,--------------------------------------.
  * |      |     |     |     |     |      | MV-DWN| D-DWN | D-UP  | MV-UP | Flip |
  * |------+-----+-----+-----+-----|      |-------+-------+-------+-------+------|
  * |      |     |     |     |     |      |  W-L  | W-DWN | W-UP  | W-R   |      |
  * |------+-----+-----+-----+-----|      |-------+-------+-------+-------+------|
  * |      |     |     |     |     |      | Scrns | Apps  | Close |       |      |
  * `------+-----+-----+-----+-----'      `--------------------------------------'
  *        .-----------------.                   .-----------------.
  *        |     |     |     |                   |     |     | HLD |
  *        '-----------------'                   '-----------------'
  */
  [_POPOS] = LAYOUT_split_3x5_3(
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     SGUI(KC_J), LCTL(LGUI(KC_J)), LCTL(LGUI(KC_K)), SGUI(KC_K), LGUI(KC_O),
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     LGUI(KC_H), LGUI(KC_J),       LGUI(KC_K),       LGUI(KC_L), KC_NO,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     LGUI(KC_D), LGUI(KC_A),       LGUI(KC_Q),       KC_NO,      KC_NO,
                  KC_NO,KC_NO,KC_NO,                   KC_NO,KC_NO,KC_TRNS
      ),
};
