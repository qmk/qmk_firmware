
#include "ergodox_stm32.h"
#include QMK_KEYBOARD_H

extern inline void ergodox_board_led_1_on(void);
extern inline void ergodox_board_led_2_on(void);
extern inline void ergodox_board_led_3_on(void);
extern inline void ergodox_board_led_1_off(void);
extern inline void ergodox_board_led_2_off(void);
extern inline void ergodox_board_led_3_off(void);
extern inline void ergodox_led_all_off(void);

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

void mcp23017_init(void) {
  i2c_init();

  // i2c_readReg(I2C_ADDR, );
}

