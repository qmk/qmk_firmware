#include <ch.h>
#include <hal.h>
#include "util.h"
#include "quantum.h"

#ifdef BOARD_STM32_F103_STM32DUINO
#define LED_ON()    do { palClearPad(GPIOC, 13) ;} while (0)
#define LED_OFF()   do { palSetPad(GPIOC, 13); } while (0)
#define LED_TGL()   do { palTogglePad(GPIOC, 13); } while (0)
#else
#define LED_ON()
#define LED_OFF()
#define LED_TGL()
#endif

void matrix_init_kb(void){
    LED_ON();
    wait_ms(500);
    LED_OFF();
}
