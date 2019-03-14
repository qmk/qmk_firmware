#include "i2c_master.h"
#include QMK_KEYBOARD_H

extern inline void ergodox_board_led_1_on(void);
extern inline void ergodox_board_led_2_on(void);
extern inline void ergodox_board_led_3_on(void);
extern inline void ergodox_board_led_1_off(void);
extern inline void ergodox_board_led_2_off(void);
extern inline void ergodox_board_led_3_off(void);
extern inline void ergodox_led_all_off(void);

volatile int mcp23017_status = 0x20;
uint8_t i2c_initializied = 0;

// static THD_WORKING_AREA(testThread1WorkingArea, 128);
// static THD_FUNCTION(testThread1, arg) {
//     palSetPadMode(GPIOA, 14, PAL_MODE_INPUT_PULLUP);
//     chThdSleepSeconds(1);
//     do {
//         if (palReadPad(GPIOA, 14)) {
//             BKP->DR1=0x4F42;
//             BKP->DR2=0x544F;
//             ergodox_board_led_3_on();
//         } else {
//           ergodox_board_led_3_off();
//         }
//         chThdSleepSeconds(1);
//     } while(1);
// }

void matrix_init_kb(void)
{
    // Init LED Ports
    palSetPadMode(GPIOA, 10, PAL_MODE_OUTPUT_PUSHPULL); // LED 1
    palSetPadMode(GPIOA, 9, PAL_MODE_OUTPUT_PUSHPULL); // LED 2
    palSetPadMode(GPIOA, 8, PAL_MODE_OUTPUT_PUSHPULL); // LED 3

    // (void)chThdCreateStatic(testThread1WorkingArea, sizeof(testThread1WorkingArea), NORMALPRIO, testThread1, NULL);

    ergodox_blink_all_leds();

    matrix_init_user();
}

void ergodox_blink_all_leds(void)
{
    ergodox_led_all_off();
    // ergodox_led_all_set(LED_BRIGHTNESS_DEFAULT);
    ergodox_board_led_1_on();
    chThdSleepMilliseconds(50);
    ergodox_board_led_2_on();
    chThdSleepMilliseconds(50);
    ergodox_board_led_3_on();
    chThdSleepMilliseconds(50);
    ergodox_board_led_1_off();
    chThdSleepMilliseconds(50);
    ergodox_board_led_2_off();
    chThdSleepMilliseconds(50);
    ergodox_board_led_3_off();
}

uint8_t init_mcp23017(void) {
    if (!i2c_initializied) {
        i2c_init();
        i2c_initializied = 1;
    }

    uint8_t data[2];
    data[0] = 0x0;
    data[1] = 0b00111111;
    mcp23017_status = i2c_writeReg(I2C_ADDR, I2C_IODIRA, data, 2, 50000);
    if (mcp23017_status) goto out;
    data[0] = 0xFFU;
    mcp23017_status = i2c_writeReg(I2C_ADDR, I2C_GPIOA, data, 1, 5000);
    if (mcp23017_status) goto out;
    mcp23017_status = i2c_writeReg(I2C_ADDR, I2C_GPPUB, data+1, 1, 2);
    if (mcp23017_status) goto out;

 out:
    return mcp23017_status;
    // i2c_readReg(I2C_ADDR, );
}

