
#include "str20.h"

#include "ch.h"
#include "hal.h"

#include "print.h"
#include "debug.h"
#include "util.h"

/* generic STM32F103C8T6 board */
#ifdef BOARD_GENERIC_STM32_F103
// #define LED_ON()    do { palClearPad(GPIOC, 12) ;} while (0)
// #define LED_OFF()   do { palSetPad(GPIOC, 12); } while (0)
// #define LED_TGL()   do { palTogglePad(GPIOC, 12); } while (0)
#endif

void matrix_init_kb(void){
      /* MOSI pin*/
    palSetPadMode(GPIOB, 15, PAL_MODE_STM32_ALTERNATE_PUSHPULL);

    // LED_ON();
    palSetPad(GPIOA, 8);
    wait_ms(500);
    palClearPad(GPIOA, 8);
    // LED_OFF();

    // leds_init();


}
