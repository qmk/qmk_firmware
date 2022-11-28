#include "retro_refit.h"
#include "led.h"

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    // Disable status LED on KB, enable status LED on Teensy (KB_STATUS = !TEENSY_STATUS)
    DDRD |= (1<<6);
    PORTD |= (1<<6);

    matrix_init_user();
};

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        if (led_state.caps_lock) {
            // output low
            DDRD |= (1<<0);
            PORTD &= ~(1<<0);
        } else {
            // Hi-Z
            DDRD &= ~(1<<0);
            PORTD &= ~(1<<0);
        }
        if (led_state.num_lock) {
            // output low
            DDRD |= (1<<1);
            PORTD &= ~(1<<1);
        } else {
            // Hi-Z
            DDRD &= ~(1<<1);
            PORTD &= ~(1<<1);
        }
        if (led_state.scroll_lock) {
            // output low
            DDRC |= (1<<6);
            PORTC &= ~(1<<6);
        } else {
            // Hi-Z
            DDRC &= ~(1<<6);
            PORTC &= ~(1<<6);
        }

    }
    return res;
}