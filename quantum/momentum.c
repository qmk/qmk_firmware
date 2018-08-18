#include "momentum.h"

#ifndef MIN
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif
#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif

#define TYPING_SPEED_MAX_VALUE 200
uint8_t typing_speed = 0;

void momentum_accelerate() {
    if (typing_speed < TYPING_SPEED_MAX_VALUE) typing_speed += (TYPING_SPEED_MAX_VALUE / 100);
}

void momentum_decay_task() {
  static uint16_t decay_timer = 0;

  if (timer_elapsed(decay_timer) > 500 || decay_timer == 0) {
    if (typing_speed > 0) typing_speed -= 1;
    //Decay a little faster at half of max speed
    if (typing_speed > TYPING_SPEED_MAX_VALUE / 2) typing_speed -= 1;
    //Decay even faster at 3/4 of max speed
    if (typing_speed > TYPING_SPEED_MAX_VALUE / 4 * 3) typing_speed -= 3;
    decay_timer = timer_read();
  }
}

uint8_t match_momentum(uint8_t minValue, uint8_t maxValue) {
  return MAX(minValue, maxValue - (maxValue - minValue) * ((float)typing_speed / TYPING_SPEED_MAX_VALUE));
}