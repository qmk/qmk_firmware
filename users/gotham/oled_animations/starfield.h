#pragma once
#include "common.h"

#define STAR_COUNT_MAX 12
#define STAR_ZOOM_SPEED_MIN 18
#define STAR_ZOOM_SPEED_MAX 32
#define STAR_SPAWN_RANGE 8
#define STAR_SPAWN_DELAY 200
#define STARFIELD_FPS 15  // High values might lock up the keyboard eventually

#define UPDATE_DELAY (uint8_t)(1000.0 / STARFIELD_FPS)

void oled_init_starfield(void);

uint8_t starfield_speed_get(void);

void starfield_speed_set(uint8_t value);

void set_starfield_center(void);

void erase_stars(void);

void render_starfield(void);
