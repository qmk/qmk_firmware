// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "custom_keycodes.h"
#include "keymap_german.h"
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

// LMAGIC and RMAGIC definitions
#include "magic.c"

// custom keystroke main logic
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case RELOAD: {
        SEND_STRING(detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS ? SS_LGUI("r")
                                                                                   : (detected_host_os() == OS_LINUX || detected_host_os() == OS_WINDOWS ? SS_LCTL("r") : ""));
      }
        return false;
      case MACLCURLY: {
        SEND_STRING(detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS ? SS_ALGR("8")
                                                                                   : (detected_host_os() == OS_LINUX || detected_host_os() == OS_WINDOWS ? SS_ALGR("7") : ""));
      }
        return false;
        case MACRCURLY: {
          SEND_STRING(detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS ? SS_ALGR("9")
                                                                                     : (detected_host_os() == OS_LINUX || detected_host_os() == OS_WINDOWS ? SS_ALGR("8") : ""));
        }
          return false;
      case LMAGIC: {
        process_left_magic(get_last_keycode(), get_last_mods());
        set_last_keycode(KC_SPC);
      }
        return false;
      case RMAGIC: {
        process_right_magic(get_last_keycode(), get_last_mods());
        set_last_keycode(KC_SPC);
      }
        return false;
      // case TD(TDH_A_AE):
      // case TD(TDH_O_OE):
      case TD(TDH_U_UE): {
        process_tap_dance_hold(keycode, record);
      }
    }
  }

  return true;
}

void keyboard_post_init_user(void) {
  rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_WIDE);
  rgb_matrix_sethsv(191, 255, 255);
}
// void keyboard_post_init_user(void) {
//   // Set the effect.
//   rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_PALETTEFX_REACTIVE);
//   // Set the palette and maximize saturation and brightness.
//   uint8_t palette_index = PALETTEFX_AFTERBURN;
//   rgb_matrix_sethsv_noeeprom(RGB_MATRIX_HUE_STEP * palette_index, 255, 255);
//   // Set speed to default.
//   rgb_matrix_set_speed_noeeprom(128);
//   // Make sure RGB Matrix is on.
//   rgb_matrix_enable_noeeprom();
// }
