#include "8x18_arm.h"

void keyboard_pre_init_kb(void){
    //init the CAPS LOCK LED pin as an output
    setPinOutput(STM32LED);

// disable JTAG  to enable PB3 and PB4
    AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;
    AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_DISABLE;

    //call any user initialization code
    keyboard_pre_init_user();
}

void led_set(uint8_t usb_led){
  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
   LED_ON
  } else {
   LED_OFF
  }
}
