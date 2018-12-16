/* Copyright 2017 Jeremy Cowgar
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

#ifdef AUTO_SHIFT_ENABLE

#include <stdio.h>

#include "process_auto_shift.h"

#define TAP(key) \
  register_code(key); \
  unregister_code(key)

#define TAP_WITH_MOD(mod, key) \
  register_code(mod); \
  register_code(key); \
  unregister_code(key); \
  unregister_code(mod)

uint16_t autoshift_time = 0;
uint16_t autoshift_timeout = AUTO_SHIFT_TIMEOUT;
uint16_t autoshift_lastkey = KC_NO;

void autoshift_timer_report(void) {
  char display[8];

  snprintf(display, 8, "\n%d\n", autoshift_timeout);

  send_string((const char *)display);
}

void autoshift_on(uint16_t keycode) {
  autoshift_time = timer_read();
  autoshift_lastkey = keycode;
}

void autoshift_flush(void) {
  if (autoshift_lastkey != KC_NO) {
    uint16_t elapsed = timer_elapsed(autoshift_time);

    if (elapsed > autoshift_timeout) {
      register_code(KC_LSFT);
    }

    register_code(autoshift_lastkey);
    unregister_code(autoshift_lastkey);

    if (elapsed > autoshift_timeout) {
      unregister_code(KC_LSFT);
    }

    autoshift_time = 0;
    autoshift_lastkey = KC_NO;
  }
}

bool autoshift_enabled = true;

void autoshift_enable(void) {
    autoshift_enabled = true;
}
void autoshift_disable(void) {
  autoshift_enabled = false;
  autoshift_flush();
}

void autoshift_toggle(void) {
  if (autoshift_enabled) {
    autoshift_enabled = false;
    autoshift_flush();
  }
  else {
    autoshift_enabled = true;
  }
}

bool autoshift_state(void) {
  return autoshift_enabled;
}

bool process_auto_shift(uint16_t keycode, keyrecord_t *record) {
#ifndef AUTO_SHIFT_MODIFIERS
  static uint8_t any_mod_pressed;
#endif

  if (record->event.pressed) {
    switch (keycode) {
      case KC_ASUP:
        autoshift_timeout += 5;
        return false;

      case KC_ASDN:
        autoshift_timeout -= 5;
        return false;

      case KC_ASRP:
        autoshift_timer_report();
        return false;

      case KC_ASTG:
        autoshift_toggle();
        return false;
      case KC_ASON:
        autoshift_enable();
        return false;
      case KC_ASOFF:
        autoshift_disable();
        return false;

#ifndef NO_AUTO_SHIFT_ALPHA
      case KC_A:
      case KC_B:
      case KC_C:
      case KC_D:
      case KC_E:
      case KC_F:
      case KC_G:
      case KC_H:
      case KC_I:
      case KC_J:
      case KC_K:
      case KC_L:
      case KC_M:
      case KC_N:
      case KC_O:
      case KC_P:
      case KC_Q:
      case KC_R:
      case KC_S:
      case KC_T:
      case KC_U:
      case KC_V:
      case KC_W:
      case KC_X:
      case KC_Y:
      case KC_Z:
#endif
#ifndef NO_AUTO_SHIFT_NUMERIC
      case KC_1:
      case KC_2:
      case KC_3:
      case KC_4:
      case KC_5:
      case KC_6:
      case KC_7:
      case KC_8:
      case KC_9:
      case KC_0:
#endif
#ifndef NO_AUTO_SHIFT_SPECIAL
      case KC_MINUS:
      case KC_EQL:
      case KC_TAB:
      case KC_LBRC:
      case KC_RBRC:
      case KC_BSLS:
      case KC_SCLN:
      case KC_QUOT:
      case KC_COMM:
      case KC_DOT:
      case KC_SLSH:
      case KC_GRAVE:
      case KC_NONUS_BSLASH:
      case KC_NONUS_HASH:
#endif

        autoshift_flush();
        if (!autoshift_enabled) return true;

#ifndef AUTO_SHIFT_MODIFIERS
        any_mod_pressed = get_mods() & (
          MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI)|
          MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT)|
          MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTL)|
          MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT)
        );

        if (any_mod_pressed) {
          return true;
        }
#endif

        autoshift_on(keycode);
        return false;

      default:
        autoshift_flush();
        return true;
    }
  } else {
    autoshift_flush();
  }

  return true;
}

#endif
