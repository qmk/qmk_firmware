#include "quantum.h"
#include "rgblight.h"
#include "timer.h"
#include "idle_rgblight.h"

bool idle_rgblight_timeout = false;
uint16_t idle_timer;
uint8_t minute_counter = 0;
extern rgblight_config_t rgblight_config;

void idle_rgblight_init(void) {
  idle_timer = timer_read();
}

void idle_rgblight_press(void) {
  if (idle_rgblight_timeout) {
    idle_rgblight_timeout = false;
    rgblight_enable();
  }
  idle_timer = timer_read();
  minute_counter = 0;
}

void idle_rgblight_matrix_scan(void) {
  if (!idle_rgblight_timeout && rgblight_config.enable) {
    if (timer_elapsed(idle_timer) >= 60000) {
      minute_counter++;
      idle_timer = timer_read();
    }
    if (minute_counter >= IDLE_RGBLIGHT_TIMEOUT) {
      idle_rgblight_timeout = true;
      rgblight_disable();
      minute_counter = 0;
      idle_timer = 0;
    }
  }
}
