#include <avr/io.h>
#include <util/delay.h>
#include "ducklib.h"

void show(void) {
  _delay_us((RES / 1000UL) + 1);
}


