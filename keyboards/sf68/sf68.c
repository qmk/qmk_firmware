#include "sf68.h"
#include "led.h"

void matrix_init_kb(void)
{
    MCUCR |= (1<<JTD);
    MCUCR |= (1<<JTD);

    // set pd0&pd1 as output
    DDRD |= _BV(0);
    DDRD |= _BV(1);

    //PORTD |= 1;
    matrix_init_user();
}
void matrix_scan_kb(void)
{
    matrix_scan_user();
}

void led_set_kb(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
      // Turn capslock on
      PORTD |= (1<<1);
    } else {
      // Turn capslock off
      PORTD &= (1<<1);
    }
  }