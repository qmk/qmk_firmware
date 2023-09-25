/*
Copyright 2017 Balz Guenat

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

#include "fc980c.h"

#ifdef ACTUATION_DEPTH_ADJUSTMENT
void matrix_init_kb(void) {
    adjust_actuation_point(ACTUATION_DEPTH_ADJUSTMENT);

    matrix_init_user();
}

void actuation_point_up(void) {
    // write RDAC register: lower value makes actuation point shallow
    uint8_t rdac = ad5258_read_rdac();
    if (rdac == 0) {
        ad5258_write_rdac(0);
    } else {
        ad5258_write_rdac(rdac - 1);
    }
}

void actuation_point_down(void) {
    // write RDAC register: higher value makes actuation point deep
    uint8_t rdac = ad5258_read_rdac();
    if (rdac == 63) {
        ad5258_write_rdac(63);
    } else {
        ad5258_write_rdac(rdac + 1);
    }
}

void adjust_actuation_point(int offset) {
    ad5258_init();
    uint8_t rdac = ad5258_read_eeprom() + offset;
    if (rdac > 63) { // protects from under and overflows
        if (offset > 0) {
            ad5258_write_rdac(63);
        } else {
            ad5258_write_rdac(0);
        }
    } else {
        ad5258_write_rdac(rdac);
    }
}
#endif
