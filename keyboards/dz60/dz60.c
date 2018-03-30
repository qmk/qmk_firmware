#include "dz60.h"
#include "led.h"

extern uint32_t layer_state;
extern struct cRGB led[16];

void matrix_init_kb(void)
{
  // Keyboard start-up code goes here
  // Runs once when the firmware starts up
  matrix_init_user();
  led_init_ports();
};

void matrix_scan_kb(void)
{
  // Looping keyboard code goes here
  // This runs every cycle (a lot)
  matrix_scan_user();

  uint8_t layer = biton32(layer_state);

  switch (layer)
  {
  case 1:
    led[15].r = 191;
    led[15].g = 216;
    led[15].b = 0;
    ws2812_setleds(led, 16);
    break;
  case 2:
    led[15].r = 107;
    led[15].g = 91;
    led[15].b = 0;
    ws2812_setleds(led, 16);
    break;
  case 3:
    led[15].r = 233;
    led[15].g = 75;
    led[15].b = 0;
    ws2812_setleds(led, 16);
    break;
  default:
    led[15].r = 0;
    led[15].g = 0;
    led[15].b = 0;
    ws2812_setleds(led, 16);
    break;
  }
};

void led_init_ports(void)
{
  // Set caps lock LED pin as output
  DDRB |= (1 << 2);
  // Default to off
  PORTB |= (1 << 2);
}

void led_set_kb(uint8_t usb_led)
{
  // Code for caps lock LED as reported by the OS
  // Set this per keymap, instead of globally
  led_set_user(usb_led);


    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        led[0].r = 255;
        ws2812_setleds(led, 16);
    } else {
        led[0].r = 0;
        ws2812_setleds(led, 16);
    }

    if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
        led[0].g = 255;
        ws2812_setleds(led, 16);
    } else {
        led[0].g = 0;
        ws2812_setleds(led, 16);
    }

    if (usb_led & (1<<USB_LED_NUM_LOCK)) {
        led[0].b = 255;
        ws2812_setleds(led, 16);
    } else {
        led[0].b = 0;
        ws2812_setleds(led, 16);
    }
}
