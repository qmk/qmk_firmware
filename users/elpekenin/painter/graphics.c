// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "graphics.h"
#include "qp.h"

painter_device_t qp_displays[QUANTUM_PAINTER_NUM_DISPLAYS] = {}; // Has to be filled by the user
painter_font_handle_t qp_fonts[QUANTUM_PAINTER_NUM_FONTS] = {};
painter_image_handle_t qp_images[QUANTUM_PAINTER_NUM_IMAGES] = {};

// Fonts, in alphabetical order to easier checking
#include "fira_code.qff.h"

// Images, in alphabetical order to easier checking
#include "ab-testing.qgf.h"
#include "lightbulb_off_outline.qgf.h"
#include "lightbulb_on_20.qgf.h"
#include "lightbulb_on_40.qgf.h"
#include "lightbulb_on_60.qgf.h"
#include "lightbulb_on_80.qgf.h"
#include "lightbulb_on.qgf.h"
#include "pokeball.qgf.h"

// =======
// Load resources
void _load_display(painter_device_t display) {
    static uint8_t i = 0;

    if (i >= QUANTUM_PAINTER_NUM_DISPLAYS) {
        dprintf("' failed, out of bounds defined by QUANTUM_PAINTER_NUM_DISPLAYS\n");
        return;
    }

    dprintf("' at position [%d]\n", i);
    qp_displays[i++] = display;
}

void _load_font(const uint8_t *font) {
    static uint8_t i = 0;

    if (i >= QUANTUM_PAINTER_NUM_FONTS) {
        dprintf("' failed, out of bounds defined by QUANTUM_PAINTER_NUM_FONTS\n");
        return;
    }

    dprintf("' at position [%d]\n", i);
    painter_font_handle_t dummy = qp_load_font_mem(font);
    qp_fonts[i++] = dummy;
}

void _load_image(const uint8_t *img) {
    static uint8_t i = 0;

    if (i >= QUANTUM_PAINTER_NUM_IMAGES) {
        dprintf("' failed, out of bounds defined by QUANTUM_PAINTER_NUM_IMAGES\n");
        return;
    }

    dprintf("' at position [%d]\n", i);
    painter_image_handle_t dummy = qp_load_image_mem(img);
    qp_images[i++] = dummy;
}

void load_qp_resources(void) {
    load_font(font_fira_code);

    load_image(gfx_ab_testing);
    load_image(gfx_lightbulb_off_outline);
    load_image(gfx_lightbulb_on_20);
    load_image(gfx_lightbulb_on_40);
    load_image(gfx_lightbulb_on_60);
    load_image(gfx_lightbulb_on_80);
    load_image(gfx_lightbulb_on);
    load_image(gfx_pokeball);
}
