#include QMK_KEYBOARD_H

bool i2c_initialized = 0;
i2c_status_t mcp23018_status = 0x20;

void matrix_init_kb(void) {
    // For whatever reason you think you need BOLT you're wrong.
  	steno_set_mode(STENO_MODE_GEMINI); // or STENO_MODE_BOLT
    // Remember to modify config_engine.c or wonky stuff will happen

    // (tied to Vcc for hardware convenience)
    //DDRB  &= ~(1<<4);  // set B(4) as input
    //PORTB &= ~(1<<4);  // set B(4) internal pull-up disabled

    // unused pins - C7, D4, D5, D7, E6
    // set as input with internal pull-up enabled
    DDRC  &= ~(1<<7);
    DDRD  &= ~(1<<5 | 1<<4 | 1<<6 | 1<<7);
    DDRE  &= ~(1<<6);
    PORTC |=  (1<<7);
    PORTD |=  (1<<5 | 1<<4 | 1<<6 | 1<<7);
    PORTE |=  (1<<6);

    matrix_init_user();
#ifdef ONLY_QWERTY
    layer_on(1);
#endif
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
    mcp23018_status = i2c_start(I2C_ADDR_WRITE, ERGODOX_EZ_I2C_TIMEOUT);    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(IODIRA, ERGODOX_EZ_I2C_TIMEOUT);            if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b10000000, ERGODOX_EZ_I2C_TIMEOUT);        if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b11111111, ERGODOX_EZ_I2C_TIMEOUT);        if (mcp23018_status) goto out;
    i2c_stop();

    // set pull-up
    // - unused  : on  : 1
    // - input   : on  : 1
    // - driving : off : 0
    mcp23018_status = i2c_start(I2C_ADDR_WRITE, ERGODOX_EZ_I2C_TIMEOUT);    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(GPPUA, ERGODOX_EZ_I2C_TIMEOUT);             if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b10000000, ERGODOX_EZ_I2C_TIMEOUT);        if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b11111111, ERGODOX_EZ_I2C_TIMEOUT);        if (mcp23018_status) goto out;

out:
    i2c_stop();
    // SREG=sreg_prev;
    //uprintf("Init %x\n", mcp23018_status);
    return mcp23018_status;
}
