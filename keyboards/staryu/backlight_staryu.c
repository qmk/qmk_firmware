#include "backlight.h"
#include <avr/pgmspace.h>

/* backlighting */
void init_backlight_led(void)
{
    DDRC |= (1<<PC2 | 1<<PC7);
    DDRD |= (1<<PD5 | 1<<PD6);
    DDRB |= (1<<PB0);
}

void backlight_led_off(uint8_t index)
{
    switch (index) {
        case 0:
            PORTC |= (1<<PC2);
            break;
        case 1:
            PORTC |= (1<<PC7);
            break;
        case 2:
            PORTD |= (1<<PD5);
            break;
        case 3:
            PORTD |= (1<<PD6);
            break;
        case 4:
            PORTB |= (1<<PB0);
            break;
    }
}

void backlight_led_on(uint8_t index)
{
    switch (index) {
        case 0:
            PORTC &= ~(1<<PC2);
            break;
        case 1:
            PORTC &= ~(1<<PC7);
            break;
        case 2:
            PORTD &= ~(1<<PD5);
            break;
        case 3:
            PORTD &= ~(1<<PD6);
            break;
        case 4:
            PORTB &= ~(1<<PB0);
            break;
    }
}
