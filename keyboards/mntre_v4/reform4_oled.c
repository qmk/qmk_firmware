// Copyright 2026 Andreas Hirschauer
// SPDX-License-Identifier: GPL-2.0-or-later

// Temporary OLED pages and the Circle lighting legend.

#include QMK_KEYBOARD_H

#include <stdio.h>
#include <string.h>

#define OLED_COLS 21

static reform4_oled_page_t page = R4_OLED_NONE;
static uint32_t            page_until;

typedef enum {
    SHOWN_NONE,
    SHOWN_PAGE,
    SHOWN_CIRCLE_MENU,
} shown_t;
static shown_t             shown = SHOWN_NONE;
static reform4_oled_page_t shown_page;

void reform4_oled_show(reform4_oled_page_t new_page, uint32_t duration_ms) {
    page       = new_page;
    page_until = timer_read32() + duration_ms;
    shown      = SHOWN_NONE;
}

// Pad rows so text from a previous page does not remain visible.
static void write_row(uint8_t row, const char *text) {
    char   buf[OLED_COLS + 1];
    size_t len = strlen(text);
    if (len > OLED_COLS) {
        len = OLED_COLS;
    }
    memcpy(buf, text, len);
    memset(buf + len, ' ', OLED_COLS - len);
    buf[OLED_COLS] = '\0';
    oled_set_cursor(0, row);
    oled_write(buf, false);
}

static void render_splash(void) {
    // MNT logo, three rows of twelve glyphs starting at 160.
    for (uint8_t y = 0; y < 3; y++) {
        oled_set_cursor(4, y + 1);
        for (uint8_t x = 0; x < 12; x++) {
            oled_write_char((char)((5 + y) * 32 + x), false);
        }
    }
}

static void render_rgb_values(uint8_t row) {
    char buf[OLED_COLS + 1];
    if (!rgb_matrix_is_enabled()) {
        write_row(row, "Backlight off");
        return;
    }
    snprintf(buf, sizeof(buf), "H%3u S%3u V%3u  #%2u", rgb_matrix_get_hue(), rgb_matrix_get_sat(), rgb_matrix_get_val(), rgb_matrix_get_mode());
    write_row(row, buf);
}

static void render_rgb(void) {
    write_row(0, "Backlight");
    if (rgb_matrix_is_enabled()) {
        char name[OLED_COLS + 1];
        strlcpy(name, rgb_matrix_get_mode_name(rgb_matrix_get_mode()), sizeof(name));
        for (char *c = name; *c; c++) {
            if (*c == '_') *c = ' ';
        }
        write_row(1, name);
    } else {
        write_row(1, "");
    }
    render_rgb_values(2);
}

static void render_circle_menu(void) {
    write_row(0, "F1-6 Bright/Hue/Sat");
    write_row(1, "F7/8 Mode  F9 On/Off");
    write_row(2, "Hyper+R / X Boot");
    render_rgb_values(3);
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }

    if (page != R4_OLED_NONE && timer_expired32(timer_read32(), page_until)) {
        page = R4_OLED_NONE;
    }

    shown_t want = SHOWN_NONE;
    if (page != R4_OLED_NONE) {
        want = SHOWN_PAGE;
    } else if (layer_state_is(R4_LAYER_CIRCLE)) {
        want = SHOWN_CIRCLE_MENU;
    }

    if (want != shown || (want == SHOWN_PAGE && page != shown_page)) {
        oled_clear();
        shown      = want;
        shown_page = page;
        if (want == SHOWN_NONE) {
            oled_render_dirty(true);
            oled_off();
            return false;
        }
    }

    switch (want) {
        case SHOWN_PAGE:
            if (page == R4_OLED_SPLASH) {
                render_splash();
            } else if (page == R4_OLED_RGB) {
                render_rgb();
            }
            break;
        case SHOWN_CIRCLE_MENU:
            render_circle_menu();
            break;
        case SHOWN_NONE:
            break;
    }
    return false;
}
