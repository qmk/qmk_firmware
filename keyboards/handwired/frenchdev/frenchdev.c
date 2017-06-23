#include "frenchdev.h"
#include "i2cmaster.h"

bool i2c_initialized = 0;
uint8_t mcp23018_status = 0x20;

void matrix_init_kb(void) {
   // keyboard LEDs (see "PWM on ports OC1(A|B|C)" in "teensy-2-0.md")
    TCCR1A = 0b10101001;  // set and configure fast PWM
    TCCR1B = 0b00001001;  // set and configure fast PWM



    // unused pins - D4, D5, D7, E6
    // set as input with internal pull-ip enabled
    DDRD  &= ~(1<<5 | 1<<4);
    DDRE  &= ~(1<<6);
    PORTD |=  (1<<5 | 1<<4);
    PORTE |=  (1<<6);

    frenchdev_blink_all_leds();
    frenchdev_blink_all_leds();
    frenchdev_blink_all_leds();
    frenchdev_blink_all_leds();

    matrix_init_user();
}

void frenchdev_blink_all_leds(void)
{
    frenchdev_led_all_off();
    frenchdev_led_all_set(LED_BRIGHTNESS_HI);
    frenchdev_led_1_on();
    _delay_ms(50);
    frenchdev_led_2_on();
    _delay_ms(50);
    frenchdev_led_3_on();
    _delay_ms(50);
    frenchdev_led_1_off();
    _delay_ms(50);
    frenchdev_led_2_off();
    _delay_ms(50);
    frenchdev_led_3_off();
    frenchdev_led_all_off();
}

uint8_t init_mcp23018(void) {
    mcp23018_status = 0x20;

    // I2C subsystem

    // uint8_t sreg_prev;
    // sreg_prev=SREG;
    // cli();
    if (i2c_initialized == 0) {
        i2c_init();  // on pins D(1,0)
        i2c_initialized++;
        _delay_ms(1000);
    }

    // set pin direction
    // - unused  : input  : 1
    // - input   : input  : 1
    // - driving : output : 0
    mcp23018_status = i2c_start(I2C_ADDR_WRITE);    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(IODIRA);            if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b00000000);        if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b00111111);        if (mcp23018_status) goto out;
    i2c_stop();

    // set pull-up
    // - unused  : on  : 1
    // - input   : on  : 1
    // - driving : off : 0
    mcp23018_status = i2c_start(I2C_ADDR_WRITE);    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(GPPUA);             if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b00000000);        if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b00111111);        if (mcp23018_status) goto out;

out:
    i2c_stop();

    // SREG=sreg_prev;

    return mcp23018_status;
}

