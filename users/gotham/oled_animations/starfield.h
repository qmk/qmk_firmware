#pragma once
#include "common.h"

#define MAX_STARS 20
#define ZOOM_SPEED 24
#define SPAWN_RANGE 16
#define SPAWN_DELAY 100
#define STARFIELD_FPS 16  // High values might lock up the keyboard eventually

#define UPDATE_DELAY (uint8_t)(1000.0 / STARFIELD_FPS)

void oled_init_starfield(void);

uint8_t get_star_x(uint8_t index);
uint8_t get_star_y(uint8_t index);

void spawn_star(void);
void update_star(uint8_t index);
void erase_stars(void);

void set_starfield_center(void);

void render_starfield(void);
