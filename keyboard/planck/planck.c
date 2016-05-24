#include "planck.h"

__attribute__ ((weak))
void matrix_init_user(void) {}

__attribute__ ((weak))
void matrix_scan_user(void) {}

__attribute__ ((weak))
bool process_action_user(keyrecord_t *record) {
    return true;
}

__attribute__ ((weak))
void led_set_user(uint8_t usb_led) {}

void matrix_init_kb(void) {
#ifdef BACKLIGHT_ENABLE
	backlight_init_ports();
#endif

#ifdef RGBLIGHT_ENABLE
	rgblight_init();
#endif

	// Turn status LED on
	DDRE |= (1<<6);
	PORTE |= (1<<6);

	matrix_init_user();
}

void matrix_scan_kb(void) {
	matrix_scan_user();
}

bool process_action_kb(keyrecord_t *record) {
	return process_action_user(record);
}

void led_set_kb(uint8_t usb_led) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

    led_set_user(usb_led);
}

#ifdef BACKLIGHT_ENABLE
#define CHANNEL OCR1C
#define BREATHING_NO_HALT  0
#define BREATHING_HALT_OFF 1
#define BREATHING_HALT_ON  2

static uint8_t breath_intensity;
static uint8_t breath_speed;
static uint16_t breathing_index;
static uint8_t breathing_halt;

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
    breathing_defaults();
}

void backlight_set(uint8_t level)
{
    // Prevent backlight blink on lowest level
    PORTB &= ~(_BV(PORTB7));

    if ( level == 0 )
    {
        // Turn off PWM control on PB7, revert to output low.
        TCCR1A &= ~(_BV(COM1C1));
        CHANNEL = 0x0;
    }
    else if ( level == BACKLIGHT_LEVELS )
    {
        // Turn on PWM control of PB7
        TCCR1A |= _BV(COM1C1);
        // Set the brightness
        CHANNEL = 0xFFFF;
    }
    else        
    {
        // Turn on PWM control of PB7
        TCCR1A |= _BV(COM1C1);
        // Set the brightness
        CHANNEL = 0xFFFF >> ((BACKLIGHT_LEVELS - level) * ((BACKLIGHT_LEVELS + 1) / 2));
    }
    breathing_intensity_default();
}


void breathing_enable(void)
{
    if (get_backlight_level() == 0)
    {
        breathing_index = 0;
    }
    else
    {
        // Set breathing_index to be at the midpoint (brightest point)
        breathing_index = 0x20 << breath_speed;
    }

    breathing_halt = BREATHING_NO_HALT;

    // Enable breathing interrupt
    TIMSK1 |= _BV(OCIE1A);
}

void breathing_pulse(void)
{
    if (get_backlight_level() == 0)
    {
        breathing_index = 0;
    }
    else
    {
        // Set breathing_index to be at the midpoint + 1 (brightest point)
        breathing_index = 0x21 << breath_speed;
    }

    breathing_halt = BREATHING_HALT_ON;

    // Enable breathing interrupt
    TIMSK1 |= _BV(OCIE1A);
}

void breathing_disable(void)
{
    // Disable breathing interrupt
    TIMSK1 &= ~_BV(OCIE1A);
    backlight_set(get_backlight_level());
}

void breathing_self_disable(void)
{
    if (get_backlight_level() == 0)
    {
        breathing_halt = BREATHING_HALT_OFF;
    }
    else
    {
        breathing_halt = BREATHING_HALT_ON;
    }

    //backlight_set(get_backlight_level());
}

void breathing_toggle(void)
{
    if (!is_breathing())
    {
        if (get_backlight_level() == 0)
        {
            breathing_index = 0;
        }
        else
        {
            // Set breathing_index to be at the midpoint + 1 (brightest point)
            breathing_index = 0x21 << breath_speed;
        }

        breathing_halt = BREATHING_NO_HALT;
    }

    // Toggle breathing interrupt
    TIMSK1 ^= _BV(OCIE1A);

    // Restore backlight level
    if (!is_breathing())
    {
        backlight_set(get_backlight_level());
    }
}

bool is_breathing(void)
{
    return (TIMSK1 && _BV(OCIE1A));
}

void breathing_intensity_default(void)
{
    //breath_intensity = (uint8_t)((uint16_t)100 * (uint16_t)get_backlight_level() / (uint16_t)BACKLIGHT_LEVELS);
    breath_intensity = ((BACKLIGHT_LEVELS - get_backlight_level()) * ((BACKLIGHT_LEVELS + 1) / 2));
}

void breathing_intensity_set(uint8_t value)
{
    breath_intensity = value;
}

void breathing_speed_default(void)
{
    breath_speed = 4;
}

void breathing_speed_set(uint8_t value)
{
    bool is_breathing_now = is_breathing();
    uint8_t old_breath_speed = breath_speed;

    if (is_breathing_now)
    {
        // Disable breathing interrupt
        TIMSK1 &= ~_BV(OCIE1A);
    }

    breath_speed = value;

    if (is_breathing_now)
    {
        // Adjust index to account for new speed
        breathing_index = (( (uint8_t)( (breathing_index) >> old_breath_speed ) ) & 0x3F) << breath_speed;

        // Enable breathing interrupt
        TIMSK1 |= _BV(OCIE1A);
    }

}

void breathing_speed_inc(uint8_t value)
{
    if ((uint16_t)(breath_speed - value) > 10 )
    {
        breathing_speed_set(0);
    }
    else
    {
        breathing_speed_set(breath_speed - value);
    }
}

void breathing_speed_dec(uint8_t value)
{
    if ((uint16_t)(breath_speed + value) > 10 )
    {
        breathing_speed_set(10);
    }
    else
    {
        breathing_speed_set(breath_speed + value);
    }
}

void breathing_defaults(void)
{
    breathing_intensity_default();
    breathing_speed_default();
    breathing_halt = BREATHING_NO_HALT;
}

/* Breathing Sleep LED brighness(PWM On period) table
 * (64[steps] * 4[duration]) / 64[PWM periods/s] = 4 second breath cycle
 *
 * http://www.wolframalpha.com/input/?i=%28sin%28+x%2F64*pi%29**8+*+255%2C+x%3D0+to+63
 * (0..63).each {|x| p ((sin(x/64.0*PI)**8)*255).to_i }
 */
static const uint8_t breathing_table[64] PROGMEM = {
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   2,   4,   6,  10,
 15,  23,  32,  44,  58,  74,  93, 113, 135, 157, 179, 199, 218, 233, 245, 252,
255, 252, 245, 233, 218, 199, 179, 157, 135, 113,  93,  74,  58,  44,  32,  23,
 15,  10,   6,   4,   2,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
};

ISR(TIMER1_COMPA_vect)
{
    // CHANNEL = (pgm_read_byte(&breathing_table[ ( (uint8_t)( (breathing_index++) >> breath_speed ) ) & 0x3F ] )) * breath_intensity;


    uint8_t local_index = ( (uint8_t)( (breathing_index++) >> breath_speed ) ) & 0x3F;

    if (((breathing_halt == BREATHING_HALT_ON) && (local_index == 0x20)) || ((breathing_halt == BREATHING_HALT_OFF) && (local_index == 0x3F)))
    {
        // Disable breathing interrupt
        TIMSK1 &= ~_BV(OCIE1A);
    }

    CHANNEL = (uint16_t)(((uint16_t)pgm_read_byte(&breathing_table[local_index]) * 257)) >> breath_intensity;

}



#endif