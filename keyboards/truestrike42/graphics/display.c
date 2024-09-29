// Copyright 2023 Dasky (@daskygit), 2024 Choi Byungyoon (@byungyoonc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "graphics/display.h"
#include "graphics/quinquefive.qff.h"
#include <stdio.h>
#include "he_switch_matrix.h"

static deferred_token         freq_display_task_token;
static deferred_token         stat_display_task_token;
static deferred_token         mods_display_task_token;

static painter_device_t display;
static painter_font_handle_t font;

#define KEYPRESS_BIN_NUM 128
static uint8_t key_press_bin[KEYPRESS_BIN_NUM];
static uint8_t current_bin_number = 0;
static bool last_nkro = false;
static uint8_t last_mod_state = UINT8_MAX;

void freq_graph_display(void);
void display_mod_update(uint8_t mod_state, uint8_t oneshot_mod_state);

uint32_t freq_graph_callback(uint32_t trigger_time, void *cb_arg) {
    freq_graph_display();
    return 1000;
}

uint32_t stat_draw_callback(uint32_t trigger_time, void *cb_arg) {
    display_task_kb();
    return 1000;
}

uint32_t mods_draw_callback(uint32_t trigger_time, void *cb_arg) {
    display_mod_update(get_mods(), get_oneshot_mods());
    return 16;
}

void display_init_kb(void) {
    display = qp_sh1106_make_i2c_device(128, 64, 0x3c);
    qp_init(display, QP_ROTATION_180);
    font    = qp_load_font_mem(font_quinquefive);
    if (!display_init_user()) {
        return;
    }
    for (uint8_t bin = 0; bin < KEYPRESS_BIN_NUM; ++bin) {
        key_press_bin[bin] = 0;
    }
    char buffer[40] = "Powered by QMK Ψ";
    uint16_t width = qp_textwidth(font, buffer);
    uint8_t height = font->line_height + 2;
    qp_drawtext(display, 64-width/2, 33 - height, font, buffer);
    snprintf(buffer, sizeof(buffer), "TrueStrike42");
    width = qp_textwidth(font, buffer);
    qp_drawtext(display, 64-width/2, 33, font, buffer);
    qp_flush(display);
    mods_display_task_token = defer_exec(2000, mods_draw_callback, NULL);
    stat_display_task_token = defer_exec(2000, stat_draw_callback, NULL);
    freq_display_task_token = defer_exec(2000, freq_graph_callback, NULL);
}

__attribute__((weak)) bool display_init_user(void) {
    return true;
}

void freq_graph_display(void) {
    uint8_t freq_graph_height = 28;
    uint8_t line_height = MIN(key_press_bin[current_bin_number], freq_graph_height);
    qp_line(display, current_bin_number, 61, current_bin_number, 61 - line_height, 0, 0, 255);
    qp_line(display, current_bin_number, 63, current_bin_number, 62, 0, 0, 0);
    uint8_t next_bin = current_bin_number + 1;
    if (KEYPRESS_BIN_NUM <= next_bin) {
        next_bin = 0;
    }
    qp_line(display, next_bin, 61-freq_graph_height, next_bin, 61, 0, 0, 0);
    qp_line(display, next_bin, 63, next_bin, 62, 0, 0, 255);
    qp_flush(display);

    current_bin_number++;
    if (KEYPRESS_BIN_NUM <= current_bin_number) {
        current_bin_number = 0;
    }
    key_press_bin[current_bin_number] = 0;

    return;
}

void display_layer_state(layer_state_t state) {
    uint16_t highest_layer = get_highest_layer(state);

    char buffer[5] = {0};

    snprintf(buffer, sizeof(buffer), "%4d", highest_layer);
    qp_drawtext(display, 100, 14, font, buffer);
}

void display_led_state(led_t state) {
    qp_rect(display, 2, 2, 10, 10, 0, 0, 255, state.num_lock);
    if (!state.num_lock) {
        qp_rect(display, 3, 3, 9, 9, 0, 0, 0, true);
    }
    qp_drawtext_recolor(display, 4, 4, font, "N", 0, 0, state.num_lock ? 0 : 255, 0, 0, state.num_lock ? 255 : 0);
    qp_rect(display, 13, 2, 21, 10, 0, 0, 255, state.caps_lock);
    if (!state.caps_lock) {
        qp_rect(display, 14, 3, 20, 9, 0, 0, 0, true);
    }
    qp_drawtext_recolor(display, 15, 4, font, "C", 0, 0, state.caps_lock ? 0 : 255, 0, 0, state.caps_lock ? 255 : 0);
    qp_rect(display, 24, 2, 32, 10, 0, 0, 255, state.scroll_lock);
    if (!state.scroll_lock) {
        qp_rect(display, 25, 3, 31, 9, 0, 0, 0, true);
    }
    qp_drawtext_recolor(display, 26, 4, font, "S", 0, 0, state.scroll_lock ? 0 : 255, 0, 0, state.scroll_lock ? 255 : 0);
}

void display_nkro_state(bool nkro) {
    qp_rect(display, 35, 2, 61, 10, 0, 0, 255, nkro);
    if (!nkro) {
        qp_rect(display, 36, 3, 60, 9, 0, 0, 0, true);
    }
    qp_drawtext_recolor(display, 37, 4, font, "NKRO", 0, 0, nkro ? 0 : 255, 0, 0, nkro ? 255 : 0);
}

void display_mod_state(uint8_t mod_state, uint8_t oneshot_mod_state) {
    if (mod_state & MOD_MASK_CTRL) {
        qp_drawtext(display, 86, 4, font, "C");
    } else {
        qp_drawtext(display, 86, 4, font, " ");
    }
    if (mod_state & MOD_MASK_ALT) {
        qp_drawtext(display, 97, 4, font, "A");
    } else {
        qp_drawtext(display, 97, 4, font, " ");
    }
    if (mod_state & MOD_MASK_GUI) {
        qp_drawtext(display, 108, 4, font, "G");
    } else {
        qp_drawtext(display, 108, 4, font, " ");
    }
    if (mod_state & MOD_MASK_SHIFT) {
        qp_drawtext(display, 119, 4, font, "S");
    } else {
        qp_drawtext(display, 119, 4, font, " ");
    }
}

void display_task_kb(void) {
    if (!display_task_user()) {
        return;
    }

    static bool     first_draw             = true;
    static uint32_t last_scan_rate         = 0;
    static uint8_t  last_actuation_mode    = UINT8_MAX;
    bool diff = false;

    if (first_draw) {
        qp_clear(display);
        qp_drawtext(display, 4, 14, font, "Active Layer  =");
        qp_drawtext(display, 4, 21, font, "Scan Rate     =");
        qp_drawtext(display, 4, 28, font, "Rapid Trigger =");
        display_led_state(host_keyboard_led_state());
        display_layer_state(layer_state);
        display_nkro_state(keymap_config.nkro);
        last_nkro = keymap_config.nkro;
        first_draw = false;
        diff = true;
    }

    char buffer[5] = {0};

    uint32_t scan_rate = get_matrix_scan_rate();
    if (last_scan_rate != scan_rate) {
        snprintf(buffer, sizeof(buffer), "%4ld", scan_rate);
        //int16_t width = qp_textwidth(font, buffer);
        qp_drawtext(display, 100, 21, font, buffer);
        last_scan_rate = scan_rate;
        diff = true;
    }

    if (last_actuation_mode != he_config.actuation_mode) {
        if (he_config.actuation_mode == 0) {
            qp_drawtext(display, 106, 28, font, "OFF");
        } else {
            qp_drawtext(display, 106, 28, font, " ON");
        }
        last_actuation_mode = he_config.actuation_mode;
        diff = true;
    }

    if (diff) {
        qp_flush(display);
    }
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);
    display_layer_state(state);
    qp_flush(display);
    return state;
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        display_led_state(led_state);
        qp_flush(display);
    }
    return res;
}

__attribute__((weak)) bool display_task_user(void) {
    return true;
}

void display_key_counter(void) {
    key_press_bin[current_bin_number]++;
}

void display_mod_update(uint8_t mod_state, uint8_t oneshot_mod_state) {
    bool diff = false;
    if (last_mod_state != mod_state) {
        display_mod_state(mod_state, oneshot_mod_state);
        diff = true;
        last_mod_state = mod_state;
    }
    if (last_nkro != keymap_config.nkro) {
        display_nkro_state(keymap_config.nkro);
        diff = true;
        last_nkro = keymap_config.nkro;
    }
    if (diff) {
        qp_flush(display);
    }
}
