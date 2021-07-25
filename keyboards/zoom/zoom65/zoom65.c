/* Copyright 2021 zoom
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

#include "zoom65.h"

bool encoder_update_kb(uint8_t index, bool clockwise)
{
    return encoder_update_user(index, clockwise);
}

bool encoder_update_user(uint8_t index, bool clockwise)
{
    if (index == 0) /* First encoder */
    {
        if (clockwise)
        {
            tap_code(pgm_read_word(&keymaps[biton32(layer_state)][4][3]));
        }
        else
        {
            tap_code(pgm_read_word(&keymaps[biton32(layer_state)][4][5]));
        }
    }
    return true;
}
