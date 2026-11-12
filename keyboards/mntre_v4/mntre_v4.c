// Copyright 2026 Andreas Hirschauer
// Copyright 2021-2024 MNT Research GmbH (mntre.com)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H

#ifdef OLED_ENABLE
#    include <stdio.h>

#    define SPLASH_DURATION_MS 1500
#    define RGB_PAGE_DURATION_MS 2000

// MNT Reform logo, three 72-pixel-wide pages.
// Taken from reform2-keyboard4-fw/src/font.c (GPL-3.0-or-later).
// clang-format off
static const char PROGMEM mnt_logo[3][72] = {
    {
        0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x00, 0xFF, 0xFE, 0xFC,
        0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x00, 0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0,
        0xC0, 0x80, 0x00, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
        0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    },
    {
        0x3F, 0x3F, 0x3F, 0x3F, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF,
        0xFF, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x0F,
        0x1F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xF0, 0xF0,
        0x30, 0xB0, 0xB0, 0x70, 0xF0, 0x30, 0xB0, 0xB0, 0xB0, 0xF0, 0x70, 0xB0,
        0xB0, 0xB0, 0xF0, 0x70, 0xB0, 0xB0, 0xB0, 0x70, 0xF0, 0x30, 0xB0, 0xB0,
        0x70, 0xF0, 0x30, 0x70, 0xF0, 0xF0, 0xF0, 0x70, 0x30, 0xF0, 0xF0, 0x00,
    },
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03,
        0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x00, 0x00, 0x00, 0x7F, 0x7F,
        0x60, 0x7D, 0x7D, 0x62, 0x7F, 0x60, 0x6D, 0x6D, 0x6D, 0x7F, 0x60, 0x7D,
        0x7D, 0x7F, 0x7F, 0x70, 0x6F, 0x6F, 0x6F, 0x70, 0x7F, 0x60, 0x7D, 0x7D,
        0x62, 0x7F, 0x60, 0x7F, 0x7E, 0x7D, 0x7E, 0x7F, 0x60, 0x7F, 0x7F, 0x00,
    },
};
// clang-format on

typedef enum {
    PAGE_NONE,
    PAGE_SPLASH,
    PAGE_RGB,
    PAGE_CIRCLE,
} oled_page_t;

static oled_page_t timed_page = PAGE_NONE;
static uint32_t    timed_page_until;
static oled_page_t shown_page = PAGE_NONE;

static void show_timed_page(oled_page_t page, uint32_t duration_ms) {
    timed_page       = page;
    timed_page_until = timer_read32() + duration_ms;
}

static void render_splash(void) {
    for (uint8_t line = 0; line < ARRAY_SIZE(mnt_logo); line++) {
        oled_set_cursor(4, line + 1);
        oled_write_raw_P(mnt_logo[line], sizeof(mnt_logo[line]));
    }
}

static void render_rgb_values(void) {
    if (!rgb_matrix_is_enabled()) {
        oled_write_ln_P(PSTR("Backlight off"), false);
        return;
    }
    char buf[22];
    snprintf(buf, sizeof(buf), "H%3u S%3u V%3u  #%2u", rgb_matrix_get_hue(), rgb_matrix_get_sat(), rgb_matrix_get_val(), rgb_matrix_get_mode());
    oled_write_ln(buf, false);
}

static void render_rgb(void) {
    // Stay below a full 21-character row so oled_write_ln does not wrap.
    char name[21] = "";
    if (rgb_matrix_is_enabled()) {
        strlcpy(name, rgb_matrix_get_mode_name(rgb_matrix_get_mode()), sizeof(name));
        for (char *c = name; *c; c++) {
            if (*c == '_') *c = ' ';
        }
    }
    oled_write_ln_P(PSTR("Backlight"), false);
    oled_write_ln(name, false);
    render_rgb_values();
}

static void render_circle(void) {
    oled_write_ln_P(PSTR("F1-6 Bright/Hue/Sat"), false);
    oled_write_ln_P(PSTR("F7/8 Mode  F9 On/Off"), false);
    oled_write_ln_P(PSTR("Hyper+R / X Boot"), false);
    render_rgb_values();
}

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    show_timed_page(PAGE_SPLASH, SPLASH_DURATION_MS);
    return oled_init_user(rotation);
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }

    if (timed_page != PAGE_NONE && timer_expired32(timer_read32(), timed_page_until)) {
        timed_page = PAGE_NONE;
    }

    oled_page_t page = timed_page;
    if (page == PAGE_NONE && layer_state_is(R4_LAYER_CIRCLE)) {
        page = PAGE_CIRCLE;
    }

    if (page != shown_page) {
        shown_page = page;
        oled_clear();
        if (page == PAGE_NONE) {
            // Push the blank frame first, otherwise the next render switches the display back on.
            oled_render_dirty(true);
            oled_off();
            return false;
        }
    }

    switch (page) {
        case PAGE_SPLASH:
            render_splash();
            break;
        case PAGE_RGB:
            render_rgb();
            break;
        case PAGE_CIRCLE:
            render_circle();
            break;
        default:
            break;
    }
    return false;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }

    // The Circle layer already shows the lighting values.
    if (record->event.pressed && IS_RGB_MATRIX_KEYCODE(keycode) && !layer_state_is(R4_LAYER_CIRCLE)) {
        show_timed_page(PAGE_RGB, RGB_PAGE_DURATION_MS);
    }
    return true;
}
#endif
