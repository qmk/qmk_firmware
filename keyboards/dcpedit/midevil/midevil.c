// Copyright 2023 Ming-Gih Lam (@dcpedit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp_comms.h"
#include "image/background.qgf.h"
#include "image/animated.qgf.h"

static painter_device_t lcd;
static painter_image_handle_t background;
static painter_image_handle_t animated;

static int animation_state;
static deferred_token my_anim;

void start_animation(void) {
    my_anim = qp_animate(lcd, 116, 194, animated);
    animation_state = 1;
}

void stop_animation(void) {
    qp_stop_animation(my_anim);
    animation_state = 0;
}

void toggle_animation(void) {
    if (animation_state == 1) {
        stop_animation();
    }
    else {
        start_animation();
    }
}

__attribute__((weak)) void draw_ui_init_user(void) {
    start_animation();
}

void keyboard_post_init_kb(void) {
    background = qp_load_image_mem(gfx_background);
    animated = qp_load_image_mem(gfx_animated);
    
    // Give the LCD some time to get some power
    wait_ms(150);
    
    // Initialise the LCD
    lcd = qp_ili9488_make_spi_device(320, 480, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 4, 0);
    qp_init(lcd, QP_ROTATION_180);
    // Turn on the LCD
    qp_power(lcd, true);
    // Draw image
    qp_drawimage(lcd, 0, 0, background);
    draw_ui_init_user();
    
    keyboard_post_init_user();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LNG8:
            if (record->event.pressed){
                toggle_animation();
            }
            return false;

        default:
            return true;
    }
    return process_record_user(keycode, record);
}