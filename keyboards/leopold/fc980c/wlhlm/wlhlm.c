// Copyright 2023 Wilhelm Schuster
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "debug.h"
#include "i2c_master.h"

#include "actuation_point.h"

keyboard_config_t fc980c_config;

void matrix_init_kb(void) {
    i2c_init(); // actuation_point

    matrix_init_user();
}

void fc980c_eeconfig_update_kb(void) {
    dprintf("saving rdac config (%" PRIu8 ") to qmk eeprom\n", fc980c_config.actuation_point_value);
    eeconfig_update_kb(fc980c_config.raw);
}

void eeconfig_init_kb(void) {
    fc980c_config.actuation_point_value = -1;
    fc980c_eeconfig_update_kb();

    eeconfig_init_user();
}

void keyboard_post_init_kb(void) {
    fc980c_config.raw = eeconfig_read_kb();

    if (fc980c_config.actuation_point_value >= 0) {
        actuation_point_write_rdac(fc980c_config.actuation_point_value);
    }

    keyboard_post_init_user();
}
