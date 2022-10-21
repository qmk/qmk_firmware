// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "jpe230.h"

uint8_t logged_row;
uint8_t logged_col;
uint32_t oled_timer = 0;

__attribute__ ((weak)) void handle_oled_keypress(uint16_t keycode, keyrecord_t *record) {}

__attribute__ ((weak)) oled_rotation_t rotate_master(oled_rotation_t rotation) {return rotation;}
__attribute__ ((weak)) oled_rotation_t rotate_slave(oled_rotation_t rotation) {return rotation;}

void oled_timer_reset() { oled_timer = timer_read32(); }

oled_rotation_t oled_init_user(oled_rotation_t rotation) {

    if (!is_keyboard_master()) {
        return rotate_slave(rotation);
    }

    return rotate_master(rotation);
}


void set_keylog(uint16_t keycode, keyrecord_t *record) {
    logged_row = record->event.key.row;
    logged_col = record->event.key.col;

    handle_oled_keypress(keycode, record);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_master_oled();
    } else {
        render_slave_oled();
    }
    return false;
}
