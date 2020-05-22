/*
Copyright 2017 Balz Guenat <balz.guenat@gmail.com>

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

// Key must be released within this many milliseconds to be considered a tap
#define TAPPING_TERM 150

// Timers for tap detection in process_record_user
uint16_t lalt_timer;
uint16_t ralt_timer;

// create some custom keycodes for your keymap
enum custom_keycodes {
  PREV_DESKTOP = SAFE_RANGE,
  NEXT_DESKTOP,
  NEXT_INPUT,
  SWITCH_APP
};

// define some useful send strings
#define SS_PREV_DESKTOP SS_LCTRL(SS_LGUI(SS_TAP(X_LEFT)))
#define SS_NEXT_DESKTOP SS_LCTRL(SS_LGUI(SS_TAP(X_RIGHT)))
#define SS_NEXT_INPUT SS_DOWN(X_LGUI) SS_TAP(X_SPC) SS_DELAY(500) SS_UP(X_LGUI)
//#define SS_SWITCH_APP SS_DOWN(X_LGUI) SS_DOWN(X_LSHT) SS_DOWN(X_TAB) SS_DELAY(300) SS_UP(X_TAB) SS_UP(X_LSHT) SS_UP(X_LGUI) 

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: plain Qwerty without layer switching
     *         ,---------------. ,---------------. ,---------------.
     *         |F13|F14|F15|F16| |F17|F18|F19|F20| |F21|F22|F23|F24|
     * ,---.   |---------------| |---------------| |---------------| ,-----------. ,---------------. ,-------.
     * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau| |VDn|VUp|Mut|Pwr| | Help  |
     * `---'   `---------------' `---------------' `---------------' `-----------' `---------------' `-------'
     * ,-----------------------------------------------------------. ,-----------. ,---------------. ,-------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|JPY|Bsp| |Ins|Hom|PgU| |NmL|  /|  *|  -| |Stp|Agn|
     * |-----------------------------------------------------------| |-----------| |---------------| |-------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  | |Del|End|PgD| |  7|  8|  9|  +| |Mnu|Und|
     * |-----------------------------------------------------------| `-----------' |---------------| |-------|
     * |CapsL |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  :|  #|Retn|               |  4|  5|  6|KP,| |Sel|Cpy|
     * |-----------------------------------------------------------|     ,---.     |---------------| |-------|
     * |Shft|  <|  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /| RO|Shift |     |Up |     |  1|  2|  3|KP=| |Exe|Pst|
     * |-----------------------------------------------------------| ,-----------. |---------------| |-------|
     * |Ctl|Gui|Alt|MHEN|HNJ| Space  |H/E|HENK|KANA|Alt|Gui|App|Ctl| |Lef|Dow|Rig| |  0    |  .|Ent| |Fnd|Cut|
     * `-----------------------------------------------------------' `-----------' `---------------' `-------'
     */

    /*
    [0] = LAYOUT_all(
                      KC_F13,  KC_F14,  KC_F15,  KC_F16, KC_F17, KC_F18, KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,
    KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  KC_F6,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,               KC_PSCR, KC_SLCK, KC_PAUS,    KC_VOLD, KC_VOLU, KC_MUTE, KC_PWR,     KC_HELP,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_JYEN, KC_BSPC,     KC_INS,  KC_HOME, KC_PGUP,    KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,    KC_STOP, KC_AGIN,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSLS,     KC_DEL,  KC_END,  KC_PGDN,    KC_P7,   KC_P8,   KC_P9,   KC_PPLS,    KC_MENU, KC_UNDO,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_NUHS, KC_ENT,                                    KC_P4,   KC_P5,   KC_P6,   KC_PCMM,    KC_SLCT, KC_COPY,
    KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RO,   KC_RSFT,              KC_UP,               KC_P1,   KC_P2,   KC_P3,   KC_PEQL,    KC_EXEC, KC_PSTE,
    KC_LCTL, KC_LGUI, KC_LALT, KC_MHEN, KC_HANJ,         KC_SPC,         KC_HAEN, KC_HENK, KC_KANA, KC_RALT, KC_RGUI, KC_APP,  KC_RCTL,     KC_LEFT, KC_DOWN, KC_RGHT,    KC_P0,            KC_PDOT, KC_PENT,    KC_FIND, KC_CUT
    ),
    */


   [0] = LAYOUT_all(
                      KC_F13,  KC_F14,  KC_F15,  KC_F16, KC_F17, KC_F18, KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,
    KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  KC_F6,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,               KC_PSCR, KC_SLCK, RESET,    KC_VOLD, KC_VOLU, KC_MUTE, KC_PWR,     KC_HELP,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_JYEN, KC_BSPC,     KC_INS,  KC_HOME, KC_PGUP,    KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,    KC_STOP, KC_AGIN,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSLS,     KC_DEL,  KC_END,  KC_PGDN,    KC_P7,   KC_P8,   KC_P9,   KC_PPLS,    KC_MENU, KC_UNDO,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_NUHS, KC_ENT,                                    KC_P4,   KC_P5,   KC_P6,   KC_PCMM,    KC_SLCT, KC_COPY,
    KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RO,   KC_RSFT,              KC_UP,               KC_P1,   KC_P2,   KC_P3,   KC_PEQL,    KC_EXEC, KC_PSTE,
    NEXT_INPUT, SWITCH_APP, PREV_DESKTOP, KC_MHEN, KC_HANJ,         KC_SPC,         KC_HAEN, KC_HENK, KC_KANA, NEXT_DESKTOP, KC_RGUI, KC_LGUI,  KC_RCTL,     KC_LEFT, KC_DOWN, KC_RGHT,    KC_P0,            KC_PDOT, KC_PENT,    KC_FIND, KC_CUT
    ),

    [1] = LAYOUT_all(
                      ______,  ______,  ______, ______, ______,  ______,  ______, ______,  ______, ______, ______, ______,
    ______,           ______,  ______,  ______, ______, ______,  ______,  ______, ______,  ______, ______, ______, ______,             ______,______,______,    ______,______,______,______,    ______,
    ______,  ______,  ______,  ______,  ______, ______, ______,  ______,  ______, ______,  ______, ______, ______, ______, ______,     ______,______,______,    ______,______,______,______,    ______,______,
    ______,  ______,  ______,  ______,  ______, ______, ______,  ______,  ______, ______,  ______, ______, ______,         ______,     ______,______,______,    ______,______,______,______,    ______,______,
    ______,  ______,  ______,  ______,  ______, ______, ______,  ______,  ______, ______,  ______, ______,         ______, ______,                              ______,______,______,______,    ______,______,
    ______,  ______,  ______,  ______,  ______, ______, ______,  ______,  ______, ______,  ______, ______,         ______, ______,            ______,           ______,______,______,______,    ______,______,
    ______,  ______,  ______,  ______,  ______,         ______,           ______, ______,  ______, ______, ______, ______, ______,     ______,______,______,    ______,       ______,______,    ______,______
    ),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch(keycode) {
  case PREV_DESKTOP:
    if (record->event.pressed) {
      // Activate LALT
      lalt_timer = timer_read();
      SEND_STRING(SS_DOWN(X_LALT));
    } else {
      // Deactivate LALT
      SEND_STRING(SS_UP(X_LALT));
      // If the action was a tap
      if (timer_elapsed(lalt_timer) < TAPPING_TERM) {
	    SEND_STRING(SS_PREV_DESKTOP);
      }
    }
    return false;

  case NEXT_DESKTOP:
    if (record->event.pressed) {
      // Activate RALT
      ralt_timer = timer_read();
      SEND_STRING(SS_DOWN(X_RALT));
    } else {
      // Deactivate RALT
      SEND_STRING(SS_UP(X_RALT));
      // If the action was a tap
      if (timer_elapsed(ralt_timer) < TAPPING_TERM) {
	    SEND_STRING(SS_NEXT_DESKTOP);
      }
    }
    return false;

    case NEXT_INPUT:
    if (record->event.pressed) {
      // Activate LCTL
      ralt_timer = timer_read();
      SEND_STRING(SS_DOWN(X_LCTL));
    } else {
      // Deactivate LCTL
      SEND_STRING(SS_UP(X_LCTL));
      // If the action was a tap
      if (timer_elapsed(ralt_timer) < TAPPING_TERM) {
	    SEND_STRING(SS_NEXT_INPUT);
      }
    }
    return false;  

    case SWITCH_APP:
    if (record->event.pressed) {
      // Activate LGUI      
      ralt_timer = timer_read();
      register_code(KC_LGUI);
    } else {
      // Deactivate LCTL
      // If the action was a tap
      if (timer_elapsed(ralt_timer) < TAPPING_TERM) {
  	    register_code(KC_LSFT);
        register_code(KC_LALT);
        register_code(KC_TAB);
        unregister_code(KC_TAB);
        SEND_STRING(SS_DELAY(2000));
        unregister_code(KC_LALT);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
      } else {
        unregister_code(KC_LGUI);
      }
    }
    return false;

  }
  return true;
}
