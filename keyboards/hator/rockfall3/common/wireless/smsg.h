/* Copyright (C) 2024 koosikus
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

#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    smsg_state_free = 0,
    smsg_state_busy,
    smsg_state_retry,
    smsg_state_replied
} smsg_states_t;

void smsg_init(void);
bool smsg_push(uint8_t *buf, uint32_t size);
uint32_t smsg_peek(uint8_t *buf);
void smsg_pop(void);
smsg_states_t smsg_get_state(void);
void smsg_set_state(smsg_states_t state);
bool smsg_is_busy(void);
