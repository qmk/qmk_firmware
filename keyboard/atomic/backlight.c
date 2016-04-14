
#include <avr/io.h>
#include "backlight.h"
#include "atomic.h"


#define CHANNEL OCR1C

void backlight_init_ports()
{

    // Setup PB7 as output and output low.
    DDRB |= (1<<7);
    PORTB &= ~(1<<7);
    
    // Use full 16-bit resolution. 
    ICR1 = 0xFFFF;

    // I could write a wall of text here to explain... but TL;DW
    // Go read the ATmega32u4 datasheet.
    // And this: http://blog.saikoled.com/post/43165849837/secret-konami-cheat-code-to-high-resolution-pwm-on
    
    // Pin PB7 = OCR1C (Timer 1, Channel C)
    // Compare Output Mode = Clear on compare match, Channel C = COM1C1=1 COM1C0=0
    // (i.e. start high, go low when counter matches.)
    // WGM Mode 14 (Fast PWM) = WGM13=1 WGM12=1 WGM11=1 WGM10=0
    // Clock Select = clk/1 (no prescaling) = CS12=0 CS11=0 CS10=1
    
    TCCR1A = _BV(COM1C1) | _BV(WGM11); // = 0b00001010;
    TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10); // = 0b00011001;

    backlight_init();
}

void backlight_set(uint8_t level)
{
    if ( level == 0 )
    {
        // Turn off PWM control on PB7, revert to output low.
        TCCR1A &= ~(_BV(COM1C1));
        CHANNEL = 0x0;
        // Prevent backlight blink on lowest level
        PORTB &= ~(_BV(PORTB7));
    }
    else if ( level == BACKLIGHT_LEVELS )
    {
        // Prevent backlight blink on lowest level
        PORTB &= ~(_BV(PORTB7));
        // Turn on PWM control of PB7
        TCCR1A |= _BV(COM1C1);
        // Set the brightness
        CHANNEL = 0xFFFF;
    }
    else        
    {
        // Prevent backlight blink on lowest level
        PORTB &= ~(_BV(PORTB7));
        // Turn on PWM control of PB7
        TCCR1A |= _BV(COM1C1);
        // Set the brightness
        CHANNEL = 0xFFFF >> ((BACKLIGHT_LEVELS - level) * ((BACKLIGHT_LEVELS + 1) / 2));
    }
}