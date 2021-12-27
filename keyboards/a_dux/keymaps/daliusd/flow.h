#pragma once

#include QMK_KEYBOARD_H

bool update_flow(
    uint16_t keycode,
    bool pressed,
    keypos_t key_position
);

void flow_matrix_scan(void);
