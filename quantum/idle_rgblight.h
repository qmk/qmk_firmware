#ifndef IDLE_RGBLIGHT_H
#define IDLE_RGBLIGHT_H

#ifndef IDLE_RGBLIGHT_TIMEOUT
  #define IDLE_RGBLIGHT_TIMEOUT 15 // in minutes
#endif

#include <stdint.h>
#include <stdbool.h>

void idle_rgblight_init(void);
void idle_rgblight_press(void);
void idle_rgblight_matrix_scan(void);
bool idle_rgblight_timeout;

#endif
