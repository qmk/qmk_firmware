#include "xelus87.h"

void led_init_ports(void) {
    setPinOutput(CAPS_LOCK_LED_PIN);
    setPinOutput(SCROLL_LOCK_LED_PIN);
}
