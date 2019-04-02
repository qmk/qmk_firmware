#include <avr/io.h>
#include <util/delay.h>
#include "duck_led.h"

void show(void) {
  wait_us((RES / 1000UL) + 1);
}
