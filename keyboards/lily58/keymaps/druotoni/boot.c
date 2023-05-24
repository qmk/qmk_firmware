// Copyright 2021 Nicolas Druoton (druotoni)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "boot.h"
#include "fast_random.h"
#include "draw_helper.h"
#include "gui_state.h"

// boot
#define ANIM_BOOT_FRAME_DURATION 8
uint16_t anim_boot_timer         = 0;
uint8_t  anim_boot_current_frame = 0;

#define NAVI_DURATION 55

// terminal stuff
#define TERMINAL_DURATION 25
#define TERMINAL_LINE_NUMBER 19
#define TERMINAL_LINE_MAX 14

#define LILY_DURATION 50

// halt
#define ANIM_HALT_FRAME_DURATION 55
uint16_t anim_halt_timer = 0;

void reset_boot(void) {
    // frame zero
    anim_boot_current_frame = 0;
}

static void draw_lily_key(uint8_t x, uint8_t y, uint8_t *key_number, unsigned long key_state, uint8_t color) {
    uint8_t       v    = *key_number;
    unsigned long mask = 1;
    mask               = mask << v;

    // ligth the key according to the mask
    if (((key_state & mask) == mask)) {
        color = !color;
    }

    draw_rectangle_fill(x, y, 3, 3, color);
    *key_number = v + 1;
}

static void draw_lily_key_row(uint8_t x, uint8_t y, int w, uint8_t *key_number, unsigned long key_state, uint8_t color) {
    // row of rectangle
    for (uint8_t i = 0; i < w; i++) {
        draw_lily_key(x + (i * 4), y, key_number, key_state, color);
    }
}

static void draw_lily_render(unsigned long key_state) {
    // different orientation base on side
#if IS_LEFT

    uint8_t x            = 0;
    uint8_t y            = 56;
    uint8_t x_ref        = 10 + x;
    uint8_t y_ref        = 2 + y;
    uint8_t i_key_number = 0;

    for (uint8_t i = 0; i < 4; i++) {
        draw_lily_key_row(x_ref, y_ref + (i * 4), 4, &i_key_number, key_state, true);
        draw_lily_key_row(x_ref - 8, y_ref + 2 + (i * 4), 2, &i_key_number, key_state, true);
    }

    draw_lily_key_row(x_ref + 2, y_ref + (4 * 4), 3, &i_key_number, key_state, true);

    uint8_t x_side = x_ref + (4 * 4);

    draw_lily_key(x_side, y_ref + (2 * 4) + 2, &i_key_number, key_state, true);
    draw_lily_key(x_side, y_ref + (4 * 4), &i_key_number, key_state, true);

    // screen
    draw_rectangle(x_side, y_ref, 4, 8, true);

    // frame
    drawline_hr(x + 1, y + 2, 8, true);
    oled_write_pixel(x + 8, y + 1, true);
    drawline_hr(x + 8, y, 23, true);

    drawline_hr(x + 1, y + 20, 10, true);
    oled_write_pixel(x + 10, y + 21, true);
    drawline_hr(x + 10, y + 22, 16, true);

    drawline_vb(x, y + 3, 17, true);
    drawline_vb(x + 31, y + 1, 20, true);
    oled_write_pixel(x + 30, y + 21, true);
    oled_write_pixel(x + 29, y + 22, true);
    oled_write_pixel(x + 28, y + 23, true);
    oled_write_pixel(x + 27, y + 24, true);
    oled_write_pixel(x + 26, y + 23, true);
#endif

#if IS_RIGHT
    uint8_t i_key_number = 0;

    for (uint8_t i = 0; i < 4; i++) {
        draw_lily_key_row(7, 58 + (i * 4), 4, &i_key_number, key_state, true);
        draw_lily_key_row(23, 60 + (i * 4), 2, &i_key_number, key_state, true);
    }

    draw_lily_key_row(9, 74, 3, &i_key_number, key_state, true);

    draw_lily_key(3, 68, &i_key_number, key_state, true);
    draw_lily_key(3, 74, &i_key_number, key_state, true);

    // screen
    draw_rectangle(2, 58, 4, 8, true);

    // frame
    drawline_hr(23, 58, 8, true);
    oled_write_pixel(23, 57, true);
    drawline_hr(1, 56, 23, true);

    drawline_hr(21, 76, 10, true);
    oled_write_pixel(21, 77, true);
    drawline_hr(6, 78, 16, true);

    drawline_vb(31, 59, 17, true);
    drawline_vb(0, 57, 20, true);
    oled_write_pixel(1, 77, true);
    oled_write_pixel(2, 78, true);
    oled_write_pixel(3, 79, true);
    oled_write_pixel(4, 80, true);
    oled_write_pixel(5, 79, true);
#endif
}

static void draw_lily(uint8_t f) {
    // frame for the events
    uint8_t tres_stroke = 10;
    uint8_t tres_boom   = 30;
    uint8_t y_start     = 56;

    if (f == 0 || f == tres_stroke || f == tres_boom) {
        // clean screen
        oled_clear();
    }

    // simple lily58 with all the keys
    if (f < tres_stroke) {
        draw_lily_render(0);
    }

    // increase number of random keys pressed
    if (f >= tres_stroke && f < tres_boom) {
        int inter_f = interpo_pourcent(tres_stroke, tres_boom, f);

        unsigned long key_state = fastrand_long();
        for (int r = 100 - inter_f; r > 0; r = r - 10) {
            key_state &= fastrand_long();
        }
        draw_lily_render(key_state);
    }

    // statir explosion
    if (f >= tres_boom) {
        oled_clear();
        uint8_t density = (f - tres_boom);
        if (density > 4) density = 4;
        draw_static(0, y_start - 8, 32, 32, true, density);
    }
}

static void draw_startup_navi(uint8_t f) {
    // text
    oled_write_cursor(0, 5, "HELL0", false);
    oled_write_cursor(0, 7, "NAVI.", false);

    // prompt
    if ((f % 8) > 4) {
        oled_write_cursor(0, 12, "> ", false);
    } else {
        oled_write_cursor(0, 12, ">_", false);
    }

    // frame threshold
    uint8_t tres_shell = 15;
    uint8_t tres_load  = 35;

    // rand text to init display
    if (f > tres_shell) {
        int inter_f = interpo_pourcent(tres_shell, tres_load, f);

        draw_random_char(1, 12, 'i', 60 + inter_f, 0);
        draw_random_char(2, 12, 'n', 20 + inter_f, 0);
        draw_random_char(3, 12, 'i', inter_f, 0);
        draw_random_char(4, 12, 't', 20 + inter_f, 0);
    }

    // loading propress bar
    if (f > tres_load) {
        int inter_f = interpo_pourcent(tres_load, 50, f);

        // ease
        float fv = inter_f / 100.00;
        fv       = fv * fv * fv * fv;
        inter_f  = fv * 100;

        draw_rectangle(0, (15 * 8), 32, 8, 1);
        draw_progress(0 + 3, (15 * 8) + 3, 26, 2, inter_f, 0, 1);
    }
}

// text dispayed on terminal
static char *boot_ref[TERMINAL_LINE_NUMBER] = {"LT:", "RT:", "M :", "    ", "cnx:", "A0:", "B0:", "    ", "0x40", "0x60", "0x85", "0x0F", "    ", "> run", "x ", "y ", " 100%", "    ", "> key"};

// prompt style for char in the font
char scan_font[5] = {'>', 1, 1, 1, 1};

static char *get_terminal_line(uint8_t i) {
    // display text
    if (i < TERMINAL_LINE_NUMBER) {
        return boot_ref[i];
    }

    // blank line every 3 lines
    if (i % 3 == 0) {
        return "     ";
    }

    // display consecutive chars in the font
    i = (i - TERMINAL_LINE_NUMBER) * 4;

    scan_font[1] = i;
    scan_font[2] = i + 1;
    scan_font[3] = i + 2;
    scan_font[4] = i + 3;

    return scan_font;
}

static void draw_startup_terminal(uint8_t f) {
    // ease for printing on screen
    f = f * 2;
    f += (f / 5);

    // scroll text
    uint8_t i_start   = 0;
    uint8_t i_nb_char = f;

    if (f > TERMINAL_LINE_MAX) {
        i_start   = f - TERMINAL_LINE_MAX;
        i_nb_char = TERMINAL_LINE_MAX;
    }

    // display lines
    oled_clear();
    for (uint8_t i = 0; i < i_nb_char; i++) {
        char *s = get_terminal_line(i + i_start);
        oled_write_cursor(0, i, s, false);
    }
}

bool render_boot(void) {
    // end of the boot sequence
    if (anim_boot_current_frame >= NAVI_DURATION + TERMINAL_DURATION + LILY_DURATION) {
        anim_boot_current_frame = 0;
        oled_clear();
        return true;
    }

    if (timer_elapsed(anim_boot_timer) > ANIM_BOOT_FRAME_DURATION) {
        anim_boot_timer = timer_read();
        if (anim_boot_current_frame < NAVI_DURATION) {
            // 55 frames
            draw_startup_navi(anim_boot_current_frame);
        } else {
            if (anim_boot_current_frame >= NAVI_DURATION && anim_boot_current_frame < NAVI_DURATION + TERMINAL_DURATION) {
                // 25
                draw_startup_terminal(anim_boot_current_frame - NAVI_DURATION);
            } else {
                if (anim_boot_current_frame >= NAVI_DURATION + TERMINAL_DURATION) {
                    // 25
                    draw_lily(anim_boot_current_frame - NAVI_DURATION - TERMINAL_DURATION);
                }
            }
        }

        anim_boot_current_frame++;
    }
    return false;
}

void render_halt(void) {
    if (timer_elapsed(anim_halt_timer) > ANIM_HALT_FRAME_DURATION) {
        anim_halt_timer = timer_read();

        // comb glitch for all the screen
        draw_glitch_comb(0, 0, 32, 128, 3, true);

        // random moving blocks of pixels
        for (uint8_t i = 0; i < 6; i++) {
            int     r  = fastrand();
            int     rr = fastrand();
            uint8_t x  = 4 + r % 28;
            uint8_t y  = rr % 128;

            uint8_t w = 7 + r % 20;
            uint8_t h = 3 + rr % 10;
            int     s = (fastrand() % 20) - 10;
            move_block(x, y, w, h, s);
        }
    }
}
