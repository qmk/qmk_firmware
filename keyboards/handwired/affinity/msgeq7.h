#include <avr/io.h>
#include <util/delay.h>
#include "analog.h"

#ifndef NOISE_FLOOR
#define NOISE_FLOOR 50
#endif

void msgeq7_init (void);
void msgeq7_read (int *buf);
