/* Copyright 2017 Peter Jones <pjones@devalot.com>
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
#ifndef PROCESS_DUAL_ROLE_H
#define PROCESS_DUAL_ROLE_H

#ifdef DUAL_ROLE_ENABLE

#include <stdbool.h>
#include <inttypes.h>

typedef struct
{
  uint16_t timer;
  uint8_t  count;
  uint8_t  max;
  bool     interrupted;
} qk_dual_role_state_t;

typedef struct
{
  uint16_t mod;
  uint16_t key;
  bool     active;
} qk_dual_role_action_t;

#define DR(n) (QK_DUAL_ROLE + n)
#define DUAL_ROLE(mod, key) {mod, key, false}
extern qk_dual_role_action_t dual_role_keys[];

/* To be used internally */
bool process_dual_role(uint16_t keycode, keyrecord_t *record);

#else // DUAL_ROLE_ENABLE
#define DR(n) KC_NO
#endif // DUAL_ROLE_ENABLE

#endif // PROCESS_TAP_DANCE_H
