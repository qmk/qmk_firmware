/* Copyright 2022 @toinux
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

static const char PROGMEM ctrl_icon[2][2][4] = {
    {
        // off
        {0x93, 0x94, 0x95, 0},
        {0xB3, 0xB4, 0xB5, 0},
    },
    {
        // on
        {0x8F ,0x90, 0x91, 0},
        {0xAF ,0xB0, 0xB1, 0},
    }
};

static const char PROGMEM shift_icon[2][2][4] = {
    {
        // off
        {0xD3, 0xD4, 0xB5, 0},
        {0xA8, 0xA9, 0xD5, 0},
    },
    {
        // on
        {0xCF ,0xD0, 0xB1, 0},
        {0xC8 ,0xC9, 0xD1, 0},
    }
};

static const char PROGMEM gui_icon[2][2][4] = {
    {
        // off
        {0x92, 0x8C, 0x8D, 0},
        {0xB2, 0xAC, 0xAD, 0},
    },
    {
        // on
        {0x8E ,0x8A, 0x8B, 0},
        {0xAE ,0xAA, 0xAB, 0},
    }
};

static const char PROGMEM alt_icon[2][2][4] = {
    {
        // off
        {0xB2, 0xCC, 0xCD, 0},
        {0xD2, 0x88, 0x89, 0},
    },
    {
        // on
        {0xAE ,0xCA, 0xCB, 0},
        {0xCE ,0x86, 0x87, 0},
    }
};

void set_keylog(uint16_t keycode, keyrecord_t *record);
