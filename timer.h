#ifndef TIMER_H
#define TIMER_H 1

#include <stdint.h>

#define TIMER_DIFF(a, b) ((a) >= (b) ?  (a) - (b) : UINT16_MAX - (b) + (a))


extern uint16_t timer_count;


void timer_init(void);
void timer_clear(void);
uint16_t timer_read(void);
uint16_t timer_elapsed(uint16_t last);

#endif
