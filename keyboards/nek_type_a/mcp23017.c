#include <stdbool.h>
#include "action.h"
//#include "i2cmaster.h"
#include "lib/lufa/LUFA/Drivers/Peripheral/TWI.h"
#include "lib/lufa/LUFA/Drivers/Peripheral/AVR8/TWI_AVR8.c"
#include "mcp23017.h"
#include "debug.h"

static uint8_t expander_status = 0;

uint8_t bit_for_pin(uint8_t pin);
uint8_t expander_write(uint8_t reg, uint8_t data);
uint8_t expander_read(uint8_t reg, uint8_t *data);
void expander_config(void);

void expander_init(void)
{
    i2c_init();
    expander_connect();
}

// set IN and HI
void expander_unselect(uint8_t pin)
{
    const uint8_t bit = bit_for_pin(pin);
    if (pin < 8)
    {
        expander_write(EXPANDER_REG_IODIRA, bit);
        expander_write(EXPANDER_REG_OLATA, bit);
    }
    else
    {
        expander_write(EXPANDER_REG_IODIRB, bit);
        expander_write(EXPANDER_REG_OLATB, bit);
    }
}

// set OUT and LOW
void expander_select(uint8_t pin)
{
    const uint8_t mask = 0xff & ~bit_for_pin(pin);
    if (pin < 8)
    {
        expander_write(EXPANDER_REG_IODIRA, mask);
        expander_write(EXPANDER_REG_OLATA, mask);
    }
    else
    {
        expander_write(EXPANDER_REG_IODIRB, mask);
        expander_write(EXPANDER_REG_OLATB, mask);
    }
}

void expander_unselect_all()
{
    expander_write(EXPANDER_REG_IODIRA, 0xff);
    expander_write(EXPANDER_REG_IODIRB, 0xff);
    expander_write(EXPANDER_REG_OLATA, 0xff);
    expander_write(EXPANDER_REG_OLATB, 0xff);
}

void expander_connect()
{
    dprintf("expander status: %d ... ", expander_status);
    i2c_init();
    uint8_t ret = i2c_start(EXPANDER_ADDR | I2C_WRITE);
    dprintf("ret %d ... ", ret);
/*    if (ret == 0) {
        i2c_stop();
        if (expander_status == 0) {
            dprintf("attached\n");
            expander_status = 1;
            expander_config();
            clear_keyboard();
        }
    }
    else {
        if (expander_status == 1) {
            dprintf("detached\n");
            expander_status = 0;
            clear_keyboard();
        }
    }*/
    dprintf("%d\n", expander_status);
}

void expander_config()
{
    // set everything to input
    expander_write(EXPANDER_REG_IODIRA, 0xff);
    expander_write(EXPANDER_REG_IODIRB, 0xff);

    // turn on pull-ups
    expander_write(EXPANDER_REG_GPPUA, 0xff);
    expander_write(EXPANDER_REG_GPPUB, 0xff);

    // disable interrupts
    expander_write(EXPANDER_REG_GPINTENA, 0x0);
    expander_write(EXPANDER_REG_GPINTENB, 0x0);

    // polarity?
}

uint8_t bit_for_pin(uint8_t pin)
{
    return pin % 8;
}

uint8_t expander_write(uint8_t reg, uint8_t data)
{
    if (expander_status == 0) {
        return 0;
    }
    uint8_t ret;
    ret = i2c_start(EXPANDER_ADDR | I2C_WRITE);
    if (ret) goto stop;
    ret = i2c_write(reg);
    if (ret) goto stop;
    ret = i2c_write(data);
    stop:
    i2c_stop();
    return ret;
}

uint8_t expander_read(uint8_t reg, uint8_t *data)
{
    if (expander_status == 0) {
        return 0;
    }
    uint8_t ret;
    ret = i2c_start(EXPANDER_ADDR | I2C_WRITE);
    if (ret) goto stop;
    ret = i2c_write(reg);
    if (ret) goto stop;
    ret = i2c_rep_start(EXPANDER_ADDR | I2C_READ);
    if (ret) goto stop;
    *data = i2c_readNak();
    stop:
    i2c_stop();
    return ret;
}
