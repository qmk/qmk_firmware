#include "adb_usb.h"

void led_set_kb(uint8_t usb_led)
{
    adb_host_kbd_led(ADB_ADDR_KEYBOARD, ~usb_led);
    led_set_user(usb_led);
}