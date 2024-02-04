// Copyright 2024 Fernando Birra
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rp2040_tft.h"

#include <qp.h>

#include "graphics/qmklogo.qgf.h"

static painter_device_t qp_display;
static painter_image_handle_t qp_image;

void keyboard_post_init_kb(void) {
    qp_display = qp_gc9107_make_spi_device(
        PANEL_WIDTH, 
        PANEL_HEIGHT, 
        PANEL_CS, 
        PANEL_DC, 
        PANEL_RST, 
        8, //spi_divisor, 
        0  //spi_mode
    );         // Create the display
    qp_init(qp_display, QP_ROTATION_180);   // Initialise the display
    qp_rect(qp_display, 0, 0, PANEL_WIDTH, PANEL_HEIGHT, 128, 255, 255, true);
    
    qp_image = qp_load_image_mem(gfx_qmklogo);
    qp_drawimage(qp_display, 0, 0, qp_image);

    return keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
    static uint32_t last_draw = 0;
    if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
        last_draw = timer_read32();
        // Draw 8px-wide rainbow down the left side of the display
        for (int i = 0; i < PANEL_WIDTH; ++i) {
            qp_line(qp_display, i, 0, i, 7, i, 255, 255);
        }
        qp_flush(qp_display);
    }
}

