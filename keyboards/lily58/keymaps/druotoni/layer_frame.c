// Copyright 2021 Nicolas Druoton (druotoni)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "gui_state.h"
#include "layer_frame.h"
#include "draw_helper.h"

#define ANIM_LAYER_FRAME_DURATION 2
#define ANIM_LAYER_FRAME_MAX 7

// current layer
uint8_t current_layer = _QWERTY;

// layer animation stuff
uint16_t anim_layer_frame_timer  = 0;
uint8_t  current_layer_frame     = ANIM_LAYER_FRAME_MAX;
uint8_t  layer_frame_destination = ANIM_LAYER_FRAME_MAX;

// layer name for display
const char*        layer_name;
static const char* layer_ref[3] = {LAYER_NAME_0, LAYER_NAME_1, LAYER_NAME_2};

void update_layer_frame(layer_state_t state) {
    // reset timer
    anim_layer_frame_timer = timer_read();

    // direction for animation base on layer selected
    current_layer = get_highest_layer(state);
    if (current_layer == _QWERTY) {
        layer_frame_destination = 0;
    } else {
        layer_frame_destination = ANIM_LAYER_FRAME_MAX;
    }
}

static void draw_black_screen(void) {
    // clean frame center
    draw_rectangle_fill(3, 42, 26, 20, false);
    drawline_hr(17, 62, 12, false);
}

void render_gears(void) {
    // 64 bytes, 8x8 font, 8 characters, 32x16 image, 4 columns, 2 rows
    static const char PROGMEM raw_logo[] = {
        0, 6, 6, 54, 118, 96, 230, 192, 192, 128, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 18, 226, 2, 18, 226, 2, 18, 226, 2, 1, 0, 0, 0, 0, 0, 128, 128, 128, 185, 187, 187, 131, 128, 184, 128, 128, 128, 128, 128, 128, 128, 128, 128, 191, 128, 128, 191, 128, 128, 191, 128, 0,
    };

    // extra line for complete the gui
    oled_write_raw_P_cursor(0, 8, raw_logo, sizeof(raw_logo));
}

void render_layer_frame(gui_state_t t) {
    // 96 bytes, 8x8 font, 12 characters, 32x24 image, 4 columns, 3 rows
    static const char PROGMEM raw_logo[] = {
        62, 1, 0, 56, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 124, 248, 241, 226, 4, 8, 240, 0, 28, 28, 28, 0, 0, 127, 4, 8, 16, 127, 0, 124, 18, 17, 18, 124, 0, 31, 32, 64, 32, 31, 0, 0, 0, 0, 255, 255, 0, 0, 255, 62, 64, 64, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 142, 30, 62, 126, 126, 70, 70, 126, 70, 70, 126, 70, 70, 127, 127, 0, 0, 255,
    };
    oled_write_raw_P_cursor(0, 5, raw_logo, sizeof(raw_logo));

    // extra line for complete the gui
    drawline_hr(2, 39, 25, 1);

    if (current_layer_frame != layer_frame_destination) {
        if (timer_elapsed(anim_layer_frame_timer) > ANIM_LAYER_FRAME_DURATION) {
            anim_layer_frame_timer = timer_read();

            if (layer_frame_destination > current_layer_frame) {
                current_layer_frame++;
            } else {
                current_layer_frame--;
            }
        }

        // black screen
        draw_black_screen();

        // gradient animation on layer selection
        draw_gradient(3, 42, current_layer_frame * 4, 10, 0, 255, 7);
        draw_gradient(3 + (27 - current_layer_frame * 4), 57, current_layer_frame * 4, 6, 255, 0, 7);

        drawline_hr(3, 46, 22, false);
        drawline_hr(3, 47, 23, false);

        draw_rectangle_fill(3, 55, 24, 2, false);
        draw_rectangle_fill(24, 48, 3, 7, false);

        draw_rectangle_fill(3, 60, 12, 2, false);
        oled_write_pixel(15, 61, false);
        drawline_hr(14, 62, 3, false);
        drawline_hr(14, 62, 3, false);
        drawline_hr(3, 62, 11, true);
    }

    // get current layer name
    layer_name = layer_ref[current_layer];

    // gui on pause : no layer name on screen
    if (t == _IDLE || t == _SLEEP || t == _WAKINGUP) {
        layer_name = "   ";
    }

    // display layer name in the frame
    oled_write_cursor(1, 6, layer_name, false);
}
