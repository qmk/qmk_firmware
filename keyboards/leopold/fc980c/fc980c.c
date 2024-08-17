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

#include QMK_KEYBOARD_H

#include "debug.h"
#include "i2c_master.h"

keyboard_config_t fc980c_config;

void matrix_init_kb(void) {
#ifdef ACTUATION_DEPTH_ADJUSTMENT
    i2c_init();
#endif

    matrix_init_user();
}

void fc980c_eeconfig_update_kb(void) {
#ifdef ACTUATION_DEPTH_ADJUSTMENT
    dprintf("saving rdac config (%" PRId8 ") to qmk eeprom\n", fc980c_config.actuation_point_value);
    eeconfig_update_kb(fc980c_config.raw);
#endif
}

void eeconfig_init_kb(void) {
#ifdef ACTUATION_DEPTH_ADJUSTMENT
    fc980c_config.actuation_point_value = -1;
    fc980c_eeconfig_update_kb();
#endif

    eeconfig_init_user();
}

void keyboard_post_init_kb(void) {
#ifdef ACTUATION_DEPTH_ADJUSTMENT
    fc980c_config.raw = eeconfig_read_kb();

    if (fc980c_config.actuation_point_value >= 0) {
        ad5258_write_rdac(fc980c_config.actuation_point_value);
    }
#endif

     keyboard_post_init_user();
}
