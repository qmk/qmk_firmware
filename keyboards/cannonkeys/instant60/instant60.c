#include "instant60.h"
#include "ch.h"
#include "hal.h"
#include "led_custom.h"
#include "util.h"
#include "quantum.h"

void matrix_init_kb(void){
      /* MOSI pin*/
    palSetPadMode(GPIOB, 15, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
    LED_ON();
    wait_ms(500);
    LED_OFF();

#ifdef RGBLIGHT_ENABLE
    leds_init();
#endif
}

void matrix_scan_kb(void)
{
  #ifdef RGBLIGHT_ENABLE
    rgblight_task();
  #endif
}
