/*
Copyright 2018 Jack Humbert <jack.humb@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "moonlander.h"

void matrix_init_kb(void) {
  setPinOutput(B0);
  setPinOutput(B1);
  setPinOutput(B2);

  writePinLow(B0);
  writePinLow(B1);
  writePinLow(B2);
}

void matrix_scan_kb(void) {

}

uint32_t layer_state_set_kb(uint32_t state) {
  writePinLow(B0);
  writePinLow(B1);
  writePinLow(B2);

  uint8_t layer = biton32(state);
  switch (layer) {
      case 0:
        break;
      case 1:
        writePinHigh(B0);
        break;
      case 2:
        writePinHigh(B1);
        break;
      case 3:
        writePinHigh(B2);
        break;
      case 4:
        writePinHigh(B0);
        writePinHigh(B1);
        break;
      case 5:
        writePinHigh(B0);
        writePinHigh(B2);
        break;
      case 6:
        writePinHigh(B1);
        writePinHigh(B2);
        break;
      case 7:
        writePinHigh(B0);
        writePinHigh(B1);
        writePinHigh(B2);
        break;
      default:
        break;
    }

  return state;
}
