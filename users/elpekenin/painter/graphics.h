// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include QMK_KEYBOARD_H
#include "qp.h"

#if !defined(QUANTUM_PAINTER_NUM_DISPLAYS)
#    define QUANTUM_PAINTER_NUM_DISPLAYS 1
#endif // QUANTUM_PAINTER_NUM_DISPLAYS

void _load_display(painter_device_t display);
void _load_font(const uint8_t *font);
void _load_img(const uint8_t *img);

#define load_display(x) qp_dprintf("Loading '" XSTR(x)); _load_display(x)
#define load_font(x) qp_dprintf("Loading '" XSTR(x)); _load_font(x)
#define load_image(x) qp_dprintf("Loading '" XSTR(x)); _load_image(x)

extern painter_device_t qp_displays[QUANTUM_PAINTER_NUM_DISPLAYS];
extern painter_font_handle_t qp_fonts[QUANTUM_PAINTER_NUM_FONTS];
extern painter_image_handle_t qp_images[QUANTUM_PAINTER_NUM_IMAGES];

void load_qp_resources(void);
