// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-3.0-or-later
#include <stdio.h>
#include QMK_KEYBOARD_H
#include "analog.h"
#include "qp.h"
#include "qp_ssd1351.h"

#define NUM_ADC_READS 32

#include "graphics/ghoul-logo.qgf.c"
#include "graphics/ghoul-name.qgf.c"
#include "graphics/lock-caps.qgf.c"
#include "graphics/lock-num.qgf.c"
#include "graphics/lock-scrl.qgf.c"
#include "graphics/thintel15.qff.c"

static painter_device_t       oled;
static painter_image_handle_t logo;
static painter_image_handle_t name;
static painter_font_handle_t  font;
static painter_image_handle_t lock_caps;
static painter_image_handle_t lock_num;
static painter_image_handle_t lock_scrl;

void ui_init(void) {
    oled      = qp_ssd1351_make_spi_device(128, 128, OLED_CS_PIN, OLED_DC_PIN, OLED_RST_PIN, 8, 0);
    logo      = qp_load_image_mem(gfx_ghoul_logo);
    name      = qp_load_image_mem(gfx_ghoul_name);
    font      = qp_load_font_mem(font_thintel15);
    lock_caps = qp_load_image_mem(gfx_lock_caps);
    lock_num  = qp_load_image_mem(gfx_lock_num);
    lock_scrl = qp_load_image_mem(gfx_lock_scrl);

    qp_init(oled, QP_ROTATION_90);
    qp_rect(oled, 0, 0, 127, 127, 0, 0, 0, true);
    qp_flush(oled);
}

void ui_task(void) {
    bool            hue_redraw = false;
    static uint16_t last_hue   = 0xFFFF;
    uint8_t         curr_hue   = rgblight_get_hue();
    if (last_hue != curr_hue) {
        last_hue   = curr_hue;
        hue_redraw = true;
    }

    if (hue_redraw) {
        qp_drawimage_recolor(oled, 0, 64 - (name->height / 2), name, curr_hue, 255, 255, curr_hue, 255, 0);
        qp_drawimage_recolor(oled, 127 - logo->width, 0, logo, curr_hue, 255, 255, curr_hue, 255, 0);
    }

    static led_t last_led_state = {0};
    if (hue_redraw || last_led_state.raw != host_keyboard_led_state().raw) {
        last_led_state.raw = host_keyboard_led_state().raw;
        qp_drawimage_recolor(oled, lock_caps->width * 0, 0, lock_caps, curr_hue, 255, last_led_state.caps_lock ? 255 : 32, curr_hue, 255, 0);
        qp_drawimage_recolor(oled, lock_caps->width * 1, 0, lock_num, curr_hue, 255, last_led_state.num_lock ? 255 : 32, curr_hue, 255, 0);
        qp_drawimage_recolor(oled, lock_caps->width * 2, 0, lock_scrl, curr_hue, 255, last_led_state.scroll_lock ? 255 : 32, curr_hue, 255, 0);

        qp_rect(oled, lock_caps->width * 0 + 1, lock_caps->height + 2, lock_caps->width * 1 - 1, lock_caps->height + 3, curr_hue, 255, last_led_state.caps_lock ? 255 : 0, true);
        qp_rect(oled, lock_caps->width * 1 + 1, lock_caps->height + 2, lock_caps->width * 2 - 1, lock_caps->height + 3, curr_hue, 255, last_led_state.num_lock ? 255 : 0, true);
        qp_rect(oled, lock_caps->width * 2 + 1, lock_caps->height + 2, lock_caps->width * 3 - 1, lock_caps->height + 3, curr_hue, 255, last_led_state.scroll_lock ? 255 : 0, true);
    }

#if HAL_USE_ADC
    static int16_t current_reads[NUM_ADC_READS] = {0};
    static int16_t voltage_reads[NUM_ADC_READS] = {0};
    static int     write_offset                 = 0;

    static uint32_t last_read = 0;
    if (timer_elapsed32(last_read) >= 1) {
        // Perform the reads
        int16_t current    = analogReadPin(ADC_CURRENT_PIN);
        int16_t voltage    = analogReadPin(ADC_VOLTAGE_PIN);
        int16_t current_ma = (int16_t)(((3300 * (int32_t)current) / ADC_SATURATION));
        int16_t voltage_mv = (int16_t)((2 * (3300 * (int32_t)voltage)) / ADC_SATURATION);

        // Duplicate the first read so that averages work
        if (last_read == 0) {
            for (int i = 0; i < NUM_ADC_READS; ++i) {
                current_reads[i] = current_ma;
                voltage_reads[i] = voltage_mv;
            }
        }

        // Dump in the current value
        current_reads[write_offset] = current_ma;
        voltage_reads[write_offset] = voltage_mv;
        write_offset                = (write_offset + 1) % NUM_ADC_READS;

        static int counter = 0;
        counter            = (counter + 1) % 2500;
        if (counter == 0) {
            dprintf("Current: %dmA (%d) -- Voltage: %dmV (%d)\n", (int)current_ma, (int)current, (int)voltage_mv, (int)voltage);
        }

        last_read = timer_read32();
    }

    static uint32_t last_draw = 0;
    if (hue_redraw || timer_elapsed32(last_draw) >= 250) {
        // Accumulate
        int32_t total_current_ma = 0;
        int32_t total_voltage_mv = 0;
        for (int i = 0; i < NUM_ADC_READS; ++i) {
            total_current_ma += current_reads[i];
            total_voltage_mv += voltage_reads[i];
        }

        // Get the averages
        int16_t avg_current_ma = (int16_t)(total_current_ma / NUM_ADC_READS);
        int16_t avg_voltage_mv = (int16_t)(total_voltage_mv / NUM_ADC_READS);

        char buf[32] = {0};
        sprintf(buf, "Current: %dmA", avg_current_ma);
        static int16_t maxlen_curr = 0;
        int16_t        len         = qp_drawtext_recolor(oled, 0, 127 - (font->line_height * 2), font, buf, 0, 0, 32, 0, 0, 0);
        if (len < maxlen_curr) {
            qp_rect(oled, len, 127 - (font->line_height * 2), maxlen_curr, 127 - (font->line_height * 1), 0, 0, 0, true);
        } else if (len > maxlen_curr) {
            maxlen_curr = len;
        }

        static int16_t maxlen_volt = 0;
        sprintf(buf, "Voltage: %dmV", avg_voltage_mv);
        len = qp_drawtext_recolor(oled, 0, 127 - (font->line_height * 1), font, buf, 0, 0, 32, 0, 0, 0);
        if (len < maxlen_volt) {
            qp_rect(oled, len, 127 - (font->line_height * 1), maxlen_volt, 127 - (font->line_height * 0), 0, 0, 0, true);
        } else if (len > maxlen_volt) {
            maxlen_volt = len;
        }

        qp_flush(oled);

        last_draw = timer_read32();
    }
#endif // HAL_USE_ADC
}
