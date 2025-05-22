#include "duck_led.h"
#include "wait.h"

void show(void) {
  wait_us((RES / 1000UL) + 1);
}
