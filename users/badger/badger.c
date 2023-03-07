/*
Copyright 2020 Dan White <opensource@bluetufa.com>

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
#include "badger.h"

__attribute__ ((weak))
void keyboard_post_init_user(void) {
}

__attribute__ ((weak))
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
    #ifdef CONSOLE_ENABLE
        uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    #endif

  switch (keycode) {
    case CS_RIGHT:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_B)SS_TAP(X_ENTER)));
        return false;
      }
      break;
    case CS_DOWN:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_V)SS_TAP(X_ENTER)));
        return false;
      }
      break;
    case SHEBANG:
      if (record->event.pressed) {
        SEND_STRING("#! /bin/bash");
        SEND_STRING(SS_TAP(X_ENTER));
        return false;
      }
    case FN:
      if (record->event.pressed) {
        SEND_STRING("function ");
        return false;
      }
    case CONST:
      if (record->event.pressed) {
        SEND_STRING("const ");
        return false;
      }
    case SHRUG:
      if (record->event.pressed) {
        SEND_STRING("¯\\_()_/¯");
        SEND_STRING(SS_LALT("D30C4"));
        return false;
      }
    case SELECT:
      if (record->event.pressed) {
        SEND_STRING("SELECT * FROM ;");
        SEND_STRING(SS_TAP(X_LEFT));
        return false;
      }
    case FOR_LOOP:
      if (record->event.pressed) {
        SEND_STRING("for file in $(ls); do echo $file; done");
        return false;
      }
    case SED:
      if (record->event.pressed) {
        SEND_STRING("sed 's/replaceme//g'");
        return false;
      }
    case BASH_IF:
      if (record->event.pressed) {
        SEND_STRING("if [[ 0 -eq 0 ]]; then echo 'true'; fi");
        return false;
      }
    case P_PAREN:
      if (record->event.pressed) {
        SEND_STRING("()");
        SEND_STRING(SS_TAP(X_LEFT));
        return false;
      }
    case P_BRACE:
      if (record->event.pressed) {
        SEND_STRING("{}");
        SEND_STRING(SS_TAP(X_LEFT));
        return false;
      }
    case P_BRACK:
      if (record->event.pressed) {
        SEND_STRING("[]");
        SEND_STRING(SS_TAP(X_LEFT));
        return false;
      }
    case TS_IMPT:
    if (record->event.pressed) {
      SEND_STRING("import {  } from \"\";");
      SEND_STRING(SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT));
      return false;
    }
    default:
      return true;
  }
  return true;
}
