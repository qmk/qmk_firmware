#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "matrix.h"
#include "keyboard.h"
#include "config.h"
#include "timer.h"

#include "i2c.h"


static void I2C_init(void){
	int err;
	
    err = i2c_master_start(TRACBALL_ADDR + I2C_WRITE);
    if (err) goto i2c_error;

    // start of matrix stored at 0x00
    err = i2c_master_write(0x00);
    if (err) goto i2c_error;

    i2c_master_write(0x00);
    i2c_master_write(0x00);
    i2c_master_write(0x00);

    if (!err) {
        i2c_master_stop();
    } else {
i2c_error: // the cable is disconnceted, or something else went wrong
        i2c_reset_state();
        return;
    }
    return;
}

// this code runs before the usb and keyboard is initialized
void matrix_setup(void) {
    i2c_master_init();
    I2C_init();

}
