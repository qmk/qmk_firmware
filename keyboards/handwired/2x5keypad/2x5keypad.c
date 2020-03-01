#include "2x5keypad.h"


void matrix_init_kb(void)
{
    setPinOutput(RED_LED);
    setPinOutput(BLUE_LED);
    setPinOutput(GREEN_LED);
}



void turn_off_leds(void)
{
    writePinLow(RED_LED);
    writePinLow(BLUE_LED);
    writePinLow(GREEN_LED);
}

void turn_on_led(pin_t pin)
{
    writePinHigh(pin);
}
