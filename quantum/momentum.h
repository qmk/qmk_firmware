#ifndef MOMENTUM_H
#define MOMENTUM_H

#include <stdint.h>
#include "timer.h"

void momentum_accelerate(void);
void momentum_decay_task(void);
uint8_t match_momentum(uint8_t minValue, uint8_t maxValue);

#endif