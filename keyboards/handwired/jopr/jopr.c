#include "jopr.h"
void matrix_init_kb(void) {
    led_init_ports();
};

void led_init_ports(void) {
    setPinOutput(F0);
    setPinOutput(F1);
    setPinOutput(F4);
}
