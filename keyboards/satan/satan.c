#include "satan.h"

#ifdef BACKLIGHT_ENABLE
#include "backlight.h"
#endif

__attribute__ ((weak))
void matrix_init_user(void) {
	// leave these blank
};

__attribute__ ((weak))
void matrix_scan_user(void) {
	// leave these blank
};


#ifdef BACKLIGHT_ENABLE

void backlight_init_ports()
{

    // Setup PB6 as output and output low.
    DDRB |= (1<<6);
    PORTB &= ~(1<<6);

    // Use full 16-bit resolution.
    ICR1 = 0xFFFF;

    // I could write a wall of text here to explain... but TL;DW
    // Go read the ATmega32u4 datasheet.
    // And this: http://blog.saikoled.com/post/43165849837/secret-konami-cheat-code-to-high-resolution-pwm-on

    // Pin PB6 = OCR1B (Timer 1, Channel C)
    // Compare Output Mode = Clear on compare match, Channel C = COM1C1=1 COM1C0=0
    // (i.e. start high, go low when counter matches.)
    // WGM Mode 14 (Fast PWM) = WGM13=1 WGM12=1 WGM11=1 WGM10=0
    // Clock Select = clk/1 (no prescaling) = CS12=0 CS11=0 CS10=1

    TCCR1A = _BV(COM1B1) | _BV(WGM11); // = 0b00001010;
    TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10); // = 0b00011001;

    backlight_init();
}

void backlight_set(uint8_t level)
{
    // Prevent backlight blink on lowest level
    PORTB &= ~(_BV(PORTB6));

    if ( level == 0 )
    {
        // Turn off PWM control on PB6, revert to output low.
        TCCR1A &= ~(_BV(COM1B1));
        OCR1B = 0x0;
    }
    else if ( level == BACKLIGHT_LEVELS )
    {
        // Turn on PWM control of PB6
        TCCR1A |= _BV(COM1B1);
        // Set the brightness
        OCR1B = 0xFFFF;
    }
    else
    {
        // Turn on PWM control of PB6
        TCCR1A |= _BV(COM1B1);
        // Set the brightness
        OCR1B = 0xFFFF >> ((BACKLIGHT_LEVELS - level) * ((BACKLIGHT_LEVELS + 1) / 2));
    }
}

#endif

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	if (matrix_init_user) {
		(*matrix_init_user)();
	}
	led_init_ports();

    #ifdef BACKLIGHT_ENABLE
        backlight_init_ports();
    #endif
};

void matrix_scan_kb(void) {
	// put your looping keyboard code here
	// runs every cycle (a lot)
	if (matrix_scan_user) {
		(*matrix_scan_user)();
	}
};