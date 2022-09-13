#pragma once

#include "progmem.h"
#include "animation.c"

extern uint8_t is_master;
// static uint16_t oled_timer = 0;

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

void render_animation(uint8_t frame) {
    oled_write_raw_P(animation[frame], sizeof(animation[frame]));
}

bool oled_task_user() {
    render_animation((timer_read() / 60) % 8);
    return false;
}