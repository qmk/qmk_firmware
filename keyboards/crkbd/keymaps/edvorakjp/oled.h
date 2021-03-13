#pragma once

// SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#include "ssd1306.h"
#include "edvorakjp.h"

extern uint8_t is_master;
extern bool    japanese_mode;

// method prototypes defined in crkbd/lib
extern const char *read_logo(void);

const char *read_mode_icon(bool swap);
const char *read_layer_state(void);
const char *read_host_led_state(void);
void        matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source);
void        iota_gfx_task_user(void);
