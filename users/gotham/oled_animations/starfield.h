#pragma once
#include "common.h"

#define STAR_COUNT_MIN 5
#define STAR_COUNT_MAX 20
#define STAR_ZOOM_SPEED 24
#define STAR_SPAWN_RANGE 16
#define STAR_SPAWN_DELAY 1000
#define STARFIELD_FPS 16  // High values might lock up the keyboard eventually

#define UPDATE_DELAY (uint8_t)(1000.0 / STARFIELD_FPS)

void oled_init_starfield(void);

void set_starfield_center(void);

void erase_stars(void);

void render_starfield(void);
