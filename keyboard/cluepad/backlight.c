#include <avr/io.h>
#include "backlight.h"
#include "led.h"

#include "print.h"

int pwm_level;

void led_set_kb(uint8_t usb_led)
{
    print("led_set\n");
}

void init_backlight_pin(void)
{
    // Set C7 to output
    DDRC |= (1<<7);

    // Initialize the timer
    TC4H = 0x03;
    OCR4C = 0xFF;
    TCCR4A = 0b10000010;
    TCCR4B = 0b00000001;
}

void backlight_set(uint8_t level)
{
    // Determine the PWM level
    switch (level)
    {
        case 0:
            // 33%
            pwm_level = 0x54;
            break;
        case 1:
            // 66%
            pwm_level = 0xA8;
            break;
        case 2:
            // 100%
            pwm_level = 0xFF;
            break;
        case 3:
            // 0%
            pwm_level = 0x00;
            break;
        default:
            xprintf("Unknown level: %d\n", level);
    }

    // Write the PWM level to the timer
    TC4H = pwm_level >> 8;
    OCR4A = 0xFF & pwm_level;
}
