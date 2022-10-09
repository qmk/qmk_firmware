// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "jpe230.h"
#include "ocean_dream.h"

void render_slave_oled() {
    render_stars();
}

oled_rotation_t rotate_slave(oled_rotation_t rotation) {return OLED_ROTATION_270;}
