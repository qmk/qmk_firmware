#include "alice.h"

// void matrix_init_user(){
//   palSetPadMode(GPIOA, 0, PAL_MODE_OUTPUT_PUSHPULL);
//   palSetPadMode(GPIOA, 1, PAL_MODE_OUTPUT_PUSHPULL);
//   palSetPadMode(GPIOA, 2, PAL_MODE_OUTPUT_PUSHPULL);
// }

void matrix_init_board(void){
  palSetPadMode(GPIOA, 0, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOA, 1, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOA, 2, PAL_MODE_OUTPUT_PUSHPULL);
}


void led_set_kb(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
        palClearPad(GPIOA, 0);
    } else {
        palSetPad(GPIOA, 0);
    }
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        palClearPad(GPIOA, 1);
    } else {
        palSetPad(GPIOA, 1);
    }
    if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
        palClearPad(GPIOA, 2);
    } else {
        palSetPad(GPIOA, 2);
    }
    led_set_user(usb_led);
}
