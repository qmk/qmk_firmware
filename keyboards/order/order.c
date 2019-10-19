/* Copyright 2019 Carlos Rödiger
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
#include "order.h"


void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up

	matrix_init_user();
}

uint8_t selected_layer = 0;
void encoder_update_user(uint8_t index, bool clockwise) {
  switch (index) {
    case 0:
      if (!clockwise && selected_layer  < 10) {
        selected_layer ++;
      } else if (clockwise && selected_layer  > 0){
        selected_layer --;
      }
      layer_clear();
      layer_on(selected_layer);
  }
}
