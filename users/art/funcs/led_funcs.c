// Copyright 2022 Artjoms Rizihs (@artjomsR)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "led_funcs.h"

bool hw_caps_on;

__attribute__ ((weak)) void num_led_on(void) {}
__attribute__ ((weak)) void num_led_off(void) {}
__attribute__ ((weak)) void caps_led_on(void) {}
__attribute__ ((weak)) void caps_led_off(void) {}
__attribute__ ((weak)) void scroll_led_on(void) {}
__attribute__ ((weak)) void scroll_led_off(void) {}

void toggle_leds(int leds) {
  if (NUM_LED_ON & leds) {
    num_led_on();
  } else {
    num_led_off();
  }
  if (SCROLL_LED_ON & leds) {
    scroll_led_on();
  } else {
    scroll_led_off();
  }
}

bool led_update_user(led_t led_state) {
  // only use caps LED - ignore Num & Scroll
  if (led_state.caps_lock) {
    caps_led_on();
  } else {
    caps_led_off();
  }

  hw_caps_on = led_state.caps_lock;
  return false; // 'false' prevents led_update_kb from firing
}

void blink_leds(int leds) {
  for (int i = 0; i < 3; i++) {
    toggle_leds(leds);
    wait_ms(BLINKING_INTERVAL);
    toggle_leds(ALL_OFF);
    wait_ms(BLINKING_INTERVAL);
  }
}

void led_show_variable_status(bool value) {
  if (value) {
    blink_leds(NUM_LED_ON);
  } else {
    blink_leds(SCROLL_LED_ON);
  }
}