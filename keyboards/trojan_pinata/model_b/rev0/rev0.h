#pragma once

#include "quantum.h"

bool oled_task_user(void);
void suspend_power_down_user(void);
void oled_render_boot(bool bootloader);
bool shutdown_user(bool jump_to_bootloader);
bool process_record_user(uint16_t keycode, keyrecord_t *record);
