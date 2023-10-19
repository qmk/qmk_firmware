// Copyright 2023 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "reverb.h"
#include "graphics/splash.qgf.h"

painter_device_t       reverb_display;

void keyboard_post_init_kb(void) {
    painter_image_handle_t splash_image;
    reverb_display = qp_gc9a01_make_spi_device(240, 240, DISPLAY_CS, DISPLAY_DC, DISPLAY_RST, 2, 0);
    qp_init(reverb_display, QP_ROTATION_0);
    splash_image = qp_load_image_mem(gfx_splash);
    qp_drawimage(reverb_display, 0, 0, splash_image);
    qp_flush(reverb_display);
    qp_close_image(splash_image);
    keyboard_post_init_user();
}
