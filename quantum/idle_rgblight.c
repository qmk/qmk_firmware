#include "quantum.h"
#include "idle_rgblight.h"
#include "timer.h"
#include <print.h>
#include <stdio.h>

bool timed_out = false;
uint16_t idle_timer;
uint8_t minute_counter = 0;

bool is_rgblight_enabled() {
  return rgblight_get_val() > 0;
}

void idle_rgblight_setup(void) {
  idle_timer = timer_read();
}

void idle_rgblight_press(void) {
  if (timed_out) {
    timed_out = false;
    rgblight_enable();
  }
  idle_timer = timer_read();
  minute_counter = 0;
}

void matrix_scan_rgblight_idle(void) {
  if (!timed_out && is_rgblight_enabled()) {
    printf("%d timeout", timed_out);
    printf("%d isrgblightenabled", is_rgblight_enabled());
    if (timer_elapsed(idle_timer) >= 1000) {
      minute_counter++;
      idle_timer = timer_read();
    }
    if (minute_counter >= IDLE_RGBLIGHT_TIMEOUT) {
      timed_out = true;
      rgblight_disable();
      minute_counter = 0;
    }
  }
}
