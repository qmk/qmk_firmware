#pragma once

#include "edvorakjp.h"

extern bool japanese_mode;

// method prototypes defined in crkbd/lib
extern const char *read_host_led_state(void);
extern const char *read_logo(void);
extern const char *read_mode_icon(bool swap);

void            render_host_led_state(void);
void            render_layer_state(void);
void            render_logo(void);
void            render_mode_icon(bool is_windows);
oled_rotation_t oled_init_user(oled_rotation_t rotation);
void            oled_task_user(void);
