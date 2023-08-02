#pragma once

#include "quantum.h"
#include "oled_driver.h"

oled_rotation_t oled_init_user(oled_rotation_t rotation);
void            render_crkbd_logo(void);
void            render_status(void);
bool            oled_task_user(void);
