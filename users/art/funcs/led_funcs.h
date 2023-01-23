// Copyright 2022 Artjoms Rizihs (@artjomsR)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include QMK_KEYBOARD_H

#define NUM_LED_ON 4
#define SCROLL_LED_ON 1
#define NUM_SCROLL_LED_ON 5
#define ALL_OFF 0

#define BLINKING_INTERVAL 25

void toggle_leds(int leds);
bool led_update_user(led_t led_state);
void blink_leds(int leds);
void led_show_variable_status(bool value);