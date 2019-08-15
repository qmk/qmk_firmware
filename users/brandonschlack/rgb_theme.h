#pragma once

#include "brandonschlack.h"
#include "color.h"
#include "rgblight_list.h"

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)

// Laser Colors
#define HSV_LSR_PURPLE   HSV_PURPLE
#define HSV_LSR_PINK     HSV_PINK
#define HSV_LSR_BLUE     HSV_BLUE
#define HSV_LSR_CYAN     HSV_CYAN
#define HSV_LSR_MAGENTA  HSV_MAGENTA

// Granite Colors
#define HSV_GNT_BLUE     HSV_BLUE
#define HSV_GNT_RED      HSV_RED
#define HSV_GNT_GREEN    HSV_GREEN
#define HSV_GNT_YELLOW   HSV_YELLOW
#define HSV_GNT_WHITE    HSV_WHITE

// Oblique Colors
#define HSV_OBQ_BLUE     130, 215, 255
#define HSV_OBQ_RED      10,  200, 255
#define HSV_OBQ_GREEN    58,  199, 255
#define HSV_OBQ_ORANGE   26,  215, 255
#define HSV_OBQ_PURPLE   186, 143, 255
#define HSV_OBQ_WHITE    HSV_WHITE

typedef enum {
    LASER = 0,
    GRANITE,
    OBLIQUE
} rgb_theme_name_t;

typedef struct {
    rgb_theme_name_t theme;
    const HSV *colors[5];
} rgb_theme_t;

void set_rgb_theme(rgb_theme_name_t theme_name);
rgb_theme_t get_rgb_theme(void);

void rgb_theme_step(void);
void rgb_theme_step_reverse(void);

HSV get_rgb_theme_color(uint8_t index);
#endif
