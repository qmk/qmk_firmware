#include "ch.h"

#include "timer.h"

static systime_t last_systime = 0;
static systime_t overflow = 0;
static uint32_t current_time_ms = 0;

void timer_init(void) {
  timer_clear();
}

void timer_clear(void) {
  last_systime = chVTGetSystemTime();
  overflow = 0;
  current_time_ms = 0;
}

uint16_t timer_read(void) {
  return (uint16_t)timer_read32();
}

uint32_t timer_read32(void) {
  // Note: We assume that the timer update is called at least once betweeen every wrap around of the system time
  systime_t current_systime = chVTGetSystemTime();
  systime_t elapsed = current_systime - last_systime + overflow;
  uint32_t elapsed_ms = ST2MS(elapsed);
  current_time_ms += elapsed_ms;
  overflow = elapsed - MS2ST(elapsed_ms);
  last_systime = current_systime;

  return current_time_ms;
}

uint16_t timer_elapsed(uint16_t last) {
  return timer_read() - last;
}

uint32_t timer_elapsed32(uint32_t last) {
  return timer_read32() - last;
}
