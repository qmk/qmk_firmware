// Copyright 2023 Wilhelm Schuster
// SPDX-License-Identifier: GPL-2.0-or-later

#include "fc980c.h"

void matrix_init_kb(void) {
    fc980c_matrix_init_kb();

    matrix_init_user();
}

void eeconfig_init_kb(void) {
    fc980c_eeconfig_init_kb();

    eeconfig_init_user();
}

void keyboard_post_init_kb(void) {
    fc980c_keyboard_post_init_kb();

    keyboard_post_init_user();
}
