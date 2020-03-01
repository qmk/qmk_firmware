#include QMK_KEYBOARD_H

bool i2c_initialized = 0;
i2c_status_t mcp23018_status = 0x20;

void matrix_init_kb(void) {
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
    mcp23018_status = i2c_start(I2C_ADDR_WRITE, I2C_TIMEOUT);    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(IODIRA, I2C_TIMEOUT);            if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b10000000, I2C_TIMEOUT);        if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b11111111, I2C_TIMEOUT);        if (mcp23018_status) goto out;
    i2c_stop();

    // set pull-up
    // - unused  : on  : 1
    // - input   : on  : 1
    // - driving : off : 0
    mcp23018_status = i2c_start(I2C_ADDR_WRITE, I2C_TIMEOUT);    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(GPPUA, I2C_TIMEOUT);             if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b10000000, I2C_TIMEOUT);        if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b11111111, I2C_TIMEOUT);        if (mcp23018_status) goto out;

out:
    i2c_stop();
    // SREG=sreg_prev;
    //uprintf("Init %x\n", mcp23018_status);
    return mcp23018_status;
}

const keypos_t hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    { {0,0}, {0,7}, {2,7}, {3,7} },
    { {0,8}, {1,8}, {2,8}, {3,8} },
    { {0,9}, {1,9}, {2,9}, {3,9} },
    { {0,10}, {1,10}, {2,10}, {3,10} },
    { {0,11}, {1,11}, {2,11}, {3,11} },
    { {0,12}, {1,12}, {2,12}, {0,0} },
    { {0,13}, {1,13}, {2,13}, {0,0} },

    { {1,0}, {0,0}, {2,0}, {3,0} },
    { {0,1}, {1,1}, {2,1}, {3,1} },
    { {0,2}, {1,2}, {2,2}, {3,2} },
    { {0,3}, {1,3}, {2,3}, {3,3} },
    { {0,4}, {1,4}, {2,4}, {3,4} },
    { {0,5}, {1,5}, {2,5}, {3,5} },
    { {0,6}, {1,6}, {2,6}, {3,6} }
};
