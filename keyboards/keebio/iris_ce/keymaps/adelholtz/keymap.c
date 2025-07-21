// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include QMK_KEYBOARD_H

#include "keymap_german.h"
#include "adelholtz.h"
// LMAGIC and RMAGIC definitions
#include "magic.c"
#include "tap_dance.c"
#include "layer_layout.c"

// clang-format off
const char PROGMEM chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] =
  LAYOUT(
        'L', 'L', 'L', 'L', 'L', 'L',        'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',        'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',        'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L','*','*','R', 'R', 'R', 'R', 'R', 'R',
                       '*', '*', '*',        '*', '*', '*'
    );
// clang-format on

#include "combos.c"

// custom keystroke main logic
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case RELOAD: {
        SEND_STRING(detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS ? SS_LGUI("r")
                                                                                   : (detected_host_os() == OS_LINUX || detected_host_os() == OS_WINDOWS ? SS_LCTL("r") : ""));
      }
        return false;
      case LCURLY: { // os specific {
        SEND_STRING(detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS ? SS_ALGR("8")
                                                                                   : (detected_host_os() == OS_LINUX || detected_host_os() == OS_WINDOWS ? SS_ALGR("7") : ""));
      }
        return false;
      case RCURLY: { // os specific }
        SEND_STRING(detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS ? SS_ALGR("9")
                                                                                   : (detected_host_os() == OS_LINUX || detected_host_os() == OS_WINDOWS ? SS_ALGR("0") : ""));
      }
        return false;
      case PIPE_: { // os specific |
        SEND_STRING(detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS ? SS_ALGR("7")
                                                                                   : (detected_host_os() == OS_LINUX || detected_host_os() == OS_WINDOWS ? "|" : ""));
      }
      case LBRACKET: { // os specific [
        SEND_STRING(detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS ? SS_ALGR("5")
                                                                                   : (detected_host_os() == OS_LINUX || detected_host_os() == OS_WINDOWS ? SS_ALGR("8") : ""));
      }
      case RBRACKET: { // os specific ]
        SEND_STRING(detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS ? SS_ALGR("6")
                                                                                   : (detected_host_os() == OS_LINUX || detected_host_os() == OS_WINDOWS ? SS_ALGR("9") : ""));
      }
        return false;
      // case LMAGIC: {
      //   process_left_magic(get_last_keycode(), get_last_mods());
      //   set_last_keycode(KC_SPC);
      // }
      //   return false;
      // case RMAGIC: {
      //   process_right_magic(get_last_keycode(), get_last_mods());
      //   set_last_keycode(KC_SPC);
      // }
      //   return false;
    }
  }

  return true;
}

void keyboard_post_init_user(void) {
  rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_WIDE);
  rgb_matrix_sethsv(191, 255, 255); // purple
}
