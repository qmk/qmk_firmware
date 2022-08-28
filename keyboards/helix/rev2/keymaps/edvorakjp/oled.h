#pragma once

#include "edvorakjp.h"

extern bool japanese_mode;

void            render_host_led_state(void);
void            render_layer_state(void);
void            render_logo(void);
void            render_mode_icon(bool is_windows);
oled_rotation_t oled_init_user(oled_rotation_t rotation);
bool            oled_task_user(void);
