#include "quantum.h"
#include "led.h"

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    // Disable status LED on KB, enable status LED on Teensy (KB_STATUS = !TEENSY_STATUS)
    gpio_set_pin_output(D6);
    gpio_write_pin_high(D6);

    matrix_init_user();
};

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(D0, !led_state.caps_lock);
        writePin(D1, !led_state.num_lock);
        writePin(C6, !led_state.scroll_lock);

    }
    return res;
}