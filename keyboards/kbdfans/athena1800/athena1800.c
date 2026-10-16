// Copyright 2026 Laszlo Toth (@laszloth)
// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Single-core GC9107 status display (upstream Quantum Painter). Static
 * content, redrawn only when layer / lock state changes - no dual-core,
 * no GIF engine.
 */
#include "quantum.h"
#include "qp.h"

/* active-low LCD power enable (high = off, low = on) */
#define LCD_PWR_PIN GP17

static painter_device_t lcd;

void keyboard_pre_init_kb(void) {
    /*
     * Power-cycle the panel, then bring it up. Keep the delays short:
     * this is a single-core build, so a long blocking wait here stalls
     * key scanning at boot. (The original fw uses 1s/200ms, but it runs
     * the display on core1.) Must run before the WS2812 driver's first
     * write: the LCD rail (GP17) also feeds the LED chain, else the last
     * 2 LEDs go dark and the rest corrupts.
     */
    gpio_set_pin_output(LCD_PWR_PIN);
    gpio_write_pin_high(LCD_PWR_PIN); /* off / reset */
    wait_ms(120);
    gpio_write_pin_low(LCD_PWR_PIN); /* on */
    wait_ms(120);
    keyboard_pre_init_user();
}

void keyboard_post_init_kb(void) {
    /*
     * The rail was already power-cycled in keyboard_pre_init_kb; just
     * bring the panel up. qp_init performs the GC9107's RST-pin reset.
     */
    lcd = qp_gc9107_make_spi_device(LCD_WIDTH, LCD_HEIGHT, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, LCD_SPI_DIVISOR, LCD_SPI_MODE);
    qp_init(lcd, LCD_ROTATION);
    qp_set_viewport_offsets(lcd, LCD_OFFSET_X, LCD_OFFSET_Y);
    qp_power(lcd, true);
    qp_rect(lcd, 0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1, HSV_BLACK, true);

    keyboard_post_init_user();
}

__attribute__((weak)) void draw_ui(void) {
    static uint8_t prev  = 0xFF;
    led_t          leds  = host_keyboard_led_state();
    uint8_t        layer = get_highest_layer(layer_state);
    uint8_t        snap  = (layer & 0x0F) | (leds.caps_lock ? 0x10 : 0) | (leds.num_lock ? 0x20 : 0);

    if (snap != prev) {
        prev = snap;
        /*
         * Always filled; brightness encodes state (bright = on, dim =
         * off) so a toggle fully repaints the bar instead of leaving the
         * previous fill behind.
         */
        /* Caps (red) */
        qp_rect(lcd, 0, 0, 63, 31, 0, 255, leds.caps_lock ? 255 : 24, true);
        /* Num (green) */
        qp_rect(lcd, 64, 0, 127, 31, 85, 255, leds.num_lock ? 255 : 24, true);
        /* Layer bar (bottom), hue scales with active layer. */
        qp_rect(lcd, 0, 96, 127, 127, (uint8_t)(layer * 80), 255, 200, true);
        qp_flush(lcd);
    }
}

void housekeeping_task_kb(void) {
    draw_ui();
}
