// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "custom_eeprom.h"

#if defined(QUANTUM_PAINTER_ENABLE)
#    include "color.h"
#    include "graphics.h"
#endif // QUANTUM_PAINTER_ENABLE

// compute the bitmask based on current `#define`s
uint32_t custom_eeprom_generate(void) {
    return
#if defined(AUDIO_ENABLE)
        (1 << 0) |
#endif // AUDIO_ENABLE

#if defined(RGB_MATRIX_ENABLE)
        (1 << 1) |
#endif // RGB_MATRIX_ENABLE

#if defined(SIPO_PINS_ENABLE)
        (1 << 2) |
#endif // SIPO_PINS_ENABLE

#if defined(TOUCH_SCREEN_ENABLE)
        (1 << 3) |
#endif // TOUCH_SCREEN_ENABLE

#if defined(UNICODE_ENABLE)
        (1 << 4) |
#endif // UNICODE_ENABLE

#if defined(QP_XAP_ENABLE)
        (1 << 5) |
#endif // QP_XAP_ENABLE

    0;
}

void custom_eeprom_draw_config(void *cb_arg) {
    user_config_t eeprom_config;
    eeprom_config.raw = eeconfig_read_user();
#if defined(QUANTUM_PAINTER_ENABLE)
    painter_device_t      device = (painter_device_t *)cb_arg;
    painter_font_handle_t font   = qp_fonts[0];
    uint8_t               height = font->line_height;
    uint8_t               x      = 0;
    uint8_t               y      = 0;

    int16_t width  = qp_textwidth(font, "       Audio: Off");
    int16_t offset = (width - qp_textwidth(font, "FEATURES")) / 2;
    qp_drawtext_recolor(device, x + offset, y, font, "FEATURES", HSV_BLACK, HSV_WHITE);
    y += height;

    if (eeprom_config.audio)   qp_drawtext_recolor(device, x, y, font, "       Audio: On",  HSV_BLACK, HSV_WHITE);
    else                       qp_drawtext_recolor(device, x, y, font, "       Audio: Off", HSV_BLACK, HSV_WHITE);
    qp_line(device, x, y, x+width, y, HSV_RED);
    y += height;

    if (eeprom_config.matrix)  qp_drawtext_recolor(device, x, y, font, "  RGB Matrix: On",  HSV_BLACK, HSV_WHITE);
    else                       qp_drawtext_recolor(device, x, y, font, "  RGB Matrix: Off", HSV_BLACK, HSV_WHITE);
    y += height;

    if (eeprom_config.sipo)    qp_drawtext_recolor(device, x, y, font, "   SIPO Pins: On",  HSV_BLACK, HSV_WHITE);
    else                       qp_drawtext_recolor(device, x, y, font, "   SIPO Pins: Off", HSV_BLACK, HSV_WHITE);
    y += height;

    if (eeprom_config.touch)   qp_drawtext_recolor(device, x, y, font, "Touch Driver: On",  HSV_BLACK, HSV_WHITE);
    else                       qp_drawtext_recolor(device, x, y, font, "Touch Driver: Off", HSV_BLACK, HSV_WHITE);
    y += height;

    if (eeprom_config.unicode) qp_drawtext_recolor(device, x, y, font, "     Unicode: On",  HSV_BLACK, HSV_WHITE);
    else                       qp_drawtext_recolor(device, x, y, font, "     Unicode: Off", HSV_BLACK, HSV_WHITE);
    y += height;

    if (eeprom_config.qp_xap)  qp_drawtext_recolor(device, x, y, font, " QP over XAP: On",  HSV_BLACK, HSV_WHITE);
    else                       qp_drawtext_recolor(device, x, y, font, " QP over XAP: Off", HSV_BLACK, HSV_WHITE);
    y += height;
#endif // QUANTUM_PAINTER_ENABLE
}
