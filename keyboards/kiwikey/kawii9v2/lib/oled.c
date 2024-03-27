// Copyright 2023 KiwiKey
// SPDX-License-Identifier: GPL-2.0-or-later
 
#include "quantum.h"
#include "oled_custom_api.h"

#ifdef OLED_ENABLE

#define LOGO_WIDTH  24
#define LOGO_HEIGHT 24
static const char PROGMEM qmk_logo[LOGO_HEIGHT/8][LOGO_WIDTH] = {
    { 0x81,0x82,0x83,0x84 },
    { 0xa1,0xa2,0xa3,0xa4 },
    { 0xc1,0xc2,0xc3,0xc4 }
};
static void render_qmk_logo(uint8_t col, uint8_t row) {
    for (uint8_t i = 0; i < LOGO_HEIGHT/8; i++) {
        oled_set_cursor(col, row++);
        oled_write_P(qmk_logo[i], false);
    }
}

static uint32_t key_timer = 0;
static uint8_t rgb_val = 0;

// Sub UI is the bottom half of OLED screen, shows WPM chart, RGB infos,...
// sub_ui_mode = 0 : WPM graph
//               1 : RGB control
//               2 : Media control (to do)
#define SUB_UI_TIMEOUT 2000 // ms
static char sub_ui_mode = 0;

// Configuration for Key Matrix
#define MATRIX_DISPLAY_X    107
#define MATRIX_DISPLAY_Y    11
#define MATRIX_DISPLAY_SIZE 22
#define KEY_SIZE            4
#define KEY_SPACING         3

// Configuration for WPM Graph
#define GRAPH_ZERO_X           25  // This is zero origin
#define GRAPH_ZERO_Y           63  // of the WPM graph
#define GRAPH_WIDTH            100
#define GRAPH_HEIGHT           28
#define GRAPH_REFRESH_INTERVAL 100 // ms
#define GRAPH_LINE_THICKNESS   1
float max_wpm = 100.0;
uint16_t graph_timer = 0;

// RGB Matrix naming, copy from @tzarc
#if defined(RGB_MATRIX_ENABLE)
#include <rgb_matrix.h>

#if defined(RGB_MATRIX_EFFECT)
#    undef RGB_MATRIX_EFFECT
#endif // defined(RGB_MATRIX_EFFECT)
#define RGB_MATRIX_EFFECT(x) RGB_MATRIX_EFFECT_##x,

enum {
    RGB_MATRIX_EFFECT_NONE,
#include "rgb_matrix_effects.inc"
#undef RGB_MATRIX_EFFECT
#ifdef RGB_MATRIX_CUSTOM_KB
#    include "rgb_matrix_kb.inc"
#endif
#ifdef RGB_MATRIX_CUSTOM_USER
#    include "rgb_matrix_user.inc"
#endif
};

#define RGB_MATRIX_EFFECT(x)    \
    case RGB_MATRIX_EFFECT_##x: \
        return #x;
const char* rgb_matrix_name(uint8_t effect) {
    switch (effect) {
        case RGB_MATRIX_EFFECT_NONE:
            return "NONE";
#include "rgb_matrix_effects.inc"
#undef RGB_MATRIX_EFFECT
#ifdef RGB_MATRIX_CUSTOM_KB
#    include "rgb_matrix_kb.inc"
#endif
#ifdef RGB_MATRIX_CUSTOM_USER
#    include "rgb_matrix_user.inc"
#endif
        default:
            return "UNKNOWN";
    }
}
#endif // defined(RGB_MATRIX_ENABLE)

void render_matrix(void) {
    for (uint8_t x = 0; x < MATRIX_ROWS-2; x++) {
        for (uint8_t y = 0; y < MATRIX_COLS-2; y++) {
            bool on = (matrix_get_row(x) & (1 << y)) > 0; // The matrix position [x,y] is being pressed
            draw_rect( MATRIX_DISPLAY_X + y*(KEY_SIZE+KEY_SPACING), // X - horizontal position of key
                       MATRIX_DISPLAY_Y + x*(KEY_SIZE+KEY_SPACING), // Y - vertical position of key
                       KEY_SIZE,
                       KEY_SIZE,
                       on);
        }
    }
}

void render_wpm_graph(void) {
    uint8_t curr_wpm = (get_current_wpm() < max_wpm ? get_current_wpm() : max_wpm);
    if (timer_elapsed(graph_timer) > GRAPH_REFRESH_INTERVAL) {
        uint8_t graph_pointer = (curr_wpm / max_wpm) * GRAPH_HEIGHT;
        draw_line_h(GRAPH_ZERO_X + 1, GRAPH_ZERO_Y - graph_pointer, GRAPH_LINE_THICKNESS, true);
        for (char i = 0; i < graph_pointer; i++) {
            draw_line_h(GRAPH_ZERO_X + 1, GRAPH_ZERO_Y - i, GRAPH_LINE_THICKNESS, true);
        }
        for (char i = 0; i < GRAPH_LINE_THICKNESS; i++) {
            oled_pan_area(GRAPH_ZERO_X,
                          GRAPH_ZERO_X + GRAPH_WIDTH,
                          (GRAPH_ZERO_Y + 1 - GRAPH_HEIGHT) / 8,
                          (GRAPH_ZERO_Y + 1) / 8 - 1,
                          false);
        }
        graph_timer = timer_read();
    }
}

void ui_clear(void) {
    oled_set_cursor(0, 4);
    oled_advance_page(true);
    oled_advance_page(true);
    oled_advance_page(true);
    oled_advance_page(true);
}

void render_ui_frame(void) {
    oled_clear();
    oled_advance_page(false);
    oled_write_ln_P(PSTR("LAYER    WPM"), false);
    oled_advance_page(false);
    oled_write_ln_P(PSTR("RGB"), false);
    oled_advance_page(false);
    oled_advance_page(false);
    oled_advance_page(false);
    // Outline for layer number
    draw_line_h(35, 7, 7, true);
    draw_line_v(34, 8, 7, true);
    draw_line_v(35, 8, 8, true);
    draw_line_v(42, 8, 7, true);
    // Outline for RGB mode number
    draw_line_h(23, 23, 19, true);
    draw_line_v(22, 24, 7, true);
    draw_line_v(23, 24, 8, true);
    draw_line_v(42, 24, 7, true);
    // Outline for Key Matrix
    draw_line_h(MATRIX_DISPLAY_X -2, MATRIX_DISPLAY_Y -3, MATRIX_DISPLAY_SIZE, true);
    draw_line_h(MATRIX_DISPLAY_X -2, MATRIX_DISPLAY_Y -2 + MATRIX_DISPLAY_SIZE, MATRIX_DISPLAY_SIZE, true);
    draw_line_v(MATRIX_DISPLAY_X -3, MATRIX_DISPLAY_Y -2, MATRIX_DISPLAY_SIZE, true);
    draw_line_v(MATRIX_DISPLAY_X -2 + MATRIX_DISPLAY_SIZE, MATRIX_DISPLAY_Y-2, MATRIX_DISPLAY_SIZE, true);
}

void render_ui_rgbcontrol(void) {
    oled_set_cursor(0, 5);
    oled_write_P(PSTR("----< Lighting >-----"), false);
    // RGB mode
    oled_set_cursor(0, 6);
    oled_write_ln(rgb_matrix_name(rgb_matrix_get_mode()), false);
    // RGB brightness bar
    oled_set_cursor(0, 7);
    oled_write_char((rgb_val == 0) ? 0x07 : 0x9D, false);
    for (uint8_t i = 0; i < 20; i++) {
        oled_write_char(0x20, i*5 < rgb_val);
    }
}

void render_stats(void) {
    // Current layer
    oled_set_cursor(6, 1);
    oled_write_char(get_highest_layer(layer_state) + 0x30, true);
    // Current WPM
    oled_set_cursor(13, 1);
    oled_write(get_u8_str(get_current_wpm(), '0'), false);
    // Show current RGB mode (#__)
    oled_set_cursor(4,3);
    if (rgb_matrix_is_enabled()) {
        oled_write_P(PSTR("#"), true);
        oled_write_char(rgb_matrix_get_mode()/10 + 0x30, true);
        oled_write_char(rgb_matrix_get_mode()%10 + 0x30, true);
    }
    else {
        oled_write_P(PSTR("OFF"), true);
    }
    // RGB brightness (percentage %)
    oled_set_cursor(9, 3);
    rgb_val = (rgb_matrix_is_enabled() ? rgb_matrix_get_val()*100/RGB_MATRIX_MAXIMUM_BRIGHTNESS : 0);
    if (rgb_matrix_is_enabled()) {
        oled_write_char((rgb_val == 0) ? 0x07 : 0x9D, false);
        oled_write(get_u8_str(rgb_val, ' '), false);
        oled_write_char(0x25, false); // %
    }
    else {
        oled_write_P(PSTR("-----"), false);
    }
}

void keyboard_post_init_kb(void) {
    render_ui_frame();
    keyboard_post_init_user();
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    render_stats();
    switch (sub_ui_mode) {
        case 0:
            render_wpm_graph();
            render_qmk_logo(0, 5);
            break;
        case 1:
            render_ui_rgbcontrol();
            break;
    }
    if ((sub_ui_mode != 0) && (timer_elapsed32(key_timer) > SUB_UI_TIMEOUT)) { // If timeout, back to default UI
        sub_ui_mode = 0;
        ui_clear();
    }
    if (timer_elapsed32(key_timer) > OLED_TIMEOUT) {
        oled_off();
    }
    return false;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_LIGHTING ... QK_LIGHTING_MAX:
            sub_ui_mode = 1;
            ui_clear();
            break;
        /** TODO 
        case KC_AUDIO_MUTE ... KC_MEDIA_EJECT:
            sub_ui_mode = 2;
            ui_clear();
            break;
        ***/
        default:
            break;
    }
    render_matrix();
    key_timer = timer_read32();
    return true;
}

#endif // defined(OLED_ENABLE)
