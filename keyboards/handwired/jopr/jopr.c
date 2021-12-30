#include "jopr.h"

void led_init_ports(void) {
    setPinOutput(F0);
    setPinOutput(F1);
    setPinOutput(F4);
}