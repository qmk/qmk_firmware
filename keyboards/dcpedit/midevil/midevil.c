// Copyright 2023 Ming-Gih Lam (@dcpedit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp_comms.h"
#include "image/background.qgf.h"
#include "image/animated.qgf.h"

static painter_device_t lcd;
static painter_image_handle_t background;
static painter_image_handle_t animated;

static int animation_state;
static int power_state;
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

void power_on(void) {
    qp_power(lcd, true);
    setPinOutput(LCD_LED_PIN);
    writePinHigh(LCD_LED_PIN);
    start_animation();
    power_state = 1;
}

void power_off(void) {
    stop_animation();
    setPinOutput(LCD_LED_PIN);
    writePinLow(LCD_LED_PIN);
    qp_power(lcd, false);
    power_state = 0;
}

void toggle_power(void) {
    if (power_state == 1) {
        power_off();
    }
    else {
        power_on();
    }
}

void keyboard_post_init_kb(void) {
    background = qp_load_image_mem(gfx_background);
    animated = qp_load_image_mem(gfx_animated);

    // Turn on the LCD
    setPinOutput(LCD_LED_PIN);
    writePinHigh(LCD_LED_PIN);

    // Let the LCD get some power...
    wait_ms(150);
    // Initialise the LCD
    lcd = qp_ili9488_make_spi_device(320, 480, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 4, 0);
    qp_init(lcd, QP_ROTATION_180);

    // Turn on the LCD and clear the display
    qp_power(lcd, true);
    power_state = 1;

    // Draw image
    qp_drawimage(lcd, 0, 0, background);
    start_animation();

    // Turn on the LCD backlight
    setPinOutput(LCD_LED_PIN);
    writePinHigh(LCD_LED_PIN);

    // Allow for user post-init
    keyboard_post_init_user();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_LNG8:
      if (record->event.pressed){
        toggle_animation();
      }
      return false;

    case KC_LNG9:
      if (record->event.pressed){
        toggle_power();
      }
      return false;

    default:
      return true;

  }
  return process_record_user(keycode, record);
}