/* Copyright 2020 Ilya Zhuravlev
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

#include <inttypes.h>
#include <stdbool.h>

#define VIAL_PROTOCOL_VERSION ((uint32_t)0x00000002)

void vial_handle_cmd(uint8_t *data, uint8_t length);

#ifdef VIAL_ENCODERS_ENABLE
void vial_encoder_update(uint8_t index, bool clockwise);
#endif

extern int vial_unlocked;
extern int vial_unlock_in_progress;

enum {
    vial_get_keyboard_id = 0x00,
    vial_get_size = 0x01,
    vial_get_def = 0x02,
    vial_get_encoder = 0x03,
    vial_set_encoder = 0x04,
    vial_get_unlock_status = 0x05,
    vial_unlock_start = 0x06,
    vial_unlock_poll = 0x07,
    vial_lock = 0x08,
};

/* Fake encoder position in keyboard matrix, can't use 255 as that is immediately rejected by IS_NOEVENT  */
#define VIAL_ENCODER_MATRIX_MAGIC 254
