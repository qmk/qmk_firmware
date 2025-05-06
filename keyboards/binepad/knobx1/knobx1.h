// (c) 2025 Binepad (@binpad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

// PCB has a 1x2 matrix. Set the ROW0 to ground for faster direct pin access.
#define ROW0_PIN B8

#define IND1_LED A6
#define IND2_LED A5
#define IND3_LED A4
#define IND4_LED A3

// clang-format off
enum x1_keycodes {
    X1_LAYER_SELECTOR_UP = QK_USER,
    X1_LAYER_SELECTOR_DOWN
};
// clang-format on

#define X1_LYRU X1_LAYER_SELECTOR_UP
#define X1_LYRD X1_LAYER_SELECTOR_DOWN

// clang-format off
static inline void x1_led_1(bool on) { gpio_write_pin(IND1_LED, on); }
static inline void x1_led_2(bool on) { gpio_write_pin(IND2_LED, on); }
static inline void x1_led_3(bool on) { gpio_write_pin(IND3_LED, on); }
static inline void x1_led_4(bool on) { gpio_write_pin(IND4_LED, on); }
static inline void x1_led_1_on(void) { gpio_write_pin_high(IND1_LED); }
static inline void x1_led_2_on(void) { gpio_write_pin_high(IND2_LED); }
static inline void x1_led_3_on(void) { gpio_write_pin_high(IND3_LED); }
static inline void x1_led_4_on(void) { gpio_write_pin_high(IND4_LED); }
static inline void x1_led_1_off(void) { gpio_write_pin_low(IND1_LED); }
static inline void x1_led_2_off(void) { gpio_write_pin_low(IND2_LED); }
static inline void x1_led_3_off(void) { gpio_write_pin_low(IND3_LED); }
static inline void x1_led_4_off(void) { gpio_write_pin_low(IND4_LED); }
// clang-format on

static inline void x1_layer_led(uint8_t lyr) {
    gpio_write_pin(IND1_LED, lyr >= 0);
    gpio_write_pin(IND2_LED, lyr >= 1);
    gpio_write_pin(IND3_LED, lyr >= 2);
    gpio_write_pin(IND4_LED, lyr >= 3);
}

bool process_x1_layer_up(keyrecord_t *record);
bool process_x1_layer_down(keyrecord_t *record);
