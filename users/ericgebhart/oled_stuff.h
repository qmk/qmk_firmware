#pragma once

#include "quantum.h"
#include "oled_driver.h"

void oled_driver_render_logo(void);
bool process_record_user_oled(uint16_t keycode, keyrecord_t *record);
