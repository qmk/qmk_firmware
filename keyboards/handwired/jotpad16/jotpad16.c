#include "quantum.h"

void keyboard_pre_init_kb(void) {
    gpio_set_pin_output(JOTPAD16_LED1);
    gpio_set_pin_output(JOTPAD16_LED2);
    
    keyboard_pre_init_user();
}
