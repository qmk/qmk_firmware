#include <avr/io.h>
#include "duck_led.h"
#include "quantum.h"

void show(void) {
  wait_us((RES / 1000UL) + 1);
}
