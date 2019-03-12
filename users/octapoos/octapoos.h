/*
Copyright 2019 Andy Poos <andpoos@gmail.com>

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
#include "wrapper.h"
#include "process_record.h"
#ifdef TAP_DANCE_ENABLE
  #include "tap_dance.h"
#endif

/* Define layer names*/
enum userspace_layers {
  _QWERTY = 0,
  _COLEMAK,
  _DVORAK,
  _WORKMAN,
  _LOWER,
  _RAISE,
  _ADJUST,
};

void matrix_init_keymap(void);
void shutdown_keymap(void);
void suspend_power_down_keymap(void);
void suspend_wakeup_init_keymap(void);
void matrix_scan_keymap(void);
uint32_t layer_state_set_keymap(uint32_t state);
uint32_t default_layer_state_set_keymap(uint32_t state);

typedef union {
  uint32_t raw;
  struct {
    bool    rgb_layer_change : 1;
  };
} userspace_config_t;

extern userspace_config_t userspace_config;

/* Custom tap dance codes */
#ifdef TAP_DANCE_ENABLE
  #define KC_TD1 TD(TD_L)
  #define KC_TD2 TD(TD_R)
  #define KC_TD3 TD(TD_ESC_CAPS)
#else // TAP_DANCE_ENABLE
  #define KC_TD1 KC_LPRN
  #define KC_TD2 KC_RPRN
  #define KC_TD3 KC_ESC
#endif // TAP_DANCE_ENABLE
