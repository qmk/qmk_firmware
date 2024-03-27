#include "2x5keypad.h"


void matrix_init_kb(void)
{
    matrix_init_user();

    gpio_set_pin_output(RED_LED);
    gpio_set_pin_output(BLUE_LED);
    gpio_set_pin_output(GREEN_LED);
}



void turn_off_leds(void)
{
    gpio_write_pin_low(RED_LED);
    gpio_write_pin_low(BLUE_LED);
    gpio_write_pin_low(GREEN_LED);
}

void turn_on_led(pin_t pin)
{
    gpio_write_pin_high(pin);
}
