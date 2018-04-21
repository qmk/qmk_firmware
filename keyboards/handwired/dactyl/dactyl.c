#include "dactyl.h"
#include "i2cmaster.h"


bool i2c_initialized = 0;
uint8_t mcp23018_status = 0x20;

void matrix_init_kb(void) {
    DDRB  &= ~(1<<4);  // set B(4) as input
    PORTB &= ~(1<<4);  // set B(4) internal pull-up disabled

    // unused pins - C7, D4, D5, D7, E6
    // set as input with internal pull-up enabled
    DDRC  &= ~(1<<7);
    DDRD  &= ~(1<<5 | 1<<4);
    DDRE  &= ~(1<<6);
    PORTC |=  (1<<7);
    PORTD |=  (1<<5 | 1<<4);
    PORTE |=  (1<<6);

    matrix_init_user();
}

uint8_t init_mcp23018(void) {
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

    return mcp23018_status;
}

#ifdef SWAP_HANDS_ENABLE
__attribute__ ((weak))
// swap-hands action needs a matrix to define the swap
const keypos_t hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    /* Left hand, matrix positions */
    {{0,11}, {1,11}, {2,11}, {3,11}, {4,11}, {5,11}},
    {{0,10}, {1,10}, {2,10}, {3,10}, {4,10}, {5,10}},
    {{0,9},  {1,9},  {2,9},  {3,9},  {4,9},  {5,9}},
    {{0,8},  {1,8},  {2,8},  {3,8},  {4,8},  {5,8}},
    {{0,7},  {1,7},  {2,7},  {3,7},  {4,7},  {5,7}},
    {{0,6},  {1,6},  {2,6},  {3,6},  {4,6},  {5,6}},

    /* Right hand, matrix positions */
    {{0,5},  {1,5},  {2,5},  {3,5},  {4,5},  {5,5}},
    {{0,4},  {1,4},  {2,4},  {3,4},  {4,4},  {5,4}},
    {{0,3},  {1,3},  {2,3},  {3,3},  {4,3},  {5,3}},
    {{0,2},  {1,2},  {2,2},  {3,2},  {4,2},  {5,2}},
    {{0,1},  {1,1},  {2,1},  {3,1},  {4,1},  {5,1}},
    {{0,0},  {1,0},  {2,0},  {3,0},  {4,0},  {5,0}},
};
#endif
