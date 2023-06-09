/* Copyright 2021 JZ-Skyloong (@JZ-Skyloong)
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



#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {  0,    1,    2,    3,    4,    5,    6,    7,    8,    9,   11 },
  { 12,   13,   14,   15,   16,   17,   18,   19,   21,   10,   22 },
  { 23,   24,   25,   26,   27,   28,   29,   30,   31,   32,   33 },
  { 34,   36,   37,   35,   38,   20,   39,   40,   41,   42,   43 }

}, {
  // LED Index to Physical Position
/* ********************************************************************************************************************************************************
 * { 0,  0 }esc, { 20,  0 }q, { 41,  0 }w, { 61,  0 }e, { 81, 0 }r, { 102, 0 }t, { 122, 0}y, { 143, 0 }u, { 163, 0}i, { 183, 0 }o, { 203, 0}p, { 224, 0 }back,
 * { 0,  21 }cap, { 22,  21 }a, { 45,  21 }s, { 67,  21 }d, { 90, 21 }f, { 112, 21 }g, { 134, 21 }h, { 157, 21 }j, { 179, 21 }k, { 202, 21 }l, { 224, 21 }enter,
 * { 0,  43 }shift, { 22,  43 }z, { 45,  43 }x, { 67,  43 }c, { 90, 43 }v, { 112, 43 }b, { 134, 43 }n, { 157, 43 }m, { 179, 43 }shift_r, { 202, 43 }up, { 224, 43 }fn,
 * { 0,  64 }ctrl, { 25,  64 }win, { 50,  64 }alt, { 75,  64 }fn1-l, { 100, 64 }space, { 124, 64 }fn1-r, { 149, 64 }menu, { 174, 64 }l, { 199, 64 }down, { 224, 64 }r
 ********************************************************************************************************************************************************/
  { 0,   0 }, { 20,   0 }, { 41,   0 }, { 61,   0 }, { 81,   0 }, { 102,  0 }, { 122,   0}, { 143,  0 }, { 163,  0 }, { 183,   0},{ 224,  0 },
  { 0,  21 }, { 22,  21 }, { 45,  21 }, { 67,  21 }, { 90,  21 }, { 112, 21 }, { 134, 21 }, { 157, 21 }, { 202, 21 }, { 203,  0 },{ 224, 21 },
  { 0,  43 }, { 22,  43 }, { 45,  43 }, { 67,  43 }, { 90,  43 }, { 112, 43 }, { 134, 43 }, { 157, 43 }, { 179, 43 }, { 202, 43 },{ 224, 43 },
  { 0,  64 }, { 30,  64 }, { 45,  64 }, { 37,  64 }, { 100, 64 }, { 179, 21 }, { 140, 64 }, { 170, 64 }, { 185, 64 }, { 202, 64 },{ 224, 64 }

}, {
  // LED Index to Flag
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
} };
#endif

void board_init(void) {
    AFIO->MAPR |= AFIO_MAPR_USART1_REMAP | AFIO_MAPR_TIM3_REMAP_PARTIALREMAP;

}
