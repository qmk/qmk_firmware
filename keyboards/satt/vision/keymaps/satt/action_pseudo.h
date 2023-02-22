/* Copyright 2020 shela
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

#define SHIFT_BIT_SIZE (0xE7 / 8 + 1) /* 1bit per 1key */
#define IS_LSFT(kc) ((QK_LSFT & (kc)) == QK_LSFT)

void     action_pseudo_process(keyrecord_t *, uint8_t, const uint16_t (*)[2]);
uint16_t convert_keycode(const uint16_t (*)[2], uint16_t, bool);

uint8_t get_shift_bit(uint16_t);
void    add_shift_bit(uint16_t);
void    del_shift_bit(uint16_t);
