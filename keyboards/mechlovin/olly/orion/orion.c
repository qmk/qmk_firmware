/* Copyright 2022 Mechlovin' Studio
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

void board_init(void) {
   //JTAG-DP Disabled and SW-DP Enabled    
   AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG_Msk) | AFIO_MAPR_SWJ_CFG_DISABLE;
}

void keyboard_pre_init_kb(void) {
  setPinOutput(B5);
  setPinOutput(B6);
  setPinOutput(B7);
  setPinOutput(B8);
  setPinOutput(B9);
  keyboard_pre_init_user();
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);
    writePin(B7, layer_state_cmp(state, 0));
    writePin(B6, layer_state_cmp(state, 1));
    writePin(B5, layer_state_cmp(state, 2));
    writePin(B8, layer_state_cmp(state, 3));
    writePin(B9, layer_state_cmp(state, 4));
    return state;
}
