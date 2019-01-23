
#include QMK_KEYBOARD_H
#include "hal.h"

static THD_WORKING_AREA(testThread1WorkingArea, 128);
static THD_FUNCTION(testThread1, arg) {
    palSetPadMode(GPIOC, 13, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA, 0, PAL_MODE_INPUT_PULLDOWN);
    do {
        palSetPad(GPIOC, 13);
        chThdSleepMilliseconds(100);
        palClearPad(GPIOC, 13);
        chThdSleepMilliseconds(200);
        if (palReadPad(GPIOA, 0)) {
            BKP->DR1=0x4F42;
            BKP->DR2=0x544F;
        }
    } while(1);
}

void matrix_init_kb(void)
{
    (void)chThdCreateStatic(testThread1WorkingArea, sizeof(testThread1WorkingArea), NORMALPRIO, testThread1, NULL);
    matrix_init_user();
}

void mcp23017_init(void) {
  i2c_init();

  i2c_readReg(I2C_ADDR, );
}

