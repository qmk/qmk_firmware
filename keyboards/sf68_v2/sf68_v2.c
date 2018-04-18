#include "sf68_v2.h"
#include "led.h"

void matrix_init_kb(void)
{
    matrix_init_user();
    led_init_ports();
}

void matrix_scan_kb(void)
{
    matrix_scan_user();
}

void led_init_ports(void)
{
    // led setting
    DDRF |= (1<<1);
    PORTF |= (1<<1);

    // rgb setting
    //DDRF |= _BV(1);
}

void led_set_kb(uint8_t usb_led) { 
    led_set_user(usb_led);
}
