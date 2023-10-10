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

#include "actuation_point.h"

#include "ad5258.h"

#include "util.h"

#ifdef ACTUATION_DEPTH_ADJUSTMENT
int8_t actuation_point_make_shallower(void) {
    return actuation_point_adjust(-1 * ACTUATION_DEPTH_ADJUSTMENT);
}

int8_t actuation_point_make_deeper(void) {
    return actuation_point_adjust(ACTUATION_DEPTH_ADJUSTMENT);
}

int8_t actuation_point_adjust(int8_t offset) {
    int8_t ret = -1;
    int8_t rdac = ad5258_read_rdac();

    if (rdac >= 0) {
        int8_t rdac_new = rdac + offset;

        if (offset > 0) {
            ret = ad5258_write_rdac(MIN(AD5258_RDAC_MAX, rdac_new));
        } else if (offset < 0) {
            ret = ad5258_write_rdac(MAX(AD5258_RDAC_MIN, rdac_new));
        }
    }

    return ret;
}

void actuation_point_reset(void) {
    ad5258_restore_from_eeprom();
}
#endif
