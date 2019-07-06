/*
Copyright 2018 Jacob Jerrell <jacob.jerrell@gmail.com> @JacobJerrell

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

#pragma once
#include "quantum.h"
#include "version.h"
#include "eeprom.h"
#include "wrappers.h"
#include "process_records.h"
#ifdef TAP_DANCE_ENABLE
  #include "tap_dances.h"
#endif // TAP_DANCE_ENABLE

/* Layer Names */
enum userspace_layers {
  _WORKMAN = 0,
  _WINWORKMAN,
  _QWERTY,
  _LOWER,
  _ADJUST,
  _DIABLO,
};

#if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
  #define BOCAJ_UNICODE_MODE UC_OSX
#else
  // set to 2 for UC_WIN, set to 4 for UC_WINC
  #define BOCAJ_UNICODE_MODE 2
#endif

/*
define modifiers here, since MOD_* doesn't seem to work for these
 */
#define MODS_SHIFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
#define MODS_CTRL_MASK  (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTRL))
#define MODS_ALT_MASK  (MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))
#define MODS_GUI_MASK  (MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI))

bool mod_key_press_timer (uint16_t code, uint16_t mod_code, bool pressed);
bool mod_key_press (uint16_t code, uint16_t mod_code, bool pressed, uint16_t this_timer);
bool send_game_macro(const char *str, keyrecord_t *record, bool override);
void matrix_init_keymap(void);
void shutdown_keymap(void);
void suspend_power_down_keymap(void);
void suspend_wakeup_init_keymap(void);
void matrix_scan_keymap(void);
uint32_t layer_state_set_keymap (uint32_t state);
uint32_t default_layer_state_set_keymap (uint32_t state);
void led_set_keymap(uint8_t usb_led);
void eeconfig_init_keymap(void);
void tap(uint16_t keycode);

typedef union {
  uint8_t raw;
} userspace_config_t;

extern userspace_config_t userspace_config;

// If Tap Dancing is enabled, we manage that here.
// If it is not, then we define the KC_D3_# codes gracefully
#ifdef TAP_DANCE_ENABLE
  #define KC_D3_1 TD(TD_D3_1)
  #define KC_D3_2 TD(TD_D3_2)
  #define KC_D3_3 TD(TD_D3_3)
  #define KC_D3_4 TD(TD_D3_4)
#else // !TAP_DANCE_ENABLE
  #define KC_D3_1 KC_1
  #define KC_D3_2 KC_2
  #define KC_D3_3 KC_3
  #define KC_D3_4 KC_4
#endif // TAP_DANCE_ENABLE
