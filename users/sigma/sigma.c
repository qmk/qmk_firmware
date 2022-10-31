/*
  Copyright 2018 Yann Hodique <yann.hodique@gmail.com> @sigma

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
#include "sigma.h"

userspace_config_t runtime_userspace_config;
userspace_config_t stored_userspace_config;

__attribute__ ((weak))
void matrix_init_keymap(void) {}

__attribute__ ((weak))
void startup_keymap(void) {}

__attribute__ ((weak))
void shutdown_keymap(void) {}

__attribute__ ((weak))
void suspend_power_down_keymap(void) {}

__attribute__ ((weak))
void suspend_wakeup_init_keymap(void) {}

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

__attribute__ ((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  return true;
}


__attribute__ ((weak))
layer_state_t layer_state_set_keymap (layer_state_t state) {
  return state;
}

__attribute__ ((weak))
layer_state_t default_layer_state_set_keymap (layer_state_t state) {
  return state;
}

__attribute__ ((weak))
void led_set_keymap(uint8_t usb_led) {}

void set_os(uint8_t os) {
  runtime_userspace_config.os_target = os;

#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE)
  switch (os) {
  case _OS_MACOS:
    set_unicode_input_mode(UC_MAC);
    break;
  case _OS_LINUX:
    set_unicode_input_mode(UC_LNX);
    break;
  case _OS_WINDOWS:
    set_unicode_input_mode(UC_WIN);
    break;
  }
#endif
}

void matrix_init_user(void) {
  stored_userspace_config.raw = eeconfig_read_user();
  runtime_userspace_config.raw = stored_userspace_config.raw;

  set_os(runtime_userspace_config.os_target);
}

void store_userspace_config(void) {
  eeconfig_update_user(stored_userspace_config.raw);
}

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_TWO_KEYS(KC_F1, KC_L) {
      set_os(_OS_LINUX);
    }
    SEQ_TWO_KEYS(KC_F1, KC_M) {
      set_os(_OS_MACOS);
    }
    SEQ_TWO_KEYS(KC_F1, KC_W) {
      set_os(_OS_WINDOWS);
    }
    SEQ_TWO_KEYS(KC_F1, KC_S) {
      stored_userspace_config.raw = runtime_userspace_config.raw;
      store_userspace_config();
    }
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint8_t os_target = runtime_userspace_config.os_target;
  bool pressed = record->event.pressed;

  switch (keycode) {
  case KC_QWERTY:
    if (pressed) {
      set_single_persistent_default_layer(_QWERTY);
    }
    return false;
    break;

  case KC_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
    if (!pressed) {
      send_string_with_delay_P(PSTR("make " QMK_KEYBOARD ":" QMK_KEYMAP
#if defined(__ARM__)
                   ":dfu-util"
#elif defined(BOOTLOADER_DFU)
                   ":dfu"
#elif defined(BOOTLOADER_HALFKAY)
                   ":teensy"
#elif defined(BOOTLOADER_CATERINA)
                   ":avrdude"
#endif // bootloader options
                   SS_TAP(X_ENTER)), 10);
    }
    return false;
    break;

  case EPRM: // Resets EEPROM
    if (pressed) {
      eeconfig_init();
      default_layer_set(1UL<<eeconfig_read_default_layer());
      layer_state_set(layer_state);
      set_os(_OS_MACOS);
      store_userspace_config();
    }
    return false;
    break;
  case VRSN: // Prints firmware version
    if (pressed) {
      send_string_with_delay_P(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE), MACRO_TIMER);
    }
    return false;
    break;

  case KC_OS_CUT:
    switch (os_target) {
    case _OS_MACOS:
      if (pressed)
        SEND_STRING(SS_LGUI("x"));
      break;
    case _OS_LINUX:
      pressed ?
        register_code(KC_CUT)
        : unregister_code(KC_CUT);
      break;
    default:
      if (pressed)
        SEND_STRING(SS_LCTL("x"));
      break;
    }
    break;

  case KC_OS_COPY:
    switch (os_target) {
    case _OS_MACOS:
      if (pressed)
        SEND_STRING(SS_LGUI("c"));
      break;
    case _OS_LINUX:
      pressed ?
        register_code(KC_COPY)
        : unregister_code(KC_COPY);
      break;
    default:
      if (pressed)
        SEND_STRING(SS_LCTL("c"));
      break;
    }
    break;

  case KC_OS_PASTE:
    switch (os_target) {
    case _OS_MACOS:
      if (pressed)
        SEND_STRING(SS_LGUI("v"));
      break;
    case _OS_LINUX:
      pressed ?
        register_code(KC_PASTE)
        : unregister_code(KC_PASTE);
      break;
    default:
      if (pressed)
        SEND_STRING(SS_LCTL("v"));
      break;
    }
    break;

  case KC_OS_UNDO:
    switch (os_target) {
    case _OS_MACOS:
      if (pressed)
        SEND_STRING(SS_LGUI("z"));
      break;
    case _OS_LINUX:
      pressed ?
        register_code(KC_UNDO)
        : unregister_code(KC_UNDO);
      break;
    default:
      if (pressed)
        SEND_STRING(SS_LCTL("z"));
      break;
    }
    break;

  case KC_OS_REDO:
    switch (os_target) {
    case _OS_MACOS:
      if (pressed)
        SEND_STRING(SS_LGUI(SS_LSFT("z")));
      break;
    case _OS_LINUX:
      pressed ?
        register_code(KC_AGAIN)
        : unregister_code(KC_AGAIN);
      break;
    default:
      if (pressed)
        SEND_STRING(SS_LCTL(SS_LSFT("z")));
      break;
    }
    break;

  case KC_OS_LOCK:
    switch (os_target) {
    case _OS_MACOS:
      if (pressed)
        SEND_STRING(SS_LGUI(SS_LCTL("q")));
      break;
    case _OS_LINUX:
      pressed ?
        register_code(KC_PWR)
        : unregister_code(KC_PWR);
      break;
    default:
      if (pressed)
        SEND_STRING(SS_LGUI("l"));
      break;
    }
    break;

  case KC_SCRT:
    if (pressed) {
      SEND_STRING(SS_LGUI("`"));
    }
    break;
  }

  return process_record_keymap(keycode, record);
}
