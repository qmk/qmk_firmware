#ifndef OLED_USER_H
#define OLED_USER_H

//SSD1306 OLED update loop
#include "ssd1306.h"
#include "edvorakjp.h"

//assign the right code to your layers for OLED display
#define L_BASE 0

extern uint8_t is_master;
extern bool japanese_mode;

void render_status(void);
void oled_task_user(void);

#endif // OLED_CONFIG_USER_H
