#include QMK_KEYBOARD_H

bool         i2c_initialized = 0;
i2c_status_t mcp23018_status = 0x20;

void matrix_init_kb(void) {
    // unused pins - C7, D4, D5, D7, E6
    // set as input with internal pull-up enabled
    setPinInput(B4);
    writePinLow(B4);

    setPinInput(B5);
    writePinLow(B5);

    setPinInput(B6);
    writePinLow(B6);

    setPinInput(B7);
    writePinLow(B7);

    setPinInput(D5);
    writePinLow(D5);

    setPinInput(D6);
    writePinLow(D6);

    setPinInput(D7);
    writePinLow(D7);

    matrix_init_user();
}
uint8_t init_mcp23018(void) {
    print("starting init");
    mcp23018_status = 0x20;

    // I2C subsystem
    if (i2c_initialized == 0) {
        i2c_init();  // on pins D(1,0)
        i2c_initialized = true;
        _delay_ms(1000);
    }
    // set pin direction
    // - unused  : input  : 1
    // - input   : input  : 1
    // - driving : output : 0
    mcp23018_status = i2c_start(I2C_ADDR_WRITE, I2C_TIMEOUT);
    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(IODIRA, I2C_TIMEOUT);
    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b10000000, I2C_TIMEOUT);
    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b11111111, I2C_TIMEOUT);
    if (mcp23018_status) goto out;
    i2c_stop();

    // set pull-up
    // - unused  : on  : 1
    // - input   : on  : 1
    // - driving : off : 0
    mcp23018_status = i2c_start(I2C_ADDR_WRITE, I2C_TIMEOUT);
    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(GPPUA, I2C_TIMEOUT);
    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b10000000, I2C_TIMEOUT);
    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b11111111, I2C_TIMEOUT);
    if (mcp23018_status) goto out;

out:
    i2c_stop();
    // SREG=sreg_prev;
    // uprintf("Init %x\n", mcp23018_status);
    return mcp23018_status;
}
