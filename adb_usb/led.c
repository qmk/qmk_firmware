#include "stdint.h"
#include "adb.h"
#include "led.h"


void led_set(uint8_t usb_led)
{
    adb_host_kbd_led(~usb_led);
}
