/*
Copyright 2013 Jun Wako <wakojun@gmail.com>

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
#ifndef ACTION_UTIL_H
#define ACTION_UTIL_H

#include <stdint.h>
#include "report.h"

#ifdef __cplusplus
extern "C" {
#endif

extern report_keyboard_t *keyboard_report;

void send_keyboard_report(void);

/* key */
inline void add_key(uint8_t key) {
  add_key_to_report(keyboard_report, key);
}

inline void del_key(uint8_t key) {
  del_key_from_report(keyboard_report, key);
}

inline void clear_keys(void) {
  clear_keys_from_report(keyboard_report);
}

/* modifier */
uint8_t get_mods(void);
void add_mods(uint8_t mods);
void del_mods(uint8_t mods);
void set_mods(uint8_t mods);
void clear_mods(void);

/* weak modifier */
uint8_t get_weak_mods(void);
void add_weak_mods(uint8_t mods);
void del_weak_mods(uint8_t mods);
void set_weak_mods(uint8_t mods);
void clear_weak_mods(void);

/* macro modifier */
uint8_t get_macro_mods(void);
void add_macro_mods(uint8_t mods);
void del_macro_mods(uint8_t mods);
void set_macro_mods(uint8_t mods);
void clear_macro_mods(void);

/* oneshot modifier */
void set_oneshot_mods(uint8_t mods);
uint8_t get_oneshot_mods(void);
void clear_oneshot_mods(void);
void oneshot_toggle(void);
void oneshot_enable(void);
void oneshot_disable(void);
bool has_oneshot_mods_timed_out(void);

uint8_t get_oneshot_locked_mods(void);
void set_oneshot_locked_mods(uint8_t mods);
void clear_oneshot_locked_mods(void);

typedef enum {
  ONESHOT_PRESSED = 0b01,
  ONESHOT_OTHER_KEY_PRESSED = 0b10,
  ONESHOT_START = 0b11,
  ONESHOT_TOGGLED = 0b100
} oneshot_fullfillment_t;
void set_oneshot_layer(uint8_t layer, uint8_t state);
uint8_t get_oneshot_layer(void);
void clear_oneshot_layer_state(oneshot_fullfillment_t state);
void reset_oneshot_layer(void);
bool is_oneshot_layer_active(void);
uint8_t get_oneshot_layer_state(void);
bool has_oneshot_layer_timed_out(void);

void oneshot_locked_mods_changed_user(uint8_t mods);
void oneshot_locked_mods_changed_kb(uint8_t mods);
void oneshot_mods_changed_user(uint8_t mods);
void oneshot_mods_changed_kb(uint8_t mods);
void oneshot_layer_changed_user(uint8_t layer);
void oneshot_layer_changed_kb(uint8_t layer);

/* inspect */
uint8_t has_anymod(void);

#ifdef __cplusplus
}
#endif

#endif
