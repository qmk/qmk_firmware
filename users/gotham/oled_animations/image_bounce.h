#pragma once
#include "common.h"

#define IMAGE_BOUNCE_SPEED 1
#define IMAGE_BOUNCE_FPS 45
#define IMAGE_BOUNCE_OFFSCREEN_PADDING 0
#define UPDATE_DELAY (uint8_t)(1000.0 / IMAGE_BOUNCE_FPS)

void oled_init_image_bounce(void);
void update_image_bounce(void);
void render_image_bounce(void);
