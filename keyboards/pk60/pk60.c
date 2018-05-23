#include "pk60.h"
#include "led.h"

void matrix_init_kb (void) {

  matrix_init_user();
  led_init_ports();

}

void matrix_scan_kb(void) {

  matrix_scan_user();

};

void led_init_ports(void) {
  
  DDRF |= (1 << 4);
  PORTF |= (1 << 4);

}

void led_set_kb(uint8_t usb_led) {
    
  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
      PORTF |= (1 << 4);
  } else {
      PORTF &= ~(1 << 4);
  }
  led_set_user(usb_led);

}