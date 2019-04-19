/* Copyright 2018 Jack Humbert <jack.humb@gmail.com>
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
#include "ez.h"

const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, A_12,  B_12,  C_12},
    {0, A_11,  B_11,  C_11},
    {0, A_10,  B_10,  C_10},
    {0, A_9,   B_9,   C_9},
    {0, A_8,   B_8,   C_8},
    {0, A_7,   B_7,   C_7},

    {0, G_12,  H_12,  I_12},
    {0, G_11,  H_11,  I_11},
    {0, G_10,  H_10,  I_10},
    {0, G_9,   H_9,   I_9},
    {0, G_8,   H_8,   I_8},
    {0, G_7,   H_7,   I_7},

    {0, A_6,   B_6,   C_6},
    {0, A_5,   B_5,   C_5},
    {0, A_4,   B_4,   C_4},
    {0, A_3,   B_3,   C_3},
    {0, A_2,   B_2,   C_2},
    {0, A_1,   B_1,   C_1},

    {0, G_6,   H_6,   I_6},
    {0, G_5,   H_5,   I_5},
    {0, G_4,   H_4,   I_4},
    {0, G_3,   H_3,   I_3},
    {0, G_2,   H_2,   I_2},
    {0, G_1,   H_1,   I_1},

    {0, D_12,  E_12,  F_12},
    {0, D_11,  E_11,  F_11},
    {0, D_10,  E_10,  F_10},
    {0, D_9,   E_9,   F_9},
    {0, D_8,   E_8,   F_8},
    {0, D_7,   E_7,   F_7},

    {0, J_12,  K_12,  L_12},
    {0, J_11,  K_11,  L_11},
    {0, J_10,  K_10,  L_10},
    {0, J_9,   K_9,   L_9},
    {0, J_8,   K_8,   L_8},
    {0, J_7,   K_7,   L_7},

    {0, D_6,   E_6,   F_6},
    {0, D_5,   E_5,   F_5},
    {0, D_4,   E_4,   F_4},
    {0, D_3,   E_3,   F_3},
    {0, D_2,   E_2,   F_2},
    {0, D_1,   E_1,   F_1},

    {0, J_6,   K_6,   L_6},
    {0, J_5,   K_5,   L_5},
    {0, J_4,   K_4,   L_4},
    {0, J_3,   K_3,   L_3},
    {0, J_2,   K_2,   L_2},

};

const rgb_led g_rgb_leds[DRIVER_LED_TOTAL] = {

    /*{row | col << 4}
      |             {x=0..224, y=0..64}
      |              |                 modifier
      |              |                 | */
    {{0|(0<<4)},   {20.36*0, 21.33*0}, 1},
    {{0|(1<<4)},   {20.36*1, 21.33*0}, 0},
    {{0|(2<<4)},   {20.36*2, 21.33*0}, 0},
    {{0|(3<<4)},   {20.36*3, 21.33*0}, 0},
    {{0|(4<<4)},   {20.36*4, 21.33*0}, 0},
    {{0|(5<<4)},   {20.36*5, 21.33*0}, 0},
    {{4|(0<<4)},   {20.36*6, 21.33*0}, 0},
    {{4|(1<<4)},   {20.36*7, 21.33*0}, 0},
    {{4|(2<<4)},   {20.36*8, 21.33*0}, 0},
    {{4|(3<<4)},   {20.36*9, 21.33*0}, 0},
    {{4|(4<<4)},  {20.36*10,21.33*0}, 0},
    {{4|(5<<4)},  {20.36*11,21.33*0}, 1},

    {{1|(0<<4)},   {20.36*0, 21.33*1}, 1},
    {{1|(1<<4)},   {20.36*1, 21.33*1}, 0},
    {{1|(2<<4)},   {20.36*2, 21.33*1}, 0},
    {{1|(3<<4)},   {20.36*3, 21.33*1}, 0},
    {{1|(4<<4)},   {20.36*4, 21.33*1}, 0},
    {{1|(5<<4)},   {20.36*5, 21.33*1}, 0},
    {{5|(0<<4)},   {20.36*6, 21.33*1}, 0},
    {{5|(1<<4)},   {20.36*7, 21.33*1}, 0},
    {{5|(2<<4)},   {20.36*8, 21.33*1}, 0},
    {{5|(3<<4)},   {20.36*9, 21.33*1}, 0},
    {{5|(4<<4)},  {20.36*10,21.33*1}, 0},
    {{5|(5<<4)},  {20.36*11,21.33*1}, 1},

    {{2|(0<<4)},   {20.36*0, 21.33*2}, 1},
    {{2|(1<<4)},   {20.36*1, 21.33*2}, 0},
    {{2|(2<<4)},   {20.36*2, 21.33*2}, 0},
    {{2|(3<<4)},   {20.36*3, 21.33*2}, 0},
    {{2|(4<<4)},   {20.36*4, 21.33*2}, 0},
    {{2|(5<<4)},   {20.36*5, 21.33*2}, 0},
    {{6|(0<<4)},   {20.36*6, 21.33*2}, 0},
    {{6|(1<<4)},   {20.36*7, 21.33*2}, 0},
    {{6|(2<<4)},   {20.36*8, 21.33*2}, 0},
    {{6|(3<<4)},   {20.36*9, 21.33*2}, 0},
    {{6|(4<<4)},  {20.36*10,21.33*2}, 0},
    {{6|(5<<4)},  {20.36*11,21.33*2}, 1},

    {{3|(0<<4)},   {20.36*0, 21.33*3}, 1},
    {{3|(1<<4)},   {20.36*1, 21.33*3}, 1},
    {{3|(2<<4)},   {20.36*2, 21.33*3}, 1},
    {{7|(3<<4)},   {20.36*3, 21.33*3}, 1},
    {{7|(4<<4)},   {20.36*4, 21.33*3}, 1},
    {{7|(5<<4)},   {20.36*5.5,21.33*3}, 0},
    {{7|(0<<4)},   {20.36*7, 21.33*3}, 1},
    {{7|(1<<4)},   {20.36*8, 21.33*3}, 1},
    {{7|(2<<4)},   {20.36*9, 21.33*3}, 1},
    {{3|(3<<4)},  {20.36*10,21.33*3}, 1},
    {{3|(4<<4)},  {20.36*11,21.33*3}, 1}
};

void matrix_init_kb(void) {
  matrix_init_user();

  palSetPadMode(GPIOB, 8, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOB, 9, PAL_MODE_OUTPUT_PUSHPULL);

  palClearPad(GPIOB, 8);
  palClearPad(GPIOB, 9);
}

void matrix_scan_kb(void) {
  matrix_scan_user();
}

uint32_t layer_state_set_kb(uint32_t state) {

  palClearPad(GPIOB, 8);
  palClearPad(GPIOB, 9);
  state = layer_state_set_user(state);
  uint8_t layer = biton32(state);
  switch (layer) {
      case 3:
        palSetPad(GPIOB, 9);
        break;
      case 4:
        palSetPad(GPIOB, 8);
        break;
      case 6:
        palSetPad(GPIOB, 9);
        palSetPad(GPIOB, 8);
        break;
      default:
        break;
    }
    return state;
}
