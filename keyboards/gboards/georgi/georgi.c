#include "georgi.h"

bool i2c_initialized = 0;
i2c_status_t mcp23018_status = 0x20;

void matrix_init_kb(void) {
  	steno_set_mode(STENO_MODE_GEMINI); // or STENO_MODE_BOLT

    // (tied to Vcc for hardware convenience)
    //gpio_set_pin_input(B4);  // set B(4) as input, internal pull-up disabled

    // unused pins - C7, D4, D5, D6, D7, E6
    // set as input with internal pull-up enabled
    gpio_set_pin_input_high(C7);
    gpio_set_pin_input_high(D4);
    gpio_set_pin_input_high(D5);
    gpio_set_pin_input_high(D6);
    gpio_set_pin_input_high(D7);
    gpio_set_pin_input_high(E6);

    matrix_init_user();
}


uint8_t init_mcp23018(void) {
    print("starting init");
    mcp23018_status = 0x20;

    // I2C subsystem

    // uint8_t sreg_prev;
    // sreg_prev=SREG;
    // cli();

    if (i2c_initialized == 0) {
        i2c_init();  // on pins D(1,0)
        i2c_initialized = true;
        _delay_ms(1000);
    }
    // i2c_init(); // on pins D(1,0)
    // _delay_ms(1000);

    // set pin direction
    // - unused  : input  : 1
    // - input   : input  : 1
    // - driving : output : 0
    uint8_t data[] = {0b10000000, 0b11111111};
    mcp23018_status = i2c_write_register(I2C_ADDR, IODIRA, data, 2, ERGODOX_EZ_I2C_TIMEOUT);

    if (!mcp23018_status) {
        // set pull-up
        // - unused  : on  : 1
        // - input   : on  : 1
        // - driving : off : 0
        mcp23018_status = i2c_write_register(I2C_ADDR, GPPUA, data, 2, ERGODOX_EZ_I2C_TIMEOUT);
    }

    // SREG=sreg_prev;
    //uprintf("Init %x\n", mcp23018_status);
    return mcp23018_status;
}
