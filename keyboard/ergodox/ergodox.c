#include "ergodox.h"
#include "i2cmaster.h"

bool i2c_initialized = 0;
uint8_t mcp23018_status = 0x20;

bool ergodox_left_led_1 = 0;  // left top
bool ergodox_left_led_2 = 0;  // left middle
bool ergodox_left_led_3 = 0;  // left bottom

void * matrix_init_user(void) {

};

void * matrix_scan_user(void) {

};

void * matrix_init_kb(void) {
   // keyboard LEDs (see "PWM on ports OC1(A|B|C)" in "teensy-2-0.md")
    TCCR1A = 0b10101001;  // set and configure fast PWM
    TCCR1B = 0b00001001;  // set and configure fast PWM

    // (tied to Vcc for hardware convenience)
    DDRB  &= ~(1<<4);  // set B(4) as input
    PORTB &= ~(1<<4);  // set B(4) internal pull-up disabled

    // unused pins - C7, D4, D5, D7, E6
    // set as input with internal pull-ip enabled
    DDRC  &= ~(1<<7);
    DDRD  &= ~(1<<7 | 1<<5 | 1<<4);
    DDRE  &= ~(1<<6);
    PORTC |=  (1<<7);
    PORTD |=  (1<<7 | 1<<5 | 1<<4);
    PORTE |=  (1<<6);

    ergodox_blink_all_leds();

	if (matrix_init_user) {
		(*matrix_init_user)();
	}
};

void * matrix_scan_kb(void) {

	if (matrix_scan_user) {
		(*matrix_scan_user)();
	}
};


void ergodox_blink_all_leds(void)
{
    ergodox_led_all_off();
    ergodox_led_all_set(LED_BRIGHTNESS_HI);
    ergodox_led_all_on();
    _delay_ms(333);
    ergodox_led_all_off();
}

uint8_t init_mcp23018(void) {
    mcp23018_status = 0x20;

    // I2C subsystem
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

    if (!mcp23018_status) mcp23018_status = ergodox_left_leds_update();

    return mcp23018_status;
}

uint8_t ergodox_left_leds_update(void) {
    if (mcp23018_status) { // if there was an error
        return mcp23018_status;
    }

    // set logical value (doesn't matter on inputs)
    // - unused  : hi-Z : 1
    // - input   : hi-Z : 1
    // - driving : hi-Z : 1
    mcp23018_status = i2c_start(I2C_ADDR_WRITE);    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(OLATA);             if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b11111111
            & ~(ergodox_left_led_3<<LEFT_LED_3_SHIFT)
          );                                        if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b11111111
            & ~(ergodox_left_led_2<<LEFT_LED_2_SHIFT)
            & ~(ergodox_left_led_1<<LEFT_LED_1_SHIFT)
          );                                        if (mcp23018_status) goto out;

out:
    i2c_stop();
    return mcp23018_status;
}

