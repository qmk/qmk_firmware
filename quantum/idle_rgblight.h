#ifndef IDLE_RGBLIGHT_H
#define IDLE_RGBLIGHT_H

#ifndef IDLE_RGBLIGHT_TIMEOUT
  #define IDLE_RGBLIGHT_TIMEOUT 1 // in minutes
#endif

#include <stdint.h>
#include <stdbool.h>

void idle_rgblight_setup(void);
void idle_rgblight_press(void);
bool is_rgblight_enabled(void);
void matrix_scan_rgblight_idle(void);
bool timed_out;

#endif
