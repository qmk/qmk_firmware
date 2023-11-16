// Copyright 2023 Cole Smith (@boardsource)
// SPDX-License-Identifier: GPL-2.0-or-later
#include <stdio.h>
#include "qp.h"
#include "qp_st7735.h"
#include "graphics/thintel15.qff.c"

static painter_device_t      oled;
static painter_font_handle_t font;

__attribute__((weak)) void ui_init(void) {
    oled = qp_st7735_make_spi_device(128, 160, OLED_CS_PIN, OLED_DC_PIN, OLED_RST_PIN, 8, 0);
    font = qp_load_font_mem(font_thintel15);
    qp_init(oled, QP_ROTATION_0);
    qp_rect(oled, 0, 0, 130, 162, 0, 0, 0, true);
    qp_rect(oled, 20, 20, 108, 60, 55, 55, 55, true);
    qp_rect(oled, 20, 80, 108, 120, 55, 55, 55, true);
    qp_flush(oled);
}

__attribute__((weak)) void ui_task(void) {
    static const char *text  = "Layer:";
    int16_t            width = qp_textwidth(font, text);
    qp_drawtext(oled, 20, 140, font, text);

    switch (get_highest_layer(layer_state)) {
        case 0:
            qp_drawtext(oled, (20 + width), 140, font, "QWERTY");
            break;
        case 1:
            qp_drawtext(oled, (20 + width), 140, font, "SYMBOL");
            break;
        case 2:
            qp_drawtext(oled, (20 + width), 140, font, "NUMBER");
            break;
        default:
            qp_drawtext(oled, (20 + width), 140, font, "_PANIC_");
            break;
    }
}
