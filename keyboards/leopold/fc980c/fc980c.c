// Copyright 2023 Wilhelm Schuster
// SPDX-License-Identifier: GPL-2.0-or-later

#include "fc980c.h"

#include "debug.h"
#include "i2c_master.h"

keyboard_config_t fc980c_config;

void fc980c_matrix_init_kb(void) {
#ifdef ACTUATION_DEPTH_ADJUSTMENT
    i2c_init();
#endif
}

void fc980c_eeconfig_update_kb(void) {
#ifdef ACTUATION_DEPTH_ADJUSTMENT
    dprintf("saving rdac config (%"PRId8") to qmk eeprom\n", fc980c_config.actuation_point_value);
    eeconfig_update_kb(fc980c_config.raw);
#endif
}

void fc980c_eeconfig_init_kb(void) {
#ifdef ACTUATION_DEPTH_ADJUSTMENT
    fc980c_config.actuation_point_value = -1;
    fc980c_eeconfig_update_kb();
#endif
}

void fc980c_keyboard_post_init_kb(void) {
#ifdef ACTUATION_DEPTH_ADJUSTMENT
    fc980c_config.raw = eeconfig_read_kb();

    if (fc980c_config.actuation_point_value >= 0) {
        ad5258_write_rdac(fc980c_config.actuation_point_value);
    }
#endif
}
