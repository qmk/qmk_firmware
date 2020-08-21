#include "otd_plus.h"

void keyboard_pre_init_kb(void) {
    led_init_ports();
    keyboard_pre_init_user();
}
void led_init_ports(void) {
    setPinOutput(CAPS_LOCK_LED_PIN);
    setPinOutput(SCROLL_LOCK_LED_PIN);
}


